#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <thread>
#include <cstdint>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include "player.hpp"

namespace beast = boost::beast;		// from <boost/beast.hpp>
namespace http = beast::http;		// from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;		// from <boost/asio.hpp>
namespace ip = boost::asio::ip;		// from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;


// TODO all is in main atm
class Server {
	using value_t = int;
    public:
	Server(ip::address add, uint16_t p);
	~Server();

	void run_forever();

    private:
	inline static value_t num_users = 0;
	uint16_t port;
	ip::address address;
	net::io_context context;
	tcp::acceptor acceptor;
	std::vector<Player*> players;

	void do_session(tcp::socket, Player *p);
};
#endif
