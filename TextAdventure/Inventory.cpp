#include "Inventory.h"
#include "Equipable.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>

Inventory::Inventory()
{
	
}
Inventory::~Inventory()
{
	//delete equippedItem;
}

void Inventory::PickUp(Item *item)
{
	inventory.push_back(item);
}
void Inventory::DisplayInventory()
{
	if (inventory.empty()){
		std::cout << "Inventory is empty" << std::endl;
		return;
	}
	system("CLS");
	bool inventoryValidChoice = false;
	std::string inventoryChoice;
	
	std::cout << "Player Inventory" << std::endl;
	
	for (auto it = inventory.begin(); it < inventory.end(); it++)
	{
		auto position = it - inventory.begin();
		std::cout << position + inventoryOffset <<" " << (*it)->GetName() << std::endl;
	}

	//while (!inventoryValidChoice) {
	//	std::cout << "What would you like to do?: ";
	//	std::cin >> inventoryChoice;
	//	std::for_each(inventoryChoice.begin(), inventoryChoice.end(), [](char & c) {
	//		c = ::tolower(c);
	//	});

	//	if (inventoryChoice == "equip" || inventoryChoice == "equip item")
	//	{
	//		inventoryValidChoice = true;
	//		EquipItem();
	//	}
	//	else if (inventoryChoice == "exit" || inventoryChoice == "e")
	//	{
	//		inventoryValidChoice = true;
	//	}
	//	else if (inventoryChoice == "sort")
	//	{
	//		SortInventory();
	//	}
	//	else
	//	{
	//		inventoryValidChoice = false;
	//	}
	//	
}

void Inventory::EquipItem(int pick, Player& player)
{
	int Pick = pick - inventoryOffset;
	Item *pickedItem = nullptr;
	
	pickedItem = inventory[Pick];

	if (pickedItem == nullptr)
	{
		std::cout << std::endl;
		std::cout << "No item in this slot" << std::endl;
	}
	else
	{
		if (pickedItem->TypeOfItem < Item::ItemType::EQUIPEND) {
			equippedItem[pickedItem->TypeOfItem] = static_cast<Equipable*> (pickedItem);
			equippedItem[pickedItem->TypeOfItem]->Equip(player);
		}
	}
	pickedItem = nullptr;
	delete pickedItem;
}
void Inventory::DisplayEquippedItems()
{
	std::cout << "Equipped Items" << std::endl << std::endl;
	if (equippedItem[0] != nullptr){
		std::cout << "Weapon: " << equippedItem[0]->GetName() << std::endl;
	}
	
	else
	{
		std::cout << "Weapon: " << "Nothing" << std::endl;
	}
	
	if (equippedItem[1] != nullptr) {
		std::cout << "Helmet: " << equippedItem[1]->GetName() << std::endl;
	}
	
	else
	{
		std::cout << "Helmet: " << "Nothing" << std::endl;
	}
	
	if (equippedItem[2] != nullptr) {
		std::cout << "Armour: " << equippedItem[2]->GetName() << std::endl;
	}
	
	else
	{
		std::cout << "Armour: " << "Nothing" << std::endl;
	}
	
	if (equippedItem[3] != nullptr) {
		std::cout << "Boots : " << equippedItem[3]->GetName() << std::endl;
	}
	
	else
	{
		std::cout << "Boots : " << "Nothing" << std::endl;
	}
}

void Inventory::SortInventory()
{
	auto sort_by_type = [](Item* a, Item* b)
	{
		return a->TypeOfItem < b->TypeOfItem;
	};

	std::sort(inventory.begin(), inventory.end(), sort_by_type);
}


