//one.cpp

#include "enemy.h"
#include <iostream>

using std::cout;
using std::cin;

one::one(const enemy& e) :enemy(e), enemyType("normal"), gen(rd()) {
  
}


//override
RandomMinMax one::setEnemy_health(int enemyLv, std::string enemyType) {
    // 체력 랜덤
    if (enemyType == "normal") {
        switch (enemyLv) {
        case 1: break;
        default:
            break;
        }
    }
    else if (enemyType == "elite") {

    }
    else if (enemyType == "boss") {

    }
}
void one::setLevel(int playerLv) {
    // 레벨 랜덤: playerLevel ±1
    std::uniform_int_distribution<int> levelDist(std::max(1, playerLv - 1), playerLv + 1);
    enemy::setLevel(levelDist(gen));
}
RandomMinMax one::randomPower(int enemyLv, std::string enemyType) {
    // 공격력 랜덤
    int min = 0;
    int max = 0;
    if (enemyType == "normal") {
        switch (enemyLv) {
        case 1: min = 4, max = 7;
            break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        default:
            break;
        }
    }
    else if (enemyType == "elite") {
        switch (enemyLv) {
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        default:
            break;
        }
    }
    else if (enemyType == "boss") {
        switch (enemyLv) {
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        default:
            break;
        }
    }
    return RandomMinMax{ {min},{max} };
}
void one::decidePower(RandomMinMax minMax) {
    std::uniform_int_distribution<int> powerDist(minMax.min, minMax.max);
    enemy::setPower(powerDist(gen));
}
int one::enemyAction() {
    std::uniform_int_distribution<unsigned int> dist(0, 2); //0. 상황 살피기, 1. 공격, 2. 공격
    return dist(gen);
}