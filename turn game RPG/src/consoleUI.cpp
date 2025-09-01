//consoleUI.cpp

#include "consoleUI.h"
#include <iostream>
#include <iomanip> // setw, left, right 줄 맞추기
using std::endl;
using std::cout;
using std::cin;

void consoleUI::battleStatus(int turn, int php, int cphp, int pattack, int pdefense
                            ,int ehp, int eattack, int level, int level_exp
                            ,int now_exp, int mana, int current_mana, std::string debuff) {
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << turn << " turn" << endl;
    cout << "*player\n Lv: " << level << " ,exp: " << now_exp << "/" << level_exp
        << "\n hp: " << cphp << "/" << php << "\n mp: " << current_mana << "/" << mana
        << "\n power: " << pattack << "\n defense: " << pdefense
        << "\n debuff: " << debuff << endl;
    cout << endl;
    cout << "*enemy\n hp: " << ehp << "\n power: " << eattack << endl;
    cout << endl;
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::playerTurnUI() {
    cout << "========== playerTurn Start ==========\n" << endl;
    cout << "select player Action" << endl;
    cout << "(1)attack  " << "  (2)defense" << "  (3)skill" << endl;
}

void consoleUI::playerTurn(int cphp, int pdefense, int battleselect, int attack, int criattack, bool criticalYN) {
    if (battleselect == 1 && criticalYN == false) {
        cout << "attack enemy!" << endl;
        cout << "enemy takes " << attack << " damage." << endl;
    }
    else if(battleselect == 1 && criticalYN == true){
        cout << "attack enemy!" << endl;
        cout << "critical!!" << "\n enemy takes " << criattack << " damage." << endl;
    }
    else if (battleselect == 2) {
        cout << "defense body" << endl;
        cout << "hp : " << cphp << "/(defensed)+" << pdefense << endl;
    }
    cout << "\n========== playerTurn End ==========" << endl;
    cout << endl;
    cout << endl;

}


void consoleUI::showSkill(int skillSize, std::string charactorClass, std::string name, int hpCost, 
                          int mpCost, int current_mana, int activeTime, int turn, int enemyCnt) {
    if (charactorClass != "warriorB" && current_mana >= mpCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << mpCost << endl;
    }
    else if (charactorClass != "warriorB" && current_mana < mpCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << "Mp不足" << endl;
    }
}

void consoleUI::showSkill(int skillSize, std::string name, int remainturn, int mpCost){
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << mpCost
            << " CT: " << remainturn << endl;
}

void consoleUI::exitSkill(int back) {
    cout << endl;
    cout << endl;
    cout << back << ". " << "back" << endl;
}

void consoleUI::executeSkillAtk(int pattack, int activeTime){
    cout << activeTime << "turnの間powerが" << pattack << "あがります。" << endl;
}

void consoleUI::executeSkillDef(int pdefense, int activeTime){
    cout << activeTime << "turnの間defenseが" << pdefense << "あがります。" << endl;

}

void consoleUI::executeSkill(){
    cout << "デバフが消えました。" << endl;
}

void consoleUI::executeSkill(int heal){
    cout <<"HPを " << heal << " 回復しました。" << endl;
}

void consoleUI::executeSkill(int attack, int criattack, bool criticalYN, std::string name){
    cout << name << "を使用しました。" << endl;
    if (criticalYN == false) {
        cout << "attack enemy!" << endl;
        cout << "enemy takes " << attack << " damage." << endl;
    }
    else if (criticalYN == true) {
        cout << "attack enemy!" << endl;
        cout << "critical!!" << "\n enemy takes " << criattack << " damage." << endl;
    }
}

void consoleUI::skillMpcostRetry(){
    cout << "MPがないです！もう一度入力してください。" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::skillCoolTimeRetry(){
    cout << "まだこのスキルは使用できません。もう一度入力してください。" << endl;
}


void consoleUI::enemyTurn(int enemyAction, int pdefense, int eattack, int battleselect) {
    cout << "========== enemyTurn Start ==========\n" << endl;
    if (enemyAction == 0) {
        cout << "enemy action : assess the situation" << endl;
    }
    else {
        cout << "enemy attacked!" << endl;
        if (battleselect == 2) {
            cout << "Player defends and takes " << eattack << " damage." << endl;
            
        }
        else {
            cout << "Player takes " << eattack << " damage." << endl;
        }
    }
    cout << "\n========== enemyTurn End ==========" << endl;
    cout << endl;
    cout << endl;

    cout << "Press Enter to continue..."<< endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::battleEnd(int cphp) {
	cout << "========== Battle End =============" << endl;
	if (cphp <= 0) { // user hp == 0
		cout << "lose player" << endl;
	}
    else { //enemy hp == 0
        cout << "wins player!" << endl;
        cout << endl;
        cout << endl;
        cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
        cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
        cin.get();
	}
}

void consoleUI::levelup_selectClassUI() { // 2레벨 직업 정하기
        cout << endl;
        cout << "========== class change =============" << endl;
        cout << "congratulations　level 2!" << endl;
        cout << "select your class!" << "\n (1)warrior (2)magician (3)assassin" << endl;
        cout << "\n(1)warrior" << endl;
        cout << "max hp + 10 / +1 level : max hp +5" << endl;
        cout << "max mp + 10 / +1 level : max mp +2" << endl;
        cout << "attack + 3  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +2 level : defense + 1" << endl;
        cout << "\n(2)magician" << endl;
        cout << "max hp + 5  / +1 level : max hp +2" << endl;
        cout << "max mp + 25 / +1 level : max mp +5" << endl;
        cout << "attack + 1  / +3 level : attack + 1" << endl;
        cout << "defense + 1" << endl;
        cout << "\n(3)assassin" << endl;
        cout << "max hp + 4  / +1 level : max hp +2" << endl;
        cout << "max mp + 15 / +1 level : max mp +2" << endl;
        cout << "attack + 4  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +3 level : defense + 1" << endl;
        cout << "agility + 4" << endl;
}

void consoleUI::levelup_selectClass(int level, int selectClass) {
    if (selectClass == 1) {
        cout << "your class is warrior! " << endl;
    } 
    else if (selectClass == 2) {
        cout << "your class is magician! " << endl;
    }
    else if (selectClass == 3) {
        cout << "your class is assassin! " << endl;
    }
    cout << "========== class change =============" << endl;
    cout << endl;
}

void consoleUI::levelup_playerStatus(int php, int cphp, int pattack, int pdefense
                                    ,int level, int level_exp, int now_exp
                                    ,int mana, int current_mana) {
    cout << "========== current player status ==========" << endl;
    cout << "*player\n Lv: " << level << " ,exp: " << now_exp << "/" << level_exp
        << "\n hp: " << cphp << "/" << php << "\n mp: " << current_mana << "/" << mana
        << "\n power: " << pattack << "\n defense: " << pdefense << endl;
    cout << endl;
    cout << "========== current player status ==========" << endl;
}

void consoleUI::enterToContinue() { //enter을 누를시 다음 화면으로 넘어가게끔 조정
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::showStatusChange(playerStatusSnapShot beforePlayer, playerStatusSnapShot afterPlayer) {
    cout << "========== Current Player Status ==========" << endl;
    cout << "* Player" << endl;

    // 헤더
    cout << std::left << std::setw(12) << "Status"
        << std::setw(20) << "Before"
        << "-> "
        << std::setw(20) << "After"
        << endl;

    cout << std::string(60, '-') << endl; // 구분선

    // 레벨 / 경험치
    cout << std::left << std::setw(12) << "Level"
        << std::setw(20) << ("Lv: " + std::to_string(beforePlayer.level) +
            " exp: " + std::to_string(beforePlayer.now_exp) + "/" + std::to_string(beforePlayer.level_exp))
        << "-> "
        << std::setw(20) << ("Lv: " + std::to_string(afterPlayer.level) +
            " exp: " + std::to_string(afterPlayer.now_exp) + "/" + std::to_string(afterPlayer.level_exp))
        << endl;

    // HP
    cout << std::left << std::setw(12) << "HP"
        << std::setw(20) << (std::to_string(beforePlayer.current_health) + "/" + std::to_string(beforePlayer.health))
        << "-> "
        << std::setw(20) << (std::to_string(afterPlayer.current_health) + "/" + std::to_string(afterPlayer.health))
        << endl;

    // MP
    cout << std::left << std::setw(12) << "MP"
        << std::setw(20) << (std::to_string(beforePlayer.current_mana) + "/" + std::to_string(beforePlayer.mana))
        << "-> "
        << std::setw(20) << (std::to_string(afterPlayer.current_mana) + "/" + std::to_string(afterPlayer.mana))
        << endl;

    // Power
    cout << std::left << std::setw(12) << "Power"
        << std::setw(20) << std::to_string(beforePlayer.attack)
        << "-> "
        << std::setw(20) << std::to_string(afterPlayer.attack)
        << endl;

    // Defense
    cout << std::left << std::setw(12) << "Defense"
        << std::setw(20) << std::to_string(beforePlayer.defense)
        << "-> "
        << std::setw(20) << std::to_string(afterPlayer.defense)
        << endl;

    cout << "========== current player status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::showGetSkill(std::string name) {
    cout << name << "を習得しました。" << endl;
}

