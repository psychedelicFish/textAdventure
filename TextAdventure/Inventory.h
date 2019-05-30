#ifndef _INVENTORY_H
#define _INVENTORY_H
#include <iostream>
#include <string>
#include <vector>

class Player;
class Equipable;
class Item;
class Inventory
{
public:
	Inventory();
	~Inventory();
	void PickUp(Item *item);
	void DisplayInventory();
	void EquipItem(int pick, Player& player);
	void DisplayEquippedItems();
	void SortInventory();
	
private:
	std::vector<Item*> inventory;
	Equipable *equippedItem[4]{ nullptr, nullptr, nullptr, nullptr };
	int inventoryOffset = 1;
};




#endif
