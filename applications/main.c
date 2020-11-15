/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-10     zhuangwei    first version
 */

#include <rtthread.h>
// 测试用的线程

rt_mutex_t dynamic_mutex = RT_NULL;

int main(int argc, char** argv)
{   
   	rt_kprintf("Loongson is ready! Welcome DYL XZH PHS!\n");
    dynamic_mutex = rt_mutex_create("dmutex", RT_IPC_FLAG_FIFO);
    if (dynamic_mutex == RT_NULL)
    {
        rt_kprintf("create dynamic mutex failed.\n");
        return -1;
    }

    uart_HMI();
    uart_Zigbee();
    SD_Write_launcher();
    Nbiot_Send_launcher();
    return 0;
}
