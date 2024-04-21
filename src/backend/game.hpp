#ifndef game_H
#define game_H

#include "player.hpp"
#include <string>
#include <vector>

using namespace std;

class Game {
	// Gestion des joueurs
	// TODO smart pointer?
	value_t id;
	Player *creator;
	Player *drawer;
	std::vector<Player *> players;
	bool creatorWaiting;

	// Gestion de la partie
	std::string wordToGuess;

  public:
	// TODO use smart pointer, probably
	Game(Player *creator, value_t);
	void guess(Player &, string guessedWord);
	void sendWordToAll(Player &player, string word);
	void sendLoseToAll(Player &player, string word);
	void broadcastPixel(value_t, value_t, Player &);
	void addPlayer(Player *player);
	void removePlayer(Player *player);
	void setWord(Player &player, string word);
	void gameOver(Player &); // player ?
	void changeDrawer(Player &);
	std::string getWordToGuess();
	value_t getId();
	void checkIfCreatorWaiting();
};

// singleton. Has store pointer to all games.
class GameIndexer {
	private:
		GameIndexer() : games{}{};
		std::vector<std::pair<std::weak_ptr<Game>, value_t>> games;

	  public:
		GameIndexer(GameIndexer const &) = delete;
		void operator=(GameIndexer const &) = delete;

		static GameIndexer &get() { static GameIndexer indexer; return indexer;}

		std::weak_ptr<Game> search_game(value_t id) {
			auto tmp = std::rbegin(games);
			auto res = std::weak_ptr<Game>{};
			for (; tmp != std::rend(games); ++tmp) {
				if (tmp->second == id) {
					res = tmp->first;
				}
			}
			return res;
		}

		void add_game(std::shared_ptr<Game> g) {
			auto space =
				std::find_if(std::begin(games), std::end(games),
							 [](std::pair<std::weak_ptr<Game>, value_t> it) {
								 return it.first.expired();
							 });

			if (space == std::end(games))
				games.push_back({std::weak_ptr<Game>{g}, g->getId()});
			else
				*space = {std::weak_ptr<Game>{g}, g->getId()};
		}

		std::vector<std::weak_ptr<Game>> *get_last_10() {
			std::vector<std::weak_ptr<Game>> *res =
				new std::vector<std::weak_ptr<Game>>();
			res->reserve(10);

			auto tmp = std::end(games) - std::min<value_t>(games.size(), 10);
			for (; tmp != std::end(games); ++tmp) {
				res->push_back(tmp->first);
			}
			return res;
		}
};

#endif
