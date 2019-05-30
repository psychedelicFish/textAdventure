#include "Footwear.h"
#include <time.h>

#pragma region Feet

std::string Footwear::GetName()
{
	return Name;
}

void Footwear::SetName(std::string name)
{
	Name = name;
}

Footwear::Footwear(int itemLevel)
{
	TypeOfItem = FootwearItem;
	//DefenceModifier = (rand() % 10 + 1) * itemLevel;
	SpeedModifier = (rand() % 10 + 1) * itemLevel;
	
	int TypeSelector = rand() % 4;

	switch (TypeSelector)
	{
	case 0:
		TypeOfFootwear = Boots;//{Boots, Sneakers, Sandles, Crocs};
	case 1:
		TypeOfFootwear = Sneakers;
		break;
	case 2:
		TypeOfFootwear = Sandles;
		break;
	case 3:
		TypeOfFootwear = Crocs;
		break;
	}

	GenerateName();
}

void Footwear::GenerateName()
{
	std::string temp_name;
	int NameEndingSelector = rand() % 5;

	if (TypeOfFootwear == 0)
	{
		temp_name = "Boots " + FootwearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfFootwear == 1)
	{
		temp_name = "Sneakers " + FootwearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfFootwear == 2)
	{
		temp_name = "Sandles " + FootwearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfFootwear == 3)
	{
		temp_name = "Crocs " + FootwearNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
}
void Footwear:: Equip(Player& player)
{
	if (!isEquipped)
	{
		isEquipped = true;
		player.AffectDefence(SpeedModifier);
	}
}
void Footwear:: Unequip(Player& player)
{
	if (isEquipped)
	{
		isEquipped = false;
		player.AffectDefence(-1 * SpeedModifier);
	}
}

#pragma endregion