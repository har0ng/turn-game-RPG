#pragma once

struct playerStatusSnapShot { //before ,after 저장
	int health;
	int current_health;
	int attack;
	int defense;
	int level;
	int level_exp;
	int now_exp;
	int mana;
	int current_mana;
};
class player {
private:
	int player_health; //player 체력 기본 30/ 최대 150
	int player_current_health; //player 현재 체력
	int basic_attack; //player 일반 공격 5
	int basic_defense; //일반 방어	
	int level; // 현재 레벨
	int level_exp; //총 경험치
	int now_exp; //현재 경험치
	int mana;//총 마나 0 (전직 전)
	int current_mana;//현재 마나
	int agility; //AGI, 회피율
	int critical; //CRI, 크리티컬
	playerStatusSnapShot beforePlayer; // 특정 시기 이전 플레이어 정보(저장, 레벨업 등)
	playerStatusSnapShot afterPlayer; // 특정 시기 이후 플레이어 정보(저장, 레벨업 등)

public:
	player();//player 체력 값 초기화
	//get
	int getPlayer_health() const;//private 플레이어 체력값 get
	int getPlayer_current_health() const;//현재 체력
	int getPlayer_defense() const;//private 플레이어 방어값 get
	int getBasic_attack() const;// player 기본 공격
	int getLevel() const; //현재 레벨
	int getLevel_exp() const; //총 경험치
	int getNow_exp() const; //현재 경험치
	int getMana() const; //총 마나
	int getCurrent_mana() const; //현재 마나
	int getAgility() const;
	int getCritical() const;
	playerStatusSnapShot getBeforePlayer() const;
	playerStatusSnapShot getAfterPlayer() const;

	//set
	void setPlayer_health(int hp); //전직 시 새롭게 정의
	void setPlayer_current_health(int hp);
	void setPlayer_defense(int defense);
	void setBasic_attack(int attack);
	void setMana(int mp);
	void setCurrent_mana(int mp);
	void setLevel(int lev);
	void setLevel_exp(int lev);
	void setNow_exp(int lev);
	void setAgility(int agi);
	void setCritical(int cri);
	void setBeforePlayer();
	void setAfterPlayer();


	int playerTakeDamage(int dmg);//데미지를 입었을 때
	int playerTakeExp(int take_exp); //현재 경험치 + 받은 경험치	
	int basic_attack_cal();//레벨 기능 추가시 공격력 계산 , 미구현

	virtual void levelup();//레벨 업 할 때.
	virtual bool classChangeYN() const; //전직 했는지 안했는지 확인

	
};

//전직은 get, set을 이용해 자식클래스에서 새로운 변수 안만들고 부모 활용.
//if player level == 2, give to class
class warrior :public player {
public:
	warrior();
	warrior(const player& p);
	void levelup() override;
	bool classChangeYN() const override;

	/*
		int warrior_health; // 2 level : +10 , +1 levelup : +5
		int warrior_attack; // 2 level : +3 , +2 levelup : +1
		int warrior_defense; // 2 level : +3, +2 levelup : +1
		int warrior_mana; // 2 level : +10 , +1 level up : +2
	*/

};
class magician :public player {
public:
	magician();
	magician(const player& p);
	void levelup() override;
	bool classChangeYN() const override;
	/*
	int magician_health; // 2 level : +5 , +1 levelup : +2
	int magician_attack; // 2 level : +1 , +3 levelup : +1
	int magician_defense; // 2 level : +1, null
	int magician_mana; // 2 level : +25 , +1 level up : +5
	*/

};
class assassin :public player {
public:
	assassin();
	assassin(const player& p);
	void levelup() override;
	bool classChangeYN() const override;

	/*
	int assassin_health;  // 2 level : +4 , +1 levelup : +2
	int assassin_attack;  // 2 level : +4 , +2 levelup : +1
	int assassin_defense;  // 2 level : +1, +3 levelup : +1
	int assassin_mana; // 2 level : +15 , +1 level up : +2
	*/
};

