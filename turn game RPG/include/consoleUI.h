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
    void battleStatus(int turn, int php, int cphp, int pattack, int pdefense, int ehp
        , int eattack, int level, int level_exp, int now_exp
        , int mana, int current_mana, std::string debuff
        , int buffAttack, int buffDefense, std::string className);
    void battleStatus(int turn, int php, int cphp, int pattack, int pdefense,int contract ,int ehp
        , int eattack, int level, int level_exp, int now_exp
        , int mana, int current_mana, std::string debuff
        , int buffAttack, int buffDefense, std::string className, bool amplifyActivate); //tiferet
    void playerTurnUI();
    void playerTurn(int cphp, int pdefense,int battleselect,int attack, int criattack, bool criticalYN);
    void showSkill(int skillSize, std::string charactorClass, std::string name,int contract ,int contractCost,
        int mpCost, int current_mana, int activeTime, int turn, int enemyCnt);
    void showSkill(int skillSize, std::string name, int remainturn ,int mpCost, int contractCost);
    void exitSkill(int back);
    void executeSkillAtk(int pattack, int activeTime);
    void executeSkillDef(int pdefense, int activeTime);
    void executeSkill();
    void executeSkill(int defense, std::string skillName); //defenseAttack
    void executeSkill(int attack, int criattack, bool criticalYN, std::string name);
    void executeHeal(int heal);
    void skillMpcostRetry(); //스킬 마나 부족이니 다시
    void skillCoolTimeRetry(); // 스킬 쿨타임이니 다시
    void skillContractCostRetry();
    void enemyTurn(int enemyAction, int pdefense, int eattack, int battleselect);
    void battleEnd(int cphp);
    void selectClassUI();
    void selectClass(int level, int selectClass);
    void levelup_playerStatus(int php, int cphp, int pattack, int pdefense
                             ,int level, int level_exp, int now_exp
                             ,int mana, int current_mana);
    void enterToContinue();
    void showStatusChange(playerStatusSnapShot beforePlayer, playerStatusSnapShot afterPlayer);
    void showGetSkill(std::string name); //추가 스킬 UI

    //tiferet
    void executeContract(); //강화 증폭
    void executeChain(); //계약의 사슬 플레이어가 사용 문구
    void activeChain(int enemyTakeDamage, int remainTurn); //계약의 사슬 에너미가 발동 문구
    void activeLightofTruth();
    void activeGuardian(); // 스킬을 썼을 때
    void executeGuardian(); //스킬이 발동 됐을 때
    void setOverclockUI(); // overclock에 쓸 contract 갯수 정하기
};  