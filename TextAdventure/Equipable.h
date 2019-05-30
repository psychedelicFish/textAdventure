#pragma once
#include "Item.h"
#include "Player.h"
class Equipable : public Item
{
protected:
	bool isEquipped = false;
public:
	virtual void Equip(Player&) = 0;
	virtual void Unequip(Player&) = 0;

};
