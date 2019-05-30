#ifndef _ROOM_H
#define _ROOM_H
#include "Enemy.h"
class Item;
class Weapon;
class Room
{
public: 
	Room();
	~Room();
	void DisplayRoomDetails();
	Enemy* enemy = nullptr;
	Item *item = nullptr;
	bool Visited = false;
	
	bool south = true;
	bool north = true;
	bool east = true;
	bool west = true;
	
	enum RoomWalls { NorthWest, North, NorthEast, East, West, South, SouthEast, SouthWest, Middle };
	RoomWalls walls;
	void SetWallsFunc();
	int GetWallsFunc(RoomWalls walls);



	


};

#endif