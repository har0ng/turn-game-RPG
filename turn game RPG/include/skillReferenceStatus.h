//skillReferenceStatus.h
#pragma once

enum class referenceStatus { //스킬 사용 목적 및 구분을 위함 (만들꺼면 totalDamage만 만들껄..)
	//Debug
	none, //버그임!
	notSpecified, //어디에도 포함 안 될 때
	//passive
	attackBuff, //공격력
	defenseBuff, //방어력
	totalDamageBUff, //최종데미지
	//active
	totalDamage, //최종데미지
	maxHp, //최대 체력 비례
	dispelDebuff, //디버프 해제
	totalDamageAndAttack, //기본 공격력 상승과 최종데미지 증가
	contractenhanced, //티페리트 전용 oveerLapping
	defenseAttack, //방어력을 이용한 공격
	takeDamage, // 적에게 받는 데미지
	dispelDebuffAndMaxHp //디스펠과 최대 체력 비례(티페리트)
};