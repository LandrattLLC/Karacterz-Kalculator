#include "stdafx.h"
#include "Player.h"


Player::Player() : name(""), isUnequipped(false)
{

}

int Player::getBonuses(int num)
{
	return this->bonuses[num];
}

void Player::addBonuses(Card* card)
{
	for (int i = 0; i < bonusSize; ++i)
		this->bonuses[i] += card->bonuses[i];
}

int Player::getEquipLimits(int num)
{
	return this->equipLimits[num];
}

void Player::addEquipLimits(int limit, int num)
{
	this->equipLimits[limit] += num;
}


Player::~Player() 
{
	for (vector<Card*>::const_iterator cardIter = equippedCards.begin(); cardIter != equippedCards.end(); ++cardIter)
	{
		delete *cardIter;
		equippedCards.erase(cardIter);
	}
}

bool Player::checkEquipRequirements(Card* card)
{
	for (int i = 0; i < requirementSize; ++i)
	{
		if (card->equipRequirements[i] == 0)
			continue;
		else
		{
			if (card->equipRequirements[i] > this->bonuses[i])
				return false;
		}
	}

	return true;
}

bool Player::specialRequirements(Card* card)
{
	if (card->getTitle() == "Blade Dancer")
	{
		for (auto &eqcard : equippedCards)
		{
			if (eqcard->getBladed())
				return true;
			else
				continue;
		}
		return false;
	}

	if (card->getTitle() == "Combatant")
	{
		for (auto &eqcard : equippedCards)
		{
			if ((eqcard->getDeck() == "Agility") || (eqcard->getDeck() == "Magic"))
				return false;
			else
				continue;
		}
		return true;
	}

	if (card->getTitle() == "Duelist")
	{
		for (auto &eqcard : equippedCards)
		{
			if ((this->bonuses[0] >= 6) | (this->bonuses[2] >= 6))
				return true;
			else
				continue;
		}
		return false;
	}

	if (card->getTitle() == "Mage")
	{
		for (auto &eqcard : equippedCards)
		{
			if ((eqcard->getDeck() == "Agility") || (eqcard->getDeck() == "Physical"))
				return false;
			else
				continue;
		}
		return true;
	}

	if (card->getTitle() == "Martial Artist")
	{
		for (auto &eqcard : equippedCards)
		{
			if ((eqcard->getDeck() == "Magic") || (eqcard->getDeck() == "Physical"))
				return false;
			else
				continue;
		}
		return true;
	}

	if (card->getTitle() == "Samurai")
	{
		for (auto &eqcard : equippedCards)
		{
			if ((eqcard->getTitle() == "Katana") || (eqcard->getTitle() == "Wakizashi") || (eqcard->getTitle() == "Kozane Armor"))
				return true;
			else
				continue;
		}
		return false;
	}

	return true;
}


void Player::equipCard(Card* card, bool isLoaded)
{
	Card* weapons[10] = { new Dagger, new Sword, new Wakizashi, new Quarterstaff, new Wand, new Katana, new Scimitar, new Bow, new MagicStaffOneHand, new MagicStaff };
	Card* armor[7] = { new ChainMail, new FullPlateArmor, new HalfPlateArmor, new MagicRobe, new Gi, new KozaneArmor, new PaddedArmor };
	Card* mastery[9] = { new ArmorMastery, new ElementalMastery, new CombatMastery, new WeaponMastery, new MagicItemMastery, new BoostMastery, new QuarterstaffMastery, new StaminaMastery, new DuelWieldMastery };
	Card* stat[3] = { new StatMagic, new StatAgility, new StatPhysical };
	Card* classes[12] = { new Combatant, new Warder, new Enforcer, new Samurai, new Mage, new BattleMage, new Elementalist, new Sorcerer, new Duelist, new MartialArtist, new Champion, new BladeDancer };
	this->setUnequipped(false);
	bool cardFound = false;


	if ((checkEquipRequirements(card)) && specialRequirements(card) && (!isLoaded))
	{
		this->equippedCards.push_back(card);
		for (int i = 0; i < bonusSize; ++i)
			this->bonuses[i] += card->bonuses[i];
	}
	else if (isLoaded)
	{
		this->equippedCards.push_back(card);
		for (int i = 0; i < bonusSize; ++i)
			this->bonuses[i] += card->bonuses[i];
	}
	else
	{
		cout << "\n" << name << " does not meet the requirements to equip " << card->getTitle() << endl;
		return;
	}

	if (card->getHandsNeeded() == 1)
		this->equipLimits[6]++;
	if (card->getHandsNeeded() == 2)
		this->equipLimits[6] += 2;

	if ((card->getHiddenItem()) || card->getWild())
		this->equipLimits[5]++;
	
	for (int i = 0; i < 5; ++i)
	{
		if (card->getType() == typesEquipped[i])
		{
			this->equipLimits[i]++;

			if (((i == 0) || (i == 1) || (i == 2) || (i == 3) || (i == 4)) && (equipLimits[i] > 1))
			{
				cout << "\nYou cannot have more than one " << card->getType() << " card equipped.\n";
				this->equipLimits[i]--;
				this->unequip(card);
				this->setUnequipped(true);
			}
		}
	}

	if ((equipLimits[5] > 2) && (!isLoaded))
	{
		cout << "\nYou cannot have more than two Wild or Hidden Item cards equipped.\n";
		this->equipLimits[5]--;
		this->unequip(card);
		this->setUnequipped(true);
	}
	if ((equipLimits[6] > 2) && (!isLoaded))
	{
		cout << "\nYou cannot have cards equipped that take more than two hands of your fighter.\n";
		this->unequip(card);
		this->setUnequipped(true);
	}

	if ((!getUnequipped()) && (!isLoaded))
		cout << "\n" << this->getName() << " has equipped " << card->getTitle() << "\n";

	for (size_t i = 0; i < equippedCards.size(); ++i)
		if (!specialRequirements(equippedCards[i]))
		{
			cout << "\n" << name << " no longer meets the requirements to have " << equippedCards[i]->getTitle() << " equipped.\n";
			this->unequip(equippedCards[i]);
		}

	if ((!getUnequipped()) && (card->hasImmediatelyPower()) && (!isLoaded))
	{
		cout << "\nExecute " << card->getTitle() << "'s power now:\n";
		cout << card->getPower() << endl;
	}


	if ((card->needAttachCard) && (!isLoaded))
	{
		string attachedName = "";
		string attachedName2 = "";

		while (!cardFound)
		{
			if (card->getTitle() == "Ancient Tradition")
			{
				string tempTitle = "";

				if ((this->equipLimits[1] > 0) || (this->equipLimits[6] > 0))
				{
					cout << "\n" << this->getName() << " already has a Class and/or Weapon card(s) equipped. Would you like to equip " << card->getTitle() << " anyway? (Y/N)  ";
					if (choiceYN() == 'N')
					{
						this->unequip(card);
						return;
					}
				}
tryAgain:
				if (this->equipLimits[6] > 1)
				{
					cout << "\n" << this->getName() << " already has 2 hands equipped and cannot attach a weapon to Ancient Tradition.\n";
					goto cl;
				}

				cout << "\nAttach a weapon card to Ancient Tradition: ";
				getline(cin, tempTitle);

				if (tempTitle == "Magic Staff")
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
						if (this->equipLimits[6] > 1)
						{
							cout << "\n" << this->getName() << " cannot equip more than 2 hands.\n\nWould you like to try another Weapon? (Y/N)  ";
							if (choiceYN() == 'N')
							{
								this->unequip(card);
								return;
							}
							else
								goto tryAgain;
						}

						card->addAttachedCard(weapons[8]);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += weapons[8]->bonuses[i];
						this->equipLimits[6]++;

					}
					else if (oneOrTwo == 2)
					{
						if (this->equipLimits[6] > 0)
						{
							cout << "\n" << this->getName() << " cannot equip more than 2 hands.\n\nWould you like to try another Weapon? (Y/N)  ";
							if (choiceYN() == 'N')
							{
								this->unequip(card);
								return;
							}
							else
								goto tryAgain;
						}

						card->addAttachedCard(weapons[9]);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += weapons[9]->bonuses[i];
						this->equipLimits[6] += 2;
					}
				}

				for (auto &wcard : weapons)
				{
					if ((tempTitle == wcard->getTitle()) && (tempTitle != "Magic Staff"))
					{
						if (this->equipLimits[6] + wcard->getHandsNeeded() > 2)
						{
							cout << "\n" << this->getName() << " cannot equip more than 2 hands.\n\nWould you like to try another Weapon? (Y/N)  ";
							if (choiceYN() == 'N')
							{
								this->unequip(card);
								return;
							}
							else
								goto tryAgain;
						}

						card->addAttachedCard(wcard);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += wcard->bonuses[i];

						if (wcard->getHandsNeeded() == 1)
							this->equipLimits[6]++;
						if (wcard->getHandsNeeded() == 2)
							this->equipLimits[6] += 2;

						attachedName = tempTitle;
					}
				}
cl:
				if (this->equipLimits[1] > 0)
				{
					cout << "\n" << this->getName() << " already has another Class card equipped. You cannot attach a Class card to " << card->getTitle() << ".\n";
					break;
				}

				cout << "\nWhich Class card would you like to attach to " << card->getTitle() << ": ";
				getline(cin, tempTitle);

				for (auto &cl : classes)
				{
					if (tempTitle == cl->getTitle())
					{
						card->addAttachedCard(cl);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += cl->bonuses[i];

						this->equipLimits[1]++;
					}
				}
				attachedName2 = tempTitle;
				cardFound = true;
			}

			if (card->getTitle() == "Armor Mastery")
			{
				string tempTitle = "";

				if (this->equipLimits[4] > 0)
				{
					cout << "\n" << this->getName() << " already has an Armor card equipped. Would you like to equip " << card->getTitle() << " anyway? (Y/N)  ";
					if (choiceYN() == 'N')
					{
						this->unequip(card);
						this->equipLimits[4]++;
						return;
					}
					else
						return;
				}

				cout << "\nAttach an armor card to Armor Mastery: ";
				getline(cin, tempTitle);
				for (auto &acard : armor)
				{
					if (tempTitle == acard->getTitle())
					{
						card->addAttachedCard(acard);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += acard->bonuses[i];
						this->equipLimits[4]++;
					}
				}
				attachedName = tempTitle;
				cardFound = true;

			}

			if (card->getTitle() == "Battle Mage")
			{
				cout << "This program has no Combat cards yet.";
				cardFound = true;

			}

			if (card->getTitle() == "Champion")
			{
				string tempTitle = "";
				cout << "\nAttach a mastery card to Champion: ";
				getline(cin, tempTitle);
				for (auto &acard : mastery)
				{
					if (tempTitle == acard->getTitle())
					{
						card->addAttachedCard(acard);
						for (int i = 0; i < bonusSize; ++i)
							this->bonuses[i] += acard->bonuses[i];
					}
				}
				attachedName = tempTitle;
				cardFound = true;

			}

			if (card->getTitle() == "Independently Studied")
			{
				cout << "\nWould you like to gain +2 to a stat of your choice? (Y/N): ";
				char answer;
				cin >> answer;
				while (!(cin) || ((answer != 'Y') && (answer != 'N')))
				{
					cout << "Please answer with Y or N: ";
					cin.clear();
					cin.ignore();
					cin >> answer;
				}
				cin.ignore(CHAR_MAX, '\n');
				if (answer == 'Y')
				{
					cout << "\nWhich stat type would like to gain +2: ";
					string tempStat = "";
					getline(cin, tempStat);
					while ((tempStat != "Magic") && (tempStat != "Agility") && (tempStat != "Physical"))
					{
						cout << "Please type \'Magic\', \'Agility\' or \'Physical\': ";
						getline(cin, tempStat);
					}
					if (tempStat == "Magic")
					{
						this->bonuses[0] += 2;
						card->gainMagic = true;
						cout << "\n" << this->name << " has +2 Magic stats.\n";
					}
					if (tempStat == "Agility")
					{
						this->bonuses[1] += 2;
						card->gainAgility = true;
						cout << "\n" << this->name << " has +2 Agility stats.\n";
					}
					if (tempStat == "Physical")
					{
						this->bonuses[2] += 2;
						card->gainPhysical = true;
						cout << "\n" << this->name << " has +2 Physical stats.\n";
					}

					card->gainStats = true;
				}
				if (answer == 'N')
				{
					string tempTitle = "";
					cout << "\nAttach a mastery card to Independently Studied: ";
					getline(cin, tempTitle);
					for (auto &acard : mastery)
					{
						if (tempTitle == acard->getTitle())
						{
							card->addAttachedCard(acard);
							for (int i = 0; i < bonusSize; ++i)
								this->bonuses[i] += acard->bonuses[i];
						}
					}
					card->gainMastery = true;
					attachedName = tempTitle;
				}
				cardFound = true;

			}

			if (card->getTitle() == "Prodigy")
			{
				cout << "\nWhich Stat card did you draw first from the [S] deck: ";
				for (int i = 0; i <= 3; ++i)
				{
					string tempStat = "";
					getline(cin, tempStat);
					while ((tempStat != "Magic Stat") && (tempStat != "Agility Stat") && (tempStat != "Physical Stat"))
					{
						cout << "Please type \'Magic Stat\', \'Agility Stat\' or \'Physical Stat\': ";
						getline(cin, tempStat);
					}
					if (tempStat == "Magic Stat")
					{
						card->addAttachedCard(stat[0]);
						this->bonuses[0]++;
						cout << "\n" << tempStat << " has been attached to " << card->getTitle() << endl;
					}
					if (tempStat == "Agility Stat")
					{
						card->addAttachedCard(stat[1]);
						this->bonuses[1]++;
						cout << "\n" << tempStat << " has been attached to " << card->getTitle() << endl;
					}
					if (tempStat == "Physical Stat")
					{
						card->addAttachedCard(stat[2]);
						this->bonuses[2]++;
						cout << "\n" << tempStat << " has been attached to " << card->getTitle() << endl;
					}
					if (i != 3)
						cout << "\nWhat's another Stat card drew from the [S] deck: ";
				}
				cardFound = true;
			}
			if ((cardFound) && (card->getTitle() != "Prodigy") || (attachedName == ""))
			{
				if (attachedName == "")
					cout << "\n" << attachedName2 << " has been attached to " << card->getTitle() << endl;
				else
					cout << "\n" << attachedName << " has been attached to " << card->getTitle() << endl;
				break;
			}
			else if ((cardFound) && (card->getTitle() == "Ancient Tradition"))
			{
				cout << "\n" << attachedName << " and " << attachedName2 << " have been attached to " << card->getTitle() << endl;
				break;
			}
			else if ((cardFound) && (card->getTitle() == "Prodigy"))
				break;

			cout << "\nPlease type the title of the card you wish to attach to " << card->getTitle();

		}
	}
}

void Player::displayBonuses()
{
	if (!equippedCards.empty())
	{
		cout << "\nHands Used: " << equipLimits[6] << "\n";

		cout << "\nYour bonuses total: \n";
		for (int i = 0; i < bonusSize; ++i)
		{
			if (bonuses[i] == 0)
				continue;
			else
				cout << bonusNames[i] << ": " << bonuses[i] << endl;
		}
	}
}

void Player::displayCards()
{
	vector<string> temp = {};

	if (equippedCards.empty())
		cout << "\n" << name << " has no cards equipped." << endl;
	else
		cout << "\n" << name << " has " << this->equippedCards.size() << " cards equipped:\n";


	for (vector<Card*>::const_iterator i = equippedCards.begin(); i != equippedCards.end(); ++i)
	{
		int counter = 0;
		
		for (size_t z = 0; z < equippedCards.size(); ++z)
		{
			if (equippedCards[z]->getTitle() == (*i)->getTitle())
				counter++;
		}
		
		if (find(temp.begin(), temp.end(), (*i)->getTitle()) != temp.end())
			continue;
		else
			temp.push_back((*i)->getTitle());

		if ((counter <= 1) && (i != equippedCards.begin()))
			cout << ", " << (*i)->getTitle();
		else if (i == equippedCards.begin())
		{
			cout << (*i)->getTitle();
			if (counter > 1)
				cout << " (x" << counter << ")";

		}
		else if ((counter >= 2) && (i != equippedCards.begin()))
		{
			cout << ", " << (*i)->getTitle();
			if (counter > 1)
				cout << " (x" << counter << ")";
		}

		if ((*i)->gainStats)
		{
			if ((*i)->gainMagic)
				cout << " (Magic +2)";
			if ((*i)->gainAgility)
				cout << " (Agility +2)";
			if ((*i)->gainPhysical)
				cout << " (Physical +2)";
		}

		if ((*i)->attachedCards.size() > 0)
		{
			vector<string> attachedCardTitles = {};

			cout << " (Attached: ";
			for (vector<Card*>::const_iterator j = (*i)->attachedCards.begin(); j != (*i)->attachedCards.end(); ++j)
			{
				int attachedCounter = 0;

				if (find(attachedCardTitles.begin(), attachedCardTitles.end(), (*j)->getTitle()) != attachedCardTitles.end())
					continue;
				else
					attachedCardTitles.push_back((*j)->getTitle());

				for (size_t t = 0; t < (*i)->attachedCards.size(); ++t)
				{
					if ((*i)->attachedCards[t]->getTitle() == (*j)->getTitle())
						attachedCounter++;
				}

				if (j == (*i)->attachedCards.begin())
				{
					cout << (*j)->getTitle();
					if (attachedCounter > 1)
						cout << " (x" << attachedCounter << ")";
				}
				else if ((attachedCounter <= 1) && (j != (*i)->attachedCards.begin()))
					cout << ", " << (*j)->getTitle();
				else if ((attachedCounter >= 2) && (j != (*i)->attachedCards.begin()))
				{
					cout << ", " << (*j)->getTitle();
					if (attachedCounter > 1)
						cout << " (x" << attachedCounter << ")";
				}

			}
			
			cout << ")";
		}
	}
}


void Player::displayPowers()
{
	vector<string> powerCheck = {};
	vector<Card*> automaticPowers = {};
	vector<Card*> activatePowers = {};
	vector<Card*> otherPowers = {};

	if (this->equippedCards.size() == 0)
		return;


	for (vector<Card*>::const_iterator i = equippedCards.begin(); i != equippedCards.end(); ++i)
	{
		if ((*i)->getPowerType() == "Automatic - ")
		{
			automaticPowers.push_back((*i));
		}
		else if ((*i)->getPowerType() == "Activate - ")
		{
			activatePowers.push_back((*i));
		}
		else if ((*i)->getPowerType() == "&")
		{
			continue;
		}
		else if ((*i)->getPowerType() == "")
		{
			otherPowers.push_back((*i));
		}

		for (vector<Card*>::const_iterator j = (*i)->attachedCards.begin(); j != (*i)->attachedCards.end(); ++j)
		{
			if ((*j)->getPowerType() == "Automatic - ")
			{
				automaticPowers.push_back((*j));
			}
			else if ((*j)->getPowerType() == "Activate - ")
			{
				activatePowers.push_back((*j));
			}
			else if ((*j)->getPowerType() == "")
			{
				otherPowers.push_back((*j));
			}
		}
	}

	if (automaticPowers.size() > 0)
	{
		cout << "Automatic Powers - \n\n";
		for (auto &power : automaticPowers)
			cout << "\t(" << power->getTitle() << ")\n\t" << power->getPower() << "\n\n";
	}


	if (activatePowers.size() > 0)
	{
		cout << "Activate Powers - \n\n";
		for (auto &power : activatePowers)
			cout << "\t(" << power->getTitle() << ")\n\t" << power->getPower() << "\n\n";
	}


	if (otherPowers.size() > 0)
	{
		//Skip this section if all other powers are blank
		int i = 0;

		for (size_t z = 0; z != otherPowers.size(); ++z)
		{
			if (otherPowers[z]->getPower() != "")
			{
				i++;
				continue;
			}
		}
		if (i == 0)
			return;

		//If your fighter does have cards with other powers equipped
		cout << "Other Combat Powers - \n\n";

		for (vector<Card*>::const_iterator card = otherPowers.begin(); card != otherPowers.end(); ++card)
		{
			int counter = 0;

			if ((*card)->getPower() == "")
				continue;

			for (size_t i = 0; i < otherPowers.size(); ++i)
			{
				if (otherPowers[i]->getTitle() == (*card)->getTitle())
					counter++;
			}

			if (find(powerCheck.begin(), powerCheck.end(), (*card)->getTitle()) != powerCheck.end())
				continue;
			else
				powerCheck.push_back((*card)->getTitle());

			if (card == otherPowers.begin())
			{
				if (counter > 1)
				{
					cout << "\t(x" << counter << ", " << (*card)->getTitle() << ")\n\t" << (*card)->getPower() << "\n\n";
				}
				else
					cout << "\t(" << (*card)->getTitle() << ")\n\t" << (*card)->getPower() << "\n\n";

			}
			else if ((counter <= 1) && (card != otherPowers.begin()))
				cout << "\t(" << (*card)->getTitle() << ")\n\t" << (*card)->getPower() << "\n\n";
			else if ((counter > 1) && (card != otherPowers.begin()))
			{
				if (counter > 1)
					cout << "\t(x" << counter << ", " << (*card)->getTitle() << ")\n\t" << (*card)->getPower() << "\n\n";
			}
		}
	}
}


void Player::unequip(Card* card)
{
	vector<Card*>::const_iterator position = find(equippedCards.begin(), equippedCards.end(), card);
	
	if (position != equippedCards.end())
	{		
		if (card->getHandsNeeded() == 1)
			equipLimits[6]--;
		if (card->getHandsNeeded() == 2)
			equipLimits[6] -= 2;
		if (card->getTitle() == "Armor Mastery")
			equipLimits[4]--;
		for (int i = 0; i < typesSize; ++i)
		{
			if (card->getType() == typesEquipped[i])
				equipLimits[i]--;
			else
				continue;
		}
		
		for (int i = 0; i < bonusSize; ++i)
			this->bonuses[i] -= card->bonuses[i];
		
		equippedCards.erase(position);

		cout << "\n" << name << " has unequipped " << card->getTitle() << endl;
	}
	else
		cout << "";
		
	
	//Checks to see if player still meets equip requirements for cards already equipped.
	for (size_t i = 0; i < equippedCards.size(); ++i)
	{
		if ((!checkEquipRequirements(equippedCards[i])) || (!specialRequirements(equippedCards[i])))
		{
			cout << "\n" << name << " no longer meets the requirements to have " << equippedCards[i]->getTitle() << " equipped.\n";
			unequip(equippedCards[i]);
		}
	}

	//Removes bonuses gained from Independently Studied
	if (card->getTitle() == "Independently Studied")
	{
		if (card->gainStats)
		{
			if (card->gainMagic)
			{
				this->bonuses[0] -= 2;
				card->gainMagic = false;
			}
			if (card->gainAgility)
			{
				this->bonuses[1] -= 2;
				card->gainAgility = false;
			}
			if (card->gainPhysical)
			{
				this->bonuses[2] -= 2;
				card->gainPhysical = false;
			}
		}
	}

	//Removes attached cards
	for (vector<Card*>::const_iterator attachIter = card->attachedCards.begin(); attachIter != card->attachedCards.end(); ++attachIter)
	{
		for (int j = 0; j < bonusSize; ++j)
			this->bonuses[j] -= ((*attachIter))->bonuses[j];

		if ((*attachIter)->getHandsNeeded() == 1)
			this->equipLimits[6]--;
		if ((*attachIter)->getHandsNeeded() == 2)
			this->equipLimits[6] -= 2;
		
		if ((*attachIter)->getType() == "Class")
			this->equipLimits[1]--;

//		if ((*attachIter)->getType() == "Armor")
//			this->equipLimits[4]--;

	}
	card->attachedCards.clear();
}
