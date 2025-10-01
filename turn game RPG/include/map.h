//map.h
#pragma once

#include <string>
#include <vector>
#include <random> // random 



struct room {
	size_t id; // 방 고유 번호
	std::string name; //백 로그 보여줄 방 이름
	std::vector<int> connectedRoom; //방과 방을 잇는 선 어느 방을 갈 수 있는가.
	std::string describe; //방 설명
};
class mapRoom {
private:
	std::random_device rd; //seed create
	std::mt19937 gen; //seed random
	int floor = 1; //그냥 층수 7층까지 존재
	int roomsInFloor; //세부 층 개수
public:
	mapRoom();
	std::string assortRoom();
	void setRoomsInFloor(int floor);
	std::vector<room> upperPartCreateMap();
	
};


