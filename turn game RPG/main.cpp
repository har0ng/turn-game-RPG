//main.cpp

#include "battle.h"

#include <iostream>



using std::cout;
using std::endl;
using std::cin;




int main() {
    cout << "(1)start  " << "(2)end" << endl; // menu
    int start = 0;
    cin >> start;
    if (start > 1) { //menu start select
        exit(0); // if start == 0 return 0;
    }
    std::unique_ptr<player> myPlayer = std::make_unique<player>(); // 객체 만들어짐 ,한번만
    while (true) {

        std::unique_ptr<enemy> myEnemy = std::make_unique<enemy>(); //객체 만들어짐, 계속 while을 통해 새롭게 생성
        //객체가 쓸모 없어지면 (unique)자동소멸자로 저절로 소멸

        battle b(std::move(myPlayer), std::move(myEnemy)); //unique다 보니 옮겨줌

        b.startBattle();  // 전투 시작 및 종료까지 내부에서 처리(battle.cpp)
        if (b.getPlay() == false) {
            break;
        }

        // battle 끝나고, myPlayer를 다시 받기 위해 unique_ptr 복구 필요
        myPlayer = std::move(b.getPlayerPtr());
    }
    return 0;
}
