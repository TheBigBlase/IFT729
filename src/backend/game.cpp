#include<string>
#include"game.hpp"

Game::Game(string _creator, string _creatorSocket) {
	creator = _creator;
	drawer = _creator;
	state = WAITING_FOR_WORD;
	players.insert(pair<string, string>(_creator, _creatorSocket));
	wordToGuess = "";
}

int Game::addPlayer(string playerName, string playerSocket) {
	if (players.find(playerName) == players.end()) {
		return 1;
	}
	
	players.insert(pair<string, string>(playerName, playerSocket));
	return 0;

}

int Game::setWord(string playerName, string word) {
	if (playerName != drawer) {
		return 1;
	}
	if (state != WAITING_FOR_WORD){
		return 1;
	}
	wordToGuess = word;
	state = ON_GOING;
	return 0;
}


int Game::guess(string playerName, string guessedWord) {
	if (guessedWord == wordToGuess) {
		return gameOver(playerName);
	}
	// TODO envoyer que t'es poche
	guessList.push_back(pair<string, string>(guessedWord, playerName));
	return 0;
}

int Game::gameOver(string winner) {

	// TODO envoyer la bonne nouvelle
	cout << "winner : " << winner << endl;
	drawer = winner;
	wordToGuess = "";
	state = WAITING_FOR_WORD;
	return 0;
}

int Game::sendWordToAll(string code, string player, string word)
{
	// Code qui va servir a envoyer les mots a tous
	return 0;
}

/*#include<iostream>
#include"logique.hpp"
using namespace std;

string isOk(int val) {
	return !val ? " : OK" : " : ERROR";
}

int main(int argc, char* argv[])
{
	cout << "yooo" << endl;
	Logique* logique
		= Logique::get();
	string player1 = "Bob";
	string player2 = "Alice";
	string socket1 = "Whatever";
	string socket2 = "WhoCares";


	//cout << "Creation de partie par " << player1 << isOk(logique->createGame(player1, socket1));

	//cout << "Rejoindre mauvaise partie par " << player2 << isOk(logique->joinGame(player2, player2, "llllll"));
	//cout << "Rejoindre partie par " << player2 << isOk(logique->joinGame(player2, player2, player1));

}
