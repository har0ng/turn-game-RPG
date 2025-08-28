#pragma once
struct buff {
    std::string name;
    int attackBoost;
    int defenseBoost;
    int remainingTurn;
    bool active = true; // false면 무시
};