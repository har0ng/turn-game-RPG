//battle.cpp

#include <iostream>
#include "main.h"
#include <random>
#include <algorithm> // std::max

using std::cout;
using std::endl;
using std::cin;


battle::battle(): gen(rd()) { //정보 받아옴.
	php = p.getPlayer_health();
	ehp = e.getEnemy_health();
	pattack = p.getBasic_attack();
	pdefense = p.getPlayer_defense();
	eattack = 0;
	battleselect = 0;
	turn = 0;
};

void battle::startBattle() {
	while (php > 0 && ehp > 0) {
		battleStatus();
		playerTurn();
		enemyTurn();
	}
	battleEnd();
};

void battle::battleStatus() {
	//player
	std::uniform_int_distribution<unsigned int> enemyDamage(4, 7); //enemy attack random 
	eattack = enemyDamage(gen);
	turn++;
	cout << "========== Battle Status ==========" << endl;
	cout << endl;
	cout << turn << " turn" << endl;
	cout << "player hp: " << php << " / power: " << pattack << endl;
	cout << "enemy hp: " << ehp << " / power: " << eattack << endl;
	cout << endl;
	cout << "========== Battle Status ==========" << endl;
	
}	

void battle::playerTurn() {//player 턴으로 실행 시켜줘야함.
	cout << "select player Action" << endl;
	cout << "(1)attack (damage 5)  " << "(2)defense (defense 5) " << endl;//select
	cin >> battleselect;
	if (battleselect == 1) {//attack
		cout << "attack enemy!" << endl;
		ehp = e.enemyTakeDamage(ehp, pattack);

	}
	else if (battleselect == 2) {//defense
		cout << "defense body" << endl;
		cout << "hp : " << php << "/(defensed)+" << pdefense << endl;
	}
	else {
		cout << "Invalid input. Skipping turn.\n";
		battleselect = 0;
	}
};

void battle::enemyTurn() {//enemy 턴으로 실행 시켜줘야함.
	
	std::uniform_int_distribution<unsigned int> dist(0, 2);/*enemy 행동 0 = 상황을 살피고 있다
																				,1 = 공격
																				,2 = 공격*/
	int enemy_action = dist(gen);
	if (enemy_action == 0) {
		cout << "enemy action : " << "assess the situation" << endl;
	}
	else if (enemy_action == 1 || enemy_action == 2) {
		cout << "enemy attacked!" << endl;//attack
		if (battleselect == 2) {
			int damage = std::max(0, eattack - pdefense);
			php -= damage;
		}
		else {
			php = std::max(0, php - eattack);
		}
	}
};

void battle::battleEnd() {
	cout << "========== Battle End ==========" << endl;
	if (php <= 0) {
		cout << "lose player" << endl;
	}
	else {
		cout << "wins player!" << endl;
	}
};