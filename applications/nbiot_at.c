#include <rtthread.h>
#include <at.h>   /* AT 组件头文件 */
#define UART_NBIOT                     "uart8"

#define OB1_Tem_ID         1
#define OB2_Fre_ID         2
#define OB3_Dis_ID         3

static rt_device_t serial_Nbiot;
static rt_uint8_t  Head_AT_Word[] = {"AT+MIPLNOTIFY=0,0,"};

static rt_uint8_t  Obj1_AT_Word[] = {"3303,"};//T
static rt_uint8_t  Obj2_AT_Word[] = {"3318,"};//F
static rt_uint8_t  Obj3_AT_Word[] = {"3330,"};//D

static rt_uint8_t  Inst0_AT_Word[] = {"0,"};
static rt_uint8_t  Inst1_AT_Word[] = {"1,"};
static rt_uint8_t  Dot = '.';
static rt_uint8_t  Reso_AT_Word[] = {"5700,4,4,\""};
static rt_uint8_t  End_AT_Word[] = {"\",0,0\r\n"};
static rt_uint8_t  Please_let_me_alive[] = {"AT+MIPLUPDATE=0,350,1\r\n"};

extern rt_uint8_t Data_BeSent_Global[];
extern rt_mutex_t dynamic_mutex;
//rt_uint8_t My_test[24] = {0x31,0x32,0x33,0x34,0x30,0x31,0x38,0x30,0x30,0x31,0x35,0x33,0x31,0x32,0x33,0x34,0x30,0x31,0x38,0x30,0x30,0x31,0x35,0x33};

static void NB_Sent_message(rt_uint8_t ObID,rt_uint8_t InsID,rt_uint8_t *Cloud_message)
{
    rt_uint8_t *Ob;
    rt_uint8_t *Inst;
    switch (ObID)
    {
        case OB1_Tem_ID:
            Ob = Obj1_AT_Word; break;
        case OB2_Fre_ID:
            Ob = Obj2_AT_Word; break;
        case OB3_Dis_ID:
            Ob = Obj3_AT_Word; break;     
        default:
            rt_kprintf("Error ObID");
            break;
    }
    switch (InsID)
    {
        case 0:
            Inst = Inst0_AT_Word; break;
        case 1:
            Inst = Inst1_AT_Word; break;   
        default:
            rt_kprintf("Error InstID");
            break;
    }
    rt_device_write(serial_Nbiot,0,Head_AT_Word,(sizeof(Head_AT_Word)-1));//AT+MIPLNOTIFY=0,0,
    rt_device_write(serial_Nbiot,0,Ob,(sizeof(Obj1_AT_Word)-1));//3303,
    rt_device_write(serial_Nbiot,0,Inst,(sizeof(Inst0_AT_Word)-1));//0,
    rt_device_write(serial_Nbiot,0,Reso_AT_Word,(sizeof(Reso_AT_Word)-1));//5700,4,4,\

    rt_device_write(serial_Nbiot,0,Cloud_message,2);
    rt_device_write(serial_Nbiot,0,&Dot,1);
    rt_device_write(serial_Nbiot,0,Cloud_message+2,2);
    

    rt_device_write(serial_Nbiot,0,End_AT_Word,(sizeof(End_AT_Word)-1));//\",0,0
}

void NB_iot_Sent_entry()
{
    static rt_uint8_t DBG_Buff[24] = {0};
    rt_uint8_t i =0;
    while(1)
    {
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
        for(i=0;i<24;i++)
        {
            DBG_Buff[i] = Data_BeSent_Global[i];
        }
        rt_mutex_release(dynamic_mutex);
        
        rt_device_write(serial_Nbiot,0,Please_let_me_alive,(sizeof(Please_let_me_alive)-1));

        rt_thread_mdelay(60000);
        rt_thread_mdelay(60000);

        NB_Sent_message(OB1_Tem_ID,0,DBG_Buff);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);
        NB_Sent_message(OB2_Fre_ID,0,DBG_Buff+4);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);
        NB_Sent_message(OB3_Dis_ID,0,DBG_Buff+8);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);

        NB_Sent_message(OB1_Tem_ID,1,DBG_Buff+12);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);

        NB_Sent_message(OB2_Fre_ID,1,DBG_Buff+16);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);

        NB_Sent_message(OB3_Dis_ID,1,DBG_Buff+20);
        rt_thread_mdelay(2000);
        rt_thread_mdelay(2000);
        rt_kprintf("NBIOT UpData done!\r\n");
        
    }
}


int Nbiot_Send_launcher(void)
{
    rt_err_t ret = RT_EOK;
    serial_Nbiot = rt_device_find(UART_NBIOT);
    rt_device_open(serial_Nbiot, RT_DEVICE_FLAG_INT_RX); 
    /* 创建 NB_iot_Sent 线程 */
    rt_thread_t Thread_Nbiot_Send = rt_thread_create("NB_iot_Sent", (void (*)(void *parameter))NB_iot_Sent_entry, RT_NULL, 1024, 28, 10);
    /* 创建成功则启动线程 */
    if (Thread_Nbiot_Send != RT_NULL)
    {
        rt_thread_startup(Thread_Nbiot_Send);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}


MSH_CMD_EXPORT(Nbiot_Send_launcher, Test my NBIOT send);


