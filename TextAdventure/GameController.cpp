#include "GameController.h"
#include "Room.h"
#include "Enemy.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <time.h>


GameController::GameController()
{
	player = nullptr;
	enemy = nullptr;
	//room = nullptr;
	item = nullptr;
	map = nullptr;

	srand(((unsigned int)(time(nullptr))));
	E_GameState = Start;
	GameState = &GameController::StartGame;
	

}

GameController::~GameController()
{
	for (int i = 0; i < map_X; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	//delete room;
	//delete item;
}

int GameController::GetMapXSize()
{
	return map_X;
}

int GameController::GetMapYSize()
{
	return map_Y;
}

void GameController::TickState()
{
	(this->*GameState)();
}

void GameController::StartGame()
{
	std::string choice;
	std::cin.ignore();
	system("CLS");
	std::cout << "What would you like to do: Start New Game" << std::endl;
	std::cout << "			    Load Game" << std::endl;
	std::cout << "			    Exit" << std::endl << std::endl;
	std::cout << "Enter your selection now: ";
	std::cin >> choice;
	
	std::for_each(choice.begin(), choice.end(), [](char & c) {
		c = ::tolower(c);
	});
	std::cin.ignore();
		
	if ((choice == "new") || (choice == "start") || (choice == "start new") || (choice == "start new game"))
	{
		GameState = &GameController::CharacterCreation;
		GameOver = false;

		return;
	}
	if ((choice == "load") || (choice == "load game"))
	{
		player = new Player();
		//player->LoadAll();
		player->DisplayStats();
		GameOver = false;
		GameState = &GameController::GenerateMapState;
		return;
	}
	if (choice == "exit")
	{
		GameState = &GameController::EndGame;
		return;
	}
}
void GameController::GenerateMapState()
{
	
	map = new Room*[map_Y];
	for (int i = 0; i < map_Y; i++)
	{
		map[i] = new Room[map_X];
	}

	for (int y = 0; y < map_Y; y++)			//
	{										//
		map[y][0].west = false;				//
		map[y][map_X - 1].east = false;		//
	}										//Ask James about doing this as a nested loop
	for (int x = 0; x < map_X; x++)			//
	{										//
		map[0][x].north = false;			//
		map[map_Y - 1][x].south = false;	//
	}
	for (int y = 0; y < map_Y; y++) {
		for (int x = 0; x < map_X; x++)
		{
			map[y][x].SetWallsFunc();
		}
	}
	GameState = &GameController::GenerateStartPositionState;
}

void GameController::GenerateStartPositionState()

{	
	MapStartX = rand()% GetMapXSize();
	MapStartY = rand()% GetMapYSize();
	currentPositionX = MapStartX;
	currentPositionY = MapStartY;
	GameState = &GameController::CreateRoomState;
}

void GameController::CreateRoomState() //Creates room from map
{

	//room = new Room();
	enemy = map[currentPositionY][currentPositionX].enemy;
	item = map[currentPositionY][currentPositionX].item;
	GameState = &GameController::ContinueGame;
}

void GameController::ContinueGame()
{
	E_GameState = Continue;
	std::string RoomChoice;

	system("CLS");
	player->DisplayStats();
	std::cout << currentPositionX << " " << currentPositionY << std::endl;
	map[currentPositionY][currentPositionX].DisplayRoomDetails();
	std::cout << "What would you like to do: ";
	std::cin >> RoomChoice;
	std::for_each(RoomChoice.begin(), RoomChoice.end(), [](char & c) {
		c = ::tolower(c);
	});

	CommandListner(RoomChoice);


}

void GameController::BattleState()
{
	E_GameState = Battle;
	player->AttackEnemy(*enemy);
	enemy->Attack(*player);

	static bool ShowStats = true;
	
	if (ShowStats)
	{
		system("CLS");
		enemy->DisplayStats();
		player->DisplayBattleStats();
		ShowStats = false;
	}
	
	if (player->checkDeath())
	{
		system("CLS");
		enemy->DisplayStats();
		player->DisplayBattleStats();
		std::cin.ignore();
		if (std::cin.get())
		{
			return;
		}
	}
	if (enemy->CheckDeath())
	{
		system("CLS");
		enemy->DisplayStats();
		player->DisplayBattleStats();
		std::cout << std::endl;
		std::cout << "Enemy is dead.... hit enter to continue" << std::endl;
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		if (std::cin.get())
		{
			GameState = &GameController::CleanUpBattleState;
			return;
		}
	}
	
	bool ValidChoiceMade = false;
	std::cout << "You and the enemy clash.... Would you like to continue the attack?" << std::endl;
	while (!ValidChoiceMade) {
		std::string choice;
		std::cin.ignore();
		std::cin >> choice;
		std::for_each(choice.begin(), choice.end(), [](char & c) {
			c = ::tolower(c);
		});
		if (choice == "yes")
		{
			ShowStats = true;
			ValidChoiceMade = true;
		}
		else if (choice == "no")
		{
			ShowStats = true;
			GameState = &GameController::ContinueGame;
			ValidChoiceMade = true;
		}
		else
		{
			ValidChoiceMade = false;
			std::cout << "Invalid choice try again" << std::endl;
		}
	}
}

void GameController::CleanUpBattleState()
{
	E_GameState = CleanBattle;
	//room->item = enemy->EnemyItemDrop();
	player->GainExp(enemy->GiveExperience());
	//item = room->item;
	
	enemy = nullptr;
	//room->enemy = nullptr;

	GameState = &GameController::ContinueGame;
}
void GameController::TranstionRoomState()
{
	E_GameState = TransitionRoom;
	switch (directionToMove)
	{
	case NorthDirect:
		currentPositionY--;
		directionToMove = DEFAULT;
		break;
	case SouthDirect:
		currentPositionY++;
		directionToMove = DEFAULT;
		break;
	case EastDirect:
		currentPositionX--;
		directionToMove = DEFAULT;
		break;
	case WestDirect:
		currentPositionX++;
		directionToMove = DEFAULT;
		break;
	case DEFAULT:
		std::cout << "Somethign went horribly wrong" << std::endl;
		break;
	}
	//delete room;
	//room = nullptr;
	GameState = &GameController::CreateRoomState;
}

void GameController::EndGame()
{
	E_GameState = End;
	system("CLS");
	std::cout << "Exiting.....";
	std::cin.get();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	GameOver = true;
	
}

void GameController::SpendExperienceState()
{
	E_GameState = SpendEXP;
	system("CLS");
	player->DisplayStats();
	if(player->GetExperience() <= 0)
	{
		std::cout << "You currently have 0 experience.... press enter to continue" << std::endl;
		std::cin.ignore();
		std::cin.get();
		GameState = &GameController::ContinueGame;
	}
	else
	{
		std::string StatToIncrease;
		std::cout << "Which stat would you like to increase: ";
		std::cin >> StatToIncrease;
		//Convert to LowerCase
		std::for_each(StatToIncrease.begin(), StatToIncrease.end(), [](char & c) {
			c = ::tolower(c);
		});
		//Pass to the Command Filter
		CommandListner(StatToIncrease);
	}
		
}

void GameController::CharacterCreation()
{
	
	std::cout << "Welcome to Text Adventure" << std::endl;
	std::cout << "Please begin to build you character!" << std::endl << std::endl;

	std::string temp_Name;
	bool NameSet = false;

	std::cin.ignore();
	std::cout << "To begin enter the name of your character" << std::endl;
	
	std::cin >> temp_Name;

	std::cout << std::endl;
	std::cout << "Thank you, you entered: " << temp_Name << std::endl;
	
	std::string characterClass;
	while (CorrectCharacterChoice == false) {
		
		std::cout << "Now all we need is your class. Please choose either Rouge or Fighter: ";
		std::cin >> characterClass;
		std::for_each(characterClass.begin(), characterClass.end(), [](char & c) {
			c = ::tolower(c);
		});
		CommandListner(characterClass);
	}


	std::cout << std::endl;
	std::cout << "Thank you, you have chosen: " << characterClass << std::endl;

	std::cout << "Creating character now....." << std::endl;
	player = new Player(temp_Name, characterIndex);
	GameState = &GameController::GenerateMapState;
}

void GameController::InventoryScreenState()
{
	E_GameState = InventoryScreen;
	
	std::string response;
	if(ShowInventory)
	{
		system("CLS");
		inventory.DisplayInventory();
		ShowInventory = false;
	}
	std::cout << "What would you like to do?: ";
	std::cin >> response;

	std::for_each(response.begin(), response.end(), [](char & c) {
		c = ::tolower(c);
	});
	CommandListner(response);
}

void GameController::EquipScreenState()
{
	E_GameState = EquipScreen;
	int response;
	if(ShowInventory || ShowEquipment)
	{
		system("CLS");
		ShowInventory = false;
		ShowEquipment = false;
		inventory.DisplayInventory();
		std::cout << std::endl;
		inventory.DisplayEquippedItems();
	}
	std::cout << "Which item would you like to equip?(Enter the number, 0 to exit): ";
	std::cin >> response;
	if (response == 0)
	{
		CommandListner("exit");
	}
	else
	{
		inventory.EquipItem(response, *player);
		
		ShowEquipment = true;
	}
	
}


void GameController::CommandListner(std::string command)
{
	if (E_GameState == InventoryScreen)
	{
		if(command == "exit")
		{
			ShowInventory = true;
			GameState = &GameController::ContinueGame;
			return;
		}
		if(command == "equip")
		{
			ShowInventory = true;
			GameState = &GameController::EquipScreenState;
			return;
		}
		if(command == "sort")
		{
			inventory.SortInventory();
			ShowInventory = true;
			return;
		}
	
	}

	if (E_GameState == EquipScreen)
	{
		if(command == "equip")
		{
		
		}
		
		if(command == "exit")
		{
			ShowInventory = true;
			ShowEquipment = true;
			GameState = &GameController::InventoryScreenState;
			return;
		}
	}
	
	
	if (E_GameState == SpendEXP)
	{
		if (command == "strength")
		{
			int increaseAmount;
			std::cout << "How much would you like to increase it by?: ";
			std::cin >> increaseAmount;
			if (increaseAmount <= 0)
			{
				std::cout << std::endl;
				std::cout << "Please select a number greater than 0";
			}
			else if (increaseAmount > player->GetExperience())
			{
				std::cout << std::endl;
				std::cout << "Not enough experience....";
			}
			else
			{
				player->SetStrength(increaseAmount);
				player->ReduceExperience(increaseAmount);
				player->SetAttack();
				player->SetDefence();
				player->SaveStrength();
				return;
			}
		}
		if (command == "dexterity")
		{
			int increaseAmount;
			std::cout << "How much would you like to increase it by?: ";
			std::cin >> increaseAmount;
			if (increaseAmount <= 0)
			{
				std::cout << std::endl;
				std::cout << "Please select a number greater than 0";
			}
			else if (increaseAmount > player->GetExperience())
			{
				std::cout << std::endl;
				std::cout << "Not enough experience....";
			}
			else
			{
				player->SetDexterity(increaseAmount);
				player->ReduceExperience(increaseAmount);
				player->SetAttack();
				player->SetDefence();
				player->SaveDexterity();
				return;
			}
		
		}
		if (command == "speed")
		{
			int increaseAmount;
			std::cout << "How much would you like to increase it by?: ";
			std::cin >> increaseAmount;
			if (increaseAmount <= 0)
			{
				std::cout << std::endl;
				std::cout << "Please select a number greater than 0";
			}
			else if (increaseAmount > player->GetExperience())
			{
				std::cout << std::endl;
				std::cout << "Not enough experience....";
			}
			else
			{
				player->SetSpeed(increaseAmount);
				player->ReduceExperience(increaseAmount);
				player->SetAttack();
				player->SetDefence();
				player->SaveSpeed();
				return;
			}
		
		}
		if (command == "health")
		{
			int increaseAmount;
			std::cout << "How much would you like to increase it by?: ";
			std::cin >> increaseAmount;
			if (increaseAmount <= 0)
			{
				std::cout << std::endl;
				std::cout << "Please select a number greater than 0";
			}
			else if (increaseAmount > player->GetExperience())
			{
				std::cout << std::endl;
				std::cout << "Not enough experience....";
			}
			else
			{
				player->SetHealth(increaseAmount);
				player->ReduceExperience(increaseAmount);
				player->SetAttack();
				player->SetDefence();
				player->SaveHealth();
				return;
			}
		}
		player->SaveExperience();
	}

	if (GameState == &GameController::CharacterCreation)
	{
		if (command == "fighter")
		{
			characterIndex = 0;
			CorrectCharacterChoice = true;
			return;
		}
		if (command == "rouge")
		
		{
			characterIndex = 1;
			CorrectCharacterChoice = true;
			return;
		}
		else
		{
			std::cout << "Try again" << std::endl;
			return;
		}
	}
	
	if (GameState == &GameController::ContinueGame)
	{
		if (command == "north")
		{
			
		
			if ((map[currentPositionY][currentPositionX].walls != Room::North) 
			 && (map[currentPositionY][currentPositionX].walls != Room::NorthWest) 
			 && (map[currentPositionY][currentPositionX].walls != Room::NorthEast))
			{
				map[currentPositionY][currentPositionX].Visited = true;
				directionToMove = NorthDirect;
				GameState = &GameController::TranstionRoomState;
				return;
			}
			else {
				std::cout << "You can't walk through walls" << std::endl;
			}
		}

		if (command == "south"){
			map[currentPositionY][currentPositionX].Visited = true;
			directionToMove = SouthDirect;
			GameState = &GameController::TranstionRoomState;
			return;
		}
		if (command == "west") {
			map[currentPositionY][currentPositionX].Visited = true;
			directionToMove = WestDirect;
			GameState = &GameController::TranstionRoomState;
			return;
		}
		if (command == "East") 
		{
			map[currentPositionY][currentPositionX].Visited = true;
			directionToMove = EastDirect;
			GameState = &GameController::TranstionRoomState;
			return;
		}
		if (command == "spend")
		{
			GameState = &GameController::SpendExperienceState;
			return;
		}

		if (command == "attack")
		{
			if (enemy != nullptr)
			{
				//player.DisplayStats();
				//enemy->DisplayStats();
				system("CLS");
				enemy->DisplayStats();
				player->DisplayBattleStats();
				GameState = &GameController::BattleState;
				return;
				//player.AttackEnemy(*enemy);
			}
			else
			{
				std::cout << "No enemy to attack" << std::endl;
				return;
			}
		}

		if (command == "pick" || command == "pick up")
		{
			if (item != nullptr)
			{
				inventory.PickUp(item);
				inventory.DisplayInventory();
				map[currentPositionY][currentPositionX].item = nullptr;
				item = nullptr;

				//inventory.DisplayEquippedItems();
				return;
			}
			else
			{
				std::cout << "Nothing to pick up" << std::endl;
				return;
			}
		}
		if (command == "inventory" || command == "i")
		{
			GameState = &GameController::InventoryScreenState;
			return;
		}
		if (command == "equipped" || command == "equip")
		{
			inventory.DisplayEquippedItems();
			return;
		}
	}
	if (command == "help")
	{
		system("CLS");
		std::cout << "List of Commands" << std::endl << std::endl;
		
		std::cout << "Room Commands: " << std::endl << std::endl;
		
		std::cout << "Attack              - Attack the enemy if one is present" << std::endl;
		std::cout << "Pick or Pick Up     - Pick up an item if it is present  " << std::endl;
		std::cout << "inventory or i      - Display your inventory" << std::endl;
		std::cout << "equipped or equip   - Display your equipped items" << std::endl << std::endl;
		
		std::cout << "Inventory Commands: " << std::endl << std::endl;

		std::cout << "equip or equip item - Equip an item you will be prompted" << std::endl;
		std::cout << "exit                - Return to Room" << std::endl << std::endl;

		std::cout << "Press Enter to exit....";
		std::cin.ignore();
		if (std::cin.get())
		{
			system("CLS");
			return;
		}
	}

	if (command == "next" || command == "next room")
	{
		if (enemy != nullptr || item != nullptr) 
		{
			std::cout << "There is still stuff to check out in this room" << std::endl;
			return;
		}
		else
		{
			system("CLS");
			//std::cout << "You begin transtioning to a new room..." << std::endl;
			GameState = &GameController::TranstionRoomState;
			return;
		}
	}
	if (command == "exit")
	{
		GameState = &GameController::EndGame; //Getting weird breakpoint here
		return;
	}
	else
	{
		std::cout << "Invalid command - Type Help for a list of commands" << std::endl;
	}

}
