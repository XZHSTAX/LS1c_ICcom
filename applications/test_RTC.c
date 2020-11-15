#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
rt_uint8_t My_Dot2      = 46;
rt_uint8_t My_Comma    = 0x2c;

void rtc_time_back(int fd)
{
    rt_uint8_t i = 0;
    rt_err_t ret = RT_EOK;
    time_t tmpcal_ptr;
    rt_uint8_t year[4] = {0};
    rt_uint8_t month[2] = {0};
    rt_uint8_t date[2] = {0};
    rt_uint8_t hour[2] = {0};
    rt_uint8_t min[2] = {0};
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr  = localtime(&tmpcal_ptr);
    year[0]  = (1900+tmp_ptr->tm_year)/1000+0x30;
    year[1]  = (1900+tmp_ptr->tm_year)%1000/100+0x30;
    year[2]  = (1900+tmp_ptr->tm_year)%1000%100/10+0x30;
    year[3]  = (1900+tmp_ptr->tm_year)%1000%100%10+0x30;

    month[0] = (1+tmp_ptr->tm_mon)/10+0x30;
    month[1] = (1+tmp_ptr->tm_mon)%10+0x30;
    
    date[0]  = (tmp_ptr->tm_mday)/10+0x30;
    date[1]  = (tmp_ptr->tm_mday)%10+0x30;
    
    hour[0]  = (tmp_ptr->tm_hour)/10+0x30;     
    hour[1]  = (tmp_ptr->tm_hour)%10+0x30;     
    
    min[0]   = (tmp_ptr->tm_min)/10+0x30; 
    min[1]   = (tmp_ptr->tm_min)%10+0x30;
    write(fd, year,4); 
    write(fd, &My_Dot2,1);

    write(fd, month,2); 
    write(fd, &My_Dot2,1);

    write(fd, date,2); 
    write(fd, &My_Dot2,1);

    write(fd, hour,2); 
    write(fd, &My_Dot2,1);

    write(fd, min,2); 
    write(fd, &My_Comma,1);

}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(rtc_time_back, rtc sample);