#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <thread>

namespace test_timer3 {

void handler1(const boost::system::error_code &ec) 
{ 
    std::cout << "timer3::handler1 2 s." << std::endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
    std::cout << "timer3::handler2 1 s." << std::endl; 
} 

boost::asio::io_service io_service; 

void run() 
{ 
    io_service.run(); 
} 

void start_timer() 
{ 
    boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(2)); 
    timer1.async_wait(handler1); 
    boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(1)); 
    timer2.async_wait(handler2); 

    // 两个线程 调度执行同一个 io_service
    // 所以 handler1() 和 handler2() 可以同时执行。
    // 如果第二个计时器触发时第一个仍在执行，则第二个句柄就会在第二个线程中执行。 
    // 如果第一个计时器的句柄已经终止，则 io_service 可以自由选择任一线程。
    std::thread thread1(run); 
    std::thread thread2(run); 

    thread1.join(); 
    thread2.join(); 
}


}