//yesod.cpp

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

using std::cout;
using std::cin;

yesod::yesod(){}
yesod::yesod(const player& p) :player(p){ //assassin status set
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
    setDebuff(static_cast<int>(p.getDebuff()));
    initSkills();
}

void yesod::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 2);
    setMana(getMana() +2);
    player::levelup();
    if (getLevel() % 2 == 0) {
        setBasic_attack(getBasic_attack() + 1);
    }
    if (getLevel() % 3 == 2) {
        setPlayer_defense(getPlayer_defense() + 1);
    }
    
}
				   
void yesod::initSkills() {
    player::initSkills();
}
std::string yesod::getClassName() { //자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함, assassin.cpp 니깐 클래스 함수는 assassin
    return "yesod";
}