//player.h

#pragma once
#include <vector>
#include <string>
#include "skillEnum.h"
#include "buff.h"
#include "skillDisable.h"

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
	debuffStatus debuff{ debuffStatus::none };
	std::vector<skill> skills;
};

struct tiferetStatusSnapShot : public playerStatusSnapShot {
	int contract{ 0 };
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
	std::vector<buff> buffs; //버프 목록
	std::vector<disable> disables; //쿨타임 걸린 스킬 목록
	playerStatusSnapShot beforePlayer; //전투 시작전 상태(레벨업 비교)
	playerStatusSnapShot afterPlayer; //전투 후 상태 데이터(레벨업 비교)
	playerStatusSnapShot battlePlayer; // 매 턴 갱신되는 상태 (버프 미적용 스텟)
	playerStatusSnapShot turnPlayer;   // 매 턴 갱신되는 상태 (버프 적용 스텟)
	debuffStatus debuff; //디버프 값 설정
	referenceStatus reference; //player의 skill 행위의 목적성 확인
	disable dis; //스킬 쿨타임 계산
	int activeBuffTurn; // 현재 버프 지속 턴
	int buffAttack;     // 현재 적용된 공격 버프
	int buffDefense;    // 현재 적용된 방어 버프

	

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
	std::vector<disable> getDisables() const; //쿨타임 스킬목록
	std::vector<buff> getBuff() const; //버프 목록
	debuffStatus getDebuff() const; //디버프 목록
	int getActiveBuffTurn() const; // 현재 버프 지속 턴
	int getBuffAttack() const; 	// 현재 적용된 공격 버프
	int getBuffDefense() const;	// 현재 적용된 방어 버프



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
	void setDebuff(int deffnum);
	

	int playerTakeDamage(int dmg);//데미지를 입었을 때
	int playerTakeExp(int take_exp); //현재 경험치 + 받은 경험치	

	//virtual
	virtual void levelup();//레벨 업 할 때.
	virtual void initSkills(); //직업에 따른 스킬을 따로 vector에 저장하기 위해 override
	virtual std::string getClassName(); //자신의 직업에 대한 클래스 함수가 무엇인지 알기위함.
	
	virtual playerStatusSnapShot& getBeforePlayer(); //전투 시작전 상태(레벨업 비교)
	virtual playerStatusSnapShot& getAfterPlayer(); //전투 후 상태 데이터(레벨업 비교)
	virtual playerStatusSnapShot& getBattlePlayer(); // 매 턴 갱신되는 상태 (버프 미적용 스텟)
	virtual playerStatusSnapShot& getTurnPlayer();   // 매 턴 갱신되는 상태 (버프 적용 스텟)
	
	virtual	void setBeforePlayer();
	virtual	void setAfterPlayer();
	virtual	void setBattlePlayer();
	virtual void setTurnPlayer();
	//json
	void roadSkillsToJson(); //직업에 필요한 스킬들을 json에서 빼오기 위해 필요
	debuffStatus stringToDebuff(const std::string& str); //string → enum 변환용
	std::string debuffToString(debuffStatus debuff); //enum -> string 변환용
	referenceStatus stringToReference(const std::string& str); //string → enum 변환용
	std::string referenceToString(referenceStatus reference); //enum -> string 변환용

	//buff
	void updateBuffedStats();//버프 적용
	void decreaseBuffTurns(int turn); // 턴 감소 처리
	void pushBuff(std::string name, int atk, int def, int remainTurn, bool check, bool amplity);//사용한 버프를 버프목록에 추가
	void clearBuff(); //전투 끝나고 버프 전부 초기화

	//CT
	void skillDisable(int skillSelect, int turn); //스킬 못쓰게 막는 함수
	void skillCT(); //쿨타임 제거
	void clearDisable(); //전투 끝나고 쿨타임 모두 초기화

	//tiferet
	//get
	virtual int getContract() const;
	virtual bool getAmplifyActivate() const;
	//set
	virtual void setContract(int null);
	virtual void setAmplifyActivate(bool YN);
	//other
	
};

//전직은 get, set을 이용해 자식클래스에서 새로운 변수 안만들고 부모 활용.
class tiferet :public player { //티페리트
private:
	int contract; //계약 가능 횟수 12
	bool amplifyActivate; //강화 중인지 판별
	tiferetStatusSnapShot beforePlayer;
	tiferetStatusSnapShot afterPlayer;
	tiferetStatusSnapShot battlePlayer;
	tiferetStatusSnapShot turnPlayer;
public:
	tiferet();
	tiferet(const player& p);
	void levelup() override; //레벨업 시 얻는 스텟이 캐릭터마다 다르기에 override
	void initSkills() override; //스킬을 json에서 받아올껀데 함수가 꽤 커서 override해서 절약
	std::string getClassName() override; //직업 이름이 뭔지 알아야하는데 각 클래스마다 만들기 귀찮아서 override

	//get
	int getContract() const override;
	tiferetStatusSnapShot& getBeforePlayer() override;
	tiferetStatusSnapShot& getAfterPlayer()	override;
	tiferetStatusSnapShot& getBattlePlayer() override;
	tiferetStatusSnapShot& getTurnPlayer() override;
	bool getAmplifyActivate() const override;

	//set
	void setContract(int contract) override; //턴마다 하나씩 추가시켜주기 위함	void setBeforePlayer();
	void setBeforePlayer() override;
	void setAfterPlayer() override;
	void setBattlePlayer() override;
	void setTurnPlayer() override;
	void setAmplifyActivate(bool YN) override;
	
	/*
		int tiferet_health; // 1 level : +10 , +1 levelup : +5
		int tiferet_attack; // 1 level : +3 , +2 levelup : +1
		int tiferet_defense; // 1 level : +3, +2 levelup : +1
		int tiferet_mana; // 1 level : +10 , +1 level up : +2
	*/

};

class chesed :public player { //헤세드
public:
	chesed();
	chesed(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;
	/*
		int chesed_health; // 1 level : +10 , +1 levelup : +5
		int chesed_attack; // 1 level : +3 , +2 levelup : +1
		int chesed_defense; // 1 level : +3, +2 levelup : +1
		int chesed_mana; // 1 level : +10 , +1 level up : +2
	*/

};

class gevurah :public player { //게부라 (누켈라비)
public:
	gevurah();
	gevurah(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;

	/*
	int gevurah_health; // 1 level : +5 , +1 levelup : +2
	int gevurah_attack; // 1 level : +1 , +3 levelup : +1
	int gevurah_defense; // 1 level : +1, null
	int gevurah_mana; // 1 level : +25 , +1 level up : +5
	*/

};

class malkuth :public player { //말쿠트 (아도나이)
public:
	malkuth();
	malkuth(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;

	/*
	int malkuth_health; // 1 level : +5 , +1 levelup : +2
	int malkuth_attack; // 1 level : +1 , +3 levelup : +1
	int malkuth_defense; // 1 level : +1, null
	int malkuth_mana; // 1 level : +25 , +1 level up : +5
	*/

};

class yesod :public player { // 예소드
public:
	yesod();
	yesod(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;

	/*
	int yesod_health;  // 1 level : +4 , +1 levelup : +2
	int yesod_attack;  // 1 level : +4 , +2 levelup : +1
	int yesod_defense;  // 1 level : +1, +3 levelup : +1
	int yesod_mana; // 1 level : +15 , +1 level up : +2
	int agility; // 1 level : +3
	*/
};

class binah :public player { //비나 (에릴림)
public:
	binah();
	binah(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;

	/*
	int binah_health;  // 1 level : +4 , +1 levelup : +2
	int binah_attack;  // 1 level : +4 , +2 levelup : +1
	int binah_defense;  // 1 level : +1, +3 levelup : +1
	int binah_mana; // 1 level : +15 , +1 level up : +2
	int agility; // 1 level : +3
	*/
};