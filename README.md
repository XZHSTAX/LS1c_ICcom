龙芯1C板级支持包


---

## 1. 简介

龙芯1C是基于GS232处理器核的高性价比单芯片系统，可应用于工业控制及物联网等领域。龙芯1C包含浮点处理单元，支持多种类型的内存，支持高容量的MLC NAND Flash。龙芯1C为开发者提供了丰富的外设接口及片上模块，包括Camera控制器、USB OTG及USB HOST接口、AC97/I2S控制器、LCD控制器、SPI接口、UART接口等，提供足够的计算能力和多应用的连接能力。

此BSP基于龙芯俱乐部推出的智龙开发板，包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| 1C300A/1C300B |
|CPU| GS232 |
|主频| 300MHz |
|片外SDRAM| 32MB |
|片外Flash| 128MB NandFlash、512K NorFlash |

## 2. 编译说明

Windows平台推荐使用[env工具][1]。龙芯1C的LS232处理器核是一款MIPS32兼容处理器，由于env工具中并未默认携带MIPS的工具链，需要下载如下工具链：

* [mips-2015.05-19-mips-sde-elf.exe][2]

安装好工具链后，假设工具链安装在`D:\mgc\embedded\codebench`目录下。使用env工具，打开console后，进入到命令行环境中，需要手动设置工具链的环境变量`RTT_EXEC_PATH`：

    set RTT_EXEC_PATH=D:\mgc\embedded\codebench\bin
	
编译前，先运行以下命令更新package list 和 下载必要的包（使用git联网下载），否则编译不通过 

    pkgs --upgrade
    pkgs --update
	
使用env工具，可以在console下进入到`bsp/ls1cdev`目录中，运行以下命令：

    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。

## 3. 烧写及执行

连接好串口，PC上使用终端软件以115200-N-8-1的配置方式连接到设备上。设备使用的串口引脚是：`[GPIO36/GPIO37]`

目前在智龙上推荐使用PMON通过tftp的方式下载到设备内存中运行。

智龙上电按下非enter键，进入PMON命令行

```
PMON> ifaddr syn0 192.168.1.100
PMON> load tftp://192.168.1.5/rtthread.elf
PMON> g
```

### 3.1 运行结果

如果编译 & 烧写无误，会在串口上看到RT-Thread的启动logo信息：

```

 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 10 2018
 2006 - 2018 Copyright by rt-thread team
eth_inited!
lwIP-1.4.1 initialized!
msh />Link is up in FULL DUPLEX mode
Link is with 100M Speed

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | 仅注册UART2，其他UART引脚未固定 |
| IIC | 支持 |  |
| SPI | 支持 |  |
| GPIO | 支持 |  |
| ETH | 支持 | RMII |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| 调试串口 | GPIO36/GPIO37 |

## 5. 联系人信息

维护人：

- [zhuangwei123](https://github.com/zhuangwei123)

## 6. 参考

* 1C芯片[用户手册][3]
* 1C芯片[数据手册][4]

  [1]: https://www.rt-thread.org/page/download.html
  [2]: https://sourcery.mentor.com/GNUToolchain/package13851/public/mips-sde-elf/mips-2015.05-19-mips-sde-elf.exe
  [3]: http://www.loongson.cn/uploadfile/cpu/1C/Loongson_1C300_user.pdf
  [4]: http://www.loongson.cn/uploadfile/cpu/1C/Loongson_1C300_data.pdf


*******************

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

