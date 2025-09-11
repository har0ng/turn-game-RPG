//tiferet.cpp

#include <iostream>
#include "player.h"
#include <vector>
#include <fstream>
#include <json.hpp>

using std::cout;
using std::cin;

tiferet::tiferet(const player& p) :player(p), contract(12),amplifyActivate(false) {
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

//other
void tiferet::levelup() { // if level > 2 (+status) 
    setPlayer_health(getPlayer_health() + 5);
    setMana(getMana() + 2);
    player::levelup();
    if (getLevel() % 2 == 0) {
        setBasic_attack(getBasic_attack() + 1);
        setPlayer_defense(getPlayer_defense() + 1);
    }
}
void tiferet::initSkills() {
    player::initSkills();
}
void tiferet::pushImSlashYou(std::string name, int atk, int def, int stack, int remainTurn, bool check, bool amplity) {
    imslashYou.push_back({ name,atk,def,stack,remainTurn,check,amplity });
}
void tiferet::clearImSlashYou() {
    imslashYou.clear();
}
//get
std::string tiferet::getClassName() {//자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함
    return "tiferet";
}
int tiferet::getContract() const {
    return contract;
}
tiferetStatusSnapShot& tiferet::getBeforePlayer() {
    return beforePlayer;
}
tiferetStatusSnapShot& tiferet::getAfterPlayer()  {
    return afterPlayer;
}
tiferetStatusSnapShot& tiferet::getBattlePlayer()  {
    return battlePlayer;
}
tiferetStatusSnapShot& tiferet::getTurnPlayer()  {
    return turnPlayer;
} 
bool tiferet::getAmplifyActivate() const {
    return amplifyActivate;
}
std::vector<buff> tiferet::getImSlashYou() const{
    if (imslashYou.empty()) {
        return {};
    }
    return imslashYou;
}

//set
void tiferet::setContract(int contract) {
    this->contract = contract;
}
void tiferet::setBeforePlayer() {
    beforePlayer.health = getPlayer_health();
    beforePlayer.current_health = getPlayer_current_health();
    beforePlayer.attack = getBasic_attack();
    beforePlayer.defense = getPlayer_defense();
    beforePlayer.level = getLevel();
    beforePlayer.level_exp = getLevel_exp();
    beforePlayer.now_exp = getNow_exp();
    beforePlayer.mana = getMana();
    beforePlayer.current_mana = getCurrent_mana();
    beforePlayer.agility = getAgility();
    beforePlayer.critical = getCritical();
    beforePlayer.debuff = getDebuff();
    beforePlayer.skills = getSkills();
    beforePlayer.contract = contract;
}
void tiferet::setAfterPlayer() {
    afterPlayer.health = getPlayer_health();
    afterPlayer.current_health = getPlayer_current_health();
    afterPlayer.attack = getBasic_attack();
    afterPlayer.defense = getPlayer_defense();
    afterPlayer.level = getLevel();
    afterPlayer.level_exp = getLevel_exp();
    afterPlayer.now_exp = getNow_exp();
    afterPlayer.mana = getMana();
    afterPlayer.current_mana = getCurrent_mana();
    afterPlayer.agility = getAgility();
    afterPlayer.critical = getCritical();
    afterPlayer.debuff = getDebuff();
    afterPlayer.skills = getSkills();
    afterPlayer.contract = contract;
}
void tiferet::setBattlePlayer() {
    battlePlayer.health = getPlayer_health();
    battlePlayer.current_health = getPlayer_current_health();
    battlePlayer.attack = getBasic_attack();
    battlePlayer.defense = getPlayer_defense();
    battlePlayer.level = getLevel();
    battlePlayer.level_exp = getLevel_exp();
    battlePlayer.now_exp = getNow_exp();
    battlePlayer.mana = getMana();
    battlePlayer.current_mana = getCurrent_mana();
    battlePlayer.agility = getAgility();
    battlePlayer.critical = getCritical();
    battlePlayer.debuff = getDebuff();
    battlePlayer.skills = getSkills();
    battlePlayer.contract = contract;
}
void tiferet::setTurnPlayer() {
    turnPlayer.health = getPlayer_health();
    turnPlayer.current_health = getPlayer_current_health();
    turnPlayer.attack = getBasic_attack() + getBuffAttack();
    turnPlayer.defense = getPlayer_defense() + getBuffDefense();
    turnPlayer.level = getLevel();
    turnPlayer.level_exp = getLevel_exp();
    turnPlayer.now_exp = getNow_exp();
    turnPlayer.mana = getMana();
    turnPlayer.current_mana = getCurrent_mana();
    turnPlayer.agility = getAgility();
    turnPlayer.critical = getCritical();
    turnPlayer.debuff = getDebuff();
    turnPlayer.skills = getSkills();
    turnPlayer.contract = contract;
}
void tiferet::setAmplifyActivate(bool YN) {
    amplifyActivate = YN;
}
bool tiferet::noneOverclock() { //overclock 발동 중인지 확인
    bool overclockAct = false;
    for (const auto b : getBuff()) {
        if (b.name == "overclock" && b.active == true) {
            overclockAct = true;
            break;
        }
    }
    if (overclockAct == true) {
        return true;
    }
    return false;
}
bool tiferet::noneIm() {
    bool imAct = false;
    for (const auto b : getImSlashYou()) {
        if (b.name == "im" && b.active == true) {
            imAct = true;
            break;
        }
    }
    if (imAct == true) {
        return true;
    }
    return false;
}
bool tiferet::noneSlash() {
    bool slashAct = false;
    for (const auto b : getImSlashYou()) {
        if (b.name == "slash" && b.active == true) {
            slashAct = true;
            break;
        }
    }
    if (slashAct == true) {
        return true;
    }
    return false;
}
