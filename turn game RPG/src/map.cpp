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
        prevFloorRooms.push_back(idCnt);
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
            currentFloorRooms.push_back(idCnt);
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


//std::vector<room> mapRoom::upperPartCreateMap() {  
//    std::vector<room> map; 
//    size_t idCnt = 1; // 고유 아이디
//
//    std::vector<int> prevFloorRooms;   // 이전 세부 층 방들 ID 저장할 공간
//    { // 이전 방 목록에 플레이어에겐 보여주진 않지만 스타트 지점을 넣어줄꺼임.
//        map.push_back({ idCnt, "start", {}, "始まりの地点"}); 
//        prevFloorRooms.push_back(idCnt);
//        idCnt++;
//    }
//
//    while (true) {
//        std::vector<int> currentFloorRooms; //현재 세부 층의 방 ID 저장하기 위함
//
//        // 현재 세부 층의 방 생성
//        for (int i = 0; i < roomsInFloor; i++) { //roomInFloor는 setRoomsInFloor()을 참조할 것.
//            std::string roomType = (roomsInFloor == 1) ? "boss" : assortRoom(); //만약 그 층의 제일 아래 세부층이라면 보스
//            if(roomType == "boss"){ map.push_back({ idCnt, roomType, {},"1stage boss"}); } 
//            else if (roomType == "enemy") { map.push_back({ idCnt, roomType, {}, "elite / normal"}); }
//            else if (roomType == "rest") { map.push_back({ idCnt, roomType, {}, "HPの30%を回復します。"}); }
//            currentFloorRooms.push_back(idCnt); //현재 세부층 ID 배열에 저장.
//            idCnt++;
//        }
//
//        // 이전 층과 연결
//        if (!prevFloorRooms.empty()) { //이전 세부 층 방의 정보가 있다면(1층이 있기에 무조건 허용)
//            for (size_t prevRoom : prevFloorRooms) { //이전 층 각방마다 다음 층 각방과 연결하기 위함
//                std::uniform_int_distribution<int> numConnDist(1, 2);// 각 이전 층 방에서 아래층 방으로 랜덤 연결 1~2개
//                int numConnections = std::min(numConnDist(gen), (int)currentFloorRooms.size()); //두 수 중에서 작은 값을 numConnections에 저장
//                std::shuffle(currentFloorRooms.begin(), currentFloorRooms.end(), gen); //currentFloorRooms의 index 처음부터 마지막까지 섞어버림
//                for (int j = 0; j < numConnections; j++) { //연결 될 수 있는 가지 수만큼 섞인 currentFloorRooms에서 방정보를 차례대로 꺼냄
//                    map[prevRoom - 1].connectedRoom.push_back(currentFloorRooms[j]); //섞었기에 언제나 다른 랜덤방이 들어가짐
//                }
//            }
//        }
//
//        if (roomsInFloor == 1) break; // 마지막 보스층
//
//        prevFloorRooms = currentFloorRooms; //whlie을 통해 돌아가기전 이전 세부층 배열을 최신껄로 갱신해둠
//        roomsInFloor = std::max(1, roomsInFloor - 1); // 층마다 방 수 감소
//    }
//
//    return map;
//}