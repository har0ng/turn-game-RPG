//battle.h

#pragma once
#include <memory> //smart pointer
#include "enemy.h"
#include "player.h"
#include "attackInfo.h"

class battle {
private:
	std::unique_ptr<player>& p;  //player status, smart pointer
	std::unique_ptr<enemy>& e; //enemy status, smart pointer
	int php{ 0 };       // player health
	int cphp{ 0 };	   // player current health
	int pattack{ 0 };   //player attack
	int pdefense{ 0 };  //player defense
	int level{ 0 }; //player level
	int battleselect{ 0 }; //player action select
	int level_exp{ 0 }; //총 경험치
	int now_exp{ 0 }; //현재 경험치
	int mana{ 0 };
	int current_mana{ 0 };
	int agility{ 0 }; //AGI, 회피율
	int critical{ 0 }; //CRI, 크리티컬(데미지 2배)
	int skillSelect{ 0 }; // battleSelect == 3 
	debuffStatus debuff; // debuff
	attackInfo attackData; //player 공격 계수 정보

	int ehp{ 0 };       // enemy health
	int echp{ 0 };
	int eattack{ 0 }; //enemy attack

	int turn{ 0 };

	//tiferet 전용
	int contract{ 0 }; //tiferet 아니면 0
	bool amplifyActivate{ false }; //계약 강화 true false

	std::mt19937 gen; //seed random
	std::random_device rd; //seed create


public:
	battle(std::unique_ptr<player>& _p, std::unique_ptr<enemy>& _e);  // 멤버 초기화
	void statusManager();
	void showGetSkill(std::vector<skill> beforeTest, std::vector<skill> afterTest);
	void playerTurn(const int& input, int skillInput = 1);      // 사용자 입력 처리
	void enemyTurn(const int& action);       // 랜덤 AI 행동
	void battleEnd();       // 승패 판단 및 출력
	void battleEndManager(); //전투 종료후 사후 처리
	int getSkillSelect(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //스킬 뭐쓰는지 입력 받아오기
	void getSkillReference(int skillSelect, std::vector<skill> const& skill, attackInfo attackData, int finalAttack);
	void passiveSkill(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //passive 스킬 처리
	int activeSkill(int skillSelect, std::vector<skill> const& skill, attackInfo attackData); //acrive 스킬 처리

	int attackEnemy(bool criticalYN,int criattack, int attack, float totalDamageBuff = 1.0f); //플레이어가 에너미 공격
	attackInfo atkInfo();
	void skillCost(int contractCost, int mpCost);
	
};