#pragma once
#include <string>

struct buff {
    std::string name{""}; //버프 이름
    int attackBoost{ 0 }; //버프로 인한 공격력 증가량
    int defenseBoost{ 0 }; //버프로 인한 방어력 증가량
    int remainTurn{ 0 }; //끝나는 턴
    bool active = false; // false면 무시
};