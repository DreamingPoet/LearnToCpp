#pragma once
#include <iostream>
#include <boost/asio.hpp>

namespace test_timer2 {

void handler1(const boost::system::error_code &ec) 
{ 
    std::cout << "timer2:: 1 s." << std::endl; 
} 

void handler2(const boost::system::error_code &ec) 
{ 
std::cout << "timer2:: 2 s." << std::endl; 
} 


void start_timer()
{

    boost::asio::io_context io_context; 
    boost::asio::deadline_timer timer1(io_context, boost::posix_time::seconds(1)); 
    boost::asio::deadline_timer timer2(io_context, boost::posix_time::seconds(2)); 

    timer1.async_wait(handler1); 
    timer2.async_wait(handler2); 


    io_context.run(); 
}

}