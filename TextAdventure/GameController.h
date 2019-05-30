#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#include "Player.h"
#include "Inventory.h"
#include <string>


class Map;
class Room;
class GameController
{
private:
	int MapStartX;
	int MapStartY;
	int currentPositionX;
	int currentPositionY;
protected:
	int map_X = 50;
	int map_Y = 50;

public:
	bool GameOver = false;
	bool ShowInventory = true;
	bool ShowEquipment = true;
	
	//For character building purposes
	bool CorrectCharacterChoice = false; // evaluates if a correct character choice has been made by the player
	int characterIndex; //Allows us to set the character class through the player constructor
	
	Player* player;
	Inventory inventory;
	Enemy* enemy;
	//Room* room;
	Item* item;
	Room** map;

	enum MoveDirection { DEFAULT ,NorthDirect, SouthDirect, EastDirect, WestDirect };
	MoveDirection directionToMove = DEFAULT;

	enum GameState { Start, Continue, End, Battle, CleanBattle, CreateRoom, TransitionRoom, SpendEXP, InventoryScreen, EquipScreen };
	GameState E_GameState;

	using gameState = void(GameController::*)();
	gameState GameState;

	GameController();
	~GameController();
	
	//Simple State Machine function declarations
	//Called every loop cycle
	void TickState();
	//Controls the basic state of the game
	void StartGame();
	void CharacterCreation();
	void ContinueGame();
	void EndGame();
	//These are called when player enters battle
	void BattleState();
	void CleanUpBattleState();
	//Controls the creation and transitioning between rooms
	void GenerateMapState();
	void GenerateStartPositionState();
	void CreateRoomState();
	void TranstionRoomState();
	//Allows Players to spend Experience
	void SpendExperienceState();
	//Inventory states
	void InventoryScreenState();
	void EquipScreenState();
	
	
	
	
	//The function that filters player responses to questions
	void CommandListner(std::string choice);

	int GetMapXSize();//Function for getting the size of the map X
	int GetMapYSize();//Function for getting the size of the map Y

};

#endif