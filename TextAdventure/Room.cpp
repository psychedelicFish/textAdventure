#include "Room.h"
#include "Item.h"
#include "Weapon.h"
#include "Headgear.h"
#include "Footwear.h"
#include "Armour.h"
#include <cstdlib>
#include <iostream>
#include <time.h>


Room::Room()
{
	
	int RoomFeature = rand() % 10 + 1;
	std::cout << RoomFeature << std::endl;
	switch(RoomFeature)
	{
		case 1: 
			item = new Weapon(1); 
			break;
		case 2: 
			item = new Armour(1); 
			break;
		case 3: 
			item = new Headgear(1);
			break;
		case 4: 
			item = new Footwear(1); 
			break;
		case 5: 
			item = new Weapon(1); 
			break;
		case 6:
			enemy = new Enemy();
			//std::cout << "a wild enemy appears" << std::endl;
			break;
		case 7:
			item = new Weapon(1);
			//std::cout << "you find a " << item->GetName() << std::endl;
			break;
		case 8:
			item = new Armour(1);
			//std::cout << "you find a " << item->GetName() << std::endl;
			break;
		case 9:
			item = new Headgear(1);
			//std::cout << "you find a " << item->GetName() << std::endl;
			break;
		case 10:
			item = new Footwear(1);
			//std::cout << "you find a " << item->GetName() << std::endl;
			break;
	}
	//DisplayRoomDetails();

}

Room::~Room()
{
	delete enemy;
	delete item;
	enemy = nullptr;
	item = nullptr;
}

void Room::DisplayRoomDetails()
{
	std::cout << "You look around this new room of the dungeon and you see: " << std::endl;

	if(walls == NorthEast)
	{
		std::cout << "Exits to your south and your west" << std::endl;
	}
	if (walls == NorthWest)
	{
		std::cout << "Exits to your south and your east" << std::endl;
	}
	if (walls == SouthEast)
	{
		std::cout << "Exits to your North and your West" << std::endl;
	}
	if (walls == SouthWest)
	{
		std::cout << "Exits to your North and your East" << std::endl;
	}
	if (walls == South)
	{
		std::cout << "Exits to your North, your West and your East" << std::endl;
	}
	if (walls == North)
	{
		std::cout << "Exits to your South, your West and your East" << std::endl;
	}
	if (walls == East)
	{
		std::cout << "Exits to your South, your North and your West" << std::endl;
	}
	if (walls == West)
	{
		std::cout << "Exits to your South, your North, and your East" << std::endl;
	}
	if (walls == Middle)
	{
		std::cout << "Exits to your South, your North, your East, and your West!!" << std::endl;
	}

	if (item == nullptr && enemy == nullptr)
	{
		std::cout << "Nothing..." << std::endl;
	}
	
	else if (item != nullptr)
	{
		std::cout << "A " << item->GetName() << std::endl;
	}
	if (enemy != nullptr)
	{
		std::cout << "A wild creature staring you down" << std::endl;
	}

}
void Room::SetWallsFunc()
{
	if ((west == false) && (north == false) && (south == true) && (east == true))
	{
		walls = NorthWest;
	}
	if ((east == false) && (north == false) && (south == true) && (west == true))
	{
		walls = NorthEast;
	}
	if ((east == false) && (south == false) && (north == true) && (west == true))
	{
		walls = SouthEast;
	}
	if ((west == false) && (south == false) && (north == true) && (east == true))
	{
		walls = SouthWest;
	}
	if ((west == false) && (north == true) && (south == true) && (east == true))
	{
		walls = West;
	}
	
	if ((east == false) && (north == true) && (south == true) && (west == true))
	{
		walls = East;
	}
	if ((east == true) && (south == false) && (north == true) && (west == true))
	{
		walls = South;
	}
	if ((west == true) && (north == false) && (south == true) && (east == true))
	{
		walls = North;
	}
	if ((west == true) && (north == true) && (east == true) && (south == true))
	{
		walls = Middle;
	}
}
