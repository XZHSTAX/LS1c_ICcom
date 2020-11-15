/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25          Bernard        first version
 * 2011-08-08          lgnq           modified for Loongson LS1B
 * 2015-07-06          chinesebear    modified for Loongson LS1C
 */

#include <rtthread.h>
#include "net/synopGMAC.h"
#include <lwip/api.h>


void rt_init_thread_entry(void *parameter)
{
    #ifdef XPT2046_USING_TOUCH
        /*触摸屏使用SPI总线SPI1 CS0  初始化*/
            rtgui_touch_hw_init("spi10");
    #endif
        rt_kprintf("Loongson系统初始化完成！\n");
    #if (defined RT_USING_RTGUI) && (defined RTGUI_USING_DEMO)
    #ifdef USING_DEMO
    extern int test_guidemo(void);
        test_guidemo();
    #endif
    #ifdef USING_UI_BUTTON
        ui_button();
    #endif
    #endif	
}

int rt_application_init(void)
{
    rt_thread_t tid;

    /* create initialization thread */
    tid = rt_thread_create("init",
                            rt_init_thread_entry, RT_NULL,
                            4096, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25          Bernard        first version
 * 2011-08-08          lgnq           modified for Loongson LS1B
 * 2015-07-06          chinesebear    modified for Loongson LS1C
 */
 
// #include <rtthread.h>
 
// // 测试用的线程
// #define THREAD_TEST_PRIORITY                    (25)
// #define THREAD_TEST_STACK_SIZE                  (4*1024)        // 4k
// #define THREAD_TEST_TIMESLICE                   (10)

// /*******************定义线程栈****************/
// struct rt_thread thread_test;
// ALIGN(8)
// /******************线程控制块*****************/
// rt_uint8_t thread_test_stack[THREAD_TEST_STACK_SIZE];
 
 
// // 测试用的线程的入口
// void thread_test_entry(void *parameter)
// {
//     rt_kprintf("\n\n[%s] hello...\n", __FUNCTION__);
 
//     while (1)
//     {
//         rt_kprintf("[%s] hello......\n", __FUNCTION__);
//         rt_thread_delay(2*1000);
//     }
// }
 
 
// void rt_init_thread_entry(void *parameter)
// {
// 	/* initialization RT-Thread Components */
// 	rt_components_init();
// }
 
// int rt_application_init(void)
// {
// 	rt_thread_t tid;
//     rt_err_t result;
 
// 	/* create initialization thread */
// 	tid = rt_thread_create("init",
// 							rt_init_thread_entry, RT_NULL,
// 							4096, RT_THREAD_PRIORITY_MAX/3, 20);
// 	if (tid != RT_NULL)
// 		rt_thread_startup(tid);
 
//     // 初始化测试用的线程
//     result = rt_thread_init(&thread_test, 
//                             "thread_test",
//                             thread_test_entry,
//                             RT_NULL,
//                             &thread_test_stack[0],
//                             sizeof(thread_test_stack),
//                             THREAD_TEST_PRIORITY,
//                             THREAD_TEST_TIMESLICE);
//     if (RT_EOK == result)
//     {
//         rt_thread_startup(&thread_test);
//     }
//     else
//     {
//         return -1;
//     }
 
// 	return 0;
// }
