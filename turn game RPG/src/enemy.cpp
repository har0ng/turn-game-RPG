//enemy.cpp

#include "enemy.h"
#include <iostream>

using std::cout;
using std::endl;

// min ~ max 범위에서 체력 랜덤 설정
enemy::enemy(int minHp, int maxHp, int playerLv) : 
    enemy_health(0),
    enemyCurrentHealth(0),
    level(0),
    power(0),
    defense(0),
    agility(0),
    critical(0),
    activeBuffTurn(0), 
    buffAttack(0), 
    buffDefense(0),
    expReward(0)
{}


//get
int enemy::getEnemy_health() const { // private에 숨긴 값 get set으로 들고오기
	return enemy_health;
}
int enemy::getEnemyCurrentHealth() const {
	return enemyCurrentHealth;
}
int enemy::getLevel() const{
    return level;
}
int enemy::getPower() const{
    return power;
}
int enemy::getDefense() const{
    return defense;
}
int enemy::getAgility() const{
    return agility;
}
int enemy::getCritical() const{
    return critical;
}
int enemy::getActiveBuffTurn() const{
    return activeBuffTurn;
}
int enemy::getBuffAttack() const{
    return buffAttack;
}
int enemy::getBuffDefense() const{
    return buffDefense;
}
int enemy::getExpReward() const{
    return expReward;
}
std::vector<enemySkill> enemy::getSkills() const{
    if (skills.empty()) {
        return {};
    }      
    return skills;
}
std::vector<enemyBuff> enemy::getBuffs() const{
    if (buffs.empty()) {
        return {};
    }
    return buffs;
}
std::vector<enemySkillDisable> enemy::getDisables() const{
    if (disables.empty()) {
        return {};
    }
    return disables;
}
std::vector<deBuff> enemy::getDeBuffs() const {
    if (deBuffs.empty()) {
        return {};
    }
    return deBuffs;
}

//set
void enemy::setEnemyCurrentHealth(int hp) {
    enemyCurrentHealth = std::max(0, hp); // 0 이하 방지
}
void enemy::setPower(int power) {
    this->power = power;
}
void enemy::setDefense(std::string enemyType, int level) {
    if (enemyType == "normal") { //잡몹
        defense = 3 + (level*1);
    }
    else if (enemyType == "elite") { //엘리트
        defense = 5 + static_cast<int>(level * 1.5);
    }
    else if (enemyType == "boss") { //보스
        defense = 10 + (level * 2);
    }
}
void enemy::setAgility(int agi){
    agility = agi;
}
void enemy::setCritical(int cri){
    critical = cri;
}
void enemy::setExpReward(int playerLv, int enemyLv,int mapFloor ,const std::string& enemyType){
    //player total exp (maxLv.10)
    //1lv.20 , 2Lv.40, 3Lv.80, 4Lv.160, 5Lv.320, 6Lv.640, 7Lv.1280, 8Lv.2560, 9Lv.5120
    // 기본 계산식
    int baseExp = 10 + (enemyLv - playerLv) * 2;
    if (baseExp < 1) baseExp = 1; // 최소 1 보장
    
    float mapFloorBonus = 1.0f;
    switch (mapFloor){
    case 1: mapFloorBonus = 1.0f; break;
    case 2: mapFloorBonus = 1.0f; break;
    case 3: mapFloorBonus = 1.1f; break;
    case 4: mapFloorBonus = 1.3f; break;
    case 5: mapFloorBonus = 1.6f; break;
    case 6: mapFloorBonus = 1.9f; break;
    case 7: mapFloorBonus = 1.9f; break;
    default:
        break;
    }

    baseExp = static_cast<int>(baseExp * mapFloorBonus);

    // 특수 케이스 처리
    if (enemyType == "elite") {
        baseExp = static_cast<int>(baseExp * 1.4); // 1.4배
    }
    else if (enemyType == "boss") {
        switch (mapFloor){
        case 1: baseExp = 20; break;
        case 2: baseExp = 80; break;
        case 3: baseExp = 320; break;
        case 4: baseExp = 640; break;
        case 5: baseExp = 1280; break;
        case 6: baseExp = 2560; break;
        case 7: baseExp = 0; break;
        default:
            break;
        }
    }

    expReward = baseExp;
}
void enemy::pushDeBuff(std::string deBuffName, int agiDown, int criDown,
                       int defenseDown, int attackDown, int stack,
                       int remainingTurn, bool active) {
    deBuffs.push_back({ deBuffName, agiDown, criDown, defenseDown, attackDown,
                        stack, remainingTurn, active });
}


//other
int enemy::enemyTakeDamage(int echp, int dmg) { //공격 받은 후 남은 체력
    int hp = 0;
    if (echp - dmg < 0) {
        hp = 0;
    }
    else {
        hp = echp - dmg;
    }
	return hp;
}

//virtual
RandomMinMax enemy::setEnemy_health(int enemyLv, std::string enemyType) {
    return{ {0},{0} };
}
RandomMinMax enemy::randomPower(int enemyLv, std::string enemyType) {
    return;
}
void enemy::decidePower(RandomMinMax minMax) {
    return;
}
void enemy::setLevel(int enemyLv) {
    level = enemyLv;
}
int enemy::enemyAction() {
    return 0;
}



