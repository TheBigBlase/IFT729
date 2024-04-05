#include "logique.hpp"

int Logique::createGame(string playerName, string playerSocket) {
	if (games.find(playerName) != games.end()) {
		return 1;
	}
	games.insert(
		pair<string, Game *>(playerName, new Game(playerName, playerSocket)));
	return 0;
}

int Logique::joinGame(string playerName, string playerSocket, string gameId) {
	auto it = games.find(gameId);
	if (it == games.end()) {
		return 1;
	}
	return it->second->addPlayer(playerName, playerSocket);
}