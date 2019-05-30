#include "Headgear.h"
#include <time.h>

#pragma region Headgear

std::string Headgear::GetName()
{
	return Name;
}

void Headgear::SetName(std::string name)
{
	Name = name;
}

Headgear::Headgear(int itemLevel)
{
	TypeOfItem = HeadgearItem;
	DefenceModifier = (rand() % 10 + 1) * itemLevel;
	
	int TypeSelector = rand() % 4;

	switch (TypeSelector)
	{
	case 0:
		TypeOfHeadgear = Hat;//{Hat, Helmet, Wig, Pot};
		break;
	case 1:
		TypeOfHeadgear = Helmet;
		break;
	case 2:
		TypeOfHeadgear = Wig;
		break;
	case 3:
		TypeOfHeadgear = Pot;
		break;
	}

	GenerateName();

}

void Headgear::GenerateName()
{
	std::string temp_name;
	int NameEndingSelector = rand() % 5;

	if (TypeOfHeadgear == 0)
	{
		temp_name = "Hat " + HeadgearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfHeadgear == 1)
	{
		temp_name = "Healmet " + HeadgearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfHeadgear == 2)
	{
		temp_name = "Wig " + HeadgearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfHeadgear == 3)
	{
		temp_name = "Pot " + HeadgearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}


}
void Headgear::Equip(Player& player)
{
	if (!isEquipped)
	{
		isEquipped = true;
		player.AffectDefence(DefenceModifier);
	}
}
void Headgear::Unequip(Player& player)
{
	if (isEquipped)
	{
		isEquipped = false;
		player.AffectDefence(-1 * DefenceModifier);
	}
}

#pragma endregion