//player.cpp

#include "player.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;


player::player() :player_health(30)
				 ,player_current_health(30)
				 ,basic_attack(5)
				 ,basic_defense(5)
				 ,level(1)
				 ,level_exp(10)
				 ,now_exp(0){} //이니셜라이져

int player::getPlayer_health() const { // private에 숨긴 값 get set으로 들고오기
	return player_health;
}

int player::getPlayer_current_health() const{
	return player_current_health;
}

int player::getPlayer_defense() const {// private에 숨긴 값 get set으로 들고오기
	return basic_defense;
}

int player::getBasic_attack() const {// private에 숨긴 값 get set으로 들고오기
	return basic_attack;
}

int player::getLevel() const { // private에 숨긴 값 get 으로 들고오기
	return level;
}

int player::getLevel_exp() const { // private에 숨긴 값 get 으로 들고오기
	return level_exp;
}

int player::getNow_exp() const { // private에 숨긴 값 get 으로 들고오기
	return now_exp;
}

int player::playerTakeDamage(int dmg) { //현재 체력 - 받은 데미지 계산
	player_current_health = std::max(0, player_current_health - dmg); // 0이하로 떨어져서 오버플로우 안일어나게 막기
	return player_current_health;
}

void player::levelup() { //레벨 업.
	level++;
}

int player::playerTakeExp(int now_exp, int take_exp) { //현재 경험치 + 받은 경험치
	if (now_exp + take_exp < getLevel_exp()) {
		return now_exp + take_exp;
	}
	else { //level up , 현재 경험치 + 받은 경험치 - 총경험치
		levelup();
		return now_exp + take_exp - getLevel_exp();
	}
}