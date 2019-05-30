#ifndef _ENEMY_H
#define _ENEMY_H

class Item;
class Weapon;
class Player;
class Enemy
{
private:
	int enemyHP;
	int enemyAttack;
	int enemyDefence;
	int enemyAttackSpeed;
	int enemyEXPDrop;
	
	bool enemyItemDrop;
	Item* item;
public:
	Enemy();
	~Enemy();
	
	Item* EnemyItemDrop();
	int GiveExperience();
	void DisplayStats();
	void TakeDamage(int dmg);
	bool CheckDeath();
	void Attack(Player &player);

	enum DroppedItemType {WEAPON, HEADGEAR, FOOTGEAR, ARMOUR , END};
	//DroppedItemType droppedItemType;
	
};
#endif
