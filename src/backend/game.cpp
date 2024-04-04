#include<string>
#include"game.hpp"

Game::Game(Player *p) : creator{ p }, drawer { p }, state { WAITING_FOR_WORD } {
	players.push_back(p);
	wordToGuess = "";
}

// TODO should be bool
int Game::addPlayer(Player *p) {
	if (std::find(std::begin(players), std::end(players), p) == players.end()) {
		return 1;
	}

	players.push_back(p);
	return 0;

}

int Game::setWord(Player &p, string word) {
	if (&p != drawer) {
		return 1;
	}
	if (state != WAITING_FOR_WORD){
		return 1;
	}
	wordToGuess = word;
	state = ON_GOING;
	return 0;
}


int Game::guess(Player &p, string guessedWord) {
	if (guessedWord == wordToGuess) {
		return gameOver(p);
	}
	// TODO envoyer que t'es poche
	guessList.push_back(pair<string, Player &>(guessedWord, p));
	sendWordToAll("", p, guessedWord);
	return 0;
}

int Game::gameOver(Player &p) {

	// TODO envoyer la bonne nouvelle
	cout << "winner : " << p.name << endl;
	drawer = &p;
	wordToGuess = "";
	state = WAITING_FOR_WORD;
	// NOTE need ret value?
	return 0;
}

int Game::sendWordToAll(string code, Player &player, string word)
{
	// Code qui va servir a envoyer les mots a tous
	// TODO what's a code
	for_each(std::begin(players), std::end(players),
			[&word, &player](Player *p){
				if (p != &player)
					p->send_message(word);
			});
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

}*/
