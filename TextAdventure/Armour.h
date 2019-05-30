#pragma once
#include "Equipable.h"
#include <string>

class Armour : public Equipable
{
private:

	std::string Name;
	int DefenceModifier;
	enum ArmourType { Plate, Chainmail, Leather, Rags };

	ArmourType TypeOfArmour;
	std::string ArmourNameEndings[5] = { "Of Protection", "Of Deflecting", "Of Rags", "Of Dodging", "Of Steel" };
	

public:
	Armour(int itemLevel);
	void GenerateName() override;
	std::string GetName() override;
	void SetName(std::string name) override;
	void Equip(Player& player) override;
	void Unequip(Player& player) override;
};