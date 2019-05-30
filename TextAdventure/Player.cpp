#include "Player.h"
#include "Enemy.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstddef>


Player::Player(std::string name, int index)
{
	Name = name; //Sets the name of the character
	CharactersClass = static_cast<CharacterClass> (index); //Sets the class for the player
	SetIntialStats(); // Set the intial stats of the character based on class
	SaveAll();// Save out the newly created character
}
Player::Player() //Default constructer - takes no parameters
{
	LoadAll(); //Function to load in all data
}
#pragma region Getters
//Returns name of character
std::string Player::getName()
{
	return Name;
}
//returns integer experience
int Player::GetExperience()
{
	return Experience;
}
//returns integer health
int Player::GetHealth() 
{
	return Health;
}
//returns integer Attack
int Player::GetAttack() 
{
	return Attack;
}
//returns integer Defence
int Player::GetDefence() 
{
	return Defence;
}
//returns integer Strength
int Player::GetStrength() 
{
	return Strength;
}
//returns integer Dexterity
int Player::GetDexterity()
{
	return Dexterity;
}
//returns integer Speed
int Player::GetSpeed()
{
	return Speed;
}
#pragma endregion

#pragma region SettersSkillpoint
//Parameter skillpoint is added to the integer strength to increase its value.
void Player::SetStrength(int skillpoint)
{
	Strength += skillpoint;
}
//Parameter skillpoint is added to the integer Dexterity to increase its value.
void Player::SetDexterity(int skillpoint)
{
	Dexterity += skillpoint;
}
//Parameter skillpoint is added to the integer Speed to increase its value.
void Player::SetSpeed(int skillpoint)
{
	Speed += skillpoint;
}
//Parameter skillpoint is added to the integer Health to increase its value.
void Player::SetHealth(int skillpoint)
{
	Health += skillpoint;
}

#pragma endregion
#pragma region SettersEquipment
void Player:: AffectDefence(int amount)
{
	Defence += amount;
}
void Player::AffectAttack(int amount)
{
	Attack += amount;
}
void Player::AffectSpeed(int amount)
{
	Speed += amount;
}
#pragma endregion

#pragma region SettersStatBased

//Sets the attack of player
void Player::SetAttack()
{
	Attack = (Strength + Speed) / 2;//Integer Attack is equal to the average of strength and speed
}
//Sets the defence of the player
void Player::SetDefence()
{
	Defence = (Dexterity); //Integer defence is equal to Dexerity
}
#pragma endregion
#pragma region SettersOther

//Sets the intial values of the character takes no parameters
//Always happens after the charaters class has been set
void Player::SetIntialStats()
{
	switch (CharactersClass)
	{
		case Fighter:
			Health = 100;	//Sets health
			Strength = 3;	//Sets Strength
			Dexterity = 1;	//Sets Dexterity
			Speed = 1;		//Sets speed
			Experience = 3;	//Sets starting Experience
			SetAttack();	//Function called to set Attack
			SetDefence();	//Function called to set Defence
			//std::cout << "Stats set to Fighters" << std::endl; //Debugging purposes
			DisplayStats();	//Displays the stats to the screen
			break;
		case Rouge:
			Health = 50;	//Sets health
			Strength = 0;	//Sets Strength
			Dexterity = 3;	//Sets Dexterity
			Speed = 3;		//Sets Speeds
			Experience = 0;	//Sets starting Experience
			SetAttack();	//Function called to set Attack
			SetDefence();	//Function called to set Defence
			//std::cout << "Stats set to Rouges" << std::endl; //Debugging purposes
			DisplayStats();	//Displays the stats the the screen
			break;
			
	}
}
#pragma endregion
//Takes no parameters and returns void
void Player::DisplayStats()
{
	std::cout << Name <<"'s stats" << std::endl; //Prints the name to the console
	std::cout << CharactersClass << std::endl;
	
	std::cout << "   Strength: " << Strength << std::endl; //Prints the value of the integer Strength to the console
	std::cout << "  Dexterity: " << Dexterity << std::endl;//Prints the value of the integer Dexterity to the console
	std::cout << "      Speed: " << Speed << std::endl << std::endl;//Prints the value of the integer Speed to the console

	std::cout << "     Health: " << Health << std::endl;//Prints the value of the integer Health to the console 
	std::cout << "     Attack: " << Attack << std::endl;//Prints the value of the integer Attack to the console 
	std::cout << "    Defence: " << Defence << std::endl;//Prints the value of the integer Defence to the console 
	std::cout << "Current EXP: " << Experience << std::endl;//Prints the value of the integer Experience to the console

}
//Takes no Parameters and returns void 
//Displays the battlestats to the screen
void Player::DisplayBattleStats()
{
	std::cout << "     " << Name <<  std::endl;// Prints the name to the screen
	std::cout << "_______________" << std::endl; //Dividing line
	std::cout << "   Hitpoints  " << std::endl; // Title of the next line
	std::cout << "       " << Health << std::endl; // Prints the value of the integer Health to the console 
	std::cout << "_______________" << std::endl; // Dividing line
}

//Returns void and takes no parameters
//Allows the saving out of the object to binary
void Player::SaveAll()
{
	std::fstream fout;// creates the fstream

	fout.open("Player.dat", std::ios::out | std::ios::binary);	//opens the fstream, names the file, tells the complier we are writing out, 
																//tells the compilier to convert to binary
	int name = Name.length();									// Creates a length of name variable to help write out a string 
	
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has
	{
		fout.write((char*)&name, sizeof(int)); //Writes out the starting point for name 
		fout.write((char*)Name.c_str(), name); //Writes out the name with the length of the string 
		
		fout.write((char*)&Health, sizeof(int)); //Writes out the integer Health
		fout.write((char*)&Strength, sizeof(int)); //Writes out the integer Strength
		fout.write((char*)&Dexterity, sizeof(int)); //Writes out the integer Dexterity
		fout.write((char*)&Speed, sizeof(int)); //Writes out the interger Speed
		fout.write((char*)&Experience, sizeof(int));//Writes out the integer Experience
		fout.write((char*)&CharactersClass, sizeof(int));
		std::cout << "Character Saved to File" << std::endl; //Lets us know the character has been saved

		fout.close(); //Closes the fstream
	}
}
//Returns void and takes know parameters
//Allows us to save out just the value of the integer Strength
void Player::SaveStrength()
{
	std::fstream fout; //Creates the fstream
	
	fout.open("Player.dat", std::ios::in | std::ios::out | std::ios::binary);
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has)
	{
		fout.read((char*)&length, sizeof(int)); //Sets length to be equal to the length of the first value which we know is Name but 
										//we don't know what length it will have
		fout.seekg(length + offsetof(Player, Strength));
		fout.read((char*)&temp, sizeof(int));
		if(temp != Strength)
		{
			fout.seekp(length + offsetof(Player, Strength));//Skips to the strength value which we know is the third value in the file
			fout.write((char*)&Strength, sizeof(int));
		}
		 //Writes out our Strength value in the correct spot
		fout.close();//Close the fstream
	}
}
//Returns void and takes know parameters
//Allows us to save out just the value of the integer Health
void Player::SaveHealth()
{
	std::fstream fout; //Creates the fstream
	fout.open("Player.dat", std::ios::out | std::ios::in | std::ios::binary); //Opens the fstream, tells us what file to open, tells us to use binary
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has)
	{
		fout.read((char*)&length, sizeof(int)); //Sets length to be equal to the length of the first value which we know is Name but 
										//we don't know what length it will have
		fout.seekg(length + sizeof(int));
		fout.read((char*)&temp, sizeof(int));

		if (temp != Health)
		{
			fout.seekp(length + sizeof(int));//Skips to the strength value which we know is the third value in the file
			fout.write((char*)&Health, sizeof(int));
		}
		
		//Writes out our Health value in the correct spot
		fout.close();//Close the fstream
	}
}
//Returns void and takes know parameters
//Allows us to save out just the value of the integer Dexterity
void Player::SaveDexterity()
{
	std::fstream fout; //Creates the fstream
	fout.open("Player.dat", std::ios::in | std::ios::out  | std::ios::binary);
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has)
	{
		fout.read((char*)&length, sizeof(int)); //Sets length to be equal to the length of the first value which we know is Name but 
											//we don't know what length it will have
		fout.seekg(length + sizeof(int) + sizeof(int) + sizeof(int));
		fout.read((char*)&temp, sizeof(int));
		if (temp != Dexterity)
		{
			fout.seekp(length + sizeof(int) + sizeof(int) + sizeof(int));//Skips to the strength value which we know is the third value in the file
			fout.write((char*)&Dexterity, sizeof(int));
		}
		//Writes out our Dexterity value in the correct spot
		fout.close();//Close the fstream
	}
}
//Returns void and takes know parameters
//Allows us to save out just the value of the integer Speed
void Player::SaveSpeed()
{
	std::fstream fout; //Creates the fstream
	fout.open("Player.dat", std::ios::out | std::ios::in | std::ios::binary); //Opens the fstream, tells us what file to open, tells us to use binary
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has)
	{
		fout.read((char*)&length, sizeof(int)); //Sets length to be equal to the length of the first value which we know is Name but 
										//we don't know what length it will have
		fout.seekg(length + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));
		fout.read((char*)&temp, sizeof(int));
		if (temp != Speed)
		{
			fout.seekp(length + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));//Skips to the strength value which we know is the third value in the file
			fout.write((char*)&Speed, sizeof(int));
		}
		//Writes out our Speed value in the correct spot
		fout.close();//Close the fstream
	}
}
void Player::SaveExperience()
{
	std::fstream fout; //Creates the fstream
	fout.open("Player.dat", std::ios::in | std::ios::out | std::ios::binary);
	if (fout.good())//Checks to make sure the file has opened correctly (returns true if it has)
	{
		fout.read((char*)&length, sizeof(int)); //Sets length to be equal to the length of the first value which we know is Name but 
												//we don't know what length it will have
		fout.seekg(length + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));
		fout.read((char*)&temp, sizeof(int));
		if (temp != Experience)
		{
			fout.seekp(length + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));//Skips to the strength value which we know is the third value in the file
			fout.write((char*)&Experience, sizeof(int));
		}
		//Writes out our Experiece value in the correct spot
		fout.close();//Close the fstream
	}
}


//Returns void and takes no Parameters
//Allows us to load in values from the "Player.dat" file
void Player::LoadAll()
{
	std::fstream fin; //Creates the fstream variable 

	fin.open(("Player.dat"), std::ios::in | std::ios::binary);//Opens the Player.dat file, tells we are reading, tells we are reading binary
	int length; //creates a length variable for reading the Name variable

	if (fin.good())
	{
		fin.read((char*)&length, sizeof(int));	//Sets length to be equal to the length of the first value which we no is Name
												//We don't know what its length is however
		char* buffer = new char[length+1];		//Creates a 'buffer' to read in the name
		buffer[length] = 0;						//Sets the last value of the buffer to be the termination point 
		fin.read((char*)buffer, length);		//Reads the Name varible into the buffer
		Name = buffer;							//Sets the Name varible to the value of the buffer
		delete[] buffer;						//As the buffer is a pointer we then delete it 
		
		fin.read((char*)&Health, sizeof(int));		//Reads in the health integer and sets it
		fin.read((char*)&Strength, sizeof(int));	//Reads in the Strength integer and sets it
		fin.read((char*)&Dexterity, sizeof(int));	//Reads in the Dexterity integer and sets it
		fin.read((char*)&Speed, sizeof(int));		//Reads in the Speed integer and sets it
		fin.read((char*)&Experience, sizeof(int));	//Reads in the Experience integer and sets it
		fin.read((char*)&CharactersClass, sizeof(int));

		SetAttack();	//Sets the Attack integer based on stats just read in
		SetDefence();	//Sets the Defence integer based on stats just read in
		fin.close();    //Closes the fstream
	}
}
//Returns a boolean takes no parameters
//Checks if the integer health is below 0 or not 
bool Player::checkDeath()
{
	if (Health <= 0)// is heatlh below 0?
	{
		return true;	//returns true if it is 
	}
	else
	{
		return false;  //returns false if it is not
	}
}

//Function to gain experience
//Returns void takes an integer as Parameter
//Parameter indicates how much experience is gained
void Player::GainExp(int exp)
{
	Experience = Experience + exp; //Current value of Experience is set to the current value of experience plus the passed in value.
}
//Function to take Damage
//Returns void takes an integer as a Parameter
//Parameter indicates how much damage is taken
void Player::TakeDamage(int dmg)
{
	if (checkDeath()) //Checks if player is already dead(returns true if they are)
	{
		std::cout << "I'm already dead" << std::endl; //If returns true prints this line 
	}
	else
	{
		Health = Health - dmg; //if false takes damage
	}
}
//Function to attack and enemy
//Returns void takes a reference to an Enemy object 
//Enemy object then calls a function
void Player::AttackEnemy(Enemy &enemy)
{
	enemy.TakeDamage(Attack); //enemy calls its TakeDamage function taking the players Attack value as a parameter
}
//Function to reduce Experience when spent
//Returns void, takes and integer to reduce experience by
void Player::ReduceExperience(int amount)
{
	Experience -= amount;//Reduces experince by the amount passed in 
}






