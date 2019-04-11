#include "stdafx.h"
#include "Card.h"


Card::Card() :
	title(""),
	type(""),
	deck(""),
	power(""),
	isBladed(false),
	isHiddenItem(false),
	isWild(false),
	handsNeeded(0),
	isImmediatelyPower(false),
	isActivatePower(false),
	isAutomaticPower(false),
	noDisplayPower(false),
	otherRequirements(""), 
	quote(""),
	needAttachCard(false)

{}

string Card::getPowerType()
{
	if (this->isActivatePower)
	{
		return "Activate - ";
	}
	else if (this->isImmediatelyPower)
	{
		return "Immediately - ";
	}
	else if (this->isAutomaticPower)
	{
		return "Automatic - ";
	}
	else if (this->noDisplayPower)
	{
		return "&";
	}
	else
		return "";
}

void Card::addBonuses(string type, int num)
{
	for (int i = 0; i < bonusSize; ++i)
	{
		if (bonusNames[i] == type)
			bonuses[i] += num;
		else
			continue;
	}
}


void Card::addEquipRequirements(string type, int num)
{
	for (int i = 0; i < requirementSize; ++i)
	{
		if (bonusNames[i] == type)
			equipRequirements[i] += num;
		else
			continue;
	}
}


Card::~Card()
{
}

bool Card::hasImmediatelyPower()
{
	if (isImmediatelyPower == true)
		return true;
	else
		return false;
}


void Card::displayCardInfo()
{
	cout << "\nHere is the all the info on "<< title <<":\n\n";
	cout << "Title: " << title << endl;
	cout << "Card Type: " << type << endl;
	cout << "Deck: " << deck << endl;

	//Hands
	if (handsNeeded > 0)
		cout << "Hands Required: " << handsNeeded << endl;

	//Bonuses
	for (int i = 0; i < bonusSize; ++i)
	{
		int temp = 0;
		if (this->bonuses[i] > 0)
			temp++;
		if (temp > 0)
			break;
		if ((i == (bonusSize-1)) && (temp == 0))
			goto powerText;
	}
	
	cout << "Bonuses: ";

	for (int i = 0; i < bonusSize; ++i)
	{
		if (bonuses[i] == 0)
			continue;
		else
		{
			cout << "\n\t" << bonusNames[i] << " +" << bonuses[i];
		}
	}

	cout << endl;

	//Finding out and listing if the card has an Immediately, Activate or Automatic Power.
powerText:
	if (power == "")
		goto equipReq;
	cout << "Power Text: ";

	//Power
	cout << getPowerType() << power << endl;

equipReq:
	//Equip Requirements
	if ((equipRequirements[0] == 0) && (equipRequirements[1] == 0) && (equipRequirements[2] == 0))
		goto afterRequirements;
	else
	{
		cout << "Requirements: \n";
		for (int i = 0; i < requirementSize; ++i)
		{
			if (equipRequirements[i] == 0)
				continue;
			else
			cout << "\t" << bonusNames[i] << " - " << equipRequirements[i] << endl;
		}
	}

	if (otherRequirements == "")
		goto afterRequirements;
	else
		cout << "\t" << otherRequirements << endl;

afterRequirements:
	//Quote
	if (quote == "")
		goto afterquote;
	else
		cout << "Quote: " << quote << endl;

afterquote:
	cout << "Artist: " << artistName << endl;
}

void Card::addAttachedCard(Card* card)
{
	this->attachedCards.push_back(card);
}



AcademyGraduate::AcademyGraduate()
{
	setTitle("Academy Graduate");
	setType("Origin");
	setDeck("Support");
	setPower("Recycle a combat card.");
	setQuote("\"From this day forth, I shall enforce what is right and strike down what is wrong.\"\n\t\t~Zuberi, The Strong");
	isActivatePower = true;
	setArtistName("Yeevon Ng");
}

AncientTradition::AncientTradition()
{
	setTitle("Ancient Tradition");
	setType("Origin");
	setDeck("Support");
	setPower("Search and attach a Weapon card. Attach a Class card, regardless of any stat requirement(s). All other requirements still apply. You cannot equip an additional Class card.");
	isImmediatelyPower = true;
	noDisplayPower = true;
	needAttachCard = true;
	setArtistName("Libertad Delgado");
}

ArmorMastery::ArmorMastery()
{
	setTitle("Armor Mastery");
	setType("Mastery");
	setDeck("Physical");
	setPower("Search and attach an Armor card. It can be equipped without meeting its requirements.");
	isImmediatelyPower = true;
	noDisplayPower = true;
	needAttachCard = true;
	addBonuses("Black Defend", 1);
	setArtistName("Yana Dmitruk");
}

BattleMage::BattleMage()
{
	setTitle("Battle Mage");
	setType("Class");
	setDeck("Class");
	setPower("Attach the top 2 combat cards from the [M] and [P] decks face-down.");
	isImmediatelyPower = true;
	noDisplayPower = true;
	needAttachCard = true;
	addBonuses("Full", 1);
	addEquipRequirements("Physical", 6);
	addEquipRequirements("Magic", 6);
	setArtistName("Nakarin Sukontakorn");
}

BladeDancer::BladeDancer()
{
	setTitle("Blade Dancer");
	setType("Class");
	setDeck("Class");
	setPower("IF: Your Attack is blocked.  Inflict 5 [A] damage to the same target to each [Bladed] weapon used.");
	addBonuses("Agility", 2);
	addEquipRequirements("Agility", 12);
	addEquipRequirements("Physical", 4);
	setOtherRequirements("A [Bladed] weapon is also required.");
	setArtistName("Alena Swan");
}

BoostMastery::BoostMastery()
{
	setTitle("Boost Mastery");
	setType("Mastery");
	setDeck("Support");
	setPower("Search and use a Combat Boost card not from the [S] deck.");
	isActivatePower = true;
	addBonuses("Half", 1);
	addBonuses("Full", 1);
	setArtistName("Pedro Ferreira");
}

Bow::Bow()
{
	setTitle("Bow");
	setType("Weapon");
	setDeck("Agility");
	setPower("All Attacks gain First Strike.");
	addBonuses("Agility", 6);
	addBonuses("Physical", 4);
	handsNeeded = 2;
	setQuote("\"You think you are stronger?! Perhaps. But you will NEVER be faster!\"\n\t\t~Edmund, The Quick");
	setArtistName("Laura Spear");
}

Buckler::Buckler()
{
	setTitle("Buckler");
	setType("Shield");
	setDeck("Agility");
	setPower("Block [A] and [P] attacks.  IF: Successful.  Execute a Half [A] Attack.");
	isActivatePower = true;
	addBonuses("Agility Defend", 1);
	handsNeeded = 1;
	setArtistName("Sam Perrin");
}

ChainMail::ChainMail()
{
	setTitle("Chain Mail");
	setType("Armor");
	setDeck("Physical");
	addBonuses("Magic Defend", 1);
	addBonuses("Agility Defend", 2);
	addBonuses("Physical Defend", 2);
	addEquipRequirements("Physical", 7);
	setQuote("\"You can't make me bleed if you hever break my skin. Give it your best shot!\"\n\t\t~Brianna, The Defender");
	setArtistName("Afda Trihatma");
}

Champion::Champion()
{
	setTitle("Champion");
	setType("Class");
	setDeck("Class");
	setPower("Search and attach a Mastery card.");
	isImmediatelyPower = true;
	noDisplayPower = true;
	needAttachCard = true;
	addBonuses("Atk", 1);
	addBonuses("Full", 1);
	addEquipRequirements("Agility", 9);
	addEquipRequirements("Physical", 5);
	setQuote("\"The crowd's cheer is my triumph!\"\n\t\t~Vaena, The Victorious");
	setArtistName("David Lojaya");
}

CombatMastery::CombatMastery()
{
	setTitle("Combat Mastery");
	setType("Mastery");
	setDeck("Support");
	setPower("Declare [M] +2, [A] +2 or [P] +2.  IF: Your attack is blocked.  Once per round, execute a Half Attack of a stat type of your choice to the same target.");
	isAutomaticPower = true;
	setArtistName("Uracil");
}

Combatant::Combatant()
{
	setTitle("Combatant");
	setType("Class");
	setDeck("Class");
	setPower("Execute a Full [P] Attack.");
	isActivatePower = true;
	addBonuses("Physical", 1);
	setOtherRequirements("You have only drawn from the [P] or [S] decks during Phase 1.");
	setArtistName("Diego Gisbert Llorens");
}

CoreAgilityFemale::CoreAgilityFemale()
{
	setTitle("Female Agility");
	setType("Core");
	setDeck("Core");
	addBonuses("Agility", 1);
	setQuote("\"Practice your skills and hone them as you would a blade. The results will be your greatest weapon.\"\n\t\t~Kamaria, The Gifted");
	setArtistName("Christopher Onciu");
}

CoreAgilityMale::CoreAgilityMale()
{
	setTitle("Male Agility");
	setType("Core");
	setDeck("Core");
	setQuote("\"Quick to strike means quick to win!\"\n\t\t~Edmund, The Quick");
	setArtistName("Christopher Onciu");
}

CoreMagicFemale::CoreMagicFemale()
{
	setTitle("Female Magic");
	setType("Core");
	setDeck("Core");
	addBonuses("Magic", 1);
	setQuote("\"Harness your inner light. Let it shine over your enemies and blind them with your greatness.\"\n\t\t~Saniya, The Powerful");
	setArtistName("Christopher Onciu");
}

CoreMagicMale::CoreMagicMale()
{
	setTitle("Male Magic");
	setType("Core");
	setDeck("Core");
	addBonuses("Magic", 1);
	setQuote("\"Seize this opportunity to achieve greater wisdom and understanding. Let your magical essence guide your path.\"\n\t\t~Haydn, The Mystical");
	setArtistName("Christopher Onciu");
}

CorePhysicalFemale::CorePhysicalFemale()
{
	setTitle("Female Physical");
	setType("Core");
	setDeck("Core");
	addBonuses("Physical", 1);
	setQuote("\"Do not worry about the power of others. Your stength is more than enough to handle anything or anyone thrown at you.\"\n\t\t~Runa, The Mighty");
	setArtistName("Christopher Onciu");
}

CorePhysicalMale::CorePhysicalMale()
{
	setTitle("Male Physical");
	setType("Core");
	setDeck("Core");
	addBonuses("Physical", 1);
	setQuote("\"Strength and courage are the two greatest traits one could possess. Proudly face your fears and then beat those fears to a pulp.\"\n\t\t~Zuberi, The Strong");
	setArtistName("Christopher Onciu");
}

Dagger::Dagger()
{
	setTitle("Dagger");
	setType("Weapon");
	setDeck("Agility");
	handsNeeded = 1;
	isBladed = true;
	isHiddenItem = true;
	addBonuses("Agility", 3);
	addBonuses("Physical", 2);
	addBonuses("Combo", 1);
	setPower("Discard to execute a Full [A] Attack. Dagger can be in your [Wild] slot. All all your [A] bonuses to this attack.");
	isActivatePower = true;
	setQuote("\"You didn't see my hidden blade? That is why you failed.\"\n\t\t~Evelyn, The Deadly");
	setArtistName("Ashley Ramos");
}

Duelist::Duelist()
{
	setTitle("Duelist");
	setType("Class");
	setDeck("Class");
	addBonuses("Agility", 1);
	addBonuses("Half", 1);
	setPower("Draw and use a card from the [M], [A] or [P] decks. Execute a Half [A] Attack if the drawn card is not a combat card.");
	isActivatePower = true;
	addEquipRequirements("Agility", 6);
	setOtherRequirements("Either [M]6 or [P]6 is required.");
	setArtistName("Katrina Lee");
}

DuelWieldMastery::DuelWieldMastery()
{
	setTitle("Duel-Wield Mastery");
	setType("Mastery");
	setDeck("Agility");
	addBonuses("Atk", 1);
	addBonuses("Combo", 1);
	setPower("IF: Using two or more weapons.  All of your Half Attacks are Full Attacks. Use either your Half or Full bonuses for your Full Attacks.");
	setArtistName("Leadpanda");
}

ElementalMastery::ElementalMastery()
{
	setTitle("Elemental Mastery");
	setType("Mastery");
	setDeck("Magic");
	addBonuses("Magic", 2);
	setPower("Once per round, give a [M] Attack [First Strike].");
	setQuote("\"Take control of the natural forces within your environment and you will obtain true power!\"\n\t\t~Saniya, The Powerful");
	setArtistName("Gloria Kang");
}

Elementalist::Elementalist()
{
	setTitle("Elementalist");
	setType("Class");
	setDeck("Class");
	addBonuses("Magic", 1);
	setPower("Draw the top [M] combat card from your discard pile into your hand.");
	isActivatePower = true;
	addEquipRequirements("Magic", 11);
	addEquipRequirements("Agility", 5);
	setArtistName("Francis Tneh");
}

Enforcer::Enforcer()
{
	setTitle("Enforcer");
	setType("Class");
	setDeck("Class");
	addBonuses("Half", 2);
	setPower("Immediately execute a Half [M] Attack.  Discard a combat card from your hand to gain Atk +5 until the end of the round.");
	isActivatePower = true;
	addEquipRequirements("Physical", 7);
	addEquipRequirements("Magic", 5);
	setArtistName("Albert Chauw Wijaya");
}

FullPlateArmor::FullPlateArmor()
{
	setTitle("Full-Plate Armor");
	setType("Armor");
	setDeck("Physical");
	addBonuses("Magic Defend", 2);
	addBonuses("Agility Defend", 4);
	addBonuses("Physical Defend", 3);
	addEquipRequirements("Physical", 10);
	setQuote("\"I let my armor embrace and protect me. That way, my sole focus is on bringing down my enemies!\"\n\t\t~Runa, The Mighty");
	setArtistName("José Arias");
}

Gi::Gi()
{
	setTitle("Gi");
	setType("Armor");
	setDeck("Agility");
	addBonuses("Agility", 1);
	addBonuses("Combo", 1);
	setPower("After your first action of the round, gain [A] +1 until the end of the round.");
	isAutomaticPower = true;
	setArtistName("Ocire");
}

HalfPlateArmor::HalfPlateArmor()
{
	setTitle("Half-Plate Armor");
	setType("Armor");
	setDeck("Physical");
	addBonuses("Magic Defend", 1);
	addBonuses("Agility Defend", 3);
	addBonuses("Physical Defend", 3);
	setQuote("\"With this armor, I worry not about my enemies as I dance around them.\"\n\t\t~Kamaria, The Gifted");
	addEquipRequirements("Physical", 8);
	setArtistName("Laura Galli");
}

IndependentlyStudied::IndependentlyStudied()
{
	setTitle("Independently Studied");
	setType("Origin");
	setDeck("Support");
	setPower("Delcare a stat type. Gain +2 of the chosen stat type.  OR  Search and attach a Mastery card.");
	isImmediatelyPower = true;
	noDisplayPower = true;
	needAttachCard = true;
	setArtistName("Mimi N.");
}

Katana::Katana()
{
	setTitle("Katana");
	setType("Weapon");
	setDeck("Physical");
	handsNeeded = 2;
	isBladed = true;
	addBonuses("Physical", 8);
	addBonuses("Agility", 6);
	addBonuses("Half", 1);
	setQuote("\"I strike so quickly and fiercely, my katana is hardly seen unsheathed!.\"\n\t\t~Kamaria, The Gifted");
	setArtistName("SiqNO");
}

KiteShield::KiteShield()
{
	setTitle("Kite Shield");
	setType("Shield");
	setDeck("Physical");
	handsNeeded = 1;
	addBonuses("Magic Defend", 2);
	addBonuses("Agility Defend", 1);
	addBonuses("Physical Defend", 2);
	addEquipRequirements("Physical", 5);
	setQuote("\"In battle, only a big shield keeps a big man strong! Anything else will keep you dead.\"\n\t\t~Jiang, The Resolute");
	setArtistName("Kurosaki Keroro");
}

KozaneArmor::KozaneArmor()
{
	setTitle("Kozane Armor");
	setType("Armor");
	setDeck("Physical");
	addBonuses("Magic Defend", 2);
	addBonuses("Agility Defend", 2);
	addBonuses("Physical Defend", 3);
	setPower("IF: Using Wakizashi, Katana or Samurai.  Gain Atk +1.");
	addEquipRequirements("Physical", 9);
	setArtistName("Kouchann");
}

Mage::Mage()
{
	setTitle("Mage");
	setType("Class");
	setDeck("Class");
	addBonuses("Magic", 2);
	addBonuses("Full", 2);
	setOtherRequirements("You have only drawn from the [M] or [S] decks during Phase 1.");
	setQuote("\"My power is ablaze and I shall engulf all who dare cross my path!\"\n\t\t~Saniya, The Powerful");
	setArtistName("Rob Joseph");
}

MagicItemMastery::MagicItemMastery()
{
	setTitle("Magic Item Mastery");
	setType("Mastery");
	setDeck("Magic");
	setPower("Every two rounds, gain Atk +1 for every equipped [M] card until the end of the round. Do not include Stat cards or combat cards.");
	isAutomaticPower = true;
	setArtistName("Joe Slucher");
}

MagicRobe::MagicRobe()
{
	setTitle("Magic Robe");
	setType("Armor");
	setDeck("Magic");
	addBonuses("Magic", 1);
	addBonuses("Magic Defend", 1);
	setQuote("\"My robe allows the harmonious flow of energy to strengthen my inner power.\"\n\t\t~Haydn, The Mystical");
	setArtistName("Izaak Moody");
}

MagicStaff::MagicStaff()
{
	setTitle("Magic Staff");
	setType("Weapon");
	setDeck("Magic");
	handsNeeded = 2;
	addBonuses("Magic", 7);
	addBonuses("Physical", 4);
	setPower("IF: [M]7 not from this card.  Declare to equip only [One Hand], changing the bonuses to [M] +4 [P] +2.");
	noDisplayPower = true;
	setArtistName("G.L. Liew");
}

MagicStaffOneHand::MagicStaffOneHand()
{
	setTitle("Magic Staff");
	setType("Weapon");
	setDeck("Magic");
	handsNeeded = 1;
	addBonuses("Magic", 4);
	addBonuses("Physical", 2);
	setPower("IF: [M]7 not from this card.  Declare to equip only [One Hand], changing the bonuses to [M] +4 [P] +2.");
	noDisplayPower = true;
	setArtistName("G.L. Liew");
}

MartialArtist::MartialArtist()
{
	setTitle("Martial Artist");
	setType("Class");
	setDeck("Class");
	addBonuses("Agility", 1);
	setPower("Recycle an [A] combat card.");
	isActivatePower = true;
	setOtherRequirements("You have only drawn from the [A] or [S] decks during Phase 1.");
	setArtistName("Jesika Barinque");
}

PaddedArmor::PaddedArmor()
{
	setTitle("Padded Armor");
	setType("Armor");
	setDeck("Magic");
	addBonuses("Black Defend", 2);
	setQuote("\"I can't tell you how good I look avoiding death!\"\n\t\t~Edmund, The Quick");
	setArtistName("Lorenzo Massaro");
}

Prodigy::Prodigy()
{
	setTitle("Prodigy");
	setType("Origin");
	setDeck("Support");
	setPower("Attach the top 4 Stat cards from the [S] deck.");
	isImmediatelyPower = true;
	needAttachCard = true;
	noDisplayPower = true;
	setQuote("\"Perfection and proficiency comes easily when you're born with greatness.\"\n\t\t~Kamaria, The Gifted");
	setArtistName("Jonas Åkerlund");
}

Quarterstaff::Quarterstaff()
{
	setTitle("Quarterstaff");
	setType("Weapon");
	setDeck("Agility");
	handsNeeded = 2;
	addBonuses("Agility", 8);
	addBonuses("Physical", 4);
	addBonuses("Half", 2);
	setQuote("\"The quarterstaff is the best of both worlds. It allows me to defend my comrades while striking my enemies down before they know what hit them!\"\n\t\t~Brianna, The Defender");
	setArtistName("Savvy Sasquatch Design");
}

QuarterstaffMastery::QuarterstaffMastery()
{
	setTitle("Quarterstaff Mastery");
	setType("Mastery");
	setDeck("Agility");
	addBonuses("Agility", 1);
	addBonuses("Physical", 1);
	setPower("IF: Using a Quarterstaff.  Activate - Block [A] and [P] Attacks.");
	setArtistName("Dane Madgwick");
}

Rondache::Rondache()
{
	setTitle("Rondache");
	setType("Shield");
	setDeck("Physical");
	handsNeeded = 1;
	addBonuses("Black Defend", 1);
	setPower("IF: Executing a Half Block.  Gain [Black Shield]2 for the turn.");
	setQuote("\"A simple shield can save a lot of lives. Well, at least MY life many times.\"\n\t\t~Vaena, The Victorious");
	setArtistName("Antonio Luzano");
}

Samurai::Samurai()
{
	setTitle("Samurai");
	setType("Class");
	setDeck("Class");
	addBonuses("Physical", 1);
	addBonuses("Agility", 1);
	addBonuses("Half", 1);
	setPower("IF: Your Combat Attack is successful.  Once a turn, you may immediately execute an [A] or [P] Combat Attack from your hand to the same target.");
	addEquipRequirements("Physical", 10);
	addEquipRequirements("Agility", 6);
	setOtherRequirements("Katana, Wakizashi or Kozane Armor is also required.");
	setArtistName("Jurikoi");
}

Scimitar::Scimitar()
{
	setTitle("Scimitar");
	setType("Weapon");
	setDeck("Agility");
	addBonuses("Agility", 4);
	addBonuses("Physical", 3);
	isBladed = true;
	handsNeeded = 1;
	setQuote("\"My preference for decapitation is the use of my sharpened scimitar blade. It has yet to fail me.\"\n\t\t~Evelyn, The Deadly");
	setArtistName("Laura Galli");
}

Sorcerer::Sorcerer()
{
	setTitle("Sorcerer");
	setType("Class");
	setDeck("Class");
	addBonuses("Magic", 1);
	setPower("You may change a bonus on any of your equipped weapons to [M]. Gain [M] +1 until the end of the round. Use [M] stats to determine damage.");
	isAutomaticPower = true;
	addEquipRequirements("Magic", 8);
	addEquipRequirements("Agility", 4);
	setArtistName("Darey Dawn");
}

SpellwroughtShield::SpellwroughtShield()
{
	setTitle("Spellwrought Shield");
	setType("Shield");
	setDeck("Magic");
	handsNeeded = 1;
	addBonuses("Magic Defend", 1);
	setPower("Block [M] Attacks. Gain [Agility Shield]5 and [Physical Shield]5 for the turn.");
	isActivatePower = true;
	setQuote("\"I call thine light! Cast your form before me to protect my body and mind from harm!\"\n\t\t~Haydn, The Mystical");
	setArtistName("Mauro Delli Bovi");
}

StaminaMastery::StaminaMastery()
{
	setTitle("Stamina Mastery");
	setType("Mastery");
	setDeck("Support");
	setPower("Heal 5 damage.");
	isAutomaticPower = true;
	setQuote("\"Get back up...push forward...keep going. I can win. I. Will. Win!\"\n\t\t~Zuberi, The Strong");
	setArtistName("Kevin McCoy");
}

StatAgility::StatAgility()
{
	setTitle("Agility Stat");
	setType("Stat");
	setDeck("Agility and Support");
	addBonuses("Agility", 1);
	setPower("IF: You execute a block.  Discard to immediately execute a Half [A] Attack. Add your Full and Half bonuses to this attack.");
	setArtistName("Alandra Morin");
}

StatMagic::StatMagic()
{
	setTitle("Magic Stat");
	setType("Stat");
	setDeck("Magic and Support");
	addBonuses("Magic", 1);
	setPower("IF: All actions are revealed and you and your target are attacking.  Discard to Enhance [M]5.");
	setArtistName("Alandra Morin");
}

StatPhysical::StatPhysical()
{
	setTitle("Physical Stat");
	setType("Stat");
	setDeck("Physical and Support");
	addBonuses("Physical", 1);
	setPower("Discard to immediately execute a Half [P] Attack. This attack gains Half +1 for every 4 [P] stats, rounded down.");
	setArtistName("Alandra Morin");
}

Sword::Sword()
{
	setTitle("Sword");
	setType("Weapon");
	setDeck("Physical");
	handsNeeded = 1;
	isBladed = true;
	addBonuses("Physical", 4);
	addBonuses("Agility", 2);
	addBonuses("Half", 1);
	setQuote("\"I use my sword to bring my enemies down to their knees because they no longer have feet to stand on!\"\n\t\t~Jiang, The Resolute");
	setArtistName("Jon Lankry");
}


Wakizashi::Wakizashi()
{
	setTitle("Wakizashi");
	setType("Weapon");
	setDeck("Physical");
	handsNeeded = 1;
	isBladed = true;
	addBonuses("Physical", 2);
	addBonuses("Agility", 4);
	setPower("Once per round give an [A] Attack [First Strike].");
	setQuote("\"This wakizashi is my most trusted companion. It always finishes what I start.\"\n\t\t~Vaena, The Victorious");
	setArtistName("Rael Mochizuki");
}

Wand::Wand()
{
	setTitle("Wand");
	setType("Weapon");
	setDeck("Magic");
	handsNeeded = 1;
	isHiddenItem = true;
	addBonuses("Magic", 4);
	addBonuses("Full", 1);
	setQuote("\"Some say, the wand is merely a useless stick. I'll show you why this wand is NO MERE STICK!\"\n\t\t~Saniya, The Powerful");
	setArtistName("Leadpanda");
}

Warder::Warder()
{
	setTitle("Warder");
	setType("Class");
	setDeck("Class");
	addBonuses("Black Defend", 1);
	setPower("Twice per round, the [M] and [P] Combat Attack cards from your hand can instead be used to block all attacks for a turn.");
	addEquipRequirements("Physical", 8);
	addEquipRequirements("Magic", 8);
	setArtistName("Dimas Wijil Pamungkas");
}

WeaponMastery::WeaponMastery()
{
	setTitle("Weapon Mastery");
	setType("Mastery");
	setDeck("Physical");
	setPower("Gain Atk +1 for every weapon equipped.  IF: [Wild] is revealed and is a weapon.  Gain Combo +1.");
	setArtistName("Brian Brinlee");
}
