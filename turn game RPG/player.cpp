//player.cpp

#include "player.h"
#include <iostream>

using std::cout;
using std::endl;


player::player() :player_health(30)
				 ,player_current_health(30)
				 ,basic_attack(5)
				 ,basic_defense(5)
				 ,mana(8)
				 ,current_mana(8)
			 	 ,level(1)
				 ,level_exp(10)
				 ,now_exp(0) {} //initializing

//get
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
int player::getMana() const {
	return mana;
}
int player::getCurrent_mana() const {
	return current_mana;
}

//set
void player::setPlayer_health(int hp) {
	player_health = hp;
}
void player::setPlayer_current_health(int hp) {
	player_current_health = hp;
};
void player::setPlayer_defense(int defense) {
	basic_defense = defense;
};
void player::setBasic_attack(int attack) {
	basic_attack = attack;
};
void player::setMana(int mp){
	mana = mp;
}
void player::setCurrent_mana(int mp) {
	current_mana = mp;
}
void player::setLevel(int lev){
	level = lev;
}
void player::setLevel_exp(int lev) {
	level_exp = lev;
}
void player::setNow_exp(int lev){
	now_exp = lev;
}

//other
int player::playerTakeDamage(int dmg) { //현재 체력 - 받은 데미지 계산
	player_current_health = std::max(0, player_current_health - dmg); // 0이하로 떨어져서 오버플로우 안일어나게 막기
	return player_current_health;
}
void player::levelup() { //레벨 업.
	level++;
	level_exp *= 2; //필요 경험치 2배씩 증가
	player_current_health = player_health; //체력 회복
	current_mana = mana; //마나 회복
}
int player::playerTakeExp(int take_exp) { //take exp
	if (now_exp + take_exp< getLevel_exp()) { //not level up
		now_exp += take_exp;
		return now_exp;
	}
	else { //level up , exp cal
		now_exp += take_exp - getLevel_exp();
		levelup();
		return now_exp;
	}
}
bool player::classChangeYN() const { //전직하면 false로 바꾸게 해주면 됨,
	return true;
}