#pragma once
#include "Equipable.h"
#include <string>

class Footwear : public Equipable
{
private:

	std::string Name;
	//int DefenceModifier;
	int SpeedModifier;

	enum FootwearType { Boots, Sneakers, Sandles, Crocs };
	FootwearType TypeOfFootwear;

	std::string FootwearNameEndings[5] = { "Of Running", "Of Walking", "Of Backflips", "Of Tripping", "Of Lightsteps" };
public:
	Footwear(int itemLevel);
	void GenerateName() override;
	std::string GetName() override;
	void SetName(std::string name) override;
	void Equip(Player& player) override;
	void Unequip(Player& player) override;
};
