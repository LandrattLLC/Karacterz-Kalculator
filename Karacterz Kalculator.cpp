// Karacterz Kalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Card.h"
#include "Player.h"
#include "Game.h"

 vector<Card*> equippableCardList = { new AcademyGraduate, new AncientTradition, new ArmorMastery, new BattleMage, new BladeDancer, new BoostMastery, new Bow, new Buckler, new ChainMail, new Champion, new CombatMastery, new Combatant, new CoreAgilityFemale, new CoreAgilityMale, new CorePhysicalFemale, new CorePhysicalMale, new CoreMagicFemale, new CoreMagicMale, new Dagger, new Duelist, new DuelWieldMastery, new ElementalMastery, new Elementalist, new Enforcer, new FullPlateArmor, new Gi, new HalfPlateArmor, new IndependentlyStudied, new Katana, new KiteShield, new KozaneArmor, new Mage, new MagicItemMastery, new MagicRobe, new MagicStaff, new MagicStaffOneHand, new MartialArtist, new PaddedArmor, new Prodigy, new Quarterstaff, new QuarterstaffMastery, new Rondache, new Samurai, new Scimitar, new Sorcerer, new SpellwroughtShield, new StaminaMastery, new StatAgility, new StatPhysical, new StatMagic, new  Sword, new Wakizashi, new Wand, new Warder, new WeaponMastery };

 Game daGame;
 Game* game;


void displayCommands();
void winCommand();
void equipCommand();
void unequipCommand();
void cardCommand();
void playerCommand();

void clearPlayersAndCards();

int main()
{
	int temp = 0;
	string choice = "";
	game = &daGame;



	//Welcome Text
	cout << "Welcome to the Karacterz Kalculator: Interactive Beta edition!\nThis program is written by Matt Hall, creator of Karacterz. Version 0.1\n\n";
	cout << "This program will keep track of all players' equipped cards and their total bonuses in an epic game of Karacterz.\n\n";

	//Initializing program

	cout << "Would you like to load a game? (Y/N)  ";
	if (choiceYN() == 'Y')
	{
		choice = "Load";
		goto load;
	}

start:
	cout << "\nHow many players are playing this game of Karacterz? ";

	//Checking to see if game->numPlayers is a positive number.
	while (!(cin >> game->numPlayers) || (game->numPlayers < 0))
	{
		cout << "\nPlease try again with a positive number: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cin.ignore();



	//Making new players and putting them in a vector
	temp = game->numPlayers;
	while (temp != 0)
	{
		game->playerPtr = new Player;
		cout << "\nWhat is this player's name: ";
		string tempName = "";
		getline(cin, tempName);
		game->playerPtr->setName(tempName);
		game->players.push_back(game->playerPtr);
		temp--;
	}


	//Welcoming the new players
	cout << "\nWelcome ";
	if (game->numPlayers > 2)
	{
		for (vector<Player*>::const_iterator playerIter = game->players.begin(); playerIter != game->players.end(); ++playerIter)
		{
			cout << (*playerIter)->getName();
			if (playerIter != (game->players.end() - 1))
				cout << ", ";
			if (playerIter == game->players.end() - 2)
				cout << "and ";
		}
	}
	else if (game->numPlayers == 2)
	{
		cout << game->players[0]->getName() << " and " << game->players[1]->getName();
	}
	else
		cout << game->players[0]->getName();
	cout << " to Karacterz!\n\nType Command to bring up the command list to use this program.\n";


	//Creating a save file
	cout << "\nPlease enter the name of this game: ";
	getline(cin, game->gameName);


	//Start playing the game!
beginning:
	cout << "\nPlease type your desired command: ";
	getline(cin, choice);

	if ((choice == "Back") || (choice == "Cancel"))
		goto beginning;

	if (choice == "Command")
	{
		displayCommands();
		goto beginning;
	}

	if (choice == "Equip")
	{
		equipCommand();
		goto beginning;
	}

	if (choice == "Unequip")
	{
		unequipCommand();
		goto beginning;
	}

	if (choice == "Card")
	{
		cardCommand();
		goto beginning;
	}

	if (choice == "Player")
	{
		playerCommand();
		goto beginning;
	}

	if (choice == "Win")
	{
		winCommand();
		goto beginning;
	}

	if (choice == "Game")
	{
		cout << "\nName: " << game->gameName << ", numPlayers: " << game->numPlayers << ", players.size(): " << game->players.size() << endl;
		cout << "\nPlayer names: ";
		for (auto &people : game->players)
		{
			cout << "\n" << people->getName() << ": ";
			people->displayCards();
			cout << endl;
			for (int z = 0; z < bonusSize; ++z)
			{
				cout<<people->getBonuses(z);
			}
			cout << endl;
			for (int x = 0; x < typesSize; ++x)
			{
				cout << people->getEquipLimits(x);
			}
			cout << endl;
		}
		goto beginning;
	}

	if (choice == "Save")
	{
		ofstream saveGame(game->gameName + ".txt");
		game->save(saveGame);
		goto beginning;
	}

	if (choice == "Load")
	{
		cout << "\nAre you sure? All unsaved progress will be lost. (Y/N)  ";

		if (choiceYN() == 'Y')
		{
		load:
			string tempName;
			cout << "\nWhat is the name of the game you want to load: ";
			getline(cin, tempName);

			ifstream loadGame;
			loadGame.open(tempName + ".txt");

			if (loadGame.fail())
			{
				cout << "\nThere is no game with that name saved on this folder.\n\nStarting a new game.\n";
				clearPlayersAndCards();
				goto start;
			}

			string buffer;

			//clearing the players' and their cards' vectors safely
			clearPlayersAndCards();


			//changing the game's name
			getline(loadGame, buffer);
			game->gameName = buffer;

			//changing how many players are playing the game
			getline(loadGame, buffer);
			game->numPlayers = stoi(buffer);

			//skipping the empty line
			getline(loadGame, buffer);

			//adding new players
			for (int i = 0; i < game->numPlayers; ++i)
			{
				game->players.push_back(new Player);
			}

			//changing each player
			for (vector<Player*>::const_iterator playerIter = game->players.begin(); playerIter != game->players.end(); ++playerIter)
			{
				int numCards;

				//updating player's name
				getline(loadGame, buffer);
				(*playerIter)->setName(buffer);

				//updating player's unequipped value
				getline(loadGame, buffer);
				(*playerIter)->setUnequipped(stoi(buffer));

				//get number of cards that were equipped to this player
				getline(loadGame, buffer);
				numCards = stoi(buffer);

				//if player didn't have cards, player is now ready
				if (numCards == 0)
				{
					getline(loadGame, buffer);
					continue;
				}

				//equipping player's cards
				for (int j = 0; j < numCards; ++j)
				{
					getline(loadGame, buffer);

					if (buffer == "Magic Staff1")
					{
						(*playerIter)->equipCard(equippableCardList[35], true);
						continue;
					}

					if (buffer == "Magic Staff2")
					{
						(*playerIter)->equipCard(equippableCardList[34], true);
						continue;
					}

					for (vector<Card*>::const_iterator cardIter = equippableCardList.begin(); cardIter != equippableCardList.end(); ++cardIter)
					{
						if ((*cardIter)->getTitle() == buffer)
						{
							(*playerIter)->equipCard((*cardIter), true);
						}
					}
				}

				//reading the next line: blank or announces the attached cards
				getline(loadGame, buffer);

				if (buffer == "Attached Cards - ")
				{
					string cardWithAttached;
					//reading which card had attachments
					getline(loadGame, cardWithAttached);

					//reading how many cards were attached to that card
					getline(loadGame, buffer);
					int attachedCards;
					attachedCards = stoi(buffer);

					//attaching all cards to the card
					for (vector<Card*>::const_iterator cardIter = (*playerIter)->equippedCards.begin(); cardIter != (*playerIter)->equippedCards.end(); ++cardIter)
					{
						if ((*cardIter)->getTitle() == cardWithAttached)
						{
							for (int k = 0; k < attachedCards; ++k)
							{
								getline(loadGame, buffer);
								for (vector<Card*>::const_iterator attachIter = equippableCardList.begin(); attachIter != equippableCardList.end(); ++attachIter)
								{
									if ((*attachIter)->getTitle() == buffer)
									{
										(*cardIter)->addAttachedCard(*attachIter);
										(*playerIter)->addBonuses(*attachIter);
										if ((*attachIter)->getType() == "Armor")
										{
											(*playerIter)->addEquipLimits(4, 1);
										}
										if ((*attachIter)->getType() == "Weapon")
										{
											(*playerIter)->addEquipLimits(6, (*attachIter)->getHandsNeeded());
										}
									}
								}
							}
						}
					}

					//skipping the blank line
					getline(loadGame, buffer);
				}
			}
			loadGame.close();
			cout << "\nSession loaded successfully!\n";
			goto beginning;
		}
		else
		goto beginning;
	}

	if ((choice == "Quit") || (choice == "Exit"))
	{
		cout << "\nThank you for playing Karacterz and using the Karacterz Kalculator!\nPlease feel free to comment on the Karacterz Facebook page, Landratt's Twitter page or send me an email with any questions, comments or suggestions.\n\nHAVE A NICE DAY :)\n\n";

		for (vector<Player*>::const_iterator playerIter = game->players.begin(); playerIter != game->players.end(); ++playerIter)
		{
			delete *playerIter;
			game->players.erase(playerIter);
		}

		for (vector<Card*>::const_iterator cardIter = equippableCardList.begin(); cardIter != equippableCardList.end(); cardIter++)
		{
			delete *cardIter;
			equippableCardList.erase(cardIter);
		}

		game->playerPtr = 0;

		return 0;
	}

	if (!(choice == "Game") || !(choice == "Command") || !(choice == "Equip") || !(choice == "Unequip") || !(choice == "Card") || !(choice == "Player") || !(choice == "Exit") || !(choice == "Quit") || !(choice == "Win") || !(choice == "Back") || !(choice == "Cancel") || !(choice == "Save") || !(choice == "Load"))
	{
		cout << "That is not a valid command.\n";
		goto beginning;
	}
}

char choiceYN()
{
	char yn;
	cin >> yn;
	while (!(cin) || ((yn != 'Y') && (yn != 'N')))
	{
		cout << "\nPlease type in \'Y\' or \'N\'  ";
		cin.clear();
		cin.ignore(CHAR_MAX, '\n');
		cin >> yn;
	}
	cin.ignore();

	return yn;
}


void displayCommands()
{
	cout << "\n\nBack or Cancel: \n\tCancel your current command. Does not work with questions that require a number or a single letter.\n";
	cout << "Equip: \n\tA player equips a new card.\n";
	cout << "Unequip: \n\tA player unequips an equipped card.\n";
	cout << "Card: \n\tDisplays all the information on a specific card.\n";
	cout << "Player: \n\tDisplays all of a player's bonuses and their equipped cards.\n";
	cout << "Win: \n\tA secret function before exiting the program.\n";
	cout << "\nExit or Quit: \n\tTo quit the Karacterz Kalculator, type Exit or Quit.\n";
}

void winCommand()
{
	bool nameFound = false;
	string tempName = "";

	//Who won the game?
	if (game->numPlayers > 2)
	{
		cout << "Did ";

		for (vector<Player*>::const_iterator playerIter = game->players.begin(); playerIter != game->players.end(); ++playerIter)
		{
			cout << (*playerIter)->getName();
			if (playerIter != (game->players.end() - 1))
				cout << ", ";
			if (playerIter == game->players.end() - 2)
				cout << " or ";
		}
		cout << " win the game: ";
	}
	else if (game->numPlayers == 2)
	{
		cout << "\nDid " << game->players[0]->getName() << " or " << game->players[1]->getName() << " win the game? ";
	}
	else
	{
		cout << "\nCongratualtions on your victory, " << game->players[0]->getName() << "!\n";
		goto endWin;
	}

	//Ask and verify winner
	while (!nameFound)
	{
		getline(cin, tempName);

		if ((tempName == "Back") || (tempName == "Cancel"))
			return;

		for (auto &player : game->players)
		{
			if (player->getName() == tempName)
			{
				cout << "\nCongratualtions on your victory, " << tempName << "!\n";
				nameFound = true;
			}

		}
		cout << "There is no player with that name. Please type in a player's name: ";
	}

endWin:
	cout << "\nThank you for playing Karacterz and using the Karacterz Kalculator!\nPlease feel free to comment on the Karacterz Facebook page, Landratt's Twitter page or send me an email with any questions, comments or suggestions.\n\nHAVE A NICE DAY :)\n\n";
		cout << "\nThank you for playing Karacterz and using the Karacterz Kalculator!\nPlease feel free to comment on the Karacterz Facebook page, Landratt's Twitter page or send me an email with any questions, comments or suggestions.\n\nHAVE A NICE DAY :)\n\n";
	cout << "\nPress any key then hit Enter, or just hit Enter, to exit.\n";
	getchar();
	exit(0);
}

void equipCommand()
{
	bool cardFound = false;
	bool nameFound = false;
	string tempName = "";


	//Ask and verify player
	if (game->numPlayers == 1)
	{
		//Asking and verifying card to equip
		cout << "\nWhich card would you like to equip: ";

		while (!cardFound)
		{
			getline(cin, tempName);

			if ((tempName == "Back") || (tempName == "Cancel"))
				return;

			//Asks which Magic Staff the player wants to equip.
			if (tempName == "Magic Staff")
			{
				cout << "\nWould you like to equip the Magic Staff with 1 Hand or 2: ";
				int oneOrTwo;
				cin >> oneOrTwo;
				while ((!cin) || (oneOrTwo < 1) || (oneOrTwo > 2))
				{
					cout << "\nPlease enter either 1 or 2: ";
					cin.clear();
					cin.ignore();
					cin >> oneOrTwo;
				}
				cin.ignore(INT_MAX, '\n');

				if (oneOrTwo == 1)
				{
					game->players[0]->equipCard(equippableCardList[35], false);
					cardFound = true;
					break;
				}
				else if (oneOrTwo == 2)
				{
					game->players[0]->equipCard(equippableCardList[34], false);
					cardFound = true;
					break;
				}
			}
			for (auto &card : equippableCardList)
			{
				//Equips the card
				if (card->getTitle() == tempName)
				{
					game->players[0]->equipCard(card, false);
					cardFound = true;
					break;
				}
			}
			if (cardFound)
				break;

			cout << "\nThere is no card with that title. Please type in the title of the card you wish to equip: ";
		}
	}

	//More than one player
	if (game->numPlayers > 1)
	{
		cout << "\nWhich player is equipping a card: ";

		while (nameFound == false)
		{
			getline(cin, tempName);

			if ((tempName == "Back") || (tempName == "Cancel"))
				return;

			for (auto &player : game->players)
			{
				if (player->getName() == tempName)
				{
					//Asking and verifying card to equip
					cout << "\nWhich card would " << player->getName() << " like to equip: ";

					while (!cardFound)
					{
						getline(cin, tempName);

						if ((tempName == "Back") || (tempName == "Cancel"))
							return;

						//Asks which Magic Staff player would like to equip.
						if (tempName == "Magic Staff")
						{

							cout << "\nWould you like to equip the Magic Staff with 1 Hand or 2: ";
							int oneOrTwo;
							cin >> oneOrTwo;
							while ((!cin) || (oneOrTwo < 1) || (oneOrTwo > 2))
							{
								cout << "\nPlease enter either 1 or 2: ";
								cin.clear();
								cin.ignore();
								cin >> oneOrTwo;
							}
							cin.ignore(INT_MAX, '\n');


							if (oneOrTwo == 1)
							{
								player->equipCard(equippableCardList[35], false);
								cardFound = true;
								break;
							}
							else if (oneOrTwo == 2)
							{
								player->equipCard(equippableCardList[34], false);
								cardFound = true;
								break;
							}
						}

						for (auto &card : equippableCardList)
						{
							if (card->getTitle() == tempName)
							{
								player->equipCard(card, false);
								cardFound = true;
							}
						}

						if (cardFound)
							break;

						cout << "\nThere is no card with that title. Please type in the title of the card you wish to equip: ";
					}

					nameFound = true;
				}
			}

			if (nameFound)
				break;

			cout << "There is no player with that name. Please type in a player's name: ";
		}
	}
}


void unequipCommand()
{
	bool nameFound = false;
	bool cardFound = false;
	string tempName = "";

	//Ask and verify player
	if (game->numPlayers == 1)
	{
		while (cardFound == false)
		{
			//Asking and verifying card to equip
			if (game->players[0]->equippedCards.empty())
			{
				cout << "You have no cards to unequip.\n";
				break;
			}

			if (game->players[0]->equippedCards.size() == 1)
			{
				game->players[0]->unequip(game->players[0]->equippedCards[0]);
				cardFound = true;
				break;
			}

			cout << "\nWhich card would you like to unequip: ";
			if (game->players[0]->equippedCards.size() > 1)
			{
				getline(cin, tempName);

				if ((tempName == "Back") || (tempName == "Cancel"))
					return;

				for (auto &card : equippableCardList)
				{
					if (card->getTitle() == tempName)
					{
						game->players[0]->unequip(card);
						cardFound = true;
					}
				}

				if (cardFound)
					break;

				cout << "\nThere is no card with that title. Please type in the title of the card you wish to unequip: ";
			}

		}
	}


	if (game->numPlayers > 1)
	{
		cout << "\nWhich player is unequipping a card: ";

		while (nameFound == false)
		{
			getline(cin, tempName);

			if ((tempName == "Back") || (tempName == "Cancel"))
				return;

			for (auto &player : game->players)
			{
				if (player->getName() == tempName)
				{
					//Asking and verifying card to equip
					if (player->equippedCards.empty())
					{
						cout << "\n" << player->getName() << " has no cards to unequip.\n";
						return;
					}

					if (player->equippedCards.size() == 1)
					{
						player->unequip(player->equippedCards[0]);
						return;
					}

					cout << "\nWhich card would " << player->getName() << " like to unequip: ";

					if (player->equippedCards.size() > 1)
					{
						while (cardFound == false)
						{
							getline(cin, tempName);

							if ((tempName == "Back") || (tempName == "Cancel"))
								return;

							for (auto &card : equippableCardList)
							{
								if (card->getTitle() == tempName)
								{
									player->unequip(card);
									cardFound = true;
								}
							}

							if (cardFound)
								break;

							cout << "\nThere is no card with that title. Please type in the title of the card you wish to unequip: ";
						}
					}

					nameFound = true;
				}
			}

			if (nameFound)
				break;

			cout << "There is no player with that name. Please type in a player's name: ";
		}
	}

	nameFound = false;
	cardFound = false;
	tempName = "";
}



void cardCommand()
{
	bool cardFound = false;
	string tempName = "";

	cout << "\nWhich card would you like to see: ";

	while (cardFound == false)
	{
		getline(cin, tempName);

		if ((tempName == "Back") || (tempName == "Cancel"))
			return;

		for (auto &card : equippableCardList)
		{
			if (card->getTitle() == tempName)
			{
				card->displayCardInfo();
				cardFound = true;
			}
		}

		if (cardFound)
			break;

		cout << "There is no card with that title. Please type in the title of the card you wish to see: ";
	}

	cardFound = false;
	tempName = "";
}



void playerCommand()
{
	bool nameFound = false;
	string tempName = "";

	if (game->numPlayers == 1)
	{
		game->players[0]->displayCards();
		game->players[0]->displayBonuses();
		cout << endl;
		game->players[0]->displayPowers();
		return;
	}

	cout << "\nWhich player would you like to see: ";

	if (game->numPlayers > 1)
	{
		while (nameFound == false)
		{
			getline(cin, tempName);

			if ((tempName == "Back") || (tempName == "Cancel"))
				return;

			for (auto &player : game->players)
			{
				if (player->getName() == tempName)
				{
					player->displayCards();
					player->displayBonuses();
					cout << endl;
					player->displayPowers();
					nameFound = true;
				}
			}

			if (nameFound)
				break;

			cout << "There is no player with that name. Please type in a player's name: ";
		}

	}


	nameFound = false;
	tempName = "";
}


void clearPlayersAndCards()
{
	for (vector<Player*>::const_iterator playerIter = game->players.begin(); playerIter != game->players.end(); ++playerIter)
	{
		for (vector<Card*>::const_iterator cardIter = (*playerIter)->equippedCards.begin(); cardIter != (*playerIter)->equippedCards.end(); ++cardIter)
		{
			if ((*cardIter)->attachedCards.size() > 0)
				(*cardIter)->attachedCards.clear();
		}

		(*playerIter)->equippedCards.clear();
	}
	game->players.clear();
}
