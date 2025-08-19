//assassin.cpp

#include <iostream>
#include "player.h"
#include <vector>

using std::cout;
using std::cin;

assassin::assassin(){}
assassin::assassin(const player& p) :player(p){ //assassin status set
    setPlayer_health(p.getPlayer_health() + 4);
    setPlayer_current_health(p.getPlayer_current_health() + 4);
    setBasic_attack(p.getBasic_attack() + 4);
    setPlayer_defense(p.getPlayer_defense() + 1);
    setMana(p.getMana() + 15);
    setCurrent_mana(p.getCurrent_mana() + 15);
    setLevel(p.getLevel());
    setLevel_exp(p.getLevel_exp());
    setNow_exp(p.getNow_exp());
    setAgility(p.getAgility()+4);
    setCritical(p.getCritical());
}

void assassin::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 2);
    setMana(getMana() +2);
    if (getLevel() > 3 && getLevel() % 2 == 0) {
        setBasic_attack(getBasic_attack() + 1);
    }
    if (getLevel() > 3 && getLevel() % 3 == 2) {
        setPlayer_defense(getPlayer_defense() + 1);
    }
    player::levelup();
}

bool assassin::classChangeYN() const { //전직 후 flase로 함으로써 전직창 이제 안뜸
    return false;
}
				   
void assassin::setSkills() {
    
}
