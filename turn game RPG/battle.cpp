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
	
	//player
	php = p->getPlayer_health(); // user 체력 get으로 받아오기
	cphp = p->getPlayer_current_health(); //user 현재 체력 가져오기
	pattack = p->getBasic_attack(); // user 공격력 get으로 받아오기
	pdefense = p->getPlayer_defense(); // user 방어력 get으로 받아오기
	level = p->getLevel(); // 플레이어 레벨
	level_exp = p->getLevel_exp();//총 경험치
	now_exp = p->getNow_exp(); //현재 경험치
	mana = p->getMana();
	current_mana = p->getCurrent_mana();

	battleselect = 0; // battle menu select 값 또한 실행하면서 값을 받아와야하니, private이기도 하고 0 으로 미리 초기화

	//enemy
	ehp = e->getEnemy_health(); //enemy 체력 get으로 받아오기
	eattack = 0; //enemy 공격력은 private 이니 0으로 미리 초기화
	
	
	//battletime
	turn = 0; // 몇번째 턴인지 알려주기위함.
	//gameover(Y/N)
	play = true;
};

void battle::startBattle() { //배틀 시작
	while (cphp > 0 && ehp > 0) { //체력이 0 이하가 되는 순간 종료
		battleStatus(); //유저와 적의 상황(체력 공격력 등)
		playerTurn(); //유저 턴
		if (ehp <= 0) { //무승부 방지
			break;
		}
		enemyTurn(); //enemy 턴
	}
	battleEnd(); // 전투 종료
	if (p->getLevel() == 2 && p -> classChangeYN()){ // 2레벨 전직, 만약 전직했으면 안뜸
		levelup_selectClass();
	}
};

void battle::battleStatus() {
	std::uniform_int_distribution<unsigned int> enemyDamage(4, 7); //랜덤 범위 조정
	eattack = enemyDamage(gen); //적의 공격력을 범위 내 초기화된 수로 랜덤화
	turn++; //몇턴 째인지 셈
	
	ui.battleStatus(turn, php, cphp, pattack, pdefense, ehp, eattack, level, level_exp, now_exp, mana, current_mana); //log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}	

void battle::playerTurn() {
	ui.playerTurnUI();
	cin >> battleselect;

	if (battleselect == 1) { // 1. 공격 2. 방어
		ehp = e->enemyTakeDamage(ehp, pattack);
	}

	ui.playerTurn(cphp, pdefense, battleselect, pattack);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::enemyTurn() {
	std::uniform_int_distribution<unsigned int> dist(0, 2); // 0. 상황 살피기, 1. 공격, 2. 공격
	int enemy_action = dist(gen);

	// 전투 로직 (데미지 계산 등)
	if (enemy_action == 0) {
		// 상황 살피기 (출력은 UI에서)
	}
	else { 
		if (battleselect == 2) { //player가 방어를 선택 했을 때
			eattack = std::max(0, eattack - pdefense);
			p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
			cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
		}
		else { //player가 방어가 아닌 다른걸 선택 했을 때
			p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
			cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
		}
	}

	ui.enemyTurn(enemy_action, pdefense, eattack, battleselect);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::battleEnd() {
	ui.battleEnd(cphp);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
	if (cphp <= 0) {
		play = false;
		exit(0);
	}	
	else {
		int instance_exp = 5;  // 몬스터의 종류, 레벨에따라 차등 적용해야하는데 임의로 10이라고 쓰고 테스트
		p->playerTakeExp(instance_exp); //player안의 nowexp 값 갱신
		now_exp = p->getNow_exp(); // 갱신된 값으로 초기화
		level_exp = p->getLevel_exp(); //레벨업 시 총 경험치 갱신된 값으로 초기화
	}
}


void battle::levelup_selectClass() { // class change , 전직
	ui.levelup_selectClassUI();
	int selectClass;
	cin >> selectClass;
	ui.levelup_selectClass(level, selectClass);
	if (selectClass == 1) { // Warrior
		p = std::make_unique<warrior>(*p); // player 객체를 warrior로 복사 생성
	}
	else if (selectClass == 2) { // Magician
		p = std::make_unique<magician>(*p);
	}
	else if (selectClass == 3) { // Assassin
		p = std::make_unique<assassin>(*p);
	}
}

bool battle::getPlay() const { //게임이 지속 가능한지 플레이어의 체력이 남아있는지 확인
	return play;
}

std::unique_ptr<player> battle::getPlayerPtr() { // 유니크 포인터를 넘겨야하니깐 이렇게 됨.
	return std::move(p);
}