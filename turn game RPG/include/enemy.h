//enemy.h 

#pragma once
#include <random> // random 


class enemy { //homunculus
private:
	int enemy_health; //enemy 전체체력 기본 ?/ 최대 ? (레벨당 최소,최대 hp 설정 필요) 
	int enemyCurrentHealth; // enemy 현재 체력
	int level; //enemy level
	int power; //공격력

	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
	
public:
	enemy();
	virtual ~enemy() = default;
	enemy(int minHp, int maxHp, int playerLv); //레벨 별 체력 차이를 위함
	//get
	int getEnemy_health() const;//전체 체력 값
	int getEnemyCurrentHealth() const; //현재 체력 값
	int getLevel() const; //현재 레벨
	int getPower() const; //현재 공격력

	//set
	void setEnemyCurrentHealth(int hp);

	//other
	int enemyTakeDamage(int rest_health, int dmg);//데미지를 입었을 때
	int enemyAction();
};	

/*class chesed :public player { //헤세드
public:
	chesed();
	chesed(const player& p);
	void levelup() override;
	void initSkills() override;
	std::string getClassName() override;
	
		int chesed_health; // 1 level : +10 , +1 levelup : +5
		int chesed_attack; // 1 level : +3 , +2 levelup : +1
		int chesed_defense; // 1 level : +3, +2 levelup : +1
		int chesed_mana; // 1 level : +10 , +1 level up : +2
	

}; */
//one
class one : public enemy { //눈 하나
public:
	one();
	one(const enemy& e);
};
class EliteOne : public one { //엘리트 몹 눈 하나
public:
	EliteOne();
	EliteOne(const one& one);
};

//two
class two : public enemy { //눈 둘
public:
	two();
	two(const enemy& e);
};
class EliteTwo : public two { //엘리트 몹 눈 둘
public:
	EliteTwo();
	EliteTwo(const two& two);
};

//three
class three : public enemy { //눈 둘
public:
	three();
	three(const enemy& e);
};
class EliteThree : public three { //엘리트 몹 눈 둘
public:
	EliteThree();
	EliteThree(const three& three);
};

//four
class four : public enemy { //눈 둘
public:
	four();
	four(const enemy& e);
};
class EliteFour : public four { //엘리트 몹 눈 둘
public:
	EliteFour();
	EliteFour(const four& four);
};

//five
class five : public enemy { //눈 둘
public:
	five();
	five(const enemy& e);
};
class EliteFive : public five { //엘리트 몹 눈 둘
public:
	EliteFive();
	EliteFive(const five& five);
};

//six
class six : public enemy { //눈 둘
public:
	six();
	six(const enemy& e);
};
class EliteSix : public six { //엘리트 몹 눈 둘
public:
	EliteSix();
	EliteSix(const six& six);
};

//seven
class seven : public enemy { //눈 둘
public:
	seven();
	seven(const enemy& e);
};
class EliteSeven : public seven { //엘리트 몹 눈 둘
public:
	EliteSeven();
	EliteSeven(const seven& seven);
};

//eight
class eight : public enemy { //눈 둘
public:
	eight();
	eight(const enemy& e);
};
class EliteEight : public eight { //엘리트 몹 눈 둘
public:
	EliteEight();
	EliteEight(const eight& eight);
};

//nine
class nine : public enemy { //눈 둘
public:
	nine();
	nine(const enemy& e);
};
class EliteNine : public nine { //엘리트 몹 눈 둘
public:
	EliteNine();
	EliteNine(const nine& nine);
};

//ten


//eleven