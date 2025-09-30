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
5.저장된 방을 x,y 좌표로 통해 클릭하기 쉽게 맵에 매핑
5-2. 방에서 방으로 갈 수 있는 방끼리 선으로 연결 해놓기(아마 map.cpp 뜯어 고쳐야할거 같음)
6.클릭 이벤트 만들어내기
7.호버시 변화 만들어내기
8.클릭 시 배틀로 넘어가게 해주기 단, 화면 전환이 아닌 화면 위로 덧씌우는 방식이 될꺼임
  아니면 화면 전환하게 하되, 원래 floorScene을 따로 저장해놓고 새롭게 만드는게 아닌 저장해놓은 scene을 불러올꺼임
(이유는 전환하면 scene이 바뀌면서 원래 층의 scene이 개박살남 그래서 정보를 남겨놓을꺼임)
9,배틀 끝나면 다음 세부층으로 이동하고 이전 세부층(vector)의 이미지는 좀 어둡게만들고 클릭 이벤트 비활성화

*/

std::vector<room> mapRoom::upperPartCreateMap() {  
    std::vector<room> map;
    size_t idCnt = 1; // 고유 아이디

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
                // 각 이전 층 방에서 아래층 방으로 랜덤 연결 1~2개
                std::uniform_int_distribution<int> numConnDist(1, 2);
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