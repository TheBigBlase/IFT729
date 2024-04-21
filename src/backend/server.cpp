#include "server.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

Server::Server(ip::address add, uint16_t p)
	: port{p}, address{add}, context{}, acceptor{context, {address, port}} {
	std::cout << "Server listening to " << address << ":" << port << std::endl;
}

Server::~Server() {}

void Server::run_forever() {
	// This will receive the new connection
	tcp::socket * socket = new tcp::socket{context};

	acceptor.async_accept(
		*socket, boost::bind(&Server::on_accept, this, socket,
							boost::placeholders::_1));

	// Launch the session, transferring ownership of the socket
	context.run();
}

void Server::on_accept(tcp::socket *socket, const boost::system::error_code &error) {
	if (!error) {
		auto p = std::make_shared<Player>(num_users, std::move(*socket));
		p->run();

		num_users++;
	}
	run_forever();
}
