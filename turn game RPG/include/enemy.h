//enemy.h 

#pragma once
#include <random> // random 
#include "enemySkill.h"
#include "enemySkillDisable.h"
#include "enemyBuff.h"
#include "debuffEnum.h"
 
struct RandomMinMax { // attack, health
	int min;
	int max;
};

class enemy { //homunculus
private:
	int enemy_health; //enemy 전체체력 기본 ?/ 최대 ? (레벨당 최소,최대 hp 설정 필요) 
	int enemyCurrentHealth; // enemy 현재 체력
	int level; //enemy level
	int power; //공격력
	int defense; //방어 선택시 방어력
	int agility; //AGI, 회피율 , 안보여줄꺼임 
	int critical; //CRI, 크리티컬 , 안보여줄꺼임
	int activeBuffTurn; // 현재 버프 지속 턴
	int buffAttack;     // 현재 적용된 공격 버프
	int buffDefense;    // 현재 적용된 방어 버프
	int expReward; //죽을 시, 플레이어에게 줄 경험치
	std::vector<enemySkill> skills; //스킬 목록
	std::vector<enemyBuff> buffs; //버프 목록
	std::vector<deBuff> deBuffs; //디버프 목록
	std::vector<enemySkillDisable> disables; //쿨타임 걸린 스킬 목록
	
	
	
public:
	enemy();
	virtual ~enemy() = default;
	enemy(int minHp, int maxHp, int playerLv); //레벨 별 체력 차이를 위함
	
    //get
	int getEnemy_health() const;//전체 체력 값
	int getEnemyCurrentHealth() const; //현재 체력 값
	int getLevel() const; //현재 레벨
	int getPower() const; //현재 공격력
	int getDefense() const; //방어하기 선택시 방어력
	int getAgility() const; // 회피율
	int getCritical() const; // 크리티컬율
	int getActiveBuffTurn() const; // 현재 버프 지속 턴
	int getBuffAttack() const; 	// 현재 적용된 공격 버프
	int getBuffDefense() const;	// 현재 적용된 방어 버프
	int getExpReward() const; //죽을시, 플레이어에게 줄 경험치
	std::vector<enemySkill> getSkills() const; //스킬 목록
	std::vector<enemyBuff> getBuffs() const; //버프 목록
	std::vector<enemySkillDisable> getDisables() const; //쿨타임 걸린 스킬 목록
	std::vector<deBuff> getDeBuffs() const; //디버프 목록

	//set
	void setEnemyCurrentHealth(int hp);
	void setPower(int power);
	void setDefense(std::string enemyType, int level); //0 = 잡몹, 1 = 엘리트 , 2 = 보스 (level에 따라 가산)
	void setAgility(int agi);
	void setCritical(int cri);
	void setExpReward(int playerLv, int enemyLv,int mapFloor ,const std::string& enemyType);
	void pushDeBuff(std::string deBuffName, int agiDown, int criDown,
					int defenseDown, int attackDown, int stack,
					int remainingTurn, bool active);
	
	//other
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	

	//virtual
	virtual RandomMinMax setEnemy_health(int enemyLv, std::string enemyType);
	virtual void setLevel(int enemyLv); // 엘리트 몹, 보스 몹은 레벨이 정해져있기 때문에 랜덤x
	virtual RandomMinMax randomPower(int enemyLv, std::string enemyType);//몹의 레벨과 잡,엘리트,보스에 따라 나뉨
	virtual void decidePower(RandomMinMax minMax); //공격력 최소와 최대에서 랜덤화 뽑은 후 setPower에 보내기
	virtual int enemyAction();
};	

//one
class one : public enemy { //눈 하나
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹

	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
public:
	one();
	one(const enemy& e);

	//override
	RandomMinMax setEnemy_health(int enemyLv, std::string enemyType) override;
	RandomMinMax randomPower(int enemyLv, std::string enemyType) override;
	void decidePower(RandomMinMax minMax) override;
	void setLevel(int playerLv) override;
	int enemyAction() override;

};

//two
class two : public enemy { //눈 둘
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	two();
	virtual ~two() = default;
	two(const enemy& e);
};
class eliteTwo : public enemy { //엘리트 몹 눈 둘
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	eliteTwo();
	eliteTwo(const enemy& e);
};

//three
class three : public enemy { //눈 셋
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	three();
	virtual ~three() = default;
	three(const enemy& e);
};
class eliteThree : public enemy { //엘리트 몹 눈 셋
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	eliteThree();
	eliteThree(const enemy& e);
};

//four
class four : public enemy { //눈 넷
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	four();
	virtual ~four() = default;
	four(const enemy& e);
};
class eliteFour : public enemy { //엘리트 몹 눈 넷
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	eliteFour();
	eliteFour(const enemy& e);
};

//five
class five : public enemy { //눈 다섯
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	five();
	virtual ~five() = default;
	five(const enemy& e);
};
class eliteFive : public enemy { //엘리트 몹 눈 다섯
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	eliteFive();
	eliteFive(const enemy& e);
};


//boss
class oneFloorBoss : public enemy { //1층 보스
private:
	std::string enemyType; //잡몹, 엘리트 몹, 보스 몹
public:
	oneFloorBoss();
	oneFloorBoss(const enemy& e);
};