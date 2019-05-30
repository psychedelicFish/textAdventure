#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item
{
private:
	
	int ItemLevel;
	
public:
	enum ItemType {WeaponItem, HeadgearItem, ArmourItem, FootwearItem, EQUIPEND, Potions};
	ItemType TypeOfItem;

	virtual void GenerateName() = 0;
	virtual std::string GetName() = 0;
	virtual void SetName(std::string name) = 0;

};
#endif








