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

/* map -> button -> scene
1.map에서 한번에 층의 모든방의 정보를 만들어내기 (끝)
2.그 정보를 button의 assortMapSelectbutton에 정보로 보내기 (끝)
3.button에서 그 정보를 하나하나 읽어서 roomType에 따라 방의 이미지를 버튼화 시켜서 그 버튼을 scene으로 넘겨주기 (끝)
4.층에 따라 세부 층에 있을 방의 개수별로 vector로 나눠 차곡차곡 저장 (끝)
5.저장된 방을 x,y 좌표로 통해 클릭하기 쉽게 맵에 매핑 (끝)
5-2. 방에서 방으로 갈 수 있는 방끼리 선으로 연결 해놓기(아마 map.cpp 뜯어 고쳐야할거 같음) (끝)
6.클릭 이벤트 만들어내기
7.호버시 변화 만들어내기 (끝)
8.클릭 시 배틀로 넘어가게 해주기 단, 화면 전환이 아닌 화면 위로 덧씌우는 방식이 될꺼임
  아니면 화면 전환하게 하되, 원래 floorScene을 따로 저장해놓고 새롭게 만드는게 아닌 저장해놓은 scene을 불러올꺼임
(이유는 전환하면 scene이 바뀌면서 원래 층의 scene이 개박살남 그래서 정보를 남겨놓을꺼임)
포인터 옮길 땐 옮기기전에 미리 현재 세부층 클릭 못하게 막아두고 넘어가기
9,배틀 끝나면 다음 세부층으로 이동하고 이전 세부층(vector)의 이미지는 좀 어둡게만들고 클릭 이벤트 비활성화
*/

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
                    int prevPick = prevFloorRooms[pickPrev(gen)];
                    map[prevPick - 1].connectedRoom.push_back(curRoom);
                }
            }
        }

        // 3. 마지막 보스 층이면 종료
        if (roomsInFloor == 1) {
            // (조건 4) 보스 층에 회복이 없다면 하나 강제로 rest로 교체
            bool bossFloorHasRest = false;
            for (int r : currentFloorRooms) {
                if (map[r - 1].name == "rest") {
                    bossFloorHasRest = true;
                    break;
                }
            }
            if (!bossFloorHasRest) {
                // 보스 제외하고 하나를 rest로 교체
                for (int r : currentFloorRooms) {
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