#include "GameController.h"


int main()
{
	GameController gameController;
	//gameController.gameState = gameController.StartGame;

	Player* player = nullptr;
	
	
	//void(GameController::*gameState) () = &GameController::StartGame;
	while (!gameController.GameOver)
	{
		gameController.TickState();
	}
	delete player;
	return 0;
	
}
