//enemy.cpp


#include <iostream>
#include "main.h"
#include <random>

using std::cout;
using std::endl;



enemy::enemy() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned int> dist(20, 100);//체력 난수
	enemy_health = dist(gen);
	
}

int enemy::getEnemy_health() const {
	return enemy_health;
}

int enemy::enemyTakeDamage(int rest_health, int dmg) {
	return	rest_health - dmg;
}



