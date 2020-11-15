#include <rtthread.h>
#include <stdlib.h>  
#include <rthw.h>
#include "ls1c.h"
#include <drivers/pin.h>
#include "ls1c_public.h"
#include "ls1c_uart.h"
#include "ls1c_pin.h"  
#include <at_log.h>
#include "ls1c_gpio.h"
void init_uart1()  
{
    rt_uint8_t uart_num = LS1C_UART1;
    ls1c_uart_info_t uart_info = {0};	
    unsigned int rx_gpio ;
    unsigned int tx_gpio ;
    int dat;

        rx_gpio = 2;
        tx_gpio = 3;
        pin_set_remap(tx_gpio, PIN_REMAP_FOURTH);
        pin_set_remap(rx_gpio, PIN_REMAP_FOURTH);
        uart_info.UARTx = uart_num;
        uart_info.baudrate = 115200;
        uart_info.rx_enable = TRUE;  
        uart_init(&uart_info);
        rt_hw_interrupt_umask(LS1C_UART1_IRQ);		
}

void init_uart8()  
{
    rt_uint8_t uart_num = LS1C_UART8;
    ls1c_uart_info_t uart_info = {0};	
    unsigned int rx_gpio ;
    unsigned int tx_gpio ;
    int dat;

        rx_gpio = 55;
        tx_gpio = 54;
        pin_set_remap(tx_gpio, PIN_REMAP_FIFTH);
        pin_set_remap(rx_gpio, PIN_REMAP_FIFTH);
        uart_info.UARTx = uart_num;
        uart_info.baudrate = 115200;
        uart_info.rx_enable = TRUE;  
        uart_init(&uart_info);
        rt_hw_interrupt_umask(LS1C_UART8_IRQ);		
}

void init_uart7()  
{
    rt_uint8_t uart_num = LS1C_UART7;
    ls1c_uart_info_t uart_info = {0};	
    unsigned int rx_gpio ;
    unsigned int tx_gpio ;
    int dat;

        rx_gpio = 57;
        tx_gpio = 56;
        pin_set_remap(tx_gpio, PIN_REMAP_FOURTH);
        pin_set_remap(rx_gpio, PIN_REMAP_FOURTH);
        uart_info.UARTx = uart_num;
        uart_info.baudrate = 115200;
        uart_info.rx_enable = TRUE;  
        uart_init(&uart_info);
        rt_hw_interrupt_umask(LS1C_UART7_IRQ);		
}

void test_uart8_sent()
{
    unsigned int pin_enable = 53;
    
    gpio_init(pin_enable, gpio_mode_output);
    gpio_set(pin_enable, gpio_level_high);
    rt_thread_mdelay(1000);  
    rt_thread_mdelay(1000);  
    rt_thread_mdelay(1000);  
    rt_thread_mdelay(1000);  
    gpio_set(pin_enable, gpio_level_low);
    
    
}

 #include  <finsh.h> 
FINSH_FUNCTION_EXPORT(init_uart1 , test_uart 0-12 e.g.test_uart(0));
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(init_uart1, test_uart_msh 0);
MSH_CMD_EXPORT(init_uart8, init_uart_8);
MSH_CMD_EXPORT(test_uart8_sent, test_uart8_sent);