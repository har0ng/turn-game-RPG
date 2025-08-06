//main.cpp

#include <iostream>
#include "main.h"


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

    battle b;
    b.startBattle();  // 전투 시작 및 종료까지 내부에서 처리(battle.cpp)
    return 0;
}
