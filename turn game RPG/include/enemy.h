//enemy.h 

#pragma once
#include <random> // random 


class enemy {
private:
	int enemy_health; //enemy 전체체력 기본 ?/ 최대 ? (레벨당 최소,최대 hp 설정 필요) 
	int enemyCurrentHealth; // enemy 현재 체력
	int level; //enemy level
	int power; //공격력

	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
	
public:
	enemy();
	enemy(int minHp, int maxHp, int playerLv); //레벨 별 체력 차이를 위함
	//get
	int getEnemy_health() const;//전체 체력 값
	int getEnemyCurrentHealth() const; //현재 체력 값
	int getLevel() const; //현재 레벨
	int getPower() const; //현재 공격력

	//set
	void setEnemyCurrentHealth(int hp);

	//other
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	int enemyAction();
};	