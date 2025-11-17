//mainManager.cpp
#include "mainManager.h"
#include <Windows.h>

void init::restart() {
    history.clear();
	clearPlayerPtr();
    currentScene.reset();
}
void init::setDeleter() {
    deleter = true;
}
void init::run() {
    while (true) {
        if (GAME == game::playing) {
            //어디서든 열어도 디버깅 모드로 열리게끔 해놓은건데 릴리즈땐 필요없을지도? 알아보기
            std::filesystem::current_path(std::filesystem::path(__argv[0]).parent_path());

            sf::RenderWindow window(sf::VideoMode(1920, 980), "test"); //창 1920x1080
            //window 전용----------
            #ifdef _WIN32
            #include <Windows.h>
            HWND hwnd = window.getSystemHandle(); // SFML 창 핸들
            RECT workArea;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0); // 작업 표시줄 제외 영역 가져오기

            // X=0, Y=0 (왼쪽 위), Y축 길이는 작업 표시줄 고려
            SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
            #endif
            // 여기까지------------
            sf::View view(sf::FloatRect(0.f, 0.f, 1820.f, 960.f));
            window.setView(view);

            sfmlLog log(window); //매개변수가 있는 생성자
            //리소스 로드(texture, font)
            resourceManager res;
            res.loadStart();
            res.battleResource();
            //공통 마우스
            mouse cursor(window, res.getTexture("cursor"));

            //초기 씬
            currentScene = std::make_unique<menuScene>(window,
                res.getFont("fantasy"), res.getTexture("menuBg"));

            window.setFramerateLimit(144);
            while (window.isOpen()) {// 창이 열려 있는 동안 반복 , 이벤트니깐 거의 UI
                window.clear(sf::Color::Black); // 화면 지우기 , 안하면 새하얀 화면 (시작이라 보면 편함)
                currentScene->update(window); // 입력 처리, 상태 업데이트 (이벤트를 만들어내야 렌더링이 가능)
                currentScene->render(window); // 화면 렌더링 (부품들을 불러옴, 마우스 제외)

                //마우스
                cursor.draw(window);
                window.display(); // 화면 업데이트

                // 씬 전환 처리
                if (currentScene->isFinished()) {
                    currentScene->setFinishBackDefault(); //finished, back = false;
                    // 메뉴 -> 직업 선택
                    if (dynamic_cast<menuScene*>(currentScene.get())) {
                        history.push_back(std::move(currentScene));
                        currentScene = std::make_unique<classSelectScene>(window, res.getFont("fantasy"), res.getTexture("menuBg"));
                        cursor.updatePositionFromWindow(window);
                        continue; // 한 프레임에 한 번만 전환
                    }
                    // 직업 -> 맵
                    else if (dynamic_cast<classSelectScene*>(currentScene.get())) {
                        history.push_back(std::move(currentScene));
                        currentScene = std::make_unique<mapScene>(window, res);
                        cursor.updatePositionFromWindow(window);
                        continue;
                    }
                    // 맵 -> 층
                    else if (dynamic_cast<mapScene*>(currentScene.get())) {
                        history.push_back(std::move(currentScene));
                        currentScene = std::make_unique<floorScene>(window, res);
                        cursor.updatePositionFromWindow(window);
                        continue;
                    }
                    // 층 -> 방
                    else if (dynamic_cast<floorScene*>(currentScene.get())) {
                        const int& roomNum = currentScene->getRoomNum();
                        history.push_back(std::move(currentScene));
                        enemy e;
                        setEnemyTLogic(roomNum, e);//몬스터 포인터 개념 정립
                        currentScene = std::make_unique<roomScene>(window, res, roomNum);
                        cursor.updatePositionFromWindow(window);
                        continue;
                    }
                }

                if (currentScene->isBack()) {
                    currentScene->setFinishBackDefault();//finished, back = false;
                    if (!history.empty()) {
                        // Back flag를 먼저 체크하고 씬 전환부터 처리
                        auto prevScene = std::move(history.back());
                        currentScene = std::move(prevScene);
                        currentScene.get()->allStartAppear(); /* 이거 없으면 vector에서도 clock은 돌아가기에 appear 할시
                                                              이미 시간 다 지나서 alpha라던지 완성체로 나옴*/
                        cursor.updatePositionFromWindow(window);
                    }
                }
                if (currentScene->isExitBtn()) {
                    currentScene->isExitBtn() = false;
                    exit = true;
                    window.close(); // ← 이렇게 해야 while(window.isOpen()) 탈출
                    break;          // window 루프 탈출
                }
                if (currentScene->isRestartBtn()) {
                    deleter = true;
                    currentScene->isRestartBtn() = false;
                }
                if (deleter) {
                    GAME = game::gameover;
                    deleter = false;
                    break;
                }
            }
        }
        if (GAME == game::gameover) {
            restart();
            GAME = game::playing;
        }
        if (exit) {
            break;
        }
    }
}