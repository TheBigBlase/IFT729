#include "player.hpp"
#include <iostream>
#include "messages.hpp"

Player::Player(value_t id)
    : id { id }
{
}

void
Player::sanitize_input(std::string input)
{
	size_t pos = 0;
	std::string token;

	std::vector<std::string> res{};
	res.reserve(max_elts); // 3 elts max

	// split string
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		res.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
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

// to check within a switch case

