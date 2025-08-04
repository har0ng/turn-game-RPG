//player.cpp


#include <iostream>
#include "main.h"
#include <string>

using std::cout;
using std::endl;


player::player() :player_health(30),basic_attack(5),basic_defense(5){}

int player::getPlayer_health() const {
	return player_health;
}

int player::getBasic_attack() const {
	return basic_attack;
}

int player::getPlayer_defense() const {
	return basic_defense;
}

int player::playerTakeDamage(int rest_health, int dmg) { // 남은 체력 - 데미지
	return	rest_health - dmg;
}