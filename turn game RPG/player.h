#pragma once

class player {
private:
	int player_health; //player 체력 기본 30/ 최대 150
	int basic_attack; //player 일반 공격 5
	int basic_defense; //일반 방어	
	int level; // 현재 레벨 , 미구현
	int level_exp; //총 경험치	, 미구현
	int now_exp; //현재 경험치 , 미구현

public:
	player();//player 체력 값 초기화

	int getPlayer_health() const;//private 플레이어 체력값 get
	int getPlayer_defense() const;//private 플레이어 방어값 get 
	int playerTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	int getBasic_attack() const;// player 기본 공격
	int getLevel() const; //현재 레벨
	int getLevel_exp() const; //총 경험치
	int getNow_exp() const; //현재 경험치
	int playerTakeExp(int rest_exp, int take_exp); //현재 경험치 + 받은 경험치
	int basic_attack_cal();//레벨 기능 추가시 공격력 계산

	void levelup();//레벨 업 할 때.


	virtual ~player(); //override 부모 삭제
};

//charactor class to override player
//if player level == 2, give to class
class warrior :public player {
private:
	int warrior_health; // 2 level : +10 , +1 levelup : +5
	int warrior_attack; // 2 level : +3 , +3 levelup : +1
	int warrior_defense; // 2 level : +3, +3 levelup : +1
	int warrior_mana; // 2 level : +10 , +1 level up : +2

public:
	warrior();

};
class magician :public player {
private:
	int magician_health; // 2 level : +5 , +1 levelup : +2
	int magician_attack; // 2 level : +1 , +4 levelup : +1
	int magician_defense; // 2 level : +1, null
	int magician_mana; // 2 level : +25 , +1 level up : +5

public:
	magician();

};
class assassin :public player {
private:
	int assassin_health;  // 2 level : +4 , +1 levelup : +2
	int assassin_attack;  // 2 level : +4 , +2 levelup : +1
	int assassin_defense;  // 2 level : +1, +2 levelup : +1
	int assassin_mana; // 2 level : +15 , +1 level up : +2

public:
	assassin();

};
