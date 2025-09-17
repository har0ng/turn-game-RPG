//boss.cpp

#include "enemy.h"
#include <iostream>

//not random parameter!

boss::boss(const enemy& e) :enemy(e), gen(rd()) {
    // 순서: 에너미타입 정하기(main에서)->레벨정하기->스텟 만들어주기
    decideLevel(e.getPlayerLevel());
    setEnemyType("boss");
    decideHealth(randomHealth(getLevel(), getEnemyType(), 1)); //1층은 아직 맵을 안만들어서 임시
    //현재 체력 설정 전에 전체 체력 설정을 먼저
    setEnemyCurrentHealth(getEnemy_health());
    decidePower(randomPower(getLevel(), getEnemyType(), 1));
    setExpReward(getPlayerLevel(), getLevel(), 1, getEnemyType()); //demo라 1층
}

//override
void boss::decideHealth(RandomMinMax minMax) {
    std::uniform_int_distribution<int> HPDist(minMax.min, minMax.max);
    enemy::setEnemy_health(HPDist(gen));
}
void boss::decidePower(RandomMinMax minMax) {
    std::uniform_int_distribution<int> powerDist(minMax.min, minMax.max);
    enemy::setPower(powerDist(gen));
}
void boss::decideLevel(int playerLv) {
    // 레벨 랜덤: playerLevel +2, 보스는 스테이터스 고정이라 레벨 사실 의미 없음
    enemy::setLevel(playerLv + 2);
}
int boss::enemyAction() {
    std::uniform_int_distribution<unsigned int> dist(0, 2); //0. 상황 살피기, 1. 공격, 2. 공격
    return dist(gen);
}