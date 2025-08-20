//enemy.h 

#pragma once
#include <random> // random 


class enemy {
private:
	int enemy_health; //enemy 체력 기본 20/ 최대 255			
public:
	enemy(); //enemy 체력 값 초기화
	int getEnemy_health() const;//private 적 체력값 get
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때

};