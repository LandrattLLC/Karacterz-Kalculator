#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}


void Game::save(ofstream &outFile)
{
	ostringstream ss;

	ss << this->gameName << endl;
	ss << this->numPlayers << endl;

	ss << endl;
	
	for (size_t i = 0; i < this->players.size(); ++i)
	{
		bool hasAttached = false;

		ss << players[i]->getName() << endl;
		ss << players[i]->getUnequipped() << endl;

		ss << players[i]->equippedCards.size() << endl;

		for (size_t j = 0; j < players[i]->equippedCards.size(); ++j)
		{
			ss << players[i]->equippedCards[j]->getTitle();
			
			if (players[i]->equippedCards[j]->getTitle() == "Magic Staff")
				ss << players[i]->equippedCards[j]->getHandsNeeded() << endl;
			else
				ss << endl;
			
			if (players[i]->equippedCards[j]->attachedCards.size() > 0)
				hasAttached = true;
		}

		if (hasAttached)
			ss << "Attached Cards - " << endl;

		for (vector<Card*>::const_iterator cardIter = players[i]->equippedCards.begin(); cardIter != players[i]->equippedCards.end(); ++cardIter)
		{
			if ((*cardIter)->attachedCards.size() > 0)
			{
				ss << (*cardIter)->getTitle() << endl;
				ss << (*cardIter)->attachedCards.size() << endl;

				for (size_t l = 0; l < (*cardIter)->attachedCards.size(); ++l)
					ss << (*cardIter)->attachedCards[l]->getTitle() << endl;
			}
		}
		
		ss << endl;
	}

	outFile << ss.str();

	cout << "\nFile saved!\n";
	outFile.close();
}

/*
void Game::load(ifstream &inFile)
{
	
}
*/
