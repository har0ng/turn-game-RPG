//malkuth.cpp

#include <iostream>
#include "player.h"
#include <vector>


using std::cout;
using std::cin;


malkuth::malkuth() {}
malkuth::malkuth(const player& p) :player(p) { //magician status set
    setPlayer_health(p.getPlayer_health() + 5);
    setPlayer_current_health(p.getPlayer_current_health() + 5);
    setBasic_attack(p.getBasic_attack() + 1);
    setPlayer_defense(p.getPlayer_defense() + 1);
    setMana(p.getMana() + 25);
    setCurrent_mana(p.getCurrent_mana() + 25);
    setLevel(p.getLevel());
    setLevel_exp(p.getLevel_exp());
    setNow_exp(p.getNow_exp());
    setAgility(p.getAgility());
    setCritical(p.getCritical());
    setDebuff(static_cast<int>(p.getDebuff()));
    initSkills();
}

void malkuth::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 2);
    setMana(getMana() + 5);
    player::levelup();
    if (getLevel() % 3 == 2) {
        setBasic_attack(getBasic_attack() + 1);
    }

}
void malkuth::initSkills() {
    player::initSkills();

}
std::string malkuth::getClassName() { ////자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함, magician.cpp 니깐 클래스 함수는 magician
    return "malkuth";
}

