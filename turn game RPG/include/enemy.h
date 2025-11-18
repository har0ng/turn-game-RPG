//enemy.h 

#pragma once
#include <random> // random 
#include <memory>

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
	/*int defense; *///방어 선택시 방어력
	int agility; //AGI, 회피율 , 안보여줄꺼임 
	int critical; //CRI, 크리티컬 , 안보여줄꺼임
	int activeBuffTurn; // 현재 버프 지속 턴
	int buffAttack;     // 현재 적용된 공격 버프
	int buffDefense;    // 현재 적용된 방어 버프
	int expReward; //죽을 시, 플레이어에게 줄 경험치
	int playerLevel;
	std::vector<enemySkill> skills; //스킬 목록
	std::vector<enemyBuff> buffs; //버프 목록
	std::vector<deBuff> deBuffs; //디버프 목록
	std::vector<enemySkillDisable> disables; //쿨타임 걸린 스킬 목록
	std::string enemyType; //적 타입

public:
	enemy();
	enemy(int playerLv);
	virtual ~enemy() = default;
	
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
	int getPlayerLevel() const;
	std::vector<enemySkill> getSkills() const; //스킬 목록
	std::vector<enemyBuff> getBuffs() const; //버프 목록
	std::vector<enemySkillDisable> getDisables() const; //쿨타임 걸린 스킬 목록
	std::vector<deBuff> getDeBuffs() const; //디버프 목록
	std::string getEnemyType() const;

	//set
	void setEnemy_health(int hp);
	void setEnemyCurrentHealth(int hp);
	void setLevel(int enemyLv); // 엘리트 몹, 보스 몹은 레벨이 정해져있기 때문에 랜덤x
	void setPower(int power);
	//void setDefense(std::string enemyType, int level);
	void setAgility(int agi);
	void setCritical(int cri);
	void setExpReward(int playerLv, int enemyLv,int mapFloor ,const std::string& enemyType);
	void setPlayerLevel(int playerLv);
	void pushDeBuff(std::string deBuffName, int stack, int remainingTurn, bool active);
	void setEnemyType(std::string enemyType);
	
	//other
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	std::string randomEnemyType(); //에너미가 normal, elite 중 뭔지 랜덤 지정
	RandomMinMax randomHealth(int enemyLv, std::string enemyType, int floor);//몹의 레벨과 잡,엘리트,보스에 따라 나뉨
	RandomMinMax randomPower(int enemyLv, std::string enemyType, int floor);//몹의 레벨과 잡,엘리트,보스에 따라 나뉨
	int convertEnemyType(std::string enemyType);
																			//void executeDeBuff(std::vector<deBuff> deBuffs);
	const int& decidePower(RandomMinMax minMax); //공격력 최소와 최대에서 랜덤화 뽑은 후 setPower에 보내기

	virtual void decideHealth(RandomMinMax minMax);// 체력의 최소와 최대에서 랜덤으로 뽑은 후 저장
	virtual void decideLevel(int playerLv);
	virtual int enemyAction();
};	

extern std::unique_ptr<enemy> e; //main에서도 쓰일 플레이어 전역 포인터
//extern이기에 데이터타입까지 cpp에 구현해줘야함
void setEnemyTLogic(const int& roomNum, enemy& e);
void setEnemyT(const std::string& EnemyT);
enemy& getEnemyPtr(); // 또는 player* getPlayerPtr();

//normal
class normal : public enemy {
private:
	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
public:
	normal();
	normal(const enemy& e);

	//override
	void decideHealth(RandomMinMax minMax) override;
	void decideLevel(int playerLv) override;
	int enemyAction() override;

};

//elite
class elite : public enemy {
private:
	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
public:
	elite();
	elite(const enemy& e);

	//override
	void decideHealth(RandomMinMax minMax) override;
	void decideLevel(int playerLv) override;
	int enemyAction() override;
};

//boss
class boss : public enemy {
private:
	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
public:
	boss();
	boss(const enemy& e);
	// override
	void decideHealth(RandomMinMax minMax) override;
	void decideLevel(int playerLv) override;
	int enemyAction() override;
};