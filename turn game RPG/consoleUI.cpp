//consoleUI.cpp

#include "consoleUI.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void consoleUI::battleStatus(int turn, int php, int cphp, int pattack, int pdefense
                            ,int ehp, int eattack, int level, int level_exp
                            ,int now_exp, int mana, int current_mana) {
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << turn << " turn" << endl;
    cout << "*player\n Lv: " << level <<" ,exp: " << now_exp << "/" << level_exp 
         << "\n hp: " << cphp <<"/" << php << "\n mp: " << current_mana << "/" << mana
         << "\n power: " << pattack << "\n defense: "<< pdefense <<endl;
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
    cout << "(1)attack  " << "  (2)defense" << endl;
}

void consoleUI::playerTurn(int cphp, int pdefense, int battleselect, int pattack) { 
    if (battleselect == 1) {
        cout << "attack enemy!" << endl;
        cout << "enemy takes " << pattack << " damage." << endl;
    }
    else if (battleselect == 2) {
        cout << "defense body" << endl;
        cout << "hp : " << cphp << "/(defensed)+" << pdefense << endl;
    }
    cout << "\n========== playerTurn End ==========" << endl;
    cout << endl;
    cout << endl;

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
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::showStatusChange(playerStatusSnapShot beforePlayer, playerStatusSnapShot afterPlayer) {
    cout << "========== current player status ==========" << endl;
    cout << "*player" << endl;
    cout << " Lv: " << beforePlayer.level << " ,exp: " << beforePlayer.now_exp << "/" << beforePlayer.level_exp
         << "  ->  " << "Lv: " << afterPlayer.level << " ,exp: " << afterPlayer.now_exp << "/" << afterPlayer.level_exp << endl;
    cout << " hp: " << beforePlayer.current_health << "/" << beforePlayer.health
         << "         -> " << " hp: " << afterPlayer.current_health << "/" << afterPlayer.health << endl;
    cout << " mp: " << beforePlayer.current_mana << "/" << beforePlayer.mana
         << "           -> " << " mp: " << afterPlayer.current_mana << "/" << afterPlayer.mana << endl;
    cout << " power: " << beforePlayer.attack << "          -> " << " power: " << afterPlayer.attack << endl;
    cout << " defense: " << beforePlayer.defense << "        -> " <<" defense: " << afterPlayer.defense << endl;

    cout << "========== current player status ==========" << endl;
    cout << endl;
    cout << endl;
}