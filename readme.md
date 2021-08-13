# MyoiHttp —— 一个简单的小型HTTP服务器

## 简介

本项目是一个使用现代C++编写的Http服务器，运行于Linux平台。本项目将随我本人对于Socket网络编程、Linux系统编程和C++的深入学习和理解，逐步完善。当前版本支持的功能以及特性如下：

* 支持GET/HEAD请求，目前仅支持处理静态资源;
* 基于`Epoll`实现，采用`Reactor`设计模式，使用固定大小的静态内存池；
* 仅支持IPv4协议，且暂不支持HTTP长连接;

## 更新日志

### 2021.08.14更新

* 在util下实现了通用的，固定大小的内存池，并用于server中；
* 将原本main函数中，初始化和执行reactor的内容封装到了HttpReactor中；

### 2021.06.25更新

* 重新设计了整体结构，将与`epoll`相关的操作独立出来，形成`event_`模块；
* 基于`event_`模块重新实现了HttpHandler(原HttpHandlerController)和HttpProcessor(原HttpHandler);

### 2021.06.19更新

* 放弃了`libaio`方案，改用`Epoll`和`Reactor`设计模式实现；

### 2021.06.15更新

* 删除了BufferedIo，改用无缓冲的I/O操作，并重新实现了HttpRequestParser以适应无缓冲的I/O；
* 使用`libaio`实现了异步IO，并采用了类似`Proactor`的设计模式重新实现了HttpServer；
* 删除了TcpListener和TcpConnection，统一使用TcpSocket代替，以便于Asio使用；

## 环境与部署

### 开发环境

* 操作系统：Arch Linux
* 编译器：GCC 10.2.0 (使用C++17)

### 构建

使用 CMake(3.19以上版本) 进行构建

### 运行

```
./MyoiHttp ip port base_dir
```

其中：

* `ip`：服务器运行的IP地址
* `port`：服务器监听的端口号
* `base_dir`：服务器文件的存储路径

## 项目结构

本项目的源程序包含`include`, `src`, `test`, 三个目录，其作用分别如下：

* `include`目录：各模块对外提供接口的头文件;
* `src`目录：各模块的内部实现，模块内部使用的头文件也会放在该目录内;
* `test`目录：各模块的单元测试（尚未完成）;

## 开发计划

目前在计划内的开发工作包括：

* 完善代码中的注释和文档，并提高异常处理的能力;
* 完善`test`目录，为每个模块编写完整的单元测试;
* 实现一套类似Java Servlet的接口，用于生成动态网页；

## 其它问题

本项目当前版本仅供学习交流使用，并不具备用于搭建生产环境的安全性和可靠性。

本项目基于[GNU GENERAL PUBLIC LICENSE Version 3](./LICENSE)开放源代码。