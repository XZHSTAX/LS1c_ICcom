/*
 * Uart接收数据，写了两个线程，一个线程用于接收zigbee的数据，另一个接收屏幕的数据
 * 使用信号量机制，当接收到信号则在回调函数中释放信号量，唤醒线程
 * 
 * UART信息：
 * 名称         Tx(GPIO)       Rx(GPIO)      波特率     用途
 * UART1        P03(3)        P02(2)         115200    Zigbee
 * UART3        P01(1)        P00(0)         115200    HMI
 * UART8        P54(54)       P55(55)        115200    NBIOT
*/


#include <rtthread.h>
void init_uart1();  
void Temperature_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent);
void Frequency_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent);
void Distant_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent);
void Copy_dataBesent_To_Data_BeSent_Global(rt_uint8_t *dataBesent,rt_uint8_t *data_BeSent_Global,rt_int8_t num);
void HMI_Plot_Data_Send(rt_device_t serial_device,rt_uint8_t *Data_Buff);
void HMI_Plot_Data_Prcess(rt_uint8_t Now_UI_is,rt_uint8_t *Data_Buff,rt_uint8_t *Data_BeSent_Global);
void History_Process_Write(rt_uint8_t *Tem1_Histroy_Buff,rt_uint8_t *Fre1_Histroy_Buff,rt_uint8_t *Dis1_Histroy_Buff);
#define UART_ZIGBEE                     "uart1"
#define UART_HMI                        "uart3"
#define DATA_CMD_END                     0xFF       /*接收信息截止位*/
#define ONE_DATA_MAXLEN                  20         /* 不定长数据的最大长度 */
#define Zigbee1_Address                  0xC111
#define Zigbee2_Address                  0x3E49

#define Length_DBG                       24
/*用于接收消息的信号量*/
static struct rt_semaphore Zigbee_sem;
static struct rt_semaphore HMI_sem;

/*创建设备结构体指针*/
static rt_device_t serial_Zigbee;
static rt_device_t serial_HMI;

extern rt_mutex_t dynamic_mutex;

/*用于暂存发送给HMI的数据*/
rt_uint8_t Data_BeSent_Global[Length_DBG]={0};//TFD
/*当前UI界面标记*/
rt_uint8_t Now_UI_is = 0X31;
#define HOME                    0x31
#define Station1_Tem            0X02
#define Station1_Fre            0X03
#define Station1_Dis            0X04
#define Station1_His            0X08

#define Station2_Tem            0X05
#define Station2_Fre            0X06
#define Station2_Dis            0X07

/*zigbee模块对应串口 接收回调函数,释放zigbee的信号量*/
static rt_err_t uart_zigbee_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    if (size > 0)
    {
        rt_sem_release(&Zigbee_sem);
    }
    return RT_EOK;
}

/**
 * 接收Zigbee传回数据，对数据处理，并存入Data_BeSent_Global
 * 功能：   
 * 1.51传回的数据是没处理过的，ls处理这些数据为10进制
 * 2.ls把数据加工为HMI可以接收的类型。（按10进制拆分，每位都用ASCII码表示）
 * 注意：
 * 1.对于不同地址的数据，进入不同的if语句中处理
 * 2.修改宏Zigbee1_Address即可修改对应地址判断
*/
static void Zigbee_data_parsing_entry(void)
{
    rt_uint8_t j=0;
    rt_uint8_t ch;
    rt_uint8_t Port_flag;
    rt_uint8_t data_BeSent[4]={0};
    rt_uint8_t data[ONE_DATA_MAXLEN];
    static rt_uint8_t i = 0;

    while (1)
    {
        while (rt_device_read(serial_Zigbee, 0, &ch, 1) == 0)
        {
            rt_sem_take(&Zigbee_sem, RT_WAITING_FOREVER);
        }
        
        //rt_device_write(serial_Zigbee, 0, &ch, 1);//调试使用
        if(ch == DATA_CMD_END)
        {
            rt_uint8_t data_Buff[ONE_DATA_MAXLEN];
            i=0;
            Port_flag = data[3];

            for(j=0;j<ONE_DATA_MAXLEN;j++)
            {
                data_Buff[j] = data[j];
            }
            rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
            if( ((data_Buff[4]<<8)|data_Buff[5]) == Zigbee1_Address)
            {
                switch (Port_flag)
                {   
                case 0x95:
                    Temperature_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,1);
                    rt_kprintf("TP1 done\r\n");
                    break;
                case 0x96:
                    Frequency_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,2);
                    rt_kprintf("FP1 done\r\n");
                    break;
                case 0x97:
                    Distant_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,3);
                    rt_kprintf("DP1 done\r\n");
                    break;
                default: rt_kprintf("Error Port Received from Zigbee"); break;
                }
            }
            
            if( ((data_Buff[4]<<8)|data_Buff[5])  == Zigbee2_Address)
            {
                switch (Port_flag)
                {   
                case 0x95:
                    Temperature_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,4);
                    rt_kprintf("TP2 done\r\n");
                    break;
                case 0x96:
                    Frequency_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,5);
                    rt_kprintf("FP2 done\r\n");
                    break;
                case 0x97:
                    Distant_Process(data_Buff,data_BeSent);
                    Copy_dataBesent_To_Data_BeSent_Global(data_BeSent,Data_BeSent_Global,6);
                    rt_kprintf("DP2 done\r\n");
                    break;
                default: rt_kprintf("Error Port Received from Zigbee"); break;
                }
            }
            rt_mutex_release(dynamic_mutex);
            continue;
            
        }
        i = (i >= ONE_DATA_MAXLEN-1) ? ONE_DATA_MAXLEN-1 : i;//表达式1 对就执行2，不对就执行3
        data[i++] = ch;
    }
}

/*
 * zigbee模块对应串口 汇总函数 完成：
 * 1.寻找，打开设备
 * 2.初始化信号量
 * 3.启动线程
 * 4.优先级25
*/
int uart_Zigbee(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    /* 查找系统中的串口设备 */
    serial_Zigbee = rt_device_find(UART_ZIGBEE);
    if (!serial_Zigbee)
    {
        rt_kprintf("find %s failed!\n", UART_ZIGBEE);
        return RT_ERROR;
    }

    /* 初始化信号量 */
    rt_sem_init(&Zigbee_sem, "Zigbee_sem", 0, RT_IPC_FLAG_FIFO);        //信号量对象，名字，初始值，标志(先到先得)
    /* 以中断接收及轮询发送模式打开串口设备 init_uart1():补丁*/
    init_uart1();
    rt_device_open(serial_Zigbee, RT_DEVICE_FLAG_INT_RX);              //设备驱动结构体指针，打开方式
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial_Zigbee, uart_zigbee_rx_ind);             //设备驱动结构体指针，回调函数

    /* 创建 serial_Zigbee 线程 */
    rt_thread_t thread = rt_thread_create("serial_Zigbee", (void (*)(void *parameter))Zigbee_data_parsing_entry, RT_NULL, 2048, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}



static rt_err_t uart_HMI_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_uint8_t ch=0;
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    if (size > 0)
    {
        rt_sem_release(&HMI_sem);
    }
    return RT_EOK;
}

static rt_uint8_t uart_HMI_get_char(void)
{
    rt_uint8_t ch;

    while (rt_device_read(serial_HMI, 0, &ch, 1) == 0)
    {
        rt_sem_take(&HMI_sem, RT_WAITING_FOREVER);
    }
    return ch;
}

/**
 * HMI接收处理函数
 * 1.接收HMI发送回的数据，由此修改全局变量Now_UI_is，以确定ls发送何种数据
*/
static void HMI_data_parsing_entry(void)
{
    rt_uint8_t ch=0;
    while (1)
    {
        while (rt_device_read(serial_HMI, 0, &ch, 1) == 0)
        {
            rt_sem_take(&HMI_sem, RT_WAITING_FOREVER);
        }
        if(ch == 0xff || ch==0xfd ||ch == 0xfe || ch==0xfd)
        {
            //Now_UI_is = Now_UI_is;
        }
        else
        {
            Now_UI_is = ch;
            rt_kprintf("change to %d",Now_UI_is);
        }    
    }
}

/**
 * 向HMI发送数据线程
 * 1.通过全局变量Now_UI_is，来判断发送何种数据
 * 2.其中包含了对数据处理的函数，把Data_BeSent_Global中的数据修改为可被HMI使用的数据
*/
static void HMI_data_Sent_entry(void)
{
    rt_uint8_t i,j=0;
    rt_uint8_t Data_Buff[Length_DBG] = {0};
    rt_uint8_t Tem1_Histroy_Buff[40] = {0};
    rt_uint8_t Fre1_Histroy_Buff[40] = {0};
    rt_uint8_t Dis1_Histroy_Buff[40] = {0};
    rt_uint8_t DBG_Buff[Length_DBG]  = {0};
    float      Buff = 0;
    while(1)
    {
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
        HMI_Plot_Data_Prcess(Now_UI_is,Data_Buff,Data_BeSent_Global);
        for(i=0;i<24;i++)
        {
            DBG_Buff[i] = Data_BeSent_Global[i];
        }
        
        switch (Now_UI_is)
        {
        case HOME:
            rt_device_write(serial_HMI,0,DBG_Buff,Length_DBG);
            rt_thread_delay(200);
            break;
        case Station1_Tem:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff);
            //rt_thread_delay(20);
            break;
        case Station1_Fre:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff+1);
            rt_thread_delay(200);
            break;
        case Station1_Dis:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff+2);
            rt_thread_delay(200);
            break;

        case Station1_His:
            History_Process_Write(Tem1_Histroy_Buff,Fre1_Histroy_Buff,Dis1_Histroy_Buff);
            rt_device_write(serial_HMI,0,Tem1_Histroy_Buff,40);
            rt_device_write(serial_HMI,0,Dis1_Histroy_Buff,40);
            rt_device_write(serial_HMI,0,Fre1_Histroy_Buff,40);
            rt_thread_delay(200);
            break;
        
        case Station2_Tem:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff+3);
            rt_thread_delay(200);
            break;
        case Station2_Fre:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff+4);
            rt_thread_delay(200);
            break;
        case Station2_Dis:
            HMI_Plot_Data_Send(serial_HMI,Data_Buff+5);
            rt_thread_delay(200);
            break;
        default:
            rt_kprintf("Error UI num");
            Now_UI_is = HOME;
            break;
        }
        rt_mutex_release(dynamic_mutex);
        rt_thread_delay(200);
    }
}

/*
 * HMI 汇总函数 完成：
 * 1.寻找，打开设备
 * 2.初始化信号量
 * 3.启动线程(HMI_data_parsing_entry,HMI_data_Sent_entry)优先级：26，25
*/
int uart_HMI(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    /* 查找系统中的串口设备 */
    serial_HMI = rt_device_find(UART_HMI);
    if (!serial_HMI)
    {
        rt_kprintf("find %s failed!\n", UART_HMI);
        return RT_ERROR;
    }

    /* 初始化信号量 */
    rt_sem_init(&HMI_sem, "HMI_sem", 0, RT_IPC_FLAG_FIFO);        //信号量对象，名字，初始值，标志(先到先得)
    /* 以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial_HMI, RT_DEVICE_FLAG_INT_RX);              //设备驱动结构体指针，打开方式
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial_HMI, uart_HMI_rx_ind);             //设备驱动结构体指针，回调函数

    /* 创建 HMI_Send 线程 */
    rt_thread_t Thread_HMI_Send = rt_thread_create("HMI_Send", (void (*)(void *parameter))HMI_data_Sent_entry, RT_NULL, 1024, 26, 10);
    /* 创建成功则启动线程 */
    if (Thread_HMI_Send != RT_NULL)
    {
        rt_thread_startup(Thread_HMI_Send);
    }
    else
    {
        ret = RT_ERROR;
    }

    /* 创建 serial_HMI 线程 */
    rt_thread_t thread = rt_thread_create("serial_HMI", (void (*)(void *parameter))HMI_data_parsing_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

MSH_CMD_EXPORT(uart_Zigbee, uart_Zigbee);
MSH_CMD_EXPORT(uart_HMI, uart_HMI);