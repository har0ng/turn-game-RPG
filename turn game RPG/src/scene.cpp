//scene.cpp

#include "scene.h"

//menuScene
menuScene::menuScene(sf::RenderWindow& win, sf::Font& font) :
    window(win), log(win)
    , startBtn("start", 70.0f, 700.0f, font) //스타트와 엔드 버튼 화면상 위치
    , endBtn("end", 70.0f, 800.0f, font)
    , titleText("title", font)
{
    if (!texture.loadFromFile("assets/images/1.png")) { //이니셜라이저로 초기화 불가능이라 여기서 넣어 초기화
        throw std::runtime_error("image load failed");
    }
    sprite.setTexture(texture); // 텍스처를 스프라이트에 연결
    titleText.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    startBtn.startAppear();
    endBtn.startAppear();
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
                startBtn.startFade();
                endBtn.startFade();
                titleText.startFade();
            }
            if (endBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window.close(); // end 버튼 누를 시 종료
            }
        }
    }
    // 매 프레임 업데이트
    startBtn.updateFade();
    endBtn.updateFade();
    titleText.updateFade();

    titleText.updateAppear(); //타이틀이 천천히 나오게 타이머 계산
    startBtn.updateAppear();
    endBtn.updateAppear();

    // 페이드가 끝났으면 씬 전환
    if (startBtn.getFading() == false && startBtn.getAlpha() <= 0) {
        finished = true; //start 버튼 누를시 시작하게끔
    }
}
void menuScene::render(sf::RenderWindow& window) { //draw
     //draw 내용
    window.draw(sprite); //배경

    titleText.draw(window); // 타이틀
    startBtn.draw(window); //부품인 버튼
    endBtn.draw(window); //부품인 버튼
}

//classSelectScene
classSelectScene::classSelectScene(sf::RenderWindow& win, sf::Font& font)
    :window(win)
    , tiferetBtn("tiferet", 250.0f, 100.0f, font) //버튼 화면상 위치
    , malkuthBtn("malkuth", 750.0f, 100.0f, font)
    , backBtn("back", 0.0f, 800.0f, font)
    , tiferetDc(
        L"契約って言う特別なコストを\n使って戦うクラスです。",
        tiferetBtn.getBackgroundGlobalBounds(),
        win)
    , malkuthDc(
        L"開発中です。",
        malkuthBtn.getBackgroundGlobalBounds(),
        win)
    ,selectBtn(false)
{
    if (!texture.loadFromFile("assets/images/1.png")) { //이니셜라이저로 초기화 불가능이라 여기서 넣어 초기화
        throw std::runtime_error("image load failed");
    }
    sprite.setTexture(texture); // 텍스처를 스프라이트에 연결
    tiferetBtn.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    malkuthBtn.startAppear();
    backBtn.startAppear();
    tiferetDc.startAppear();
    malkuthDc.startAppear();
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
                tiferetBtn.startFade();
                malkuthBtn.startFade();
                backBtn.startFade();
                tiferetDc.startFade();
                malkuthDc.startFade();
                selectBtn = true;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) { // 앞으로
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (malkuthBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //말쿠트 직업 개발중
                finished = false; //tiferet 버튼 누를시 직업 선택 되게끔
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) { // 돌아오기
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //window 안넣으면 모니터 해상도 기준임
            if (backBtn.isClicked(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                tiferetBtn.startFade();
                malkuthBtn.startFade();
                backBtn.startFade();
                tiferetDc.startFade();
                malkuthDc.startFade();
            }
        }
    }
    // 매 프레임 업데이트
    tiferetBtn.updateFade();
    malkuthBtn.updateFade();
    backBtn.updateFade();
    tiferetDc.updateFade();
    malkuthDc.updateFade();

    tiferetBtn.updateAppear();
    malkuthBtn.updateAppear();
    backBtn.updateAppear();
    tiferetDc.updateAppear();
    malkuthDc.updateAppear();
    // 페이드가 끝났으면 씬 전환
    if (tiferetBtn.getFading() == false && tiferetBtn.getAlpha() <= 0 && selectBtn == true) {
        finished = true; //start 버튼 누를시 시작하게끔
    }
    else if (backBtn.getFading() == false && backBtn.getAlpha() <= 0) {
        back = true; //start 버튼 누를시 시작하게끔
    }
}
void classSelectScene::render(sf::RenderWindow& window){
    window.draw(sprite); //배경
    tiferetBtn.draw(window); //티페리트 버튼
    malkuthBtn.draw(window);//말쿠트(아도나이) 버튼
    backBtn.draw(window); //돌아가기 버튼
    tiferetDc.draw(window);
    malkuthDc.draw(window);
}


//mapScene
mapScene::mapScene(sf::RenderWindow& win, sf::Font& font)
    :window(win), log(win)
{
    if (!texture.loadFromFile("assets/images/map2.png")) { // 맵 이미지 임의. 떠오른게 없어서.
        throw std::runtime_error("image load failed");
    }
    sprite.setTexture(texture);
}
void mapScene::update(sf::RenderWindow& window){
    return;
}
void mapScene::render(sf::RenderWindow& window){
    window.draw(sprite); //배경
}

//battleScene


