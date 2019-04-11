#pragma once
#include "Card.h"

class Player
{
private:
	string name;
	bool isUnequipped;

	string bonusNames[bonusSize] = { "Magic", "Agility", "Physical", "Atk", "Magic Defend", "Agility Defend", "Physical Defend", "Black Defend", "Half", "Full", "Combo" };
	int bonuses[bonusSize] = {};

	string typesEquipped[typesSize] = { "Core", "Class", "Origin", "Mastery", "Armor", "Wild", "Hands" };
	int equipLimits[typesSize] = {};

public:
	Player();
	~Player();

	string getName() { return name; }
	void setName(string n) { name = n; }

	int getBonuses(int);
	void addBonuses(Card*);

	int getEquipLimits(int);
	void addEquipLimits(int, int);

	bool getUnequipped() { return isUnequipped; }
	void setUnequipped(bool unequipped) { isUnequipped = unequipped; }

	bool checkEquipRequirements(Card*);
	bool specialRequirements(Card*);

	void equipCard(Card*, bool);
	void unequip(Card*);

	void displayBonuses();
	void displayCards();
	void displayPowers();

	vector<Card*> equippedCards = {};
	
};
