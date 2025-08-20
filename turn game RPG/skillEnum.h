//skillEnum.h

#pragma once
#include <string>

struct skill {
	std::string charactorClass; // class
	std::string name; // skill name
	int power; // totalDamage = totalDamage + power 
	float multiplier; // totalDamage * , power *
	int HpCost; //berserker
	int mpCost;
	int activeTime; // active passive skill time(turn)
	int turn; // CT: turn
	int levelReq; // level required
};
enum class commonSkill {
	powerStrike, //totaldamage * 1.2
	heal // maxhp *0.2
};
enum class warriorSkill {
	//lv2
	strength = 2, // attack * 1.6 , 3turn
	doubleAttack, // totalDamage = 2*(dmgcalculator(attack = attack * 0.8)) 
	//lv3 
	defenseUp, // defense += defense * 1.2
	reflection, // defense * 0.7
	//lv4
	disarrayAttack, // totalDamage * 0.8 , enemy turn delete
	
	//lv5
	//lv6

	//lv7
	berserker, /* warrior attack skill mpCost instead hpCost(mpCost/2), attack * 2.0, on/off */
	//lv8

	//lv9

	//lv10
	leviathan
};
enum class magicianSkill {
	//lv2
	magicArrow = 2,
	magicGard,
	//lv3
	fireball,
	wave,
	//lv4
	lightning,
	stoneEdge,
	freeze,
	//lv5
	//lv6
	//lv7
	//lv8
	overrode, // on/off
	//lv9

	//lv10
	meteor,
	RedSpiderLily,
	absoluteZero
};
enum class assassinSkill {
	//lv2
	poison = 2,
	speedUp,
	//lv3
	//lv4
	//lv5
	hiding,
	//lv6
	//lv7
	//lv8
	marionette,
	//lv9
	//lv10
};