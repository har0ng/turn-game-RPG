//consoleUI.cpp

#include "consoleUI.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void consoleUI::battleStatus(int turn, int php, int cphp, int pattack, int ehp, int eattack, int level) {
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << turn << " turn" << endl;
    cout << "*player\n Lv: " << level << "\n hp: " << cphp <<"\n power: " << pattack << endl;
    cout << endl;
    cout << "*enemy\n hp: " << ehp << "\n power: " << eattack << endl;
    cout << endl;
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::playerTurnUI() {
    cout << "========== playerTurn Start ==========" << endl;
    cout << "select player Action" << endl;
    cout << "(1)attack (damage 5)  " << "(2)defense (defense 5) " << endl;
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
    cout << "========== playerTurn End ==========" << endl;
    cout << endl;
    cout << endl;

}

void consoleUI::enemyTurn(int enemyAction, int pdefense, int eattack, int battleselect) {
    cout << "========== enemyTurn Start ==========" << endl;
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
    cout << "========== enemyTurn End ==========" << endl;
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