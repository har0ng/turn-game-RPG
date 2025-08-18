//magician.cpp

#include <iostream>
#include "player.h"

using std::cout;
using std::cin;

magician::magician() {}
magician::magician(const player& p) :player(p){ //magician status set
    setPlayer_health(p.getPlayer_health() + 5);
    setPlayer_current_health(p.getPlayer_current_health() + 5);
    setBasic_attack(p.getBasic_attack() + 1);
    setPlayer_defense(p.getPlayer_defense() + 1);
    setMana(p.getMana() + 25);
    setCurrent_mana(p.getCurrent_mana() + 25);
    setLevel(p.getLevel());
    setLevel_exp(p.getLevel_exp());
    setNow_exp(p.getNow_exp());
}

void magician::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 2);
    setMana(getMana() + 5);
    if (getLevel() > 3 && getLevel() % 3 == 2) {
        setBasic_attack(getBasic_attack() + 1);
    }
    player::levelup();
}

bool magician::classChangeYN() const { //전직 후 flase로 함으로써 전직창 이제 안뜸
    return false;
}