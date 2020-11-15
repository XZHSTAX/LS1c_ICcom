/*
 * 这里储存了数据处理的函数，接收到了对应的数据会调用这里的函数
 * 在这里编写要使用的函数
*/

#include <rtthread.h>
#define DATA_BUFF  10
/**
 * @brief 温度处理函数，把51传回的原始数据变为HMI可显示的数据,
 *        如传入温度为26.65，则把每位数据拆分，转换后的数组变为 [0x32 0x36 0x36 0x35]
 * @param data 传入的原始数据
 * @param data_BeSent 要发送的数据
 * 
*/
void Temperature_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent)
{
    rt_uint8_t   i,j=0;
    rt_uint8_t   Temp_Buff[DATA_BUFF];
    for(i=6;data[i]!=0xff;i++)
    {
        Temp_Buff[j]=data[i];
        j++;
    }
    data_BeSent[0] = 625*((Temp_Buff[0]<<8) | Temp_Buff[1])/ 100000;
    data_BeSent[1] = 625*((Temp_Buff[0]<<8) | Temp_Buff[1])%100000/10000;
    data_BeSent[2] = 625*((Temp_Buff[0]<<8) | Temp_Buff[1])%10000/1000;
    data_BeSent[3] = 625*((Temp_Buff[0]<<8) | Temp_Buff[1])%1000/100;
    for(i=0;i<4;i++)
    {
        data_BeSent[i] = data_BeSent[i]+0x30;
    }
}

void Frequency_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent)
{
    rt_uint8_t   i,j=0;
    rt_uint8_t   Fre_Buff[DATA_BUFF];
    for(i=6;data[i]!=0xff;i++)
    {
        Fre_Buff[j]=data[i];
        j++;
    }
    data_BeSent[0] = ((Fre_Buff[0]<<8) | Fre_Buff[1])*10/75/10;
    data_BeSent[1] = ((Fre_Buff[0]<<8) | Fre_Buff[1])*10/75%10;
    data_BeSent[2] = ((Fre_Buff[0]<<8) | Fre_Buff[1])*100/75%10;
    data_BeSent[3] = 0;
    for(i=0;i<4;i++)
    {
        data_BeSent[i] = data_BeSent[i]+0x30;
    }
}

//18.4265,55
void Distant_Process(rt_uint8_t *data,rt_uint8_t *data_BeSent)
{
    rt_uint8_t   i,j=0;
    rt_uint8_t  disBuff1=0;   //整数
    rt_uint8_t  disBuff2=0;   //小数disBuff1.disbuff2
    rt_uint32_t  disdata=0;
    rt_uint8_t Dis_Buff[DATA_BUFF];
    for(i=6;data[i]!=0xff;i++)
    {
        Dis_Buff[j]=data[i];
        j++;
    }
    disdata = ((Dis_Buff[0]<<24)|(Dis_Buff[1]<<16))|((Dis_Buff[2]<<8)|(Dis_Buff[3]));
    disdata = disdata*1085*17/1000000;
    disBuff1 = disdata/100;
    disBuff2 = disdata%100;
    data_BeSent[0] = 0;
    data_BeSent[1] = disBuff1;
    data_BeSent[2] = disBuff2/10;
    data_BeSent[3] = disBuff2%10;
    for(i=0;i<4;i++)
    {
        data_BeSent[i] = data_BeSent[i]+0x30;
    }
    //rt_kprintf("disdata is %d.%d\r\n",disBuff1,disBuff2);
}

/**
 * @brief 把处理好的缓存数据存入全局变量数组Data_BeSent_Global对应位置
 *        num=1,放入[0]~[3]; num=2,放入[4]~[7]...
 * @param dataBesent         缓存数据
 * @param data_BeSent_Global 全局数组
 * @param num                位置量
*/
void Copy_dataBesent_To_Data_BeSent_Global(rt_uint8_t *dataBesent,rt_uint8_t *data_BeSent_Global,rt_int8_t num)
{
    rt_uint8_t i =0;
    for(i=0;i<4;i++)
    {
        data_BeSent_Global[num*4+i-4] = dataBesent[i];
    }
}
