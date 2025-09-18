//main.cpp

#include "battle.h"
#include "map.h"
#include "consoleUI.h"
#include "sfmlUI.h"
#include "sfmlLog.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;
using std::cin;

int main() {
    sf::RenderWindow window(sf::VideoMode(1440, 1080), "SFML Window"); //창
    sfmlLog log(window); //매개변수가 있는 생성자
    sf::Font font;//폰트
    sf::Texture texture; //이미지

    try {
        if (!font.loadFromFile("assets/fonts/smartfont.otf")) {
            throw std::runtime_error("Font load failed"); //예외처리
        }
    }
    catch (const std::runtime_error& err) {
        cout << "フォントエーラー" << err.what() << endl;
    }


    button startBtn("start", 50.0f, 780.0f, font);
    button endBtn("end", 50.0f, 850.0f, font);
    sf::Event event;

    bool gameStart = false;

    while (window.isOpen()) { // 창이 열려 있는 동안 반복 , 이벤트니깐 거의 UI
        while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
            if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
                window.close();//창이 닫힌다
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
                if (startBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    gameStart = true;
                }
                if (endBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    window.close(); // 종료
                }
            }
        }
        window.clear(sf::Color::Black); // 화면 지우기 , 안하면 새하얀 화면 (시작이라 보면 편함)
        //draw 내용
        if (!gameStart) {
            try {
                if (!texture.loadFromFile("assets/images/1.png")) {
                    throw std::runtime_error("Font load failed"); //예외처리
                }
            }
            catch (const std::runtime_error& err) {
                cout << "イメージエーラー" << err.what() << endl;
            }
            log.title("Title", 600, 220);
            log.draw();
            log.clear();
            startBtn.draw(window);
            endBtn.draw(window);
        }
        else { //gameStart

        }
        window.display(); // 화면 업데이트
    }
    return 0; // 임시


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

    std::vector<room> gameMap = upperPartCreateMap();
     
    {// 시작하자마자 직업 선택
        std::unique_ptr<enemy> dummyEnemy = std::make_unique<enemy>(); //에너미 객체가없으면 못만들어서 더미로 만들어둠
        battle tempBattle(std::move(myPlayer), std::move(dummyEnemy));
        tempBattle.selectClass();                  // 직업 선택 UI 호출
        myPlayer = std::move(tempBattle.getPlayerPtr()); // 선택 후 myPlayer 복구
    }

    size_t startRoomId = 1; //시작
    consoleUI ui;
    while (true) {
        room& currentRoom = gameMap[startRoomId - 1]; //시작의 방

        // 연결된 방 출력
        if (!currentRoom.connectedRoom.empty()) {
            for (size_t i = 0; i < currentRoom.connectedRoom.size(); i++) {
                size_t nextId = currentRoom.connectedRoom[i];
                ui.connectMap(i + 1, gameMap[nextId - 1]);
            }

            size_t choice = 0;
            do {
                cout << "next room Select: ";
                cin >> choice;
                if (cin.fail() || choice < 1 || choice >(int)currentRoom.connectedRoom.size()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    choice = 0;
                }
            } while (choice == 0);

            startRoomId = currentRoom.connectedRoom[choice - 1]; // 선택한 방으로 이동
        }

        // 방 이동 후 currentRoom 갱신
        currentRoom = gameMap[startRoomId - 1];

        if (currentRoom.name == "rest") {
            myPlayer->restPlayer();
            ui.restMap();
        }
        else if (currentRoom.name == "enemy") {
            enemy e; // 플레이어의 레벨과 각층에따라 달라질 적을 위해 enemy.cpp에서 구분하고 그걸 끌고 오기 위함
            std::unique_ptr<enemy> myEnemy;
            std::string enemyType = e.randomEnemyType();
            e.setPlayerLevel(myPlayer->getLevel());
            if (enemyType == "normal") {
                myEnemy = std::make_unique<normal>(e.getPlayerLevel()); //객체 만들어짐, 계속 while을 통해 새롭게 생성
            //객체가 쓸모 없어지면 (unique)자동소멸자로 저절로 소멸
            }
            else if (enemyType == "elite") {
                myEnemy = std::make_unique<elite>(e.getPlayerLevel());
            }

            battle b(std::move(myPlayer), std::move(myEnemy)); //unique 둘다 유니크라 포인터가 하나뿐이니 옮겨줌

            b.startBattle();  // 전투 시작 및 종료까지 내부에서 처리(battle.cpp)
            if (b.getPlay() == false) {
                break;
            }

            // battle 끝나고, myPlayer를 다시 받기 위해 unique_ptr 복구 필요
            myPlayer = std::move(b.getPlayerPtr());
        }
        else if (currentRoom.name == "boss") {
            enemy e; // 플레이어의 레벨과 각층에따라 달라질 적을 위해 enemy.cpp에서 구분하고 그걸 끌고 오기 위함
            std::unique_ptr<enemy> myEnemy;
            myEnemy = std::make_unique<boss>(e.getPlayerLevel());
            battle b(std::move(myPlayer), std::move(myEnemy)); //unique 둘다 유니크라 포인터가 하나뿐이니 옮겨줌

            b.startBattle();  // 전투 시작 및 종료까지 내부에서 처리(battle.cpp)
            if (b.getPlay() == false) {
                break;
            }

            // battle 끝나고, myPlayer를 다시 받기 위해 unique_ptr 복구 필요
            myPlayer = std::move(b.getPlayerPtr());
        }

        // 이동할 방 선택
        if (currentRoom.connectedRoom.empty()) {
            cout << "clear!\n";
            break; // 마지막 보스 방
        }
    }
    return 0;
}
