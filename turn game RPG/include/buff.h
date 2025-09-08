#pragma once
struct buff {
    std::string name{ "unknown" }; //스킬 이름
    int attackBoost{ 0 };//얼마나 공격력이 올라가는지
    int defenseBoost{ 0 };//얼마나 방어력이 올라가는지
    int remainingTurn{ 0 };//남은턴
    bool active = true; // false면 무시
    bool amplify = false; //flase면 강화x
};