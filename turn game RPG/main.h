//main.h
#pragma once
#include <random> // random 

class player {
private:
	int player_health; //player 체력 기본 30/ 최대 150
	int basic_attack; //player 일반 공격 5
	int basic_defense; //일반 방어	

public:
	player();//player 체력 값 초기화

	int getPlayer_health() const;//private 플레이어 체력값 get
	int getPlayer_defense() const;//private 플레이어 방어값 get 
	int playerTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	int getBasic_attack() const;// player 기본 공격
	int basic_attack_cal();//레벨 기능 추가시 공격력 계산
};

class magician {};
class warrior {};
class Assassin {};

class enemy {
private:
	int enemy_health; //enemy 체력 기본 20/ 최대 255			
public:
	enemy(); //enemy 체력 값 초기화
	int getEnemy_health() const;//private 적 체력값 get
	int enemyTakeDamage(int rest_health,int dmg);//데미지를 입었을 때

};

class battle {
private:
	player p; //player status
	enemy e; //enemy status
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
	battle();               // 멤버 초기화
	void startBattle();     // 전체 전투 루프 돌리기
	void battleStatus();    // 스탯 출력
	void playerTurn();      // 사용자 입력 처리
	void enemyTurn();       // 랜덤 AI 행동
	void battleEnd();       // 승패 판단 및 출력
	
};