#ifndef UTILS_HPP
#define UTILS_HPP
//#include <zmq.hpp>
//#include <zmq_addon.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace ws = boost::beast:: websocket;

#include <cstdint>

class Server {
    public:
	uint16_t port;

	Server(uint16_t p);
	~Server();

	void do_receive();
	void do_send();

	private:
	//zmq::socket_t socket;
	//zmq::context_t context;
	net::io_context context{1};

	boost::asio::ip::address_v4 const addr = net::ip::make_address_v4("0.0.0.0");
	boost::asio::ip::tcp::acceptor acceptor{context, {addr, port}};
	
	ws::stream<beast::tcp_stream> ws;
	boost::asio::ip::tcp::socket socket;


	//enum { max_len = 1024 };
	//char data[max_len];
	beast::flat_buffer data;
};

#endif
