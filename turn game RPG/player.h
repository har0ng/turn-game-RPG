//player.h

#pragma once
#include <vector>
#include <string>
#include "skillEnum.h"
#include "debuffEnum.h"

struct playerStatusSnapShot { //before ,after 저장 (저장, 스테이터스 상태변화 등등 많이 쓰임)
	int health{0};
	int current_health{0};
	int attack{0};
	int defense{0};
	int level{0};
	int level_exp{0};
	int now_exp{0};
	int mana{0};
	int current_mana{0};
	int agility{0};
	int critical{0};
};

class player {
private:
	int player_health; //player 체력 기본 30
	int player_current_health; //player 현재 체력
	int basic_attack; //player 일반 공격력 5
	int basic_defense; //일반 방어	
	int level; // 현재 레벨
	int level_exp; //총 경험치
	int now_exp; //현재 경험치
	int mana;//총 마나 8 (전직 전)
	int current_mana;//현재 마나
	int agility; //AGI, 회피율 , 안보여줄꺼임 
	int critical; //CRI, 크리티컬 , 안보여줄꺼임
	std::vector<skill> skills; //스킬 목록
	playerStatusSnapShot beforePlayer; // 특정 시기 이전 플레이어 정보(저장, 레벨업 등)
	playerStatusSnapShot afterPlayer; // 특정 시기 이후 플레이어 정보(저장, 레벨업 등)
	debuffStatus debuff; //디버프 값 설정
public:
	player();//player 체력 값 초기화
	virtual ~player() = default; //스마트 포인터가 있더라도 가상 쪽을 지워주지 않으면 override 한 것들이 안지워짐
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
	int getAgility() const; // 회피율
	int getCritical() const; // 크리티컬율
	std::vector<skill> getSkills() const; // 스킬 목록
	playerStatusSnapShot getBeforePlayer() const; //저장 전 혹은 싸움 전 플레이어 데이터
	playerStatusSnapShot getAfterPlayer() const; //저장 후 혹은 싸움 후 플레이어 데이터
	debuffStatus getDebuff() const; //디버프 목록

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
	void setDebuff(int deffnum);
	

	int playerTakeDamage(int dmg);//데미지를 입었을 때
	int playerTakeExp(int take_exp); //현재 경험치 + 받은 경험치	

	//virtual
	virtual void levelup();//레벨 업 할 때.
	virtual bool classChangeYN() const; //전직 했는지 안했는지 확인
	virtual void initSkills(); //직업에 따른 스킬을 따로 vector에 저장하기 위해 override
	virtual std::string getClassName(); //자신의 직업에 대한 클래스 함수가 무엇인지 알기위함.

	//json
	void skillClear(); //스킬 초기화
	void roadSkillsToJson(); //직업에 필요한 스킬들을 json에서 빼오기 위해 필요
	debuffStatus stringToDebuff(const std::string& str); // //string → enum 변환용
	std::string debuffToString(debuffStatus debuff); //enum -> string 변환용
};

//전직은 get, set을 이용해 자식클래스에서 새로운 변수 안만들고 부모 활용.
//if player level == 2, give to class
class warrior :public player {
public:
	warrior();
	warrior(const player& p);
	void levelup() override;
	bool classChangeYN() const override;
	void initSkills() override;
	std::string getClassName() override;
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
	void initSkills() override;
	std::string getClassName() override;

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
	void initSkills() override;
	std::string getClassName() override;

	/*
	int assassin_health;  // 2 level : +4 , +1 levelup : +2
	int assassin_attack;  // 2 level : +4 , +2 levelup : +1
	int assassin_defense;  // 2 level : +1, +3 levelup : +1
	int assassin_mana; // 2 level : +15 , +1 level up : +2
	int agility; // 2 level : +3
	*/
};

