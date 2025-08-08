#pragma once
#include <memory> //smart pointer
#include "enemy.h"
#include "player.h"
#include "consoleUI.h"

class battle {
private:
	consoleUI ui;// UI
	std::unique_ptr<player>  p;  //player status, smart pointer
	std::unique_ptr<enemy> e; //enemy status, smart pointer
	int php;       // player health
	int ehp;       // enemy health
	int pattack;   //player attack
	int pdefense;  //player defense
	int eattack; //enemy attack
	int battleselect; //player action select
	int turn;
	std::mt19937 gen; //seed random
	std::random_device rd; //seed create


public:
	battle(std::unique_ptr<player> p, std::unique_ptr<enemy> e);  // 멤버 초기화
	void startBattle();     // 전체 전투 루프 돌리기 , 리턴 해줄게 없어서 void 이하 동문
	void battleStatus();    // 스탯 출력
	void playerTurn();      // 사용자 입력 처리
	void enemyTurn();       // 랜덤 AI 행동
	void battleEnd();       // 승패 판단 및 출력

};