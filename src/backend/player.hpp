#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>

#include "value_types.hpp"
#include <string>
#include <vector>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace http = beast::http;

using tcp = boost::asio::ip::tcp;
class Game;

class Player : public std::enable_shared_from_this<Player> {
  public:
	typedef boost::shared_ptr<Player> sptr;
	Player(value_t, tcp::socket &&);
	~Player();
	std::string name;
	bool is_in_game;
	void send_message(std::string);
	void send_pixel(pixel_t, pixel_t);
	void send_room(std::string);

	void run();

  private:
	value_t id;
	websocket::stream<tcp::socket> ws;
	beast::flat_buffer buffer;
	std::shared_ptr<Game> game;

	std::vector<std::string> sanitize_input(std::string);
	void handle_input(std::vector<std::string>);

	void on_run();
	void on_accept(beast::error_code);
	void do_accept();
	void on_read(beast::error_code, std::size_t);
	void do_read();
	void on_write(beast::error_code, std::size_t);
	void do_write(std::string);
	inline static std::string delimiter = ":";
	inline static value_t max_elts = 3;
};

#endif
