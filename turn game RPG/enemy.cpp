//enemy.cpp

#include "enemy.h"

#include <iostream>
#include <random>

using std::cout;
using std::endl;



enemy::enemy() {
	static std::random_device rd; //시드 생성
	static std::mt19937 gen(rd()); //시드 초기화
	std::uniform_int_distribution<unsigned int> dist(20,21);//초기화된 시드의 범위 구성
	enemy_health = dist(gen); // 범위 내 초기화 후 섞어 체력값 할당(랜덤)
	
}

int enemy::getEnemy_health() const { // private에 숨긴 값 get set으로 들고오기
	return enemy_health;
}

int enemy::enemyTakeDamage(int rest_health, int dmg) { //공격 받은 후 남은 체력
	return	rest_health - dmg;
}



