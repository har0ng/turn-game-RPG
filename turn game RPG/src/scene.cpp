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
void scene::setFinishBackDefault(){
    finished = false;
    back = false;
}

void scene::allStartAppear(){
    return;
}

//menuScene
menuScene::menuScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex) :
    window(win)
    , startBtn("start", 70.0f, 700.0f, font) //스타트와 엔드 버튼 화면상 위치
    , endBtn("end", 70.0f, 800.0f, font)
    , titleText("title", font, tex)
{
    //sprite
    sprite.setTexture(tex); // 텍스처를 스프라이트에 연결
    //timer
    allStartAppear();
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
        if (event.type == sf::Event::MouseButtonReleased && !transition && event.mouseButton.button == sf::Mouse::Left) {
            if (startBtn.isClicked(worldPos) && !startBtn.getAppear()) {
                isTransition();
                startBtn.startFade();
                endBtn.startFade();
                titleText.startFade();
            }
            if (endBtn.isClicked(worldPos)) {
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
void menuScene::allStartAppear() {
    titleText.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    startBtn.startAppear();
    endBtn.startAppear();
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
        if (event.type == sf::Event::MouseButtonReleased && !transition && event.mouseButton.button == sf::Mouse::Left) { // 앞으로
            if (tiferetBtn.isClicked(worldPos) && !tiferetBtn.getAppear()) {
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
        if (event.type == sf::Event::MouseButtonReleased && !transition && event.mouseButton.button == sf::Mouse::Left) { // 앞으로
            if (malkuthBtn.isClicked(worldPos) && !malkuthBtn.getAppear()) {
                //isTransition();
                //말쿠트 직업 개발중
                finished = false; //tiferet 버튼 누를시 직업 선택 되게끔
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && !transition && event.mouseButton.button == sf::Mouse::Left) { // 돌아오기
            if (backBtn.isClicked(worldPos) && !backBtn.getAppear()) {
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
        back = true; //back 버튼 누를시 시작하게끔
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
    background.setTexture(tex); //배경화면
    sf::Color color = background.getColor();
    color.a = static_cast<sf::Uint8>(0); //배경화면 서서히 나오게끔 하기
    background.setColor(color);
    sf::View view(sf::Vector2f(910.f, 1024.f), sf::Vector2f(1440.f, 960.f));
    view.zoom(2.13f);
    win.setView(view);
    startAppear();
}
void mapScene::update(sf::RenderWindow& window){
    deltaTime = clock.restart().asSeconds(); // 이전 프레임과 현재 프레임 사이 시간
    elapsed += deltaTime;
    sf::Event event;
    if (elapsed >= 13.f) { 
        finished = true;
    }
    if (background.getColor().a == static_cast<sf::Uint8>(180.f) && elapsed >= 7.f) {
        startFade();
    }
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
    }

    updateAppear(background); //while 밖인 이유는 event(마우스 키보드등)이 없다면 while이 실행이 안됨.
    updateFade(background);
}
void mapScene::render(sf::RenderWindow& window) {
    window.draw(background); //배경
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
floorScene::floorScene(sf::RenderWindow& win, resourceManager& res)
    : window(win)
    , log(win)
    , view(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)) // 일단 비어 있는 상태로 초기화
    , line(assortBtns) // 일단 비어 있는 상태로 초기화
    ,floorName(L"裏側の入口",res.getFont("fantasy"),view,floorCnt)
{
    // 1.기본 뷰 초기화
    window.setView(window.getDefaultView()); //mapScene view에서의 누적 초기화
    background.setTexture(res.getTexture("floorBg"));
    sf::Color color = background.getColor();
    color.a = (static_cast<sf::Uint8>(0));
    background.setColor(color);
    view.setCenter(sf::Vector2f(background.getGlobalBounds().width / 2, 1920.f)); // 화면의 정중앙
    view.setSize(sf::Vector2f(background.getGlobalBounds().width, 1280.f));  // 화면의 정중앙으로부터 좌우, 상하 길이
    win.setView(view);
    // 2.층 수에 따라 층 이름 다르게 title에 넣어주기
    floorName.setView(view);
    // 3.층수 기반 첫 세부층 방 개수 설정
    setFirstAssortMapCnt(floorCnt);
    // 4.버튼 생성
    pushAssortMap(firstAssortMapCnt, res);
    // 5.버튼 위치 세팅
    imageDraw(background.getGlobalBounds().width, background.getGlobalBounds().height);
    // 6.line 클래스에 assortBtns 전달
    line.setAssortBtns(assortBtns);
    // 7.버튼 위치가 세팅된 후 라인 생성
    line.createLine();
    // 8. 천천히 이미지 밝아지기
    startAppear();
    floorName.startAppear();
    for (auto& assortBtnInfo: assortBtns) {
        for (auto& roomInfo : assortBtnInfo) {
            roomInfo.startAppear();
        }
    }
    line.startAppear();
}
void floorScene::update(sf::RenderWindow& window) {
    deltaTime = clock.restart().asSeconds(); // 이전 프레임과 현재 프레임 사이 시간
    elapsed += deltaTime;
    sf::Event event;
    sf::Vector2f center = view.getCenter(); //보이는 화면 중심값
    if (!animationYN && !appear) {
        animation(center, elapsed);
        floorName.startFade();
    }
    while (window.pollEvent(event)) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
        if (animationYN) {
            for (auto& assortFloor : assortBtns) { //room에 마우스 갖다대면 scale 변화
                for (auto& roomInfo : assortFloor) { //버튼 호버시 변화
                    roomInfo.spriteScaleManager(worldPos);
                    line.setFillColor(worldPos, roomInfo);
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && roomInfo.isClicked(worldPos)) {
                        finished = true;
                    }
                }
            }
        }
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseWheelScrolled && animationYN && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta > 0) {
            center.y -= scrollSpeed; // 위로 이동
        }
        if (event.type == sf::Event::MouseWheelScrolled && animationYN && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta < 0) {
            center.y += scrollSpeed; // 아래로 이동
        }
    }
    //center.y == 640 , halfSize.y == 640.
    sf::Vector2f halfSize = view.getSize() / 2.0f;//화면(직사각형)의 중심. x,y의 절반이 중심값이 됨.
    if (center.y < halfSize.y) { center.y = halfSize.y; } //만약 중심값의 y보다 플레이어가 보는 화면의 y값이 작다면 이미지를 나가버림
    if (center.y > background.getGlobalBounds().height - halfSize.y) {
        center.y = background.getGlobalBounds().height - halfSize.y;
    } //반대로 화면을 내렸을 때 총크기의 y - 중심값 y를 넘으면 화면 나가버림
    //640.f

    //set
    view.setCenter(center); // 중심값 재설정
    window.setView(view); // 뷰 이동.
    floorName.setView(view); //층 이름 이동.

    //fade,appear
    floorName.updateFade();
    floorName.updateAppear();
    updateAppear(background);
    for (auto& assortBtnInfo : assortBtns) {
        for (auto& roomInfo : assortBtnInfo) {
            roomInfo.updateAppear();
        }
    }
    line.updateAppear();
}
void floorScene::render(sf::RenderWindow& window) {
    window.draw(background);
    line.draw(window); // 선 그리기
    for (auto& floor : assortBtns) {
        for (auto& btn : floor) {
            btn.draw(window);
        }
    }
    floorName.draw(window);
}
void floorScene::imageDraw(float bgWidth, float bgHeight) {
    // 버튼 초기 Y 위치: 배경 높이의 50% 정도로 중앙 근처에서 시작
    float startY = bgHeight * 0.16;
    // 층 간격: 배경 높이 기준 10~12% 정도
    float gapY = bgHeight * 0.12f;

    float centerX = bgWidth / 2.0f;

    float buttonWidthRatio = 0.08f; // 버튼 폭 = 배경 너비의 8%
    float buttonWidth;
    float gapX;

    for (int floor = 0; floor < assortBtns.size(); floor++) {
        int numButtons = assortBtns[floor].size();

        buttonWidth = bgWidth * buttonWidthRatio;

        if (numButtons > 1) {
            gapX = (bgWidth * 0.12f) / (numButtons - 1);
        }// 버튼 사이 간격
        else {
            gapX = 0.f;
        }
        float totalWidth = buttonWidth * numButtons + gapX * (numButtons - 1);
        float startX = centerX - totalWidth / 2.f;

        float posY = startY + floor * gapY;

        for (int i = 0; i < numButtons; i++) {
            sf::Vector2f pos(startX + i * (buttonWidth + gapX), posY);

            if (assortBtns[floor][i].getRoomInformation().name == "rest") {
                pos += sf::Vector2f(buttonWidth * 0.1f, buttonWidth * 0.1f);
            }
            else if (assortBtns[floor][i].getRoomInformation().name == "boss") {
                pos += sf::Vector2f(-buttonWidth * 2.0f, -100.f);
            }

            assortBtns[floor][i].setPosition(pos);
            assortBtns[floor][i].draw(window);
        }
    }
}
void floorScene::pushAssortMap(int assortMapCnt, resourceManager& res) { //각 방 무슨 이벤트 발생하는지 map과 연결해 정의
    if (assortBtns.empty()) { //다시 맵 넘어왔을 떄 있으면 곤란.
        std::vector<room> gameMap = map.upperPartCreateMap(); //맵 만들어놓기.
        auto mapIndex = 1;
        while (assortMapCnt > 0) {
            for (int i = 0; i < assortMapCnt && mapIndex < gameMap.size(); i++) {
                assortBtn.push_back(assortMapSelectButton(gameMap[mapIndex], res));
                mapIndex++;
            }
            assortMapCnt -= 1;
            assortBtns.push_back(assortBtn);
            assortBtn.clear();
        }
    }
}
void floorScene::animation(sf::Vector2f& center, float& elapsed) {
    if (center.y <= 640.f) {
        center.y == 640.f;
        animationYN = true;
    }
    if (center.y != 640.f) {
        center.y = std::max(640.f, center.y - ((scrollSpeed / 12) * elapsed)); // 위로 이동
    }
}
std::vector<std::vector<assortMapSelectButton>>& floorScene::getAssortBtns() {
    return assortBtns;
}
void floorScene::setFirstAssortMapCnt(int &floor) {
    switch (floor){
    case 1:
        firstAssortMapCnt = 6;
        floor++; //미리 층수 한칸 올려놓기
        break;
    case 2:
        firstAssortMapCnt = 6;
        floor++;
        break;
    case 3:
        firstAssortMapCnt = 5;
        floor++;
        break;
    case 4:
        firstAssortMapCnt = 4;
        floor++;
        break;
    case 5:
        firstAssortMapCnt = 4;
        floor++;
        break;
    case 6:
        firstAssortMapCnt = 4;
        floor++;
        break;
    case 7:
        firstAssortMapCnt = 2;
        floor++;
        break;
    default:
        break;
    }
}
void floorScene::setLine(std::vector<std::vector<assortMapSelectButton>>& assortBtns) {
    line.setAssortBtns(assortBtns);
}
void floorScene::updateAppear(sf::Sprite& sprite) {
    if (appear == false) {
        return;
    }
    sf::Color color = sprite.getColor();//스프라이트라 색상값 알아서 불러오게끔
    float appearDuration = 2.f; // 3초 동안 나타나게
    float alphaStep = 255.0f / appearDuration; // 초당 증가량
    alpha += alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha >= 255.f) {
        alpha = 255.f;
        appear = false;
    }

    color.a = static_cast<sf::Uint8>(std::min(alpha, 255.f));
    sprite.setColor(color);
}

//battleScene
battleScene::battleScene(sf::RenderWindow& win, resourceManager& res) :
    window(win),log(win), backBtn("back", 0.0f, 800.0f, res.getFont("fantasy"))
{
   
}
void battleScene::update(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
        //아웃라인 색상 변경
        backBtn.outlineColormanager(worldPos);
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            window.close();//창이 닫힌다
        }
        if (event.type == sf::Event::MouseButtonReleased && backBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            back = true;    
        }
    }
}
void battleScene::render(sf::RenderWindow& window) {
    backBtn.draw(window); //돌아가기 버튼 (임시용)
}