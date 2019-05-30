#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Armour.h"
#include "Footwear.h"
#include "Headgear.h"
#include <cstdlib>
#include <time.h>
Enemy::Enemy()
{
	enemyAttack = rand() % 10 + 1;
	enemyAttackSpeed = rand() % 2 + 1;
	enemyDefence = rand() % 5 + 1;
	enemyHP = 1; //rand() % 30 + 1;

	enemyEXPDrop = 1;//rand() % 100 + 1;
	enemyItemDrop = true;
	item = nullptr;
}

Enemy::~Enemy()
{
	item = nullptr;
	delete item;
}


int Enemy::GiveExperience()
{
	return enemyEXPDrop;
}

Item* Enemy::EnemyItemDrop()
{
	switch (static_cast<DroppedItemType>(rand() % END))
	{
	case WEAPON:
		item = new Weapon(1);
		break;
	case ARMOUR:
		item = new Armour(1);
		break;
	case FOOTGEAR:
		item = new Footwear(1);
		break;
	case HEADGEAR:
		item = new Headgear(1);
	}
	return  item;
}

void Enemy::TakeDamage(int dmg)
{
	if (CheckDeath())
	{
		std::cout << "I'm already dead" << std::endl;
	}
	else
	{
		enemyHP = enemyHP - dmg;
	}
}

bool Enemy::CheckDeath()
{
	if (enemyHP <= 0) {
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::Attack(Player& player)
{
	player.TakeDamage(enemyAttack);
}

void Enemy::DisplayStats()
{
	std::cout << "     Enemy " << std::endl;
	std::cout << "_______________" << std::endl;
	std::cout << "   Hitpoints  " <<  std::endl;
	std::cout << "       " << enemyHP << std::endl;
	std::cout << "_______________" << std::endl <<std::endl;
}



