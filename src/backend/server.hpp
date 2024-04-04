#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>

#include "player.hpp"
#include <cstdint>
#include <vector>

namespace net = boost::asio;
namespace ip = boost::asio::ip;
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
	std::vector<Player::sptr> players;

	void do_session(tcp::socket, Player *p);
};
#endif
