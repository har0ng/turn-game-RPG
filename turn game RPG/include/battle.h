//battle.h

#pragma once
#include <memory> //smart pointer
#include "enemy.h"
#include "player.h"
#include "consoleUI.h"
#include "attackInfo.h"

class battle {
private:
	consoleUI ui;// consoleUI.h 
	std::unique_ptr<player>  p;  //player status, smart pointer
	std::unique_ptr<enemy> e; //enemy status, smart pointer
	int php;       // player health
	int cphp;	   // player current health
	int pattack;   //player attack
	int pdefense;  //player defense
	int level; //player level
	int battleselect; //player action select
	int level_exp; //총 경험치
	int now_exp; //현재 경험치
	int mana;
	int current_mana;
	int agility; //AGI, 회피율
	int critical; //CRI, 크리티컬(데미지 2배)
	int skillSelect; // battleSelect == 3 
	debuffStatus debuff; // debuff
	attackInfo attackData; //player 공격 계수 정보

	int ehp;       // enemy health
	int eattack; //enemy attack

	int turn;
	bool play; //player의 hp의 상태에 따라 게임 지속 가능한지 확인

	std::mt19937 gen; //seed random
	std::random_device rd; //seed create


public:
	battle(std::unique_ptr<player> p, std::unique_ptr<enemy> e);  // 멤버 초기화
	void startBattle();     // 전체 전투 루프 돌리기 , 리턴 해줄게 없어서 void 이하 동문
	void battleStatus();    // 스탯 출력
	void playerTurn();      // 사용자 입력 처리
	void enemyTurn();       // 랜덤 AI 행동
	void battleEnd();       // 승패 판단 및 출력
	void selectClass(); // 전직 결정
	bool getPlay() const;   // 플레이어의 체력이 남아있어 지속 가능한지 확인
	std::unique_ptr<player> getPlayerPtr(); // 플레이어 정보 계속 들고 가야해서 들고 갈 바구니 만든 것
	int inputCheck(int min, int max);

	void getSkillSelect(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //스킬 뭐쓰는지 입력 받아오기
	void passiveSkill(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //passive 스킬 처리
	void activeSkill(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //acrive 스킬 처리

	void attackEnemy(bool criticalYN,int criattack, int attack); //플레이어가 에너미 공격
	attackInfo atkInfo();
	void skillCost(int hpCost, int mpCost);
	void showGetSkill(std::vector<skill> beforeTest, std::vector<skill> afterTest);
};