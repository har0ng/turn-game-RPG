//skillEnum.h

#pragma once
#include <string>
#include "debuffEnum.h"

struct skill {
	std::string charactorClass{""};  // class
	std::string name{"unknown"}; // skill name
	std::string targetObject{"player"}; //skill target (player,enemy)
	int power{0}; // totalDamage = totalDamage + power 
	float multiplier{1.0}; // totalDamage * , power *
	int hpCost{0}; //berserker
	int mpCost{0};
	int activeTime{1}; // active passive skill time(turn)
	int turn{1}; // CT: turn
	int levelReq{1}; // level required
	int enemyCnt{1}; // attack anemy number count (enemy 1, 2, 3)
	debuffStatus debuff; //debuff
};



enum class commonSkill {
	powerStrike, //totaldamage * 1.2
	heal, // maxhp *0.2
	antiDebuff //debuff remove
};
enum class warriorSkill {
	//lv2
	strength = 2, // attack * 1.3 , 3turn
	doubleAttack, // totalDamage = 2*(dmgcalculator(attack = attack * 0.8)) 
	//lv3 
	defenseUp, // defense += defense * 1.2
	reflection, // defense * 0.7
	//lv4
	disarrayAttack, // totalDamage * 0.8 , enemy turn delete
	scarring // 
	//lv5
	
	//lv6

};

enum class warriorA {

};
enum class warriorB{
		//lv7
		berserker, /* warrior attack skill mpCost instead hpCost(mpCost/2, 0.4/down, 0.5/up)
					,attack * 1.8, on/off */
		//lv10
		leviathan //totalDamage * 1.1 + 50
};
enum class magicianSkill {
	//lv2
	magicArrow = 2, // totalDamage = attack 
	magicGard,
	//lv3
	fireball,
	waterball,
	//lv4
	lightning,
	stoneEdge,
	freeze,
	//lv5
	blaze,
	wave,
	//lv6
	lightingStorm,
	freezeBreak
};

enum class magicianA {
	//lv8
	overrode, // on/off
	//lv9

	//lv10
	meteor,
	RedSpiderLily,
	absoluteZero
};
enum class magicianB {
	//lv8
	overrode // on/off
};
enum class assassinSkill {
	//lv2
	poison = 2,
	speedUp
	//lv3
	//lv4
	//lv5
	//lv6

};
enum class assassinA {

};
enum class assassinB {
	//lv7
	hiding
	//lv8
	//lv9
	//lv10
};