//map.h
#pragma once

#include <string>
#include <vector>
#include <random> // random 


struct room {
	int id; // 방 고유 번호
	std::string name; //플레이어에게 보여줄 방 이름
	std::vector<int> connectedRoom; //방과 방을 잇는 선 어느 방을 갈 수 있는가.
};

static std::random_device rd; //seed create
static std::mt19937 gen(rd()); //seed random
std::vector<room> upperPartCreateMap();



