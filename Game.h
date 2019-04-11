#pragma once
#include "Player.h"

struct Game
{

	Game();
	~Game();
	string gameName = "";
	int numPlayers = 0;

	Player* playerPtr;
//	vector<Player*>::const_iterator playerIter;
	vector<Player*> players = {};

	void save(ofstream &);
//	void load(ifstream &); //Needed access to equippableCardList (global vector of Card*), could not access vector as function. Defined inside main(). Preserved as a comment in case solution is found.

	
};

