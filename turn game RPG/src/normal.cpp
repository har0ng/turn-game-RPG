//normal.cpp

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

#include "enemy.h"
#include <iostream>

using std::cout;
using std::cin;

normal::normal() {}
normal::normal(const enemy& e) :enemy(e), gen(rd()) {
    //순서: 에너미타입 정하기(main에서) -> 레벨정하기 -> 스텟 만들어주기 
    decideLevel(e.getPlayerLevel());
    setEnemyType("normal");
    decideHealth(randomHealth(getLevel(), getEnemyType(), 1)); //demo라 1층 밖에 없음
    //현재 체력 설정 전에 전체 체력 설정을 먼저
    setEnemyCurrentHealth(getEnemy_health());
    setExpReward(getPlayerLevel(), getLevel(), 1, getEnemyType()); //demo라 1층
}

//override
void normal::decideHealth(RandomMinMax minMax){
    std::uniform_int_distribution<int> HPDist(minMax.min, minMax.max);
    enemy::setEnemy_health(HPDist(gen));
}
void normal::decideLevel(int playerLv) {
    // 레벨 랜덤: playerLevel ±1
    std::uniform_int_distribution<int> levelDist(std::max(1, playerLv - 1), playerLv + 1);
    enemy::setLevel(levelDist(gen));
}
int normal::enemyAction() {
    std::uniform_int_distribution<unsigned int> dist(0, 2); //0. 상황 살피기, 1. 공격, 2. 공격
    return dist(gen);
}