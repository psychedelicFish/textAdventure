#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include "Inventory.h"

class Enemy;
class Player
	
{
public:
	
	//Character class enum - indexs the characters class
	enum CharacterClass { Fighter, Rouge }; 
	
	//Decleration of the enum for use in code
	enum CharacterClass CharactersClass; 
	
	//Intial stats constructor. 
	//Parameters: name of character, Class of character
	Player(std::string name, int index);


	Player();// Default constructor. Used to Load Player stats from binary
	

	//Get values returned for use in code
	int GetHealth();
	int GetAttack();
	int GetDefence();
	int GetStrength();
	int GetDexterity();
	int GetSpeed();
	int GetExperience();
	
	std::string getName();
	//Allows the setting of attack and defence
	void SetAttack();
	void SetDefence();
	
	//Allows the setting of stats using experience
	void SetHealth(int exp);
	void SetStrength(int exp);
	void SetDexterity(int exp);
	void SetSpeed(int exp);

	//Changes Stats based on equipment
	void AffectDefence(int amount);
	void AffectAttack(int amount);
	void AffectSpeed(int amount);
	
	//Sets the Intial stats of the character
	void SetIntialStats();

	//Display the important stuff
	void DisplayStats();
	void DisplayBattleStats();

	//Save out the Character
	void SaveAll();
	void SaveStrength();
	void SaveHealth();
	void SaveDexterity();
	void SaveSpeed();
	void SaveExperience();
	
	//Load the Character
	void LoadAll();
	
	//Spend Experience
	void ReduceExperience(int amount);
	
	//Allows the player to take damage
	void TakeDamage(int dmg);
	
	//Allows the player to attack the enemy
	void AttackEnemy(Enemy &enemy);
	
	//Allows the player to gain experience
	void GainExp(int exp);
	//Checks to see if the player is dead.
	bool checkDeath();


	
private:
	
	//Basic Stats of the Character
	int Health;
	int Attack;
	int Defence;
	int Strength;
	int Dexterity;
	int Speed;
	std::string Name;
	
	//Amount of Experience character has to spend
	int Experience;

	int length;
	int temp;

	
};

#endif