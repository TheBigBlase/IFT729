#include "server.hpp"
#include <iostream>

Server::Server(uint16_t p)
    : port{p}, data{}
{
	socket = zmq::socket_t{context, zmq::socket_type::push};
	socket.bind("ws://127.0.0.1:8888");
}

Server::~Server()
{
}

void Server::do_receive() {
	for(;;) {
		res = socket.recv(msg, zmq::recv_flags::none);
		if (res)
			std::cout << msg;
	}
}
