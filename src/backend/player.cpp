#include "game.hpp"
#include "messages.hpp"
#include "player.hpp"
#include <format>
#include <iostream>
#include <thread>

Player::Player(value_t id, tcp::socket socket)
    : id { id }
	, ws { std::move(socket) }
    , name { std::format("Player {}", id) }
    , is_in_game { false }
{
	// Set a decorator to change the Server of the handshake
	ws.set_option(
		websocket::stream_base::decorator([](websocket::response_type &res) {
			res.set(http::field::server,
			std::string(BOOST_BEAST_VERSION_STRING) +
				" websocket-server-sync");
		}));

	// TODO async instead
	// std::thread(&Player::do_session, this);
}

std::vector<std::string>
Player::sanitize_input(std::string input)
{
	size_t pos = 0;
	std::string token;

	std::vector<std::string> res {};
	res.reserve(max_elts); // 3 elts max

	// split string
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		res.push_back(token);
		input.erase(0, pos + delimiter.length());
	}

	return res;
}

void
Player::handle_input(std::vector<std::string> in)
{
	// TODO
	switch (string_to_int(in[0].data())) {
	case PX:
		// client has drawn a new px
		break;
	case MSG:
		// client has sent a message / submitted a guess
		break;
	case JOIN:
		// client has joined a room
		break;
	case NEWROOM:
		//if (!is_in_game) {
		//	new Game(this);
		//	is_in_game = true;
		//}
		break;
	case LEAVE:
		// client has left the room
		break;
	case WIN:
		// client has drawn a new px
		// TODO should this be here ?
		break;
	case LOOSE:
		// client has drawn a new px
		// TODO should this be here ?
		break;
	default:
		// client has drawn a new px
		std::cout << "Could not interpret cmd " << in[0] << std::endl;
		break;
	}
}

void
Player::send_pixel(pixel_t x, pixel_t y)
{
	ws.text(true);
	//ws.async_write(boost::asio::buffer(std::format("PX:{}:{}", x, y)), 
			// TODO
			//[](){});
}

void
Player::send_message(std::string msg)
{
	ws.text(true);

	//ws.async_write(boost::asio::buffer("MSG:" + msg),
			//TODO
			//[](){});
}

void
Player::do_session()
{
	try {
		// Construct the stream by moving in the socket
		// Accept the websocket handshake
		// TODO async handshakes + write + read
		ws.accept();

		for (;;) {
			// This buffer will hold the incoming message

			// Read a message
			// TODO
			//ws.async_read(buffer, 
			//		beast::bind_front_handler([](std::string){}, shared_from_this()));

			// Echo the message back
			auto res = sanitize_input(
			    static_cast<char *>(buffer.data().data()));
			
			handle_input(res);
		}
	} // TODO remove excepts
	catch (beast::system_error const &se) {
		// This indicates that the session was closed
		if (se.code() != websocket::error::closed)
			std::cerr << "Error: " << se.code().message()
				  << std::endl;
	}
	catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }	
}
