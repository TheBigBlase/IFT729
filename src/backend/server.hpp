#ifndef UTILS_HPP
#define UTILS_HPP
#include <zmq.hpp>
#include <zmq_addon.hpp>

#include <cstdint>

class Server {
    public:
	uint16_t port;

	Server(uint16_t p);
	~Server();

	void do_receive();
	void do_send();

    private:
	zmq::socket_t socket;
	zmq::context_t context;

	zmq::message_t msg;
	zmq::recv_result_t res;
	zmq::mutable_buffer data;
};

#endif
