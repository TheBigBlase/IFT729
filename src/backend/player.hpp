#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#ifndef VALUE_T
#define VALUE_T

using value_t = int;

#endif

class Game;
class Player {
	public:
		Player(value_t);
	private:
		value_t id;
		Game * game;
		void sanitize_input(std::string);
		void handle_input(std::vector<std::string>);
		inline static std::string delimiter = ":";
		inline static value_t max_elts = 3;
};


#endif
