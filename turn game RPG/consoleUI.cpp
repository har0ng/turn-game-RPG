#include "consoleUI.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void consoleUI::battleStatus(int turn, int php, int pattack, int ehp, int eattack) {
	cout << "========== Battle Status ==========" << endl;
	cout << endl;
	cout << turn << " turn" << endl;
	cout << "player hp: " << php << " / power: " << pattack << endl;
	cout << "enemy hp: " << ehp << " / power: " << eattack << endl;
	cout << endl;
	cout << "========== Battle Status ==========" << endl;
}

int consoleUI::playerTurn() {
    int battleselect;
    cout << "select player Action" << endl;
    cout << "(1)attack (damage 5)  " << "(2)defense (defense 5) " << endl;
    while (true) {
        cin >> battleselect;
        if (battleselect == 1 || battleselect == 2) {
            return battleselect;
        }
    }
}

void consoleUI::enemyTurn(int enemyAction, int php, int pdefense, int eattack, int battleselect) {
    if (enemyAction == 0) {
        cout << "enemy action : assess the situation" << endl;
    }
    else {
        cout << "enemy attacked!" << endl;
        if (battleselect == 2) {
            int damage = std::max(0, eattack - pdefense);
            cout << "Player defends and takes " << damage << " damage." << endl;
            cout << "Player hp : " << php << endl;
        }
        else {
            cout << "Player takes " << eattack << " damage." << endl;
            cout << "Player hp : " << php << endl;
        }
    }
}

void consoleUI::battleEnd(int php) {
	cout << "========== Battle End ==========" << endl;
	if (php <= 0) { // user hp == 0
		cout << "lose player" << endl;
	}
	else { //enemy hp == 0
		cout << "wins player!" << endl;
	}
}