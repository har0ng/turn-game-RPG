//enemy.cpp

#include "enemy.h"
#include <iostream>

using std::cout;
using std::endl;



enemy::enemy(){}

// min ~ max 범위에서 체력 랜덤 설정
enemy::enemy(int minHp, int maxHp, int playerLv) : gen(rd()), power(0) {
    // 체력 랜덤
    std::uniform_int_distribution<int> dist(minHp, maxHp);
    enemy_health = dist(gen);
    enemyCurrentHealth = enemy_health;

    // 레벨 랜덤: playerLevel ±1
    std::uniform_int_distribution<int> levelDist(std::max(1, playerLv - 1), playerLv + 1);
    level = levelDist(gen);

    // 공격력 랜덤
    std::uniform_int_distribution<int> powerDist(4, 7);
    power = powerDist(gen);
}


//get
int enemy::getEnemy_health() const { // private에 숨긴 값 get set으로 들고오기
	return enemy_health;
}
int enemy::getEnemyCurrentHealth() const {
	return enemyCurrentHealth;
}
int enemy::getLevel() const{
    return level;
}
int enemy::getPower() const{
    return power;
}

//set
void enemy::setEnemyCurrentHealth(int hp) {
    enemyCurrentHealth = std::max(0, hp); // 0 이하 방지
}

//other
int enemy::enemyTakeDamage(int echp, int dmg) { //공격 받은 후 남은 체력
    int hp = 0;
    if (echp - dmg < 0) {
        hp = 0;
    }
    else {
        hp = echp - dmg;
    }
	return hp;
}
int enemy::enemyAction(){
    std::uniform_int_distribution<unsigned int> dist(0, 2); //0. 상황 살피기, 1. 공격, 2. 공격
    return dist(gen);
}



