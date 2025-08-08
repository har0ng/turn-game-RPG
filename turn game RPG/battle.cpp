//battle.cpp

#include "player.h"
#include "enemy.h"
#include "consoleUI.h"
#include "battle.h"

#include <iostream>
#include <random>
#include <algorithm> // std::max
#include <memory> // smart pointer

using std::cout;
using std::endl;
using std::cin;
using std::unique_ptr;

battle::battle(unique_ptr<player> _p , unique_ptr<enemy> _e)
	: p(std::move(_p)), e(std::move(_e)), gen(rd()) { //정보 받아옴.
	php = p->getPlayer_health(); // user 체력 get으로 받아오기
	ehp = e->getEnemy_health(); //enemy 체력 get으로 받아오기
	pattack = p->getBasic_attack(); // user 공격력 get으로 받아오기
	pdefense = p->getPlayer_defense(); // user 방어력 get으로 받아오기
	eattack = 0; //enemy 공격력은 private 이니 0으로 미리 초기화
	battleselect = 0; // battle menu select 값 또한 실행하면서 값을 받아와야하니, private이기도 하고 0 으로 미리 초기화
	turn = 0; // 몇번째 턴인지 알려주기위함.
};

void battle::startBattle() { //배틀 시작
	while (php > 0 && ehp > 0) { //체력이 0 이하가 되는 순간 종료
		battleStatus(); //유저와 적의 상황(체력 공격력 등)
		playerTurn(); //유저 턴
		if (ehp <= 0) { //무승부 방지
			break;
		}
		enemyTurn(); //enemy 턴
	}
	battleEnd(); // 전투 종료
};

void battle::battleStatus() {
	std::uniform_int_distribution<unsigned int> enemyDamage(4, 7); //랜덤 범위 조정
	eattack = enemyDamage(gen); //범위 내 초기화된 수 랜덤화
	turn++; //몇턴 째인지 셈
	
	ui.battleStatus(turn, php, pattack, ehp, eattack); //log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}	

void battle::playerTurn() {
	battleselect = ui.playerTurn();  //log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기

	if (battleselect == 1) {
		cout << "attack enemy!" << endl;
		ehp = e->enemyTakeDamage(ehp, pattack);
	}
	else if (battleselect == 2) {
		cout << "defense body" << endl;
		cout << "hp : " << php << "/(defensed)+" << pdefense << endl;
	}
}

void battle::enemyTurn() {
	std::uniform_int_distribution<unsigned int> dist(0, 2);
	int enemy_action = dist(gen);

	// 전투 로직 (데미지 계산 등)
	if (enemy_action == 0) {
		// 상황 살피기 (출력은 UI에서)
	}
	else {
		if (battleselect == 2) {
			int damage = std::max(0, eattack - pdefense);
			php -= damage;
		}
		else {
			php = std::max(0, php - eattack);
		}
	}

	ui.enemyTurn(enemy_action, php, pdefense, eattack, battleselect);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::battleEnd() {
	ui.battleEnd(php);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
};	