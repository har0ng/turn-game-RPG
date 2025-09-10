//enemy.cpp

#include "enemy.h"

#include <iostream>
#include <random>

using std::cout;
using std::endl;



enemy::enemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(10, 11);

    enemy_health = dist(gen);
    enemyCurrentHealth = enemy_health;
}

// min ~ max 범위에서 체력 랜덤 설정
enemy::enemy(int minHp, int maxHp) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minHp, maxHp);

    enemy_health = dist(gen);
    enemyCurrentHealth = enemy_health;
}


//get
int enemy::getEnemy_health() const { // private에 숨긴 값 get set으로 들고오기
	return enemy_health;
}
int enemy::getEnemyCurrentHealth() const {
	return enemyCurrentHealth;
}

//set
void enemy::setEnemyCurrentHealth(int hp){
	enemyCurrentHealth = hp;
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



