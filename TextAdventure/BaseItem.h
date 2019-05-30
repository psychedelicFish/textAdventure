#ifndef _BASEITEM_H_
#define _BASEITEM_H_
#include <string>

class BaseItem
{
private:
	std::string Name;

public:
	enum ItemType {Weapon, Armour, Potion};
	ItemType itemType;
	BaseItem();
	BaseItem(std::string name, ItemType type);

	std::string GetName();

	
};


#endif

