#pragma once

#include <iostream>
#include <boost/asio.hpp>

namespace test_timer {

void handler(const boost::system::error_code &ec) 
{ 
    std::cout << "timer1:: 1 s." << std::endl; 
} 

void start_timer()
{
    // io_context 类为 异步 I/O 对象 的用户提供核心 I/O 功能
    // 异步io对象有 boost::asio::deadline_timer，boost::asio::ip::tcp::socket 等
    boost::asio::io_context io_context; 

    // 创建 异步io对象 deadline_timer
    boost::asio::deadline_timer timer(io_context, boost::posix_time::seconds(1)); 

    // 对 异步io对象 启动一个异步等待方法，
    // 该io对象执行完成后，会调用 handler
    timer.async_wait(handler); 

    // 阻塞当前线程，并把控制权交给操作系统以接管异步处理
    io_context.run(); 
}

}