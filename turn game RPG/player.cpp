//player.cpp


#include <iostream>
#include "main.h"
#include <string>

using std::cout;
using std::endl;


player::player() :player_health(30),basic_attack(5),basic_defense(5){} //이니셜라이져

int player::getPlayer_health() const { // private에 숨긴 값 get set으로 들고오기
	return player_health;
}

int player::getBasic_attack() const {// private에 숨긴 값 get set으로 들고오기
	return basic_attack;
}

int player::getPlayer_defense() const {// private에 숨긴 값 get set으로 들고오기
	return basic_defense;
}

int player::playerTakeDamage(int rest_health, int dmg) { // 남은 체력 - 데미지
	return	rest_health - dmg;
}