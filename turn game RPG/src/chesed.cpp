//chesed.cpp

#pragma warning(push)
#pragma warning(disable : 26819)
#include "json.hpp"
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4251 26812 26819 4244 4267)
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#pragma warning(pop)

#include <iostream>
#include "player.h"
#include <vector>
#include <fstream>
#include <json.hpp>

using std::cout;
using std::cin;

chesed::chesed() {}
chesed::chesed(const player& p) :player(p) { 
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
    initSkills();
}

void chesed::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 5);
    setMana(getMana() + 2);
    player::levelup();
    if (getLevel() % 2 == 0) {
        setBasic_attack(getBasic_attack() + 1);
        setPlayer_defense(getPlayer_defense() + 1);
    }
}



void chesed::initSkills() {
    player::initSkills();
}
std::string chesed::getClassName() {//자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함
    return "chesed";
}