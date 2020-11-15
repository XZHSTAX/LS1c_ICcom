#include <rtthread.h>


/**
 * @brief 把要发送的数据按HMI曲线绘制格式发送
 *        这里只负责发送一位数据。HMI的读取有些奇怪。发送想绘制x位数据，必须发送x+3位数，且读x位
 * @param serial_device      指定设备
 * @param Data_Buff          原始数据
*/
void HMI_Plot_Data_Send(rt_device_t serial_device,rt_uint8_t *Data_Buff)
{
    char       instru1[]    = "addt 2,0,4";
    rt_uint8_t instru2[3]   = {0xff,0xff,0xff};
    rt_device_write(serial_device,0,instru1,(sizeof(instru1)-1));
    rt_device_write(serial_device,0,instru2,sizeof(instru2));
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,Data_Buff,1);
//    rt_device_write(serial_device,0,Data_Buff,1);
    rt_device_write(serial_device,0,instru2,sizeof(instru2));
}

/**
 * @brief 把全局数据中的数据变为显示数据
 *        全局数组中的数据是变为一位一位的ASIIC码的，这里先转为普通数据，在对应0~255的坐标
 *        Tem:0~25.5-->0~255; Fre;Dis:0~102cm-->0~255
 * @param Now_UI_is              当前UI界面号
 * @param Data_Buff              转换后的数据
 * @param Data_BeSent_Global     全局数组
*/
void HMI_Plot_Data_Prcess(rt_uint8_t Now_UI_is,rt_uint8_t *Data_Buff,rt_uint8_t *Data_BeSent_Global)
{
    rt_uint8_t i =0;
    float      Buff = 0;
    if(Now_UI_is != 0x31)
        {
            for(i=0;i<24;i++)
            {
                Data_Buff[i] = Data_BeSent_Global[i]-0x30;
            }
            for(i=0;i<24/4;i++)
            {
                Buff = Data_Buff[i*4]*10+Data_Buff[i*4+1]+Data_Buff[i*4+2]*0.1+Data_Buff[i*4+3]*0.01;
                switch (i%3)
                {
                case 0x00:Data_Buff[i]=Buff*10;break;  //Tem
                case 0x01:Data_Buff[i]=17;break;       //Fre
                case 0x02:Data_Buff[i]=Buff*250;break; //Dis
                default:rt_kprintf("HMI_UI_Data process wrong");break;        
                }
            }   
        }
}