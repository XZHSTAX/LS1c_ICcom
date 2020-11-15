# The Persimmon Runtime for JavaScript

## 1、介绍

JS Persimmon 是 RT-Thread 开发的。

RT-Thread 提供的 JS Persimmon 组件具有以下优势：

### 1.1 目录结构

> 说明：参考下面表格，整理出 packages 的目录结构

| 名称 | 说明 |
| ---- | ---- |
| api | JS api 接口 |
| launcher | JS 入口 |
| startup  | 组件启动机制代码 |

### 1.2 许可证

**JS Persimmon** package 严禁一切个人、组织、团体以任何形式传播源代码。

### 1.3 依赖

- RT-Thread 3.0+
- [gui_engine](https://github.com/RT-Thread-packages/gui_engine.git)
- [Persimmon](https://git.rt-thread.com/packages/persimmon.git)
- [jerryscript](https://github.com/RT-Thread-packages/jerryscript.git)
- [ezXML](https://github.com/RT-Thread-packages/ezXML.git)

## 2、如何打开 JS Persimmon

**JS Persimmon** 可以使用 RT-Thread 的包管理器中选择使用它，具体路径如下：

```env
Privated Packages of RealThread --->
    [*] JS Persimmon: The Persimmon Runtime for JavaScript
          version (latest)  --->
    (32)  JS Persimmon thread stack size KB
    (500) JS Persimmon logo show time ms
    [*]   JS Persimmon enable default logo
    [*]   JS Persimmon automatic startup
    [ ]   JS Persimmon waiting ready sem to load app
    [ ]   JS Persimmon enable lcd api
    [ ]   JS Persimmon enable ota api
```

开发者可以根据需要进行配置：

- 任务栈的大小，默认为 32 KB
- 启动 logo 显示时间，默认为 500 ms
- 是否使用默认 logo
- 是否自动启动任务
- 是否使能等待加载 app.js 信号
- 是否使能 lcd 背光控制功能 JS 接口
- 是否使能 ota 功能 JS 接口

保存后等待 RT-Thread 的包管理器自动更新完成，或者使用 `pkgs --update` 命令手动更新包到 BSP 中。

## 3、使用 JS Persimmon

## 4、注意事项

## 5、联系方式 & 感谢
