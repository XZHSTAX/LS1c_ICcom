#include <rtthread.h>
#include <dfs_posix.h>

void rtc_time_back(int fd);
extern rt_mutex_t dynamic_mutex;
extern rt_uint8_t Data_BeSent_Global[];

rt_uint8_t My_Enter[2] = {13,10};
rt_uint8_t My_Dot      = 46;


rt_uint8_t My_Pointer  = 0;
rt_uint8_t Tem1_Histroy[10][4] ={0};//暂存信息，每行为一分钟的数据
rt_uint8_t Fre1_Histroy[10][4] ={0};
rt_uint8_t Dis1_Histroy[10][4] ={0};

#define Write_Tem1      0x00
#define Write_Fre1      0x01
#define Write_Dis1      0x02

#define Write_Tem2      0x03
#define Write_Fre2      0x04
#define Write_Dis2      0x05

static void History_Send_Prepare()
{

    rt_uint8_t i = 0;
    if(My_Pointer >=10)
    {
        My_Pointer = 0;
    }
    for(i=0;i<4;i++)
    {
        Tem1_Histroy[My_Pointer][i] = Data_BeSent_Global[i];
        Fre1_Histroy[My_Pointer][i] = Data_BeSent_Global[i+4];
        Dis1_Histroy[My_Pointer][i] = Data_BeSent_Global[i+8];
    }
    My_Pointer++;
    
}

/**
 * @brief 写入数据处理
 *         写入时，依次写入整数，小数点，小数，换行
 * @param fd 文件指针
 * @param num 写入序号
 * 
*/
static void SD_write_channel(int fd,rt_uint8_t num)
{
    rtc_time_back(fd);
    write(fd, Data_BeSent_Global+num*4,2);    //写入整数位
    write(fd, &My_Dot,1);                     //小数点
    write(fd, Data_BeSent_Global+num*4+2,2);  //写入小数位
    write(fd, My_Enter,2);                    //换行
    close(fd);//关闭文件，释放空间
}

/**
 * @brief 向SD卡写入数据
 *       SD_write_process(Write_Tem1)向tem1文件写入数据
 * @param num 写入序号
 *
 * 
*/
static void SD_write_process(rt_uint8_t num)
{
    int fd;
    switch (num)
    {
        case Write_Tem1:fd = open("/tem1.csv",O_WRONLY | O_APPEND);break;
        case Write_Fre1:fd = open("/fre1.csv",O_WRONLY | O_APPEND);break;
        case Write_Dis1:fd = open("/dis1.csv",O_WRONLY | O_APPEND);break;
        case Write_Tem2:fd = open("/tem2.csv",O_WRONLY | O_APPEND);break;
        case Write_Fre2:fd = open("/fre2.csv",O_WRONLY | O_APPEND);break;
        case Write_Dis2:fd = open("/dis2.csv",O_WRONLY | O_APPEND);break;
    
    default:
        rt_kprintf("Error fd num.\n");
        break;
    }
    
    if(fd>=0)
    {
        SD_write_channel(fd,num);
        rt_kprintf("Write done.\n");
    }
    else
    {
      rt_kprintf("fail to found this txt.");
    }
}

/**
 * 向SD卡写入数据
*/
static void SD_write_entry(void)
{

    while(1)
        {
            rt_thread_mdelay(60000);
            rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
            SD_write_process(Write_Tem1);
            SD_write_process(Write_Fre1);
            SD_write_process(Write_Dis1);
            SD_write_process(Write_Tem2);
            SD_write_process(Write_Fre2);
            SD_write_process(Write_Dis2);

            //为查询准备的内容
            History_Send_Prepare();
            rt_mutex_release(dynamic_mutex);
        }
}

int SD_Write_launcher(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 SD_Write 线程 */
    rt_thread_t Thread_HMI_Send = rt_thread_create("SD_Write", (void (*)(void *parameter))SD_write_entry, RT_NULL, 2048, 27, 10);
    /* 创建成功则启动线程 */
    if (Thread_HMI_Send != RT_NULL)
    {
        rt_thread_startup(Thread_HMI_Send);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

void History_Process_Write(rt_uint8_t *Tem1_Histroy_Buff,rt_uint8_t *Fre1_Histroy_Buff,rt_uint8_t *Dis1_Histroy_Buff)
{
    rt_uint8_t i,j =0;
    rt_uint8_t My_Pointer_Buff = My_Pointer;
    for(j=0;j<10;j++)
    {
        for(i=0;i<4;i++)
        {
            if(My_Pointer_Buff-1-j <0)
            {
                My_Pointer_Buff = 10+j;
            }
            Tem1_Histroy_Buff[i+j*4] = Tem1_Histroy[My_Pointer_Buff-1-j][i];
            Fre1_Histroy_Buff[i+j*4] = Fre1_Histroy[My_Pointer_Buff-1-j][i];
            Dis1_Histroy_Buff[i+j*4] = Dis1_Histroy[My_Pointer_Buff-1-j][i];
        }
    }
}

MSH_CMD_EXPORT(SD_write_entry, Temp_SD_Write_Test);