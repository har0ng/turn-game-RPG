//skillEnum.h

#pragma once
#include <string>
#include "debuffEnum.h"
#include "skillReferenceStatus.h"

struct skill {
	std::string charactorClass{""};  // class
	std::string name{"unknown"}; // skill name
	std::string targetObject{"player"}; //skill target (player,enemy)
	int power{0}; // totalDamage = totalDamage + power 
	float TDMultiplier{1.0}; // totalDamage *
	float playerMultiplier{0.0}; //attack, heal ,defense * etc
	referenceStatus referenceStatus{referenceStatus::none}; //totalDamage, defense,attack, maxHp etc
	int hpCost{0}; //berserker
	int mpCost{0};
	int activeTime{1}; // active passive skill time(turn) //activeTime 적어놓은 턴보다 -1 턴만 유지 되기에 그걸 생각하고 쓸것
	int turn{1}; // CT: turn
	int levelReq{1}; // level required
	int enemyCnt{1}; // attack anemy number count (enemy 1, 2, 3)
	bool passiveActive{false}; //true == active / false == passive , turn을 확인하는 문구를 넣기 위함.
	debuffStatus debuff{debuffStatus::none}; //debuff

	//true이면 반환.기존 객체가 다른 객체보다 작을 때 기존 객체 반환, 기준은 name
	bool operator<(const skill& other) const {
		return name < other.name; // std::string의 < 사용
	}
	bool operator==(const skill& other) const {
		return name == other.name; // 이름이 같으면 같은 스킬로 간주
	}
};


//Skillname
enum class commonSkill { // 공용 1레벨
	powerStrike, //totaldamage * 1.3
	heal, // maxhp *0.2
};
//2레벨 부터 직업 스킬 분류
enum class tiferetSkill {
	//lv2
	doubleAttack = 2,  // totalDamage = 2*(dmgcalculator(attack = attack * 0.8)) 
	//lv3 
	strength, // attack * 0.2 , 2turn
	defenseUp, // defense += defense * 0.2
	//lv4
	reflection, // defense * 0.7
	scarring, // 출혈(bleed) 3턴, totalDamage * 0.9
	//lv5
	disarrayAttack, // totalDamage * 0.8 , enemy turn delete
	//lv6
	overLapping, //다음 계약 강화 , -1구체
	onePointStrike, //일점 공격
	//lv7
	theLigthOfTruth, //진실의 빛 , 모든 cc기로부터 3턴 무효화 , -2구체 / 강화 시 5턴
	contractOfGuardian,//수호자의 계약, 치명적 일격(HP -40%) 한번 무효화 , -2구체 /강화 시, 두번
	//lv8
	overStrength, //극한 강화 , -3구체

	//lv9 

	//lv10

	//lv11
	im, // 나는 계약  /-3 구체
	slash, //벤다 계약  /-4 구체
	you //너를 계약 3개다 활성화 시 필살 일격 /-3 구체
};
		
enum class chesedSkill{ //그림자
		//lv6
		
		//lv7
		
		//lv8

		//lv9
		
		//lv10

		//lv11
		leviathan //totalDamage * 1.1 + 50
};
enum class gevurahSkill { //파동
	//lv8
	overrode // on/off
};

enum class malkuthSkill { //원소
	//lv2
	magicArrow = 2, // totalDamage = attack 
	magicGard,
	//lv3
	fireball,
	waterball,
	//lv4
	stoneEdge,
	//lv5
	blaze,
	wave,
	//lv6 
	lightning,
	freeze,
	//lv7

	//lv8
	overrode, // on/off
	//lv9
	lightingStorm,
	freezeBreak,
	//lv10
	meteor,
	//lv11
	RedSpiderLily,
	absoluteZero
};

enum class yesodSkill { //역장(비틀림)
	//lv2
	speedUp = 2,

	//lv3
	//lv4
	//lv5
	//lv7
	hiding
	//lv8
	//lv9
	//lv10
};
enum class binahSkill { //관념(클로버, 금전)

};
