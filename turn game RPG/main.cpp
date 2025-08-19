//main.cpp

#include "battle.h"

#include <iostream>



using std::cout;
using std::endl;
using std::cin;




int main() {
    cout << "(1)start  " << "(2)end" << endl; // menu
    int start = 0;
    do {
        cin >> start;
        if (start == 2) { //menu start select
            exit(0); // if start == 0 return 0;
        }
        if (cin.fail()) {        // 숫자가 아닌 입력 감지
            cin.clear();        // fail 상태 초기화
            // 입력 버퍼 비우기 , cin.ignore(무시할수 있는 최대 문자수,	무시를 멈출 기준이 되는 문자)
            cin.ignore(1000, '\n');
            start = 0;   // 유효하지 않은 값으로 초기화
        }
    } while (start != 1 && start != 2);
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
