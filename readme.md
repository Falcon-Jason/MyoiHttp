# MyoiHttp —— 一个简单的小型HTTP服务器

## 简介

本项目是一个使用现代C++编写的Http服务器，运行于Linux平台。本项目将随我本人对于Socket网络编程、Linux系统编程和C++的深入学习和理解，逐步完善。当前版本支持的功能以及特性如下：

* 仅支持解析GET请求，处理静态资源（后续将支持GET/POST/HEAD三种基本请求，以及基于CGI的动态资源）;
* 对于每个请求，单独启动一个线程处理之（后续将优化这部分存在的性能问题）;
* 仅支持IPv4协议，且暂不支持HTTP长连接、日志系统以及与安全性相关的功能（后续可能实现）;

## 更新日志

### 2021.06.21更新

* 删除了BufferedIo，改用无缓冲的I/O操作，并重新实现了HttpRequestParser以适应无缓冲的I/O；
* 使用`libaio`实现了异步IO，并采用了类似`Proactor`的设计模式重新实现了HttpServer；
* 删除了TcpListener和TcpConnection，统一使用TcpSocket代替，以便于Asio使用；

## 环境与部署

### 开发环境

* 操作系统：Arch Linux
* 编译器：GCC 10.2.0

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

本项目的源程序包含`include`, `src`, `test`, `examples`四个目录，其作用分别如下：

* `include`目录：各模块对外提供接口的头文件;
* `src`目录：各模块的内部实现，模块内部使用的头文件也会放在该目录内;
* `test`目录：各模块的单元测试（尚未完成）;
* `examples`目录：基于部分模块实现的小型工具，与项目整体无关;

## 开发计划

目前在计划内的开发工作包括：

* 完善代码中的注释和文档;
* 完善`test`目录，为每个模块编写完整的单元测试;
* 实现对POST/HEAD请求的处理，以及对CGI程序的支持;
* 使用select/poll/epoll等技术，优化对请求的处理;

## 其它问题

本项目当前版本仅供学习交流使用，并不具备用于搭建生产环境的安全性和可靠性。

本项目基于[GNU GENERAL PUBLIC LICENSE Version 3](./LICENSE)开放源代码。