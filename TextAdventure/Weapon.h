#pragma once
#include <string>
#include "Equipable.h"
class Weapon : public Equipable

{
private:
	std::string Name;
	int AttackModifier;
	//int AttackSpeedModifier;
	enum WeaponType { Sword, Spear, Axe, Bow };

	WeaponType TypeOfWeapon;
	std::string WeaponNameEndings[5] = { "Of Destruction", "Of Flailing", "Of Stabbing", "Of Fighting", "Of Hurting" };

public:

	Weapon(int itemLevel);
	void GenerateName() override;
	std::string GetName() override;
	void SetName(std::string name) override;
	void Equip(Player& player) override;
	void Unequip(Player& player) override;

};