 #include <boost/asio.hpp> 
 #include <boost/array.hpp> 
 #include <iostream> 
 #include <string> 
 
namespace test_socket1 {

// 
boost::asio::io_service io_service; 
// 域名解析io对象
boost::asio::ip::tcp::resolver resolver(io_service); 
// socket io对象
boost::asio::ip::tcp::socket sock(io_service); 
boost::array<char, 4096> buffer; 


void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
    if (!ec) 
    { 
        std::cout << std::string(buffer.data(), bytes_transferred) << std::endl; 
        // 无法保证仅在一次异步操作中就可以接收到整个网页,所以需要多次读取
        // 直到数据传输完毕，连接断开，此时 read_handler() 内部将报告一个错误，从而停止读取
        sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
    } 
} 

void connect_handler(const boost::system::error_code &ec) 
{ 
    if (!ec) 
    { 
        // 连接成功后，向 socket 通过 HTTP 协议 发送GET请求 
        boost::asio::write(sock, boost::asio::buffer("GET / HTTP/1.1\r\nHost: www.baidu.com\r\n\r\n")); 
        sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
    } 
} 

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) 
{ 
    if (!ec) 
    {
        // 域名解析成功后，调用 connect_handler
        sock.async_connect(*it, connect_handler); 
    } 
} 

void run() 
{
    // 创建域名解析io对象
    boost::asio::ip::tcp::resolver::query query("www.baidu.com", "80");

    // 异步等待域名解析完成，后调用 resolve_handler
    resolver.async_resolve(query, resolve_handler); 

    // 运行 io_service
    io_service.run(); 
} 

}