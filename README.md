## 项目开发者记录
**First time update ls1c：**

终于步上正轨，这里完成了UART2的调试，UART3接收Zigbee数据，发送给HMI 但还只完成了温度部分，并且接收发送Zigbee数据用的是UART3；原本设想使用UART1完成Zigbee数据的接收，UART1完成和HMI的通讯。 下一步完成水位，流速部分的数据处理函数，UART1的注册， 再下一次完成读写SD卡记录数据

****
**Second Time:finish frequency and Distant：**

完成了水位流速部分数据处理，还没有使用HMI实验，已经焊接好一个实验板，可以更方便进行测试，目前好像距离算法有问题，所得距离不真实。
下一步完成对流速，温度的的测试；在下面是UART1的注册，SD卡的读写，NB-IOT的使用。

****
**Third Time:fix mistake in the code last time push**

十分奇怪，出于不明原因，rt_kprintf 和 rt_device_write有时无法同时使用，不知道哪里出了问题。而且更奇怪的是有时候同样的程序烧录后结果不一样，处理了好久，才算解决了原来的问题。
这次更改中删去了函数 `uart_sample_get_char` 在线程中不调用，而是直接使用。另外 `rt_sem_control` 这个函数十分诡异，也被删去了。现在向HMI传输数据终于完成，下面是UART1的注册，SD卡的读写，NB-IOT的使用。

****
**Fourth Time:use uart1 successfully**

使用图形化界面激活UART1后，竟然无法使用？进入`drv_uart.c`文件中发现，非常正常，配置应该正确，并且在msh中使用`list_device`也可看见设备已被激活，但串口1始终无法使用。之后在调用原例程包发现原本的例程程序`test_uart`使用后，串口1可以被使用，因此精简了例程为`Just_init_uart1`专为激活uart1，在`rt_device_open`前使用。并且修改和Zigbee通讯模块为uart1，和HMI通讯接口为uart3.

****
**Fifth Time:First Week Finish**

*2020.10.18*

这次工作把发送给HMI的部分单独挑出，作为线程使用。已完成测试主页数据显示（测试完成），完成发送绘制曲线函数（未测试）。

****
**Sixth Time:Defect in Sending Data**

*2020.10.9*

今天测试了一下温度曲线绘制，出现了一系列问题：当点击温度曲线绘制时，HMI向ls发送0x32，用串口调试助手可以看见，确实是0x32，但ls接收到了诸如0xff，0xfe的数据，导致ls数据发送一直停留在主界面。无奈，暂时在 `HMI_data_parsing_entry` 中加入判断，若为乱码则跳过。但从调试信息可以看出，虽然HMI只发送了一次数据，但ls却一直重复进入`HMI_data_parsing_entry`。发送0x31就不会有这种问题，虽然现在问题被暂时解决，但并不完美，下一步最好要想办法解决。这周应当完成高限报警，SD卡读写，历史数据查询。


****
**Seventh Time:Finish SD**

*2020.10.31*

完成SD卡写入，和10min钟内的历史数据回放。需要加速，设计外观，NBIOT。


****
**Eighth Time:Finish NBIOT**

*2020.11.14*

这太极限了，经过一番苦战，终于把NBIOT模块完成了。

****
**Ninth Time:Finish NBIOT**

*2020.11.16 2:30*

至此，所有工作已经完成了，最后我们极限冲刺，完成了任务。非常感谢我的队友们，真是一次奇妙的冒险。

