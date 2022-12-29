#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <thread>

namespace test_timer4 {




void handler1(const boost::system::error_code &ec) 
{ 
    std::cout << "timer4::handler1 1 s." << std::endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
    std::cout << "timer4::handler2 2 s." << std::endl; 
} 

boost::asio::io_service io_service1; 
boost::asio::io_service io_service2; 

void run1() 
{ 
    io_service1.run(); 
} 

void run2() 
{ 
    io_service2.run(); 
}

void start_timer() 
{ 

    // 不绑定多个线程到单个 I/O 服务，而是创建多个 I/O 服务。 然后每一个 I/O 服务使用一个线程。
    boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(1)); 
    timer1.async_wait(handler1); 
    boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(2)); 
    timer2.async_wait(handler2); 
    std::thread thread1(run1); 
    std::thread thread2(run2); 
    thread1.join(); 
    thread2.join(); 
}


}