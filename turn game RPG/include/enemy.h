//enemy.h 

#pragma once
#include <random> // random 


class enemy {
private:
	int enemy_health; //enemy 전체체력 기본 ?/ 최대 ? (레벨당 최소,최대 hp 설정 필요) 
	int enemyCurrentHealth; // enemy 현재 체력
	

public:
	enemy();
	enemy(int minHp, int maxHp); //레벨 별 체력 차이를 위함
	//get
	int getEnemy_health() const;//전체 체력 값
	int getEnemyCurrentHealth() const; //현재 체력 값
	//set
	void setEnemyCurrentHealth(int hp);

	//other
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
};	