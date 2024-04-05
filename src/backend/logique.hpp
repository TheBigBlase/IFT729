/*#ifndef Logique_H
#define Logique_H

#include <map>
#include <string>
#include <cstdlib>
#include"game.hpp"

using namespace std;
class Logique {
    // pointeur vers le singleton
    static Logique* singleton;
    Logique();

    std::map<string, int> joueurs = {};
    std::map<string, Game*> games = {};


public:
    Logique(const Logique&) = delete;
    Logique& operator=(const Logique&) = delete;
    static Logique* get() {
        if (!singleton)
            singleton = new Logique;
        return singleton;
    }

    int createGame(string playerName, string playerSocket);
    int joinGame(string playerName, string playerSocket, string gameId);

};

#endif*