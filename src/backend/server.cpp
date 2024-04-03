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

// Echoes back all received WebSocket messages
void
Server::do_session(tcp::socket socket, Player *p)
{
	try {
		// Construct the stream by moving in the socket
		websocket::stream<tcp::socket> ws { std::move(socket) };

		// Set a decorator to change the Server of the handshake
		ws.set_option(websocket::stream_base::decorator(
		    [](websocket::response_type &res) {
			    res.set(http::field::server,
				std::string(BOOST_BEAST_VERSION_STRING) +
				    " websocket-server-sync");
		    }));

		// Accept the websocket handshake
		ws.accept();

		for (;;) {
			// This buffer will hold the incoming message
			beast::flat_buffer buffer;

			// Read a message
			ws.read(buffer);

			// Echo the message back
			ws.text(ws.got_text());
			std::cout << static_cast<char *>(buffer.data().data())
				  << std::endl;
			ws.write(buffer.data());
		}
	}  // TODO remove excepts
	catch (beast::system_error const &se) {
		// This indicates that the session was closed
		if (se.code() != websocket::error::closed)
			std::cerr << "Error: " << se.code().message()
				  << std::endl;
	}
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
		Player *p = new Player(num_users);
		threads.push_back(std::thread(&Server::do_session, this, std::move(socket), std::move(p)));
	}
}
