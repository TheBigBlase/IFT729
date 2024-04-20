#include "game.hpp"
#include "word_list.hpp"
#include <iostream>
#include <string>

Game::Game(Player *p, value_t id)
	: creator{ p }, drawer{ p }, id{ id }, players{}, creatorWaiting{true}{
	players.push_back(p);
	wordToGuess = Word_list::get().get_random_word();
}

void Game::addPlayer(Player *p) {
	if (std::find(std::begin(players), std::end(players), p) == players.end()) {
		players.push_back(p);
	}
}

void Game::removePlayer(Player* p) {
	players.erase(std::find(std::begin(players), std::end(players), p));
}

void Game::guess(Player &p, string guessedWord) {
	if (guessedWord == wordToGuess) {
		return gameOver(p);
	}
	guessList.push_back(pair<string, Player &>(guessedWord, p));
	sendWordToAll(p, guessedWord);
}

void Game::gameOver(Player &p) {
	std::cout << "[WINNER] : " << p.name << endl;
	string prev(wordToGuess);
	changeDrawer(p);
	p.send_win(wordToGuess);
	sendLoseToAll(p, prev);
}

void Game::changeDrawer(Player &p){
	wordToGuess = Word_list::get().get_random_word_different_from(wordToGuess);
	drawer = &p;
}

void Game::sendWordToAll(Player &player, string word) {
	for (auto p : players) {
		if (p != &player)
			p->send_message(word);
	};
}

void Game::sendLoseToAll(Player &player, string word) {
	for (auto p : players) {
		if (p != &player)
			p->send_lose(p->name, word);
	};
}

void Game::broadcastPixel(value_t x, value_t y, Player &author) {
	for (auto p : players) {
		if (p != nullptr && p != &author)
			p->send_pixel(x, y);
	}
}

value_t Game::getId() { return id; }

std::string Game::getWordToGuess() { return wordToGuess; }

void Game::checkIfCreatorWaiting() {
	if (creatorWaiting) {
		creator->send_start();
		creatorWaiting = false;
	}
}
