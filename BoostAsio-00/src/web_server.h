#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <string>

namespace web_server {


boost::asio::io_service io_service;
// 定义一个 host（ip + port）
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 8080);
// 定义一个 acceptor io 对象
boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
// 定义一个 sock io 对象
boost::asio::ip::tcp::socket sock(io_service);

// boost::asio::io_service::work work(io_service);

// 定义 web_server 在接收到请求时的返回数据
std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";


void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout << "send data to client! "<< bytes_transferred << " bytes_transferred" << std::endl; 
    }
    else 
    {
        std::cout << "send data to client failed ! " << std::endl; 
    }
    
}


void accept_handler(const boost::system::error_code &ec)
{
    if (!ec)
    {
        // 如果有客户端连接，则给客户端发送数据
        boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);
    }
}


void run_server()
{
    // 开始监听客户端的连接
    acceptor.listen();

    // 异步处理连接
    acceptor.async_accept(sock, accept_handler); 

    io_service.run();


}

    
}