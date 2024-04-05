#include <boost/asio/dispatch.hpp>
#include <boost/beast/core.hpp>

#include "game.hpp"
#include "messages.hpp"
#include "player.hpp"
#include <iostream>

Player::Player(value_t id, tcp::socket &&socket)
    : id { id }
    , ws { std::move(socket) }
    , name { std::format("Player {}", id) }
    , is_in_game { false }
{
	// Set a decorator to change the Server of the handshake
	ws.set_option(websocket::stream_base::decorator(
	    [](websocket::response_type &res) {
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
	size_t pos = input.find(delimiter);
	std::string token;

	std::vector<std::string> res {};
	res.reserve(max_elts); // 3 elts max

	std::cout << "[SANITIZE] ";
	// split string
	do {
		token = input.substr(0, pos);
		res.push_back(token);
		input.erase(0, pos + delimiter.length());

		std::cout << token << " ";
	} while ((pos = input.find(delimiter)) != std::string::npos);

	std::cout << endl;

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
	case MSSG:
		// client has sent a message / submitted a guess
		break;
	case JOIN:
		// client has joined a room
		break;
	case NEWROOM:
		if (!is_in_game) {
			new Game(this);
			is_in_game = true;
		}
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
	// ws.text(ws.got_text());
	// ws.async_write(boost::asio::buffer(std::format("PX:{}:{}", x, y)),
	//     beast::bind_front_handler(&Player::on_write,
	//     shared_from_this()));
}

void
Player::send_message(std::string msg)
{
	ws.text(ws.got_text());
	ws.async_write(boost::asio::buffer(std::format("MSSG:{}", msg)),
	    beast::bind_front_handler(&Player::on_write, shared_from_this()));
}

void
Player::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec) {
		std::cerr << "write: " << ec.message() << "\n";
	}

	// Clear the buffer
	buffer.consume(buffer.size());
}

void
Player::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);
	// This indicates that the session was closed
	if (ec == websocket::error::closed)
		return;

	if (ec) {
		std::cerr << "read: " << ec.message() << "\n";
		return;
	}

	if (ws.got_text()) {
		std::cout << "[READ] "
			  << static_cast<const char *>(buffer.cdata().data())
			  << std::endl;
		auto res = sanitize_input(
		    static_cast<const char *>(buffer.cdata().data()));
		handle_input(res);
	}

	// ws.text(ws.got_text());
	// ws.async_write(buffer.data(),
	//     beast::bind_front_handler(&Player::on_write,
	//     shared_from_this()));
}

void
Player::run()
{
	boost::asio::dispatch(ws.get_executor(),
	    beast::bind_front_handler(&Player::on_run, shared_from_this()));
}

void
Player::on_run()
{
	try {
		ws.async_accept(beast::bind_front_handler(&Player::on_accept,
		    shared_from_this()));

		// This buffer will hold the incoming message
	} // TODO remove excepts
	catch (beast::system_error const &se) {
		// This indicates that the session was closed
		if (se.code() != websocket::error::closed)
			std::cerr << "Error: " << se.code().location()
				  << se.code().message() << std::endl;
	} catch (std::exception const &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void
Player::on_accept(beast::error_code)
{
	std::cout << "[ACCEPT] new socket accepted" << std::endl;
	// Read a message
	ws.async_read(buffer,
	    beast::bind_front_handler(&Player::on_read, shared_from_this()));
}
