//debuffEnum.h
#pragma once

enum class debuffStatus {
	none,
	agiDown, //회피율 저하
	criDown, //크리티컬율 저하
	defDown, //방어도 저하
	atkDown, //공격력 저하
	disarray, // 혼란, 적의 턴 한턴 넘김 
	weekness, // 약화, 2턴동안 20% 데미지 추가로 받음
	bleed, // 출혈, 4턴동안 턴당 maxhp 대비 hp-4%
	burn, // 화상, 3턴동안 maxhp 대비 hp-7% , 젖음에 해제. 상태이상 
	wet // 젖음, 3턴동안 젖음 상태 agi -20%

};
struct deBuff {
	std::string name{ "unknown" }; //스킬 이름
	int stack{ 0 };// enum class와 연계해서 디버프 효과 적용
	int remainingTurn{ 0 };//남은턴
	bool active = true; // false면 무시
};

struct agiDown {
	float percent{ 0.0f };
};

struct criDown {
	float percent{ 0.0f };
};

struct defDown {
	float percent{ 0.0f };
};

struct atkDown {
	float percent{ 0.0f };
};

struct disarray {
	std::string name{ "disarray" };
	int turn{ 1 };
};

struct weekness {
	std::string name{ "weekness" };
	int turn{ 2 };
	float totalDamage{ 0.2f };
};

struct bleed {
	std::string name{ "bleed" };
	int turn{ 4 };
	float maxHp{ 0.04f };
};

struct burn {
	std::string name{ "burn" };
	int turn{ 3 };
	float maxHp{ 0.07f };
};

struct wet {
	std::string name{ "wet" };
	int turn{ 3 };
	agiDown debuff{ {0.0f} };
};

