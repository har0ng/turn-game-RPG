//battle.cpp

#include <iostream>
#include "main.h"
#include <random>
#include <algorithm> // std::max

using std::cout;
using std::endl;
using std::cin;


battle::battle(): gen(rd()) { //정보 받아옴.
	php = p.getPlayer_health(); // user 체력 get으로 받아오기
	ehp = e.getEnemy_health(); //enemy 체력 get으로 받아오기
	pattack = p.getBasic_attack(); // user 공격력 get으로 받아오기
	pdefense = p.getPlayer_defense(); // user 방어력 get으로 받아오기
	eattack = 0; //enemy 공격력은 private 이니 0으로 미리 초기화
	battleselect = 0; // battle menu select 값 또한 실행하면서 값을 받아와야하니, private이기도 하고 0 으로 미리 초기화
	turn = 0; // 몇번째 턴인지 알려주기위함.
};

void battle::startBattle() { //배틀 시작
	while (php > 0 && ehp > 0) { //체력이 0 이하가 되는 순간 종료
		battleStatus(); //유저와 적의 상황(체력 공격력 등)
		playerTurn(); //유저 턴
		enemyTurn(); //enemy 턴
	}
	battleEnd(); // 전투 종료
};

void battle::battleStatus() {
	//player
	std::uniform_int_distribution<unsigned int> enemyDamage(4, 7); //랜덤 범위 조정
	eattack = enemyDamage(gen); //범위 내 초기화된 수 랜덤화
	turn++; //몇턴 째인지 알려주기
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
		ehp = e.enemyTakeDamage(ehp, pattack); //enemy 남은 체력 계산

	}
	else if (battleselect == 2) {//defense
		cout << "defense body" << endl;
		cout << "hp : " << php << "/(defensed)+" << pdefense << endl; // 더하는게 아닌 임시 체력
	}
	else {// !!Error caution 1 or 2 를 입력하지 않고 다른걸 입력했을 때 턴이지나가게끔 해놓은것인데 아무런 입력이 없고 턴이 넘어가지 않게 방지 해놓을 것
		cout << "Invalid input. Skipping turn." << endl; 
		battleselect = 0;
	}
};

void battle::enemyTurn() {//enemy 턴으로 실행 시켜줘야함.
	
	std::uniform_int_distribution<unsigned int> dist(0, 2);/*enemy 행동 0 = 상황을 살피고 있다
																				,1 = 공격
																				,2 = 공격*/
	int enemy_action = dist(gen);
	if (enemy_action == 0) { // 상황을 지켜보는 action
		cout << "enemy action : " << "assess the situation" << endl;
	}
	else if (enemy_action == 1 || enemy_action == 2) { //enemy의 공격 
		cout << "enemy attacked!" << endl;//attack
		if (battleselect == 2) {
			int damage = std::max(0, eattack - pdefense); //방어력과 enemy의 공격력 계산, 만약 공격력이 0미만이 되버리면 오버플로어라 max 0값 조정
			php -= damage; // 체력 깎기
		}
		else {
			php = std::max(0, php - eattack);
		}
	}
};

void battle::battleEnd() {
	cout << "========== Battle End ==========" << endl;
	if (php <= 0) { // user hp == 0
		cout << "lose player" << endl;
	}
	else { //enemy hp == 0
		cout << "wins player!" << endl;
	}
};