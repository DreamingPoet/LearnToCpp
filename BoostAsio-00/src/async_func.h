#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread.hpp>

// using namespace boost::placeholders;

namespace async_func {

boost::asio::io_service service;

void func(int i) {
    std::cout << "func called, i= " << i << std::endl;
}
void worker_thread() {
    service.run();
}

void start() {

    for (int i = 0; i < 10; ++i)
        service.post(boost::bind(func, i));
        
    // boost::thread_group threads;
    // for (int i = 0; i < 3; ++i)
    //     threads.create_thread(worker_thread);
    // // wait for all threads to be created
    // boost::this_thread::sleep(boost::posix_time::millisec(500));
    // threads.join_all();

}

// post()这个方法能立即返回，并且请求一个io_service实例调用制定的函数操作(function handler)，之后会在某一个盗用io_service.run()的线程中执行。
// dispach()这个方法请求一个io_service实例调用函数操作，但是如果当前线程执行了io_service.run(),它就会直接调用handler。
// wrap()这个方法包装一个方法，当它被调用时它会调用io_service.dispach().





}