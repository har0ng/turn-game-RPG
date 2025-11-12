#pragma once

struct disable {
	int skillNum{ 0 };
	int remainTurn{ 0 };//쿨타임이 끝날 때까지 계산
	bool enabled{ true }; //true 면 사용가능
};