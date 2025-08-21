//warrior.cpp

#include <iostream>
#include "player.h"
#include <vector>

using std::cout;
using std::cin;

warrior::warrior() {}
warrior::warrior(const player& p):player(p) { //warrior status set
	setPlayer_health(p.getPlayer_health() + 10);
    setPlayer_current_health(p.getPlayer_current_health() + 10);
    setBasic_attack(p.getBasic_attack() + 3);
    setPlayer_defense(p.getPlayer_defense() + 3);
    setMana(p.getMana() + 10);
    setCurrent_mana(p.getCurrent_mana() + 10);
    setLevel(p.getLevel());
    setLevel_exp(p.getLevel_exp());
    setNow_exp(p.getNow_exp());
    setAgility(p.getAgility());
    setCritical(p.getCritical());
    setDebuff(static_cast<int>(p.getDebuff()));
}

void warrior::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 5);
    setMana(getMana() + 2);
    if (getLevel() > 3 && getLevel() % 2 == 0) {
        setBasic_attack(getBasic_attack() + 1);
        setPlayer_defense(getPlayer_defense() + 1);
    }
    player::levelup();
}

bool warrior::classChangeYN() const { //전직 후 flase로 함으로써 전직창 이제 안뜸
    return false;
}

void warrior::initSkills() {

}
std::string warrior::getClassName() {//자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함  warrior.cpp 니깐 클래스 함수는 warrior
    return "warrior"; 
}