#include "Armour.h"
#include <time.h>

#pragma region Armour

std::string Armour::GetName()
{
	return Name;
}

void Armour::SetName(std::string name)
{
	Name = name;
}


Armour::Armour(int itemLevel)
{
	TypeOfItem = ArmourItem;
	DefenceModifier = (rand() % 10 + 1) * itemLevel;

	int TypeSelector = rand() % 4;

	switch (TypeSelector)
	{
	case 0:
		TypeOfArmour = Plate;
		break;
	case 1:
		TypeOfArmour = Chainmail;
		break;
	case 2:
		TypeOfArmour = Leather;
		break;
	case 3:
		TypeOfArmour = Rags;
		break;
	}

	GenerateName();
}

void Armour::GenerateName()
{
	std::string temp_name;
	int NameEndingSelector = rand() % 5;

	if (TypeOfArmour == 0)
	{
		temp_name = "Plate " + ArmourNameEndings[NameEndingSelector];//Plate, Chainmail, Leather, Rags
		SetName(temp_name);
	}
	if (TypeOfArmour == 1)
	{
		temp_name = "Chainmail " + ArmourNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfArmour == 2)
	{
		temp_name = "Leather " + ArmourNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfArmour == 3)
	{
		temp_name = "Rags " + ArmourNameEndings[NameEndingSelector];
		SetName(temp_name);
	}

}
void Armour:: Equip(Player& player) 
{
	if(!isEquipped)
	{
		isEquipped = true;
		player.AffectDefence(DefenceModifier);
	}
}
void Armour:: Unequip(Player& player) 
{
	if (isEquipped)
	{
		isEquipped = false;
		player.AffectDefence(-1 * DefenceModifier);
	}
}

#pragma endregion