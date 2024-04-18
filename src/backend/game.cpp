#include "game.hpp"
#include <iostream>
#include <string>

Game::Game(Player *p, value_t id)
	: creator{p}, drawer{p}, state{WAITING_FOR_WORD}, id{id}, players{} {
	players.push_back(p);
	wordToGuess = "";
	name = std::format("{}'s room", p->name);
}

// TODO should be bool
int Game::addPlayer(Player *p) {
	if (std::find(std::begin(players), std::end(players), p) == players.end()) {
		players.push_back(p);
		return 1;
	}

	return 0;
}

// TODO should be bool
int Game::setWord(Player &p, string word) {
	if (&p != drawer) {
		return 1;
	}
	if (state != WAITING_FOR_WORD) {
		return 1;
	}
	wordToGuess = word;
	state = ON_GOING;
	return 0;
}

// TODO should be bool
int Game::guess(Player &p, string guessedWord) {
	if (guessedWord == wordToGuess) {
		return gameOver(p);
	}
	// TODO envoyer que t'es poche
	guessList.push_back(pair<string, Player &>(guessedWord, p));
	sendWordToAll("", p, guessedWord);
	return 0;
}

// TODO should be bool
int Game::gameOver(Player &p) {

	// TODO envoyer la bonne nouvelle
	std::cout << "winner : " << p.name << endl;
	drawer = &p;
	wordToGuess = "";
	state = WAITING_FOR_WORD;
	// NOTE need ret value?
	return 0;
}

// TODO should be bool
int Game::sendWordToAll(string code, Player &player, string word) {
	// Code qui va servir a envoyer les mots a tous
	// TODO what's a code
	for_each(std::begin(players), std::end(players),
			 [&word, &player](Player *p) {
				 if (p != &player)
					 p->send_message(word);
			 });
	return 0;
}

// TODO should be bool
// TODO dont ret 0 if we got nothing to return in the first place
int Game::broadcastPixel(value_t x, value_t y, Player &author) {
	for (auto p : players) {
		if (p != nullptr && p != &author)
			p->send_pixel(x, y);
	}

	return 0;
}

std::string Game::getName() { return name; }

value_t Game::getId() { return id; }
