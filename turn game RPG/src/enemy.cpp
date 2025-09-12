//enemy.cpp

#include "enemy.h"
#include <iostream>

using std::cout;
using std::endl;

enemy::enemy()
    : enemy_health(0),
    enemyCurrentHealth(0),
    level(1),
    power(0),
    defense(0),
    agility(0),
    critical(0),
    activeBuffTurn(0),
    buffAttack(0),
    buffDefense(0),
    expReward(0),
    playerLevel(1),
    enemyType("")
{}
// min ~ max 범위에서 체력 랜덤 설정
enemy::enemy(int playerLv) :
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
    expReward(0),
    playerLevel(0),
    enemyType("")
{
    setPlayerLevel(playerLv);
}


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
int enemy::getPlayerLevel() const{
    return playerLevel;
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
std::string enemy::getEnemyType() const{
    return enemyType;
}
void enemy::setEnemy_health(int hp){
    enemy_health = hp;
}

//set
void enemy::setEnemyCurrentHealth(int hp) {
    enemyCurrentHealth = std::max(0, hp); // 0 이하 방지
}
void enemy::setLevel(int enemyLv) {
    level = enemyLv;
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
void enemy::setPlayerLevel(int playerLv){
    playerLevel = playerLv;
}
void enemy::pushDeBuff(std::string deBuffName, int agiDown, int criDown,
                       int defenseDown, int attackDown, int stack,
                       int remainingTurn, bool active) {
    deBuffs.push_back({ deBuffName, agiDown, criDown, defenseDown, attackDown,
                        stack, remainingTurn, active });
}
void enemy::setEnemyType(std::string enemyType){
    this->enemyType = enemyType;
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
std::string enemy::randomEnemyType() { //적이 노말인지 엘리트인지 랜덤
    std::random_device rd; //seed create
    std::mt19937 gen; //seed random
    std::uniform_int_distribution<int> enemyTypelDist(0, 3);
    return enemyTypelDist(gen) == 3 ? "elite" : "normal";
}
RandomMinMax enemy::randomHealth(int enemyLv, std::string enemyType, int floor) {
    // 체력 랜덤
    int min = 0;
    int max = 0;
    if (enemyType == "normal") {
        switch (enemyLv) {
        case 1: min = 12, max = 20; break;
        case 2: min = 18, max = 29; break;
        case 3: min = 26, max = 36; break;
        case 4: min = 30, max = 39; break;
        case 5: min = 37, max = 45; break;
        case 6: min = 44, max = 51; break;
        case 7: min = 50, max = 59; break;
        case 8: min = 56, max = 64; break;
        case 9: min = 61; max = 71; break;
        case 10: min = 67; max = 79; break;
        case 11: min = 76; max = 86; break;
        default:
            break;
        }
    }
    else if (enemyType == "elite") {
        switch (enemyLv) {
        case 2: min = 55, max = 67; break;
        case 3: min = 77, max = 90; break;
        case 4: min = 88, max = 118; break;
        case 5: min = 109, max = 137; break;
        case 6: min = 121, max = 158; break;
        case 7: min = 148, max = 172; break;
        case 8: min = 166, max = 186; break;
        case 9: min = 182, max = 215; break;
        case 10: min = 201, max = 242; break;
        case 11: min = 230, max = 270; break;
        default:
            break;
        }
    }
    else if (enemyType == "boss") {
        switch (floor) {
        case 1: min = 110, max = 110; break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        default:
            break;
        }
    }
    return RandomMinMax{ {min},{max} };
}
RandomMinMax enemy::randomPower(int enemyLv, std::string enemyType, int floor) {
    // 공격력 랜덤
    int min = 0;
    int max = 0;
    if (enemyType == "normal") {
        switch (enemyLv) {
        case 1: min = 4, max = 6; break;
        case 2: min = 6, max = 8; break;
        case 3: min = 7, max = 9; break;
        case 4: min = 8, max = 10; break;
        case 5: min = 9, max = 11; break;
        case 6: min = 10, max = 12; break;
        case 7: min = 13, max = 15; break;
        case 8: min = 14, max = 16; break;
        case 9: min = 16, max = 19; break;
        case 10: min = 19, max = 23; break;
        case 11: min = 21, max = 26; break;
        default:
            break;
        }
    }
    else if (enemyType == "elite") {
        switch (enemyLv) {
        case 2: min = 9, max = 18; break;
        case 3: min = 13, max = 21; break;
        case 4: min = 16, max = 23; break;
        case 5: min = 19, max = 28; break;
        case 6: min = 23, max = 31; break;
        case 7: min = 25, max = 33; break;
        case 8: min = 27, max = 35; break;
        case 9: min = 33, max = 39; break;
        case 10: min = 35, max = 41; break;
        case 11: min = 39, max = 45; break;
        default:
            break;
        }
    }
    else if (enemyType == "boss") {
        switch (floor) {
        case 1: min = 16, max = 23; break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        default:
            break;
        }
    }
    return RandomMinMax{ {min},{max} };
}

//virtual
void enemy::decideHealth(RandomMinMax minMax){
    return;
}
void enemy::decidePower(RandomMinMax minMax) {
    return;
}
void enemy::decideLevel(int playerLv) {
    return;
}
int enemy::enemyAction() {
    return 0;
}



