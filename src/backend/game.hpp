#ifndef game_H
#define game_H
#include<map>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

//static const string WRONG_GUESS = "WRONG_GUESS";
//static const string GAME_OVER = "GAME_OVER";

class Game
{
	// Constantes
	enum State {
		WAITING_FOR_WORD,
		ON_GOING,
	};

	// Gestion des joueurs
	string creator;
	string drawer;
	map<string, string> players; // <nom du joueur, truc de connection?>

	//Gestion de la partie
	State state;
	string wordToGuess;
	vector<pair<string, string>> guessList; // <guess, nomDuJoueur> on peut preallouer pour accelerer surment


public:
	Game(string creator, string _creatorSocket);
	int guess(string player, string guessedWord);
	int sendWordToAll(string code, string player, string word);
	int addPlayer(string player, string playerSocket);
	int setWord(string player, string word);
	int gameOver(string winner);
};

#endif