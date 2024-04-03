#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include "value_types.hpp"
#include <string>
#include <vector>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace http = beast::http;

using tcp = boost::asio::ip::tcp;

class Player : std::enable_shared_from_this<Player>{
    public:
	Player(value_t, tcp::socket);
	void send_message(std::string);
	std::string name;
	bool is_in_game;

    private:
	value_t id;
	websocket::stream<tcp::socket> ws;
	beast::flat_buffer buffer;


	void do_session();
	std::vector<std::string> sanitize_input(std::string);
	void handle_input(std::vector<std::string>);

	void send_pixel(pixel_t, pixel_t);
	inline static std::string delimiter = ":";
	inline static value_t max_elts = 3;
};

#endif
