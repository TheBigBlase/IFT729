#include <boost/asio/dispatch.hpp>
#include <boost/beast/core.hpp>

#include "game.hpp"
#include "messages.hpp"
#include "player.hpp"
#include <iostream>

// a player is an entity that handles everything a player do. 
// Therefore, it can communicate via a tcp socket 
// TODO move the socket to a whole new class, for readability.
Player::Player(value_t id, tcp::socket &&socket)
	: id{id}, ws{std::move(socket)}, name{std::format("Player {}", id)},
	  is_in_game{false} {
	// Set a decorator to change the Server of the handshake
	ws.set_option(
		websocket::stream_base::decorator([](websocket::response_type &res) {
			res.set(http::field::server,
					std::string(BOOST_BEAST_VERSION_STRING) +
						" websocket-server-sync");
		}));

	// TODO async instead
	std::cout << "[PLAYER] player #" << id << " has connected" << std::endl;
	indexer = &GameIndexer::get();
}

Player::~Player() { std::cout << "[DTOR]" << std::endl; }

// TODO remove cout when release
std::vector<std::string> Player::sanitize_input(std::string input) {
	size_t pos = input.find(delimiter);
	std::string token;

	std::vector<std::string> res{};
	res.reserve(max_elts); // 3 elts max

	std::cout << "[SANITIZE] ";
	// split string
	// "MSG:un tres beau msg"
	// [0] : MSG
	// [1] : un tres beau msg
	// NOTE last chunk has to finish with \0. clearing buffer doesnt clean it.
	do {
		token = input.substr(0, pos);
		res.push_back(token);
		input.erase(0, pos + delimiter.length());

		std::cout << token << " ";
	} while ((pos = input.find(delimiter)) != std::string::npos);
	std::cout << std::endl;

	return res;
}

// handle every case that a client can send
void Player::handle_input(std::vector<std::string> in) {
	// TODO
	switch (string_to_int(in[0].data())) {
	case PX:
		game->broadcastPixel(std::atoi(in[1].c_str()),
							 std::atoi(in[2].c_str()), *this);
		break;
	case MSSG:
		// client has sent a message / submitted a guess
		break;
	case JOIN:
		std::cout << "[JOIN] player " << id << " joined game" << std::endl;
		if (game == nullptr) {
			game = indexer->search_game(std::atoi(in[1].c_str())).lock();
		}
		game->addPlayer(this);
		is_in_game = true;
		break;
	// TODO rename to game
	case NEWROOM:
		if (!is_in_game) {
			game = make_shared<Game>(this, num_games++);
			indexer->add_game(game);
			is_in_game = true;
			send_room();
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
	case RECONN:
		// send connection id
		id = static_cast<value_t>(std::atoi(in[1].c_str()));
		break;
	case ROOMLIST:
		// send connection id
		send_room();
		break;
	default:
		std::cout << "Could not interpret cmd " << in[0] << std::endl;
		break;
	}

	// restart a read option
	do_read();
}

// send last 10 room created to everyone
// TODO search by id
void Player::send_room() {
	auto rooms = indexer->get_last_10();
	auto rooms_str = std::string{};

	for(auto room : *rooms) {
		rooms_str.append(std::format(":{}", room->getId()));
	}

	// if empty, wtf, send error
	if (!rooms->empty()) {
		// first colon already included
		std::string res = std::format("ROOM{}", rooms_str);
		do_write(res);
	}

	else
		do_write("ERR");
}

void Player::send_pixel(pixel_t x, pixel_t y) {
	do_write(std::format("PX:{}:{}", x, y));
}

void Player::send_message(std::string msg) {
	do_write(std::format("MSSG:{}", msg));
}

// SERVER STUFF

void Player::on_write(beast::error_code ec, std::size_t bytes_transferred) {
	boost::ignore_unused(bytes_transferred);

	if (ec) {
		std::cerr << "write: " << ec.message() << "\n";
	}
}

void Player::on_read(beast::error_code ec, std::size_t bytes_transferred) {
	boost::ignore_unused(bytes_transferred);
	// This indicates that the session was closed
	if (ec == websocket::error::closed)
		return;

	if (ec) {
		std::cerr << "read: " << ec.message() << "\n";
		return;
	}

	if (ws.got_text()) {
		auto res =
			sanitize_input(static_cast<const char *>(buffer.cdata().data()));
		handle_input(res);
	}
}

void Player::run() {
	std::cout << "[RUN]" << std::endl;
	boost::asio::dispatch(
		ws.get_executor(),
		beast::bind_front_handler(&Player::on_run, shared_from_this()));
}

void Player::on_run() {
	std::cout << "[ONRUN]" << std::endl;
	try {
		ws.async_accept(
			beast::bind_front_handler(&Player::on_accept, shared_from_this()));

		// This buffer will hold the incoming message
	} // TODO remove excepts
	catch (beast::system_error const &se) {
		// This indicates that the session was closed
		if (se.code() != websocket::error::closed)
			std::cerr << "Error: " << se.code().location()
					  << se.code().message() << std::endl;
		delete this;
	} catch (std::exception const &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		delete this;
	}
}

void Player::on_accept(beast::error_code) {
	std::cout << "[ACCEPT] new socket accepted" << std::endl;
	do_write(std::format("CONN:{}", id)); // send id
	do_read();
}

void Player::do_read() {
	ws.async_read(buffer, beast::bind_front_handler(&Player::on_read,
													shared_from_this()));
	// clear the buffer
	buffer.clear();
}

void Player::do_write(const std::string msg) {
	ws.async_write(
		boost::asio::buffer(msg),
		beast::bind_front_handler(&Player::on_write, shared_from_this()));

	// clear the buffer
	buffer.clear();
}
