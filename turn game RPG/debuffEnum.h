//debuffEnum.h
#pragma once

enum class debuffStatus {
	none,
	disarray, // 혼란, 적의 턴 한턴 넘김 
	weekness, // 약화, 2턴동안 20% 데미지 추가로 받음
	bleed, // 출혈, 4턴동안 턴당 maxhp 대비 hp-4%
	burn, // 화상, 3턴동안 maxhp 대비 hp-3% , 젖음에 해제. 상태이상 
	wet, // 젖음, 3턴동안 젖음 상태
	freeze, // 젖음 -> 얼음, 2턴 동안 25% 데미지 추가로 받음, 회피율 저하
	electricShock, // 젖음 -> 감전, 기절 한턴 넘김
	agiDown, //회피율 저하
	criDown, //크리티컬율 저하
	defDown, //방어도 저하
	atkDown //공격력 저하

};