//skillEnum.h

#pragma once
#include <string>
#include "debuffEnum.h"
#include "skillReferenceStatus.h"

struct skill {
	std::string charactorClass{ "" };  // class
	std::string name{ "unknown" }; // skill name
	std::string targetObject{ "player" }; //skill target (player,enemy)
	std::string imgName{ "" };
	std::string script{""};
	int power{0}; // 최종데미지에 +power 만큼 추가 데미지
	float TDMultiplier{1.0}; // 토탈데미지에 % 만큼 추가데미지
	float playerMultiplier{0.0}; //attack, heal ,defense * etc
	referenceStatus referenceStatus{referenceStatus::none}; //totalDamage, defense,attack, maxHp etc
	int contractCost{0}; //tiferet
	int mpCost{0};
	int activeTime{1}; // active passive skill time(turn) //activeTime 적어놓은 턴보다 -1 턴만 유지 되기에 그걸 생각하고 쓸 것 / 즉 1로 설정하면 담턴에 꺼져있음
	int turn{1}; // CT: turn 쿨타임
	int levelReq{1}; // level required 레벨 제한
	int enemyCnt{1}; // attack anemy number count (enemy 1, 2, 3) 몇명의 적을 때릴수 있는지
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
enum class tiferetSkill { //12개 구체
	//lv2
	overLapping, //다음 계약스킬 강화 , -1구체
	doubleAttack,  // totalDamage = 2*(dmgcalculator(attack = attack * 0.8)) 
	//lv3 
	strength, // attack * 0.2 , 2turn , -1구체 / 강화 시, 3턴
	defenseUp, // defense += defense * 0.2
	//lv4
	reflection, // defenseAttack = defense + (defense * 0.7) / totalDmg = defenseAttack * 1.2 / 왜쓰냐? 주사위 랜덤 안해서 방어력 비례 고정 뎀지임
	scarring, // 출혈(bleed) 3턴, totalDamage * 0.9
	//lv5	
	disarrayAttack, // totalDamage * 0.8 , 혼란(2턴간 적이 플레이어 공격시 30% 확률로 자해 enemy totalDmg -60%) 
	//lv6
	chainOfPact, //계약의 사슬, 2턴간 받는 피해의 50%를 적도 같이 데미지를 받음(반사아님), -2구체 / 강화 시, 60%
					/*
						player.cpp:패시브로 나한테 사슬 걸어놓고, 패시브가 유지중일 때 상대방한테 공격을 받으면
						enemy.cpp: player buff 목록에 사슬버프가 있다면 절반 데미지를 자신도 데미지를 입게끔 하면 될듯.
					*/
	bladeOfOath, //계약의 검 (약점 공격), 치명타율 100% , totalDamage에 1.8배 ,-3구체 / 강화 시, 2.2배 
	//lv7
	theLightOfTruth, //진실의 빛 , 모든 cc기로부터 2턴 무효화 , -3구체 / 강화 시 3턴 /한번 사용시 그 전투에서 더이상 사용 불가
						/*enemy의 debuff 스킬이 사용될 때 만약 player의 버프 목록에 이 스킬이 있다면
							debuff는 안들어가게끔 if else로 enemy 턴에서 나눠주기 이건 player쪽에서 못함
						*/
	contractOfGuardian,//수호자의 계약, 치명적 일격(HP -40%) 한번 받는 데미지의 절반 무효화 , -3구체 /강화 시, 한번 받는 데미지 전부 무효화 
	//lv8
	halfSlash, // 거합, attack*=1.9 , 치명타 확률 +20%, -3구체 / 강화 시, attack*= 2.4, 치명타 확률 +40%
	overclock, // 최대 6개까지의 구체 지정 사용 가능, 3턴동안 -1 구체당 최종데미지(totalDmg +10%, max +60%)/ 강화 불가능
	//lv9 
	weaponMaster, //만병지왕의 계약, -6 구체 / 이번 싸움이 끝날 때까지 모든 스킬 구체 사용량 1개 줄여줌 /강화 불가능
	covenantUltima, //최후의 계약 , -7구체 / 체력 50% 회복 + 2턴 무적 /강화 시, 65% 회복 + 2턴 무적 /한번 사용시 그전투에서 더이상 사용 불가
	//lv10
	im, // 나는 계약  /-3 구체 /강화 불가능
	slash, //벤다 계약  /-4 구체 /강화 불가능
	you //너를 계약 3개다 활성화 시 방어무시 상대방 최대 체력 60% /-3 구체 / 강화 불가능 / overclock 중복 불가
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
