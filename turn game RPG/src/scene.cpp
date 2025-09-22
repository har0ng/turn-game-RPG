//scene.cpp

#include "scene.h"

//menuScene
menuScene::menuScene(sf::RenderWindow& win, sf::Font& font) :
	window(win), log(win)
	,startBtn("start", 70.0f, 700.0f, font) //스타트와 엔드 버튼 화면상 위치
	,endBtn("end", 70.0f, 800.0f, font) 
{
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
    
    sf::Text text = log.title("Title", sprite); // 타이틀

    startBtn.draw(window); //부품인 버튼
    endBtn.draw(window); //부품인 버튼
    window.draw(text); //텍스트 그리기
}

//classSelectScene
classSelectScene::classSelectScene(sf::RenderWindow& win, sf::Font& font)
    :window(win), log(win)
    , tiferetBtn("tiferet", 250.0f, 100.0f, font) //버튼 화면상 위치
    , malkuthBtn("malkuth", 750.0f, 100.0f, font)
    , backBtn("back", 0.0f, 800.0f, font)
{
    if (!texture.loadFromFile("assets/images/1.png")) { //이니셜라이저로 초기화 불가능이라 여기서 넣어 초기화
        throw std::runtime_error("image load failed");
    }
    sprite.setTexture(texture); // 텍스처를 스프라이트에 연결
}
void classSelectScene::update(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseButtonPressed) { // 앞으로
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (tiferetBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                finished = true; //tiferet 버튼 누를시 직업 선택 되게끔
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) { // 앞으로
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (malkuthBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //말쿠트 직업 개발중
                finished = true; //tiferet 버튼 누를시 직업 선택 되게끔
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) { // 돌아오기
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (backBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                back = true; //back 버튼 누를시 돌아가게끔
            }
        }
    }
}
void classSelectScene::render(sf::RenderWindow& window){
    window.draw(sprite); //배경
    tiferetBtn.draw(window); //티페리트 버튼
    sf::FloatRect tiferetBtnGlobalBounds = tiferetBtn.getBackgroundGlobalBounds(); //버튼이 SMFL 클래스가 아닌 사용자 정의 클래스라 get으로 따로 불러와야함
    sf::Text tiferetDiscription = log.tiferetDescription(L"契約って言う特別なコストを\n使って戦うクラスです。", tiferetBtnGlobalBounds); // 타이틀
    window.draw(tiferetDiscription); //티페리트 설명
    malkuthBtn.draw(window);//말쿠트(아도나이) 버튼
    sf::FloatRect malkuthBtnGlobalBounds = malkuthBtn.getBackgroundGlobalBounds(); //버튼이 SMFL 클래스가 아닌 사용자 정의 클래스라 get으로 따로 불러와야함
    sf::Text malkuthDiscription = log.malkuthDescription(L"開発中です。", malkuthBtnGlobalBounds); // 타이틀
    window.draw(malkuthDiscription); //말쿠트(아도나이) 설명
    backBtn.draw(window); //돌아가기 버튼
}


//mapScene


//battleScene


