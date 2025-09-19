//scene.cpp

#include "scene.h"

menuScene::menuScene(sf::RenderWindow& win, sf::Font& font) :
	window(win), log(win)
	,startBtn("start", 70.0f, 700.0f, font) //스타트와 엔드 버튼
	,endBtn("end", 70.0f, 800.0f, font) {
    if (!texture.loadFromFile("assets/images/1.png")) { //이니셜라이저로 초기화 불가능이라 여기서 넣어 초기화
        throw std::runtime_error("image load failed");
    }
    sprite.setTexture(texture); // 텍스처를 스프라이트에 연결
}

void menuScene::update(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (startBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                finished = true; //start 버튼 누를시 시작하게끔
            }
            if (endBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window.close(); // end 버튼 누를 시 종료
            }
        }
    }
}

void menuScene::render(sf::RenderWindow& window) { //draw
     //draw 내용
    window.draw(sprite); //배경
    log.title("Title", 770, 250); // 타이틀
    startBtn.draw(window); //부품인 버튼
    endBtn.draw(window); //부품인 버튼
}
