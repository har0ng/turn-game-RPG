//skillReferenceStatus.h
#pragma once
#include <string>

enum class referenceStatus { //스킬 사용 목적 및 구분을 위함
	//Debug
	none,
	//passive
	attack,
	defense,
	//active
	totalDamage,
	maxHp,
	playerDebuff,
	tatalDamageAndAttack,
};