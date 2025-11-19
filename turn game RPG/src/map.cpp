//map.cpp

#pragma warning(push)
#pragma warning(disable : 26819)
#include "json.hpp"
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4251 26812 26819 4244 4267)
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#pragma warning(pop)

#include <iostream>
#include <vector>
#include <string>

#include "map.h"
/*
 A B C D E F  => 1-1 Floor
  
  G H I J K   => 1-2 Floor
  
   L M N O    => 1-3 Floor
    
    P Q R     => 1-4 Floor

     S T      => 1-5 Floor
     
      U       => 1-6 Floor boss
*/

mapRoom::mapRoom():gen(rd()) 
{
    setRoomsInFloor(floor);
}
std::string mapRoom::assortRoom(){
    std::uniform_int_distribution<int> roomDist(0, 3);
    return roomDist(gen) == 0 ? "rest" : "enemy";
}
void mapRoom::setRoomsInFloor(int floor) {
    switch (floor) {
    case 1:
        roomsInFloor = 6;
        break;
    case 2:
        roomsInFloor = 6;
        break;
    case 3:
        roomsInFloor = 5;
        break;
    case 4:
        roomsInFloor = 4;
        break;
    case 5:
        roomsInFloor = 4;
        break;
    case 6:
        roomsInFloor = 4;
        break;
    case 7:
        roomsInFloor = 2;
        break;
    default:
        break;
    }
}

std::vector<room> mapRoom::upperPartCreateMap() {
    std::vector<room> map;
    size_t idCnt = 1; // 고유 아이디

    std::vector<int> prevFloorRooms; // 이전 세부 층 방들 ID 저장할 공간
    {
        // 스타트 지점 (플레이어한테 안 보임)
        map.push_back({ idCnt, "start", {}, "始まりの地点" });
        prevFloorRooms.push_back(static_cast<int>(idCnt));
        idCnt++;
    }

    int startRoomInFloor = roomsInFloor;
    while (true) {
        std::vector<int> currentFloorRooms; //현재 세부 층의 방 ID 저장하기 위함
        int restCount = 0; // 이번 세부층에서 등장한 회복 개수
        // 1. 현재 세부 층 방 생성
        for (int i = 0; i < roomsInFloor; i++) {
            std::string roomType;
            // (조건 1) 제일 윗줄은 전부 enemy
            if (startRoomInFloor == roomsInFloor) { // 스타트 바로 아래 줄
                roomType = "enemy";
            }
            else if (roomsInFloor == 1) {
                roomType = "boss";
            }
            else {
                roomType = assortRoom();
                // (조건 2) 한 줄에 rest는 최대 2개
                if (roomType == "rest") {
                    if (restCount >= 2) {
                        roomType = "enemy"; 
                    }
                    else {
                        restCount++; 
                    }
                }
            }
            // 텍스트 설정
            if (roomType == "boss") {
                map.push_back({ idCnt, roomType, {}, "1stage boss" });
            }
            else if (roomType == "enemy") {
                map.push_back({ idCnt, roomType, {}, "elite / normal" });
            }
            else if (roomType == "rest") {
                map.push_back({ idCnt, roomType, {}, "HPの30%を回復します。" });
            }
            currentFloorRooms.push_back(static_cast<int>(idCnt));
            idCnt++;
        }

        // 2. 이전 층과 연결
        if (!prevFloorRooms.empty()) { //이전 세부 층 방의 정보가 있다면(더미 1층이 있기에 무조건 허용)
            // (랜덤 연결)
            for (size_t prevRoom : prevFloorRooms) {
                std::uniform_int_distribution<int> numConnDist(1, 1);
                int numConnections = std::min(numConnDist(gen), (int)currentFloorRooms.size());
                std::shuffle(currentFloorRooms.begin(), currentFloorRooms.end(), gen);
                for (int j = 0; j < numConnections; j++) {
                    map[prevRoom - 1].connectedRoom.push_back(currentFloorRooms[j]);
                }
            }
            // (조건 5) 연결 못 받은 방은 강제로 연결
            for (int curRoom : currentFloorRooms) {
                bool connected = false;
                for (size_t prevRoom : prevFloorRooms) {
                    auto& conns = map[prevRoom - 1].connectedRoom;
                    if (std::find(conns.begin(), conns.end(), curRoom) != conns.end()) {
                        connected = true;
                        break;
                    }
                }
                if (!connected) {
                    std::uniform_int_distribution<int> pickPrev(0, (int)prevFloorRooms.size() - 1);
                    long long prevPick = prevFloorRooms[pickPrev(gen)];
                    map[prevPick - 1].connectedRoom.push_back(curRoom);
                }
            }
        }

        // 3. 마지막 보스 층이면 종료
        if (roomsInFloor == 1) {
            // (조건 4) 보스 층에 회복이 없다면 하나 강제로 rest로 교체
            bool bossFloorHasRest = false;
            for (long long r : currentFloorRooms) {
                if (map[r - 1].name == "rest") {
                    bossFloorHasRest = true;
                    break;
                }
            }
            if (!bossFloorHasRest) {
                // 보스 제외하고 하나를 rest로 교체
                for (long long r : currentFloorRooms) {
                    if (map[r - 1].name != "boss") {
                        map[r - 1].name = "rest";
                        map[r - 1].description = "HPの30%を回復します。";
                        break;
                    }
                }
            }
            break;
        }
        prevFloorRooms = currentFloorRooms;
        roomsInFloor = std::max(1, roomsInFloor - 1);
    }
    // (조건 3) 보스전 방은 휴식 방과 몬스터 방 1개씩 고정.
    for (auto& r : map) {//21개의 방과 start(dumydata)방 1개로 총합 22개 id 2부터 시작
        if (r.id == map.size()- 1 && r.name != "enemy") { // 보스방의 id와 map의 사이즈는 같음
            r.name = "enemy";
            r.description = "elite / normal";
        }
        if (r.id == map.size() - 2 && r.name != "rest") {
            r.name = "rest";
            r.description = "HPの30%を回復します。";
        }
    }
    return map;
}