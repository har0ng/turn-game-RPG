//map.cpp

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
std::string assortRoom(){
    std::uniform_int_distribution<int> roomDist(0, 3);
    return roomDist(gen) == 0 ? "rest" : "enemy";
}

std::vector<room> upperPartCreateMap() {
    std::vector<room> map;
    size_t idCnt = 1; // 고유 아이디

    int roomsInFloor = 6;              // 1층 세부 층 개수(시작 층 포함)
    std::vector<int> prevFloorRooms;   // 이전 세부 층 방들 ID 저장

    {
        map.push_back({ idCnt, "start", {}, "始まりの地点"});
        prevFloorRooms.push_back(idCnt);
        idCnt++;
    }

    while (true) {
        std::vector<int> currentFloorRooms; //현재 세부 층의 방 ID 저장하기 위함

        // 현재 세부 층의 방 생성
        for (int i = 0; i < roomsInFloor; i++) {
            std::string roomType = (roomsInFloor == 1) ? "boss" : assortRoom();
            if(roomType == "boss"){ map.push_back({ idCnt, roomType, {},"1stage boss"}); }
            else if (roomType == "enemy") { map.push_back({ idCnt, roomType, {}, "elite / normal"}); }
            else if (roomType == "rest") { map.push_back({ idCnt, roomType, {}, "HPの30%を回復します。"}); }
            currentFloorRooms.push_back(idCnt);
            idCnt++;
        }

        // 이전 층과 연결
        if (!prevFloorRooms.empty()) { //이전 세부 층 방의 정보가 있다면
            for (size_t prevRoom : prevFloorRooms) { //이전 층 각방마다 다음 층 각방과 연결
                // 각 이전 층 방에서 아래층 방으로 랜덤 연결 2~4개
                std::uniform_int_distribution<int> numConnDist(2, 4);
                int numConnections = std::min(numConnDist(gen), (int)currentFloorRooms.size()); //몇개의 방과 연결 됐는지

                std::shuffle(currentFloorRooms.begin(), currentFloorRooms.end(), gen); // 섞어서 랜덤 선택
                for (int j = 0; j < numConnections; j++) {
                    map[prevRoom - 1].connectedRoom.push_back(currentFloorRooms[j]);
                }
            }
        }

        if (roomsInFloor == 1) break; // 마지막 보스층

        prevFloorRooms = currentFloorRooms;
        roomsInFloor = std::max(1, roomsInFloor - 1); // 층마다 방 수 감소
    }

    return map;
}