#include "Weapon.h"
#include <time.h>

#pragma region Weapon

std::string Weapon::GetName()
{
	return Name;
}

void Weapon::SetName(std::string name)
{
	Name = name;
}
Weapon::Weapon(int itemLevel)
{
	TypeOfItem = WeaponItem;
	AttackModifier = rand() % 10 * itemLevel;
	//AttackSpeedModifier = rand() % 10 * itemLevel;
	int TypeSelector = rand() % 4;

	switch (TypeSelector)
	{
	case 0:
		TypeOfWeapon = Sword;
		break;
	case 1:
		TypeOfWeapon = Spear;
		break;
	case 2:
		TypeOfWeapon = Axe;
		break;
	case 3:
		TypeOfWeapon = Bow;
		break;
	}

	GenerateName();
}

void Weapon::GenerateName()
{
	std::string temp_name;
	int NameEndingSelector = rand() % 5;

	if (TypeOfWeapon == 0)
	{
		temp_name = "Sword " + WeaponNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfWeapon == 1)
	{
		temp_name = "Spear " + WeaponNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfWeapon == 2)
	{
		temp_name = "Axe " + WeaponNameEndings[NameEndingSelector];
		SetName(temp_name);
	}
	if (TypeOfWeapon == 3)
	{
		temp_name = "Bow " + WeaponNameEndings[NameEndingSelector];
		SetName(temp_name);
	}

}
void Weapon::Equip(Player& player)
{
	if (!isEquipped)
	{
		isEquipped = true;
		player.AffectDefence(AttackModifier);
	}
}
void Weapon::Unequip(Player& player)
{
	if (isEquipped)
	{
		isEquipped = false;
		player.AffectDefence(-1 * AttackModifier);
	}
}
#pragma endregion