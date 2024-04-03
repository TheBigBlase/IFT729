#include "server.hpp"
#include <iostream>

// TODO all is in main atm
Server::Server(ip::address add, uint16_t p)
    : port { p }
    , address { add }
    , context {}
    , acceptor { context, { address, port } }
{
	std::cout << "Server listening to " << address << ":" << port;
}

// TODO
Server::~Server()
{
}

void
Server::run_forever()
{
	for (;;) {
		// This will receive the new connection
		tcp::socket socket { context };

		// Block until we get a connection
		acceptor.accept(socket);

		// Launch the session, transferring ownership of the socket
		// TODO player?
		Player *p = new Player(num_users, std::move(socket));
		players.push_back(p);
	}
}
