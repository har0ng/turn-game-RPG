//player.cpp


#include <iostream>
#include "main.h"
#include <string>

using std::cout;
using std::endl;


player::player() :player_health(30)
				 ,basic_attack(5)
				 ,basic_defense(5)
				 ,level(1)
				 ,level_exp(10)
				 ,now_exp(0){} //이니셜라이져

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

int player::getLevel() const { // private에 숨긴 값 get set으로 들고오기
	return level;
}

int player::getLevel_exp() const{ // private에 숨긴 값 get set으로 들고오기
	return level_exp;
}

int player::getNow_exp() const { // private에 숨긴 값 get set으로 들고오기
	return now_exp;
}

void player::levelup() { //레벨 업. enum 쓰면 되지않나? 알아보기
	level++;
}

int player::playerTakeExp(int rest_exp, int take_exp) { //현재 경험치 + 받은 경험치
	if (rest_exp + take_exp < getLevel_exp()) {
		return rest_exp + take_exp;
	}
	else { //level up , 현재 경험치 + 받은 경험치 - 총경험치
		levelup();
		return rest_exp + take_exp - getLevel_exp();
	}
}