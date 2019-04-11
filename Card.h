#pragma once

class Card
{
protected:



	//Title of the card
	string title;

	//Armor, Core, Class, Mastery, etc.
	string type;
	
	//Which deck card comes from
	string deck;

	//Power
	string power;

	//Symbols
	bool isBladed;
	bool isHiddenItem;
	bool isWild;
	int handsNeeded;

	//Power Types (Immediately, Activate, Automatic)
	bool isImmediatelyPower;
	bool isActivatePower;
	bool isAutomaticPower;
	bool noDisplayPower;

	//Other requirements needed to equip card.
	string otherRequirements;


	//Filler text quote
	string quote;

	//Credit to the artist!
	string artistName;
	
public:
	Card();
	virtual ~Card();

	string getTitle() { return title; }
	void setTitle(string name) { title = name; }

	string getType() { return type; }
	void setType(string cardType) { type = cardType; }

	string getDeck() { return deck; }
	void setDeck(string deckType) { deck = deckType; }

	string getPower() { return power; }
	void setPower(string powerText) { power = powerText; }
	string getPowerType();

	string getQuote() { return quote; }
	void setQuote(string fillerText) { quote = fillerText; }

	string getArtistName() { return artistName; }
	void setArtistName(string name) { artistName = name; }

	int getHandsNeeded() { return handsNeeded; }
	void setHandsNeeded(int num) { handsNeeded = num; }

	bool getBladed() { return isBladed; }
	bool getWild() { return isWild; }
	bool getHiddenItem() { return isHiddenItem; }
	
	//Stats
	//Magic, Agility, Physical, Atk, Defends, Black Defend, Half, Full, Combo
	void addBonuses(string, int);
	string bonusNames[bonusSize] = { "Magic", "Agility", "Physical", "Atk", "Magic Defend", "Agility Defend", "Physical Defend", "Black Defend", "Half", "Full", "Combo" };
	int bonuses[bonusSize] = {};

	void addEquipRequirements(string, int);
	int equipRequirements[requirementSize] = {};

	string getOtherRequirements() { return otherRequirements; }
	void setOtherRequirements(string requirement) { otherRequirements = requirement; }
	
	bool hasImmediatelyPower();
	void displayCardInfo();

	vector<Card*> attachedCards = {};
	void addAttachedCard(Card* card);
	bool needAttachCard;

	//For Independently Studied
	bool gainStats = false;
	bool gainMagic = false;
	bool gainAgility = false;
	bool gainPhysical = false;
	bool gainMastery = false;
	
	bool toDelete = false;
};


class AcademyGraduate : public Card
{
public:
	AcademyGraduate();
	virtual ~AcademyGraduate() {} ;
};

class AncientTradition : public Card
{
public:
	AncientTradition();
	virtual ~AncientTradition() {};
};


class ArmorMastery : public Card
{
public:
	ArmorMastery();
	virtual ~ArmorMastery() {};
};

class BattleMage : public Card
{
public:
	BattleMage();
	virtual ~BattleMage() {};
};

class BladeDancer : public Card
{
public:
	BladeDancer();
	virtual ~BladeDancer() {};
};

class BoostMastery : public Card
{
public:
	BoostMastery();
	virtual ~BoostMastery() {};
};

class Bow : public Card
{
public:
	Bow();
	virtual ~Bow() {};
};

class Buckler : public Card
{
public:
	Buckler();
	virtual ~Buckler() {};
};

class ChainMail : public Card
{
public:
	ChainMail();
	virtual ~ChainMail() {};
};

class Champion : public Card
{
public:
	Champion();
	virtual ~Champion() {};
};

class CombatMastery : public Card
{
public:
	CombatMastery();
	virtual ~CombatMastery() {};
};

class Combatant : public Card
{
public:
	Combatant();
	virtual ~Combatant() {};
};

class CoreAgilityFemale : public Card
{
public:
	CoreAgilityFemale();
	virtual ~CoreAgilityFemale() {};
};

class CoreAgilityMale : public Card
{
public:
	CoreAgilityMale();
	virtual ~CoreAgilityMale() {};
};

class CoreMagicFemale : public Card
{
public:
	CoreMagicFemale();
	virtual ~CoreMagicFemale() {};
};

class CoreMagicMale : public Card
{
public:
	CoreMagicMale();
	virtual ~CoreMagicMale() {};
};

class CorePhysicalFemale : public Card
{
public:
	CorePhysicalFemale();
	virtual ~CorePhysicalFemale() {};
};

class CorePhysicalMale : public Card
{
public:
	CorePhysicalMale();
	virtual ~CorePhysicalMale() {};
};

class Dagger : public Card
{
public:
	Dagger();
	virtual ~Dagger() {};
};

class Duelist : public Card
{
public:
	Duelist();
	virtual ~Duelist() {};
};

class DuelWieldMastery : public Card
{
public:
	DuelWieldMastery();
	virtual ~DuelWieldMastery() {};
};

class ElementalMastery : public Card
{
public:
	ElementalMastery();
	virtual ~ElementalMastery() {};
};

class Elementalist : public Card
{
public:
	Elementalist();
	virtual ~Elementalist() {};
};

class Enforcer : public Card
{
public:
	Enforcer();
	virtual ~Enforcer() {};
};

class FullPlateArmor : public Card
{
public:
	FullPlateArmor();
	virtual ~FullPlateArmor() {};
};

class Gi : public Card
{
public:
	Gi();
	virtual ~Gi() {};
};

class HalfPlateArmor : public Card
{
public:
	HalfPlateArmor();
	virtual ~HalfPlateArmor() {};
};

class IndependentlyStudied : public Card
{
public:
	IndependentlyStudied();
	virtual ~IndependentlyStudied() {};
};

class Katana : public Card
{
public:
	Katana();
	virtual ~Katana() {};
};

class KiteShield : public Card
{
public:
	KiteShield();
	virtual ~KiteShield() {};
};

class KozaneArmor : public Card
{
public:
	KozaneArmor();
	virtual ~KozaneArmor() {};
};

class Mage : public Card
{
public:
	Mage();
	virtual ~Mage() {};
};

class MagicItemMastery : public Card
{
public:
	MagicItemMastery();
	virtual ~MagicItemMastery() {};
};

class MagicRobe : public Card
{
public:
	MagicRobe();
	virtual ~MagicRobe() {};
};

class MagicStaff : public Card
{
public:
	MagicStaff();
	virtual ~MagicStaff() {};
};

class MagicStaffOneHand : public Card
{
public:
	MagicStaffOneHand();
	virtual ~MagicStaffOneHand() {};
};

class MartialArtist : public Card
{
public:
	MartialArtist();
	virtual ~MartialArtist() {};
};

class PaddedArmor : public Card
{
public:
	PaddedArmor();
	virtual ~PaddedArmor() {};
};

class Prodigy : public Card
{
public:
	Prodigy();
	virtual ~Prodigy() {};
};

class Quarterstaff : public Card
{
public:
	Quarterstaff();
	virtual ~Quarterstaff() {};
};

class QuarterstaffMastery : public Card
{
public:
	QuarterstaffMastery();
	virtual ~QuarterstaffMastery() {};
};

class Rondache : public Card
{
public:
	Rondache();
	virtual ~Rondache() {};
};

class Samurai : public Card
{
public:
	Samurai();
	virtual ~Samurai() {};
};

class Scimitar : public Card
{
public:
	Scimitar();
	virtual ~Scimitar() {};
};

class Sorcerer : public Card
{
public:
	Sorcerer();
	virtual ~Sorcerer() {};
};

class SpellwroughtShield : public Card
{
public:
	SpellwroughtShield();
	virtual ~SpellwroughtShield() {};
};

class StaminaMastery : public Card
{
public:
	StaminaMastery();
	virtual ~StaminaMastery() {};
};

class StatAgility : public Card
{
public:
	StatAgility();
	virtual ~StatAgility() {};
};

class StatMagic : public Card
{
public:
	StatMagic();
	virtual ~StatMagic() {};
};

class StatPhysical : public Card
{
public:
	StatPhysical();
	virtual ~StatPhysical() {};
};

class Sword : public Card
{
public:
	Sword();
	virtual ~Sword() {};
};

class Wakizashi : public Card
{
public:
	Wakizashi();
	virtual ~Wakizashi() {};
};

class Wand : public Card
{
public:
	Wand();
	virtual ~Wand() {};
};

class Warder : public Card
{
public:
	Warder();
	virtual ~Warder() {};
};

class WeaponMastery : public Card
{
public:
	WeaponMastery();
	virtual ~WeaponMastery() {};
};
