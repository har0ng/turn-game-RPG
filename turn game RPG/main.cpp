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

    std::unique_ptr<player> myPlayer = std::make_unique<player>();
    std::unique_ptr<enemy> myEnemy = std::make_unique<enemy>();
    
    battle b(std::move(myPlayer), std::move(myEnemy)); //unique다 보니 옮겾무
    b.startBattle();  // 전투 시작 및 종료까지 내부에서 처리(battle.cpp)
    return 0;
}
