#pragma once
#include <string>

struct disable {
	std::string skillName; //스킬 이름
	int remainTurn{ 0 };//쿨타임이 끝날 때까지 계산
	bool enabled{ true }; //true 면 사용가능
};