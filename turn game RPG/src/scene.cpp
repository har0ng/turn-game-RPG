//scene.cpp

#include "scene.h"

//공용
void scene::isTransition() { //반복 클릭 막기
    if (transition) { return; }
    transition = true;
}

//menuScene
menuScene::menuScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex) :
    window(win), log(win)
    , startBtn("start", 70.0f, 700.0f, font) //스타트와 엔드 버튼 화면상 위치
    , endBtn("end", 70.0f, 800.0f, font)
    , titleText("title", font)
{
    //sprite
    sprite.setTexture(tex); // 텍스처를 스프라이트에 연결
    //timer
    titleText.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    startBtn.startAppear();
    endBtn.startAppear();
}
void menuScene::update(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
        startBtn.outlineColormanager(worldPos);
        endBtn.outlineColormanager(worldPos);
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseButtonPressed && !transition) {
            if (startBtn.isClicked(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !startBtn.getAppear()) {
                isTransition();
                startBtn.startFade();
                endBtn.startFade();
                titleText.startFade();
            }
            if (endBtn.isClicked(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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
        transition = false;
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
classSelectScene::classSelectScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex)
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
    sprite.setTexture(tex); // 텍스처를 스프라이트에 연결
    tiferetBtn.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    malkuthBtn.startAppear();
    backBtn.startAppear();
    tiferetDc.startAppear();
    malkuthDc.startAppear();
}
void classSelectScene::update(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
        //아웃라인 색상 변경
        tiferetBtn.outlineColormanager(worldPos);
        malkuthBtn.outlineColormanager(worldPos);
        backBtn.outlineColormanager(worldPos);

        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseButtonPressed && !transition) { // 앞으로
            if (tiferetBtn.isClicked(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !tiferetBtn.getAppear()) {
                isTransition();
                tiferetBtn.startFade();
                malkuthBtn.startFade();
                backBtn.startFade();
                tiferetDc.startFade();
                malkuthDc.startFade();
                selectBtn = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && !transition) { // 앞으로
            if (malkuthBtn.isClicked(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !malkuthBtn.getAppear()) {
                //isTransition();
                //말쿠트 직업 개발중
                finished = false; //tiferet 버튼 누를시 직업 선택 되게끔
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && !transition) { // 돌아오기
            if (backBtn.isClicked(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !backBtn.getAppear()) {
                isTransition();
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
        transition = false;
        finished = true; //start 버튼 누를시 시작하게끔
    }
    else if (backBtn.getFading() == false && backBtn.getAlpha() <= 0) {
        transition = false;
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
mapScene::mapScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex)
    :window(win), log(win)
{
    sprite.setTexture(tex);
    sf::View view(sf::Vector2f(910.f, 1024.f), sf::Vector2f(1440.f, 960.f));
    view.zoom(2.1f);
    win.setView(view);
}
void mapScene::update(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event)) {
        
    }
}
void mapScene::render(sf::RenderWindow& window){

    window.draw(sprite); //배경
}

//battleScene


