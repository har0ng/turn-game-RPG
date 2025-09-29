//scene.cpp

#include "scene.h"

//공용
void scene::isTransition() { //반복 클릭 막기
    if (transition) { return; }
    transition = true;
}
void scene::startFade() {
    fading = true;
    clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void scene::updateFade(sf::Sprite& sprite) {
    if (fading == false) {
        return;
    }
    sf::Color color = sprite.getColor();//스프라이트라 색상값 알아서 불러오게끔
    float appearDuration = 0.5f; // 0.5초 동안 나타나게
    float alphaStep = 255.0f / appearDuration; // 초당 증가량
    alpha -= alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha <= 0.f) {
        alpha = 0.f;
        fading = false;
    }

    color.a = static_cast<sf::Uint8>(alpha);
    sprite.setColor(color);
}
void scene::startAppear() {
    appear = true;
    alpha = 0.0f;
    clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void scene::updateAppear(sf::Sprite& sprite) {
    if (appear == false) {
        return;
    }
    sf::Color color = sprite.getColor();//스프라이트라 색상값 알아서 불러오게끔
    float appearDuration = 10.0f; // 10초 동안 나타나게
    float alphaStep = 255.0f / appearDuration; // 초당 증가량
    alpha += alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha >= 255.f) {
        alpha = 255.f;
        appear = false;
    }

    color.a = static_cast<sf::Uint8>(alpha);
    sprite.setColor(color);
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
void menuScene::setMainView() {
    mainViewX = sprite.getGlobalBounds().width;
    mainViewY = sprite.getGlobalBounds().height;
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
                startFade();
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
    updateFade(sprite);

    tiferetBtn.updateAppear();
    malkuthBtn.updateAppear();
    backBtn.updateAppear();
    tiferetDc.updateAppear();
    malkuthDc.updateAppear();
    // 페이드가 끝났으면 씬 전환
    if (tiferetBtn.getFading() == false && tiferetBtn.getAlpha() <= 0 && selectBtn == true) {
        transition = false; //씬 바뀌고 있는데 클릭 금지
        finished = true; //start 버튼 누를시 시작하게끔
    }
    else if (backBtn.getFading() == false && backBtn.getAlpha() <= 0) {
        transition = false; //씬 바뀌고 있는데 클릭 금지
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
    sf::Color color = sprite.getColor();
    color.a = static_cast<sf::Uint8>(0);
    sprite.setColor(color);
    sf::View view(sf::Vector2f(910.f, 1024.f), sf::Vector2f(1440.f, 960.f));
    view.zoom(2.13f);
    win.setView(view);
    startAppear();
}
void mapScene::update(sf::RenderWindow& window){
    deltaTime = clock.restart().asSeconds(); // 이전 프레임과 현재 프레임 사이 시간
    elapsed += deltaTime;
    if (elapsed >= 13.f) {
        finished = true;
    }
    if (sprite.getColor().a == static_cast<sf::Uint8>(180.f) && elapsed >= 7.f) {
        startFade();
    }
    updateAppear(sprite); //while 밖인 이유는 event(마우스 키보드등)이 없다면 while이 실행이 안됨.
    updateFade(sprite);
}
void mapScene::render(sf::RenderWindow& window) {
    window.draw(sprite); //배경
}
void mapScene::updateFade(sf::Sprite& sprite) {
    if (fading == false) {
        return;
    }
    sf::Color color = sprite.getColor();//스프라이트라 색상값 알아서 불러오게끔
    float appearDuration = 4.0f; // 4초 동안 없어지게
    float alphaStep = 180.0f / appearDuration; // 초당 증가량
    alpha -= alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha <= 0.f) {
        alpha = 0.f;
        fading = false;
    }

    color.a = static_cast<sf::Uint8>(alpha);
    sprite.setColor(color);
}
void mapScene::updateAppear(sf::Sprite& sprite) {
    if (appear == false) {
        return;
    }
    sf::Color color = sprite.getColor();//스프라이트라 색상값 알아서 불러오게끔
    float appearDuration = 4.f; // 4초 동안 나타나게
    float alphaStep = 180.0f / appearDuration; // 초당 증가량
    alpha += alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha >= 180.f) {
        alpha = 180.f;
        appear = false;
    }

    color.a = static_cast<sf::Uint8>(alpha);
    sprite.setColor(color);
}

//floorScene
floorScene::floorScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex) :
    window(win), log(win), view(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f))
{
    window.setView(window.getDefaultView()); //mapScene에서의 zoom 풀기
    background.setTexture(tex); //sprite는 이미지
    view.setCenter(sf::Vector2f(background.getGlobalBounds().width / 2, 640.f)); //sprite라는 이미지에서 view를 통해 볼 일부분의 center 설정.
    view.setSize(sf::Vector2f(background.getGlobalBounds().width, 1280.f)); // 1438/1280
    win.setView(view);
}
void floorScene::update(sf::RenderWindow& window) {
    deltaTime = clock.restart().asSeconds(); // 이전 프레임과 현재 프레임 사이 시간
    sf::Event event;
    float scrollSpeed = 50.f; //스크롤 +1-1에 얼마나 움직이는지
    sf::Vector2f center = view.getCenter(); //보이는 화면 중심값
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta > 0) {
                center.y -= scrollSpeed; // 위로 이동
            }

            else if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta < 0) {
                center.y += scrollSpeed; // 아래로 이동
            }
        }
    }
    //center.y == 640 , halfSize.y == 640.
    std::cout << center.y << std::endl;
    sf::Vector2f halfSize = view.getSize() / 2.0f;//화면(직사각형)의 중심. x,y의 절반이 중심값이 됨.
    if (center.y < halfSize.y) { center.y = halfSize.y; } //만약 중심값의 y보다 플레이어가 보는 화면의 y값이 작다면 이미지를 나가버림
    if (center.y > background.getGlobalBounds().height - halfSize.y) {
        center.y = background.getGlobalBounds().height - halfSize.y;
    } //반대로 화면을 내렸을 때 총크기의 y - 중심값 y를 넘으면 화면 나가버림
    //640.f
    view.setCenter(center); // 중심값 재설정
    window.setView(view); // 뷰 이동.
}
//0928 오면 스크롤 위아래 갈수 있는곳 제한 걸고 마우스 크기 바꾸고 아이콘 설치하고 클릭되게해서 화면 넘기기..

void floorScene::render(sf::RenderWindow& window){
    window.draw(background);
}



//battleScene


