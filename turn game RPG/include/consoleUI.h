//consoleUI.h


#pragma once
#include "enemy.h"
#include "player.h"


/*ConsoleUI의 각 함수에 인자를 넘기는 이유
* 
UI 출력 책임만 갖게 하기 위해(SRP)
다른 클래스와의 결합도를 낮추기 위해
유닛 테스트 및 유지보수 용이성을 확보하기 위해*/

class consoleUI {
public:
    void battleStatus(int turn, int php, int cphp, int pattack,int pdefense, int ehp
                     ,int eattack, int level, int level_exp, int now_exp
                     ,int mana, int current_mana, std::string debuff);
    void playerTurnUI();
    void playerTurn(int cphp, int pdefense,int battleselect,int attack, int criattack, bool criticalYN);
    void showSkill(int skillSize, std::string charactorClass, std::string name, int hpCost, 
                   int mpCost, int activeTime, int turn, int enemyCnt);
    void enemyTurn(int enemyAction, int pdefense, int eattack, int battleselect);
    void battleEnd(int cphp);
    void levelup_selectClassUI();
    void levelup_selectClass(int level, int selectClass);
    void levelup_playerStatus(int php, int cphp, int pattack, int pdefense
                             ,int level, int level_exp, int now_exp
                             ,int mana, int current_mana);
    void enterToContinue();
    void showStatusChange(playerStatusSnapShot beforePlayer, playerStatusSnapShot afterPlayer);
    void activeSkillOfReference();
};  