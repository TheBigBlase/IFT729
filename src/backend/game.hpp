#ifndef game_H
#define game_H

#include "player.hpp"
#include <string>
#include <vector>

using namespace std;

// static const string WRONG_GUESS = "WRONG_GUESS";
// static const string GAME_OVER = "GAME_OVER";

class Game {
	// Constantes
	enum State {
		WAITING_FOR_WORD,
		ON_GOING,
	};

	// Gestion des joueurs
	// TODO smart pointer
	Player *creator;
	Player *drawer;
	std::vector<Player *> players; // <nom du joueur, truc de connection?>

	// Gestion de la partie
	State state;
	std::string name;
	string wordToGuess;
	vector<pair<string, Player &>>
		guessList; // <guess, nomDuJoueur> on peut preallouer pour accelerer
				   // surment

  public:
	// TODO use smart pointer, probably
	Game(Player *creator);
	int guess(Player &, string guessedWord);
	int sendWordToAll(string code, Player &player, string word);
	int addPlayer(Player *player);
	int setWord(Player &player, string word);
	int gameOver(Player &); // player ?
	std::string getName();
};

#endif
