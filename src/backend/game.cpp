#include "game.hpp"
#include <iostream>
#include <string>

Game::Game(Player *p, value_t id)
	players.push_back(p);
	: creator{p}, drawer{p}, id{id}, players{} {
	wordToGuess = "pomme";
	name = std::format("{}'s room", p->name);
}

void Game::addPlayer(Player *p) {
	if (std::find(std::begin(players), std::end(players), p) == players.end()) {
		players.push_back(p);
	}
}

}

void Game::removePlayer(Player* p) {
	players.erase(std::find(std::begin(players), std::end(players), p));
}

void Game::setWord(Player &p, string word) {
	wordToGuess = word;
}

void Game::guess(Player &p, string guessedWord) {
	if (guessedWord == wordToGuess) {
		return gameOver(p);
	}
	guessList.push_back(pair<string, Player &>(guessedWord, p));
	sendWordToAll("", p, guessedWord);
}

void Game::gameOver(Player &p) {
	std::cout << "winner : " << p.name << endl;
	p.send_win(wordToGuess);
	sendLoseToAll("",p, wordToGuess);
}

void Game::sendWordToAll(string code, Player &player, string word) {
	for_each(std::begin(players), std::end(players),
			 [&word, &player](Player *p) {
				 if (p != &player) //en comment pour lisntant, a voir quest ce quon  fait avec ca
					p->send_message(word);
			 });
}

void Game::sendLoseToAll(string code, Player& player, string word) {
	for_each(std::begin(players), std::end(players),
		[&word, &player](Player* p) {
			if (p != &player) //en comment pour lisntant, a voir quest ce quon  fait avec ca
				p->send_lose(p->name,word);
		});
}

void Game::broadcastPixel(value_t x, value_t y, Player &author) {
	for (auto p : players) {
		if (p != nullptr && p != &author)
			p->send_pixel(x, y);
	}
}

std::string Game::getName() { return name; }

value_t Game::getId() { return id; }
