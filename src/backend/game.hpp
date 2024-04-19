#ifndef game_H
#define game_H

#include "player.hpp"
#include <string>
#include <vector>

using namespace std;

class Game {
	// Constantes
	enum State {
		WAITING_FOR_WORD,
		ON_GOING,
	};

	// Gestion des joueurs
	// TODO smart pointer?
	value_t id;
	Player *creator;
	Player *drawer;
	std::vector<Player *> players;

	// Gestion de la partie
	State state;
	std::string name;
	string wordToGuess;
	vector<pair<string, Player &>>
		guessList; // <guess, nomDuJoueur> on peut preallouer pour accelerer
				   // surment

  public:
	// TODO use smart pointer, probably
	Game(Player *creator, value_t);
	void guess(Player &, string guessedWord);
	void sendWordToAll(string code, Player &player, string word);
	void sendLoseToAll(string code, Player &player, string word);
	void broadcastPixel(value_t, value_t, Player &);
	void addPlayer(Player *player);
	void removePlayer(Player *player);
	void setWord(Player &player, string word);
	void gameOver(Player &); // player ?
	std::string getName();
	value_t getId();
};

class GameIndexer {
	private:
		GameIndexer() : games{}{};
		// TODO clean games when everyone leaves the lobby
		std::vector<std::pair<std::shared_ptr<Game>, value_t>> games;

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
			games.push_back({g, g->getId()});
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
