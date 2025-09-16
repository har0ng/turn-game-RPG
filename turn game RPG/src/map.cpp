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

std::vector<int> connect(int roomInFloor) {
    std::uniform_int_distribution<int> connectDistA(roomInFloor + (roomInFloor - 1), roomInFloor+1);
    std::uniform_int_distribution<int> connectDistB(roomInFloor + (roomInFloor - 1), roomInFloor + 1);
    return{ connectDistA(gen),connectDistB(gen) };
}

std::vector<room> upperPartCreateMap() { //room 구조체를 데이터타입으로 삼은 가변배열을 리턴하는 함수
    std::vector<room> map;
    int idCnt = 1; //방 고유 id 카운팅

    std::vector<int> prevFloorRooms; // 이전 층의 방 ID 저장
    int roomsInFloor = 6; //1층이라 6

    while (true) {
        for (int i = 0; i < roomsInFloor; i++) {
            std::string roomType = (roomsInFloor == 1) ? "boss" : assortRoom();

            if (roomsInFloor != 1) {
                map.push_back({ idCnt, roomType, connect(roomsInFloor) });
            }
            else {
                map.push_back({ idCnt, roomType, {} });
            }
        }
        if (roomsInFloor == 1) { break; } // 마지막 보스층
        roomsInFloor = std::max(1, roomsInFloor - 1); // 세부층에 따른 방 줄이기
    }
    return map;
}
