#pragma once
#include "Equipable.h"
#include <string>

class Headgear : public Equipable
{
private:

	std::string Name;
	int DefenceModifier;

	enum HeadgearType { Hat, Helmet, Wig, Pot };
	HeadgearType TypeOfHeadgear;

	std::string HeadgearNameEndings[5] = { "Of Headaches", "Of Disguise", "Of Hatiness", "Of Fanciness", "Of the really dull name" };
public:
	Headgear(int itemLevel);
	void GenerateName() override;
	std::string GetName() override;
	void SetName(std::string name) override;
	void Equip(Player& player) override;
	void Unequip(Player& player) override;


};
