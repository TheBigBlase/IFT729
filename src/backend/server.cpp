#include "server.hpp"
#include <boost/bind/bind.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>

// TODO all is in main atm
Server::Server(ip::address add, uint16_t p)
	: port{p}, address{add}, context{}, acceptor{context, {address, port}} {
	std::cout << "Server listening to " << address << ":" << port << std::endl;
}

// TODO
Server::~Server() {}

void Server::run_forever() {
	for (;;) {
		// This will receive the new connection
		tcp::socket * socket = new tcp::socket{context};

		// Block until we get a connection

		acceptor.async_accept(
			*socket, boost::bind(&Server::on_accept, this, socket,
								boost::asio::placeholders::error ));

		// TODO
		// Launch the session, transferring ownership of the socket
		// auto p = new Player() ; p.run();

		context.poll();
	}
}

void Server::on_accept(tcp::socket *socket, const boost::system::error_code &error) {
	if (!error) {
		auto p = std::make_shared<Player>(num_users, std::move(*socket));
		p->run();

		num_users++;
		//players.push_back(p);
		//p->run();
	}
}
