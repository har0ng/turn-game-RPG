//scene.cpp

#pragma warning(push)
#pragma warning(disable : 26819)
#include "json.hpp"
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4251 26812 26819 4244 4267)
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#pragma warning(pop)

#include "scene.h"

//공용
void scene::isTransition() { //반복 클릭 막기
    if (transition) { return; }
    transition = true;
}
void scene::setRestartBtn() {
    restartBtn = true;
}
const int& scene::getRoomNum() {
    return roomNum;
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
            exitBtn = true;
        }
        if (event.type == sf::Event::MouseButtonReleased && !transition && event.mouseButton.button == sf::Mouse::Left) {
            if (startBtn.isClicked(worldPos) && !startBtn.getAppear()) {
                isTransition();
                startBtn.startFade();
                endBtn.startFade();
                titleText.startFade();
            }
            if (endBtn.isClicked(worldPos)) {
                exitBtn = true;
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
        L"契約を使って戦う独特な\nキャラクターです。",
        tiferetBtn.getBackgroundGlobalBounds(),
        win)
    , malkuthDc(
        L"開発中です。",
        malkuthBtn.getBackgroundGlobalBounds(),
        win)
    ,selectBtn(false)
{
    sprite.setTexture(tex); // 텍스처를 스프라이트에 연결
    allStartAppear();
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
            exitBtn = true;
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
                selectClass("tiferet"); //player 전역 함수
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
void classSelectScene::allStartAppear() {
    tiferetBtn.startAppear(); //천천히 타이틀이 나오게 타이머 활성화
    malkuthBtn.startAppear();
    backBtn.startAppear();
    tiferetDc.startAppear();
    malkuthDc.startAppear();
}

//mapScene
mapScene::mapScene(sf::RenderWindow& win, resourceManager& res)
    :window(win), log(win)
{
    effectUploading(res); // 캐릭터별 이펙트 정보 받아놓기
    res.unloadTexture("menuBg");
    background.setTexture(res.getTexture("mapBg")); //배경화면
    sf::Color color = background.getColor();
    color.a = static_cast<sf::Uint8>(0); //배경화면 서서히 나오게끔 하기
    background.setColor(color);
    sf::View view(sf::Vector2f(910.f, 1024.f), sf::Vector2f(1440.f, 960.f));
    view.zoom(2.13f);
    win.setView(view);
    allStartAppear();
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
            exitBtn = true;
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
void mapScene::allStartAppear() {
    startAppear();
}
void mapScene::effectUploading(resourceManager& res) {
    if (p->getClassName() == "tiferet") classname = className::tiferet;
    if (p->getClassName() == "malkuth") classname = className::malkuth;
    switch (classname) {
    case className::tiferet:
        res.tiferetEffect();
        break;
    case className::malkuth:
        break;
    default:
        break;
    }
}

//floorScene
floorScene::floorScene(sf::RenderWindow& win, resourceManager& res)
    : window(win)
    , log(win)
    , view(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)) // 일단 비어 있는 상태로 초기화
    , line(assortBtns) // 일단 비어 있는 상태로 초기화
    ,floorName(L"裏側の入口",res.getFont("fantasy"),view,floorCnt)
{
    res.unloadTexture("mapBg");
    assortBtn.reserve(6);
    assortBtns.reserve(6);
    visitedRoom.reserve(2); //미리 vector크기를 지정함으로써 index늘어날 때마다 복사 비용 제거.
    connectedRoom.reserve(5);
    p->setBeforePlayer(); //전투 시작전 상태(레벨업 비교)
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
    floorName.startAppear(); //제일 처음만 보여줄꺼라 allStartAppear()에 넣지 않음으로써 반복성 부여x
    allStartAppear();
}
void floorScene::update(sf::RenderWindow& window) {
    deltaTime = clock.restart().asSeconds(); // 이전 프레임과 현재 프레임 사이 시간
    sf::Event event;
    sf::Vector2f center = view.getCenter(); //보이는 화면 중심값
    if (!animationYN && !appear) {
        animation(center, deltaTime);
        floorName.startFade();
    }
    while (window.pollEvent(event)) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
        if (animationYN) {
            for (auto& assortFloor : assortBtns) { //room에 마우스 갖다대면 scale 변화
                for (auto& roomInfo : assortFloor) { //버튼 호버시 변화
                    roomInfo.spriteScaleManager(worldPos, visitedRoom);
                    line.setFillColor(worldPos, roomInfo);     
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left 
                        && roomInfo.isClickedExtra(worldPos, connectedRoom) && roomInfo.getIndexRow() == assortBtnRow) {
                        visitedRoom.push_back({ roomInfo.getIndexRow(), roomInfo.getIndexCol() });
                        connectedRoom.clear();
                        connectedRoom = roomInfo.getRoomInformation().connectedRoom;
                        assortBtnRow++;
                        setRoomNum(roomInfo.getRoomInformation().name);
                        finished = true;                       
                    }
                }
            }
        }
        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            exitBtn = true;
        }
        if (event.type == sf::Event::MouseWheelScrolled && animationYN && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta > 0) {
            center.y -= scrollSpeed; // 위로 이동
        }
        if (event.type == sf::Event::MouseWheelScrolled && animationYN && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && event.mouseWheelScroll.delta < 0) {
            center.y += scrollSpeed; // 아래로 이동
        }
    }
    //center.y == 640 , halfSize.y == 640.f
    sf::Vector2f halfSize = view.getSize() / 2.0f;//화면(직사각형)의 중심. x,y의 절반이 중심값이 됨.
    if (center.y < halfSize.y) { center.y = halfSize.y; } //만약 중심값의 y보다 플레이어가 보는 화면의 y값이 작다면 이미지를 나가버림
    if (center.y > background.getGlobalBounds().height - halfSize.y) {
        center.y = background.getGlobalBounds().height - halfSize.y;
    } //반대로 화면을 내렸을 때 총크기의 y - 중심값 y를 넘으면 화면 나가버림


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
            roomInfo.updateAppear(visitedRoom);
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
    float startY = bgHeight * 0.16f;
    // 층 간격: 배경 높이 기준 10~12% 정도
    float gapY = bgHeight * 0.12f;

    float centerX = bgWidth / 2.0f;

    float buttonWidthRatio = 0.08f; // 버튼 폭 = 배경 너비의 8%
    float buttonWidth;
    float gapX;

    for (int floor = 0; floor < assortBtns.size(); floor++) {
        int numButtons = static_cast<int>(assortBtns[floor].size());

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
        int row = 0;//이 함수가 끝나면 없어질 변수라 &을 못씀
        auto mapIndex = 1;
        while (assortMapCnt > 0) {
            int col = 0; //이 함수가 끝나면 없어질 변수라 &을 못씀
            for (int i = 0; i < assortMapCnt && mapIndex < gameMap.size(); i++) {
                assortBtn.push_back(assortMapSelectButton(gameMap[mapIndex], res, { row, col}));
                mapIndex++;
                col++;
            }
            assortMapCnt -= 1;
            assortBtns.push_back(assortBtn);
            row++;
            assortBtn.clear();
        }
    }
}
void floorScene::animation(sf::Vector2f& center, float& dt) {
    if (animationYN) { return; }
    animationTime += dt;

    float progress = animationTime / animationDuration;
    if (progress >= 1.f) {
        progress = 1.f;
        animationYN = true;
    }

    // Cubic Ease-Out (처음 빠르게 → 끝 감속)
    float eased = 1.f - pow(1.f - progress, 3.f);

    float totalDistance = startY - targetY;
    float offset = totalDistance * eased;

    center.y = startY - offset;

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
    float appearDuration = 1.f; // 2초 동안 나타나게
    float alphaStep = 255.0f / appearDuration; // 초당 증가량
    alpha += alphaStep * deltaTime; // deltaTime 곱해서 프레임 독립적 처리

    if (alpha >= 255.f) {
        alpha = 255.f;
        appear = false;
    }

    color.a = static_cast<sf::Uint8>(std::min(alpha, 255.f));
    sprite.setColor(color);
}
void floorScene::allStartAppear() {
    startAppear();
    for (auto& assortBtnInfo : assortBtns) {
        for (auto& roomInfo : assortBtnInfo) {
            roomInfo.startAppear();
        }
    }
    line.startAppear();
}
void floorScene::setRoomNum(std::string roomName) {
    if (roomName == "rest") {
        roomNum = 1;
    }
    else if (roomName == "enemy") {
        roomNum = 2;
    }
    else if (roomName == "boss") {
        roomNum = 3;
    }
    return;
}

//roomScene
roomScene::roomScene(sf::RenderWindow& win, resourceManager& res, const int& roomNum) :
    res(res), window(win), log(win), view(sf::Vector2f(1280.f, 720.f), sf::Vector2f(2560.f, 1440.f)),
    frameDuration(0.15f), backBtn("back", 0.0f, 960.0f, res.getFont("fantasy")),
    statusFrame(res), hpB(win, res), mpB(win, res), expB(win, res), eloaImg(win, res,roomNum),
    normalOneImg(win, res), eliteOneImg(win, res), bossOneImg(win, res),
    hoHpB(win, res), action(win, res), startGD(res), battleState(BattleState::NotStarted), b(p, e)
    , battleGD(res), up(win, res, view), upBtn(res), battleBackBtn(res, view),skillT(view,res), skillTBtn(res)
    ,fire(win,res),eloaContract(win,res),GAMEOVER(res,view)
{
    //0.무슨 방인지 구분 rest, enemy , boss
    roomType = roomNum;
   
    if (roomType == 1) {
        heal = true;
    }

    //1. 기본 뷰 초기화
    window.setView(window.getDefaultView()); //main에서 하면 좋지만..늦게 알아버린,mapScene view에서의 누적 초기화
    window.setView(view);
    setBackground(res);
    
    //3. player mp, hp,action 위치 조정
    hpB.setTextHp();
    statusFrame.setPosition(eloaImg.getPosition(), expB.getPosition(), res);
    hpB.position(statusFrame.getHpmpPosition());
    mpB.position(statusFrame.getHpmpPosition());
    action.setPosition(eloaImg.getPosition(), eloaImg.getSprite());

    //4. enemy hp 위치 조정,player attack effect 위치 조정
    switch (e->convertEnemyType(getEnemyPtr().getEnemyType())) {
    case 0: //normal
        hoHpB.position(normalOneImg.getPosition(), normalOneImg.getEnemyImg());
        eloaImg.setEffectPosition(normalOneImg.getPosition(),eloaImg.getPosition());
        normalOneImg.setEffectPosition(eloaImg.getPosition());
        normalOneImg.homunculusStartFade();
        break; 
    case 1: //elite
        hoHpB.position(eliteOneImg.getPosition(), eliteOneImg.getEnemyImg());
        eloaImg.setEffectPosition(eliteOneImg.getPosition(), eloaImg.getPosition());
        eliteOneImg.setEffectPosition(eloaImg.getPosition());
        eliteOneImg.homunculusStartFade();
        break;
    case 2: //boss
        hoHpB.position(bossOneImg.getPosition(), bossOneImg.getEnemyImg());
        eloaImg.setEffectPosition(sf::Vector2f(bossOneImg.getPosition().x + res.getTexture("normal1").getSize().x / 1.1f,
            bossOneImg.getPosition().y + res.getTexture("normal1").getSize().y / 4.f), eloaImg.getPosition());
        normalOneImg.setEffectPosition(eloaImg.getPosition());
        bossOneImg.setEffectPosition(eloaImg.getPosition());
        bossOneImg.homunculusStartFade();
        break;
    default:
        break;
    }
    hoHpB.homunculusHpStartFade();

    //5. enemy hp text 위치 조정 , 포인터가 정해지는게 4번이라 그 이후에 해야 enemyType에 맞는 hp를 들고옴
    hoHpB.setTextHp();
    startGD.startFade();

    //6. skillBtn 위치 조절
    skillTBtn.setPosition(skillT.getSkTablePosition(), skillT.getSkTableSize());
    
    //7. tifiret라면 조정
    if (p->getClassName() == "tiferet") {
        eloaContract.setPosition(eloaImg.getPosition());
    }

    //8. gameover  설정
    GAMEOVER.startAppear();

    //9.debuglog
    hpDebug::initLogFiles();
}
void roomScene::update(sf::RenderWindow& window) {
    deltaTime = roomClock.restart().asSeconds();  // 프레임 독립적 시간
    if (eloaImg.isSkillEnd() && skillTurn) {
        skillTurn = false;
    }

    if (skillTurn) {
        eloaImg.skillUpdateFrame(deltaTime, res);
    }
    else {
        eloaImg.updateFrame(deltaTime, res);
    }          // F 애니메이션 갱신
    if (disableSkillCheck) {
        skillT.setDisableSkill();
        disableSkillCheck = false;
    }
    //tiferet
    if (p->getClassName() == "tiferet") {
        eloaContract.setContractText();
        eloaContract.updateTexture(res);
    }
    selectRoomType(roomType,window);   //무슨 방인지 구분
    sf::Event event;
    while (window.pollEvent(event)) {//이벤트가 있다면 계속 반복
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //설정 해놓은 창 기준 마우스
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//창 크기가 바뀌더라도 마우스의 위치를 제대로 찾게끔
     
        //아웃라인 색상 변경
        backBtn.outlineColormanager(worldPos);
        upBtn.outlineColormanager(worldPos);
        skillTBtn.outlineColormanager(worldPos);
        skillT.smallTableColorManager(worldPos);

        if (event.type == sf::Event::Closed) { //만약 event 타입으로써 닫기 event가 일어나면
            exitBtn = true;
        }
        if (event.type == sf::Event::MouseButtonReleased && backBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            back = true;
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::MouseButtonReleased && skillTBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            skillTBtn.close();
            skillT.close();
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && playerselect == playerSelect::skillVisible) {
            skillTBtn.close();
            skillT.close();
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::MouseButtonReleased && skillT.prevClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            skillT.prevPage();
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && playerselect == playerSelect::skillVisible && p->getLevel() > 1) {
            skillT.prevPage();
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::MouseButtonReleased && skillT.nextClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            skillT.nextPage();
        }
        if (battleState == BattleState::PlayerTurn && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && playerselect == playerSelect::skillVisible && p->getLevel() > 1) {
            skillT.nextPage();
        }
        if (battleState == BattleState::BackToMap && event.type == sf::Event::MouseButtonReleased && battleBackBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            back = true;
        }
        if (battleState == BattleState::BackToMap && event.type == sf::Event::MouseButtonReleased && upBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left) {
            next = true;
        }
        if (battleState == BattleState::BackToMap && event.type == sf::Event::MouseButtonReleased && upBtn.isClicked(worldPos) && event.mouseButton.button == sf::Mouse::Left && colorChange) {
            close = true;
        }

        if(roomType != 1){
            //선택지 아웃라인 스프라이트
            action.ActionManager(worldPos);

            // 플레이어 턴일 때만 클릭 처리
            if (battleState == BattleState::PlayerTurn && event.type == sf::Event::MouseButtonReleased 
                && action.isClicked(worldPos, skillT.isVisible()) != static_cast<int>(playerSelect::none)
                && event.mouseButton.button == sf::Mouse::Left && !startGD.isFading() && !battleGD.isAppearing()
                && !battleGD.isFading()) {
                playerselect = static_cast<playerSelect>(action.isClicked(worldPos, skillT.isVisible()));
                isTransition();
                switch (playerselect){
                case playerSelect::attack:
                    b.playerTurn(static_cast<int>(playerSelect::attack)); // cmd 로그를 보면 업뎃 되어있음. 이걸 실시간으로 피가 깎인걸 그래픽적인 부분과 현재체력을 보여주게끔 해줘야함 
                    eloaImg.updateTexture(res, static_cast<int>(playerSelect::attack));
                    battleState = BattleState::EnemyTurn;
                    break;
                case playerSelect::defense:
                    b.playerTurn(static_cast<int>(playerSelect::defense));
                    hpB.isBarrierOn() = true;
                    eloaImg.updateTexture(res, static_cast<int>(playerSelect::defense));
                    battleState = BattleState::EnemyTurn;
                    break;
                case playerSelect::skillVisible:
                    skillT.startVisible();
                    skillTBtn.unClose();
                    break;
                default:
                    break;
                }
            }
            else if (battleState == BattleState::PlayerTurn && event.type == sf::Event::MouseButtonReleased
                && playerselect == playerSelect::skillVisible && skillT.skillClicked(worldPos) >= 0
                && event.mouseButton.button == sf::Mouse::Left && !startGD.isFading() && !battleGD.isAppearing()
                && !battleGD.isFading()) {
                    isTransition();
                    eloaImg.skillTexture(res, skillT.skillClicked(worldPos));
                    b.playerTurn(static_cast<int>(playerSelect::skill),skillT.skillClicked(worldPos));
                    skillTBtn.close();
                    skillT.close();
                    skillTurn = true;
                    battleState = BattleState::EnemyTurn;
            }
            //선택지 아웃라인 스프라이트
            action.ActionManager(worldPos); 
        }
    } //End of while
    // 2. 게임 상태 처리 (전투 흐름)
    updateGameStatus(window);
    levelUp();
    battleBackBtn.slideToTarget(deltaTime);
    battleBackBtn.updateHitbox();
    skillT.pageCounting(res);
}
void roomScene::render(sf::RenderWindow& window) {
    window.draw(background);
    backBtn.draw(window); //돌아가기 버튼 (임시용)
    if (roomType != 1) {
        expB.draw(window);
        hpB.draw(window);
        mpB.draw(window);
        hoHpB.draw(window);
        statusFrame.draw(window);
        if (!skillT.isVisible() && battleState == BattleState::PlayerTurn) {
            action.draw(window);
        }
        if (p->getClassName() == "tiferet") {
            eloaContract.draw(window);
            eloaImg.draw(window);
        }
        switch (e->convertEnemyType(getEnemyPtr().getEnemyType())) {
        case 0:
            normalOneImg.draw(window);
            break;
        case 1:
            eliteOneImg.draw(window);
            break;
        case 2:
            bossOneImg.draw(window);
            break;
        default:
            break;
        }
        startGD.draw(window);
        battleGD.draw(window);
      
        if (skillT.isVisible() && battleState == BattleState::PlayerTurn) {
            skillT.draw(window);
            skillTBtn.draw(window);
        }
        if (p->getClassName() == "tiferet") {
            eloaImg.effectDraw(window);
        }
        normalOneImg.effectDraw(window);
        eliteOneImg.effectDraw(window);
        bossOneImg.effectDraw(window);
        battleBackBtn.draw(window);
        if (p->getBeforePlayer().level < p->getAfterPlayer().level) {
            up.draw(window);
            upBtn.draw(window);
        }
    }
    else {
        eloaImg.draw(window);
        fire.draw(window);
    }
    GAMEOVER.draw(window);
}
void roomScene::allStartAppear() {
    return;
}
void roomScene::selectRoomType(const int& roomType, sf::RenderWindow& win) {
    switch (roomType) {
    case 1:
        eloaImg.restFrame(deltaTime);
        fire.fireFrame(deltaTime);
        if (isHeal()) {
            int hp = static_cast<int>(p->getPlayer_current_health() + p->getPlayer_health() * 0.3f);
            if (hp > p->getPlayer_health()) { hp = p->getPlayer_health(); }
            p->setPlayer_current_health(hp);
            heal = false;
        }
        break;
    case 2:
        if (frame > 0.3f) {
            startGD.updateFade(deltaTime); // 시작 그라데이션
        }
        if (getEnemyPtr().getEnemyType() == "normal") {
            frame += deltaTime;
            normalOneImg.updateFrame(deltaTime, res, win);
        }
        else if (getEnemyPtr().getEnemyType() == "elite") {
            frame += deltaTime;
            eliteOneImg.updateFrame(deltaTime, res,win);
        }
        break;
    case 3:
        if (frame > 0.3f) {
            startGD.updateFade(deltaTime);
        }
        frame += deltaTime;
        bossOneImg.updateFrame(deltaTime,res,win);
        break;
    default:
        break;
    }
}
void roomScene::setBackground(resourceManager& res) {
    if (roomType == 1) {
        background.setTexture(res.getTexture("1floorRestRoom"));
        return;
    }
    background.setTexture(res.getTexture("1floorBattleRoomBg"));
}
void roomScene::updateGameStatus(sf::RenderWindow& win) {
    int enemyAction = 0;
    if (roomType != 1) {
        switch (battleState) {
        case BattleState::NotStarted:
            battleState = BattleState::PlayerTurn;// 전투 시작
            p->setBeforePlayer(); //전투 시작전 상태(레벨업 비교)
            break;
        case BattleState::PlayerTurn:
            if (hpB.isBarrierOn()) { hpB.isBarrierOn() = false; }
            updateTurnLog();
            p->setTurnPlayer();   // (버프 적용 스텟)
            p->setBattlePlayer(); // (버프 미적용 스텟)
            break;
        case BattleState::EnemyTurn:
            if (e->getEnemyCurrentHealth() <= 0 && !homunculusUpdateEnd) {//무승부 방지
                switch (e->convertEnemyType(getEnemyPtr().getEnemyType())) {
                case 0: // normal
                    normalOneImg.homunculusUpdateFade(homunculusUpdateEnd);
                    break;
                case 1: // elite
                    eliteOneImg.homunculusUpdateFade(homunculusUpdateEnd);
                    break;
                case 2: //boss
                    bossOneImg.homunculusUpdateFade(homunculusUpdateEnd);
                    break;
                default:
                    break;
                }
                hoHpB.homunculusHpUpdateFade(homunculusUpdateEnd);
                break;
            }
            if (homunculusUpdateEnd) {
                battleState = BattleState::Ended;
                break;
            }
            updateTurnLog();
            if(!battleGD.isAppearing() && !battleGD.isFading()){
                enemyAction = e->enemyAction(); //랜덤값 저장
                switch (e->convertEnemyType(getEnemyPtr().getEnemyType())) {
                case 0: //normal
                    normalOneImg.updateTexture(res, win ,enemyAction); //텍스쳐 바꾸기 위함
                    break;
                case 1: //elite
                    eliteOneImg.updateTexture(res, win ,enemyAction);
                    break;
                case 2: //boss
                    bossOneImg.updateTexture(res, win, enemyAction);
                    break;
                default:
                    break;
                }                
                b.enemyTurn(enemyAction);// 적 행동
                if (hpB.isBarrierOn() && enemyAction != 0) { hpB.isBarrierOn() = false; }
                if (p->getPlayer_current_health() == 0) {
                        battleState = BattleState::Ended;
                }
                else {
                    disableSkillCheck = true;
                    b.statusManager();
                    battleState = BattleState::PlayerTurn;
                    transition = false; //반복 클릭 해제
                }
            }
            break;
        case BattleState::Ended:
            if (p->getPlayer_current_health() > 0) {
                //eloaImg.isSkillEnd() = true;
                b.battleEnd();
                b.battleEndManager();
                up.setlevUpStatus(); //레벨 업 전과 레벨업 후의 내용 담기
                upBtn.setPosition(up.getStatusBackgroundPosition(), up.getStatusBackgroundSize());
                if (p->getBeforePlayer().level == p->getAfterPlayer().level) {
                    battleBackBtn.startSliding();
                }
                else {
                    statusFrame.setLevel();
                }
                battleState = BattleState::BackToMap;
            }
            else {
                if (hpB.getBarSize().x == 0.f) {
                    eloaImg.updateTexture(res, static_cast<int>(playerSelect::dead));
                    end = true;
                }
                if (end) {
                    GAMEOVER.updateAppear(deltaTime);
                }
                if (GAMEOVER.isExchange()) {
                    GAMEOVER.startFade();
                    GAMEOVER.setExchange();
                }
                GAMEOVER.updateFade(deltaTime);
                if (GAMEOVER.isGoRestart()) {
                    battleState = BattleState::restart;
                    GAMEOVER.isGoRestart() = false;
                }
            }
            
            break;
        case BattleState::BackToMap:
            break;
        case BattleState::restart:
            setRestartBtn();
            break;
        default:
            break;
        }
        battleGD.updateAppear(deltaTime);
        battleGD.updateFade(deltaTime);

        // hp/mp/exp 업데이트 
        hoHpB.setTextHp();
        hoHpB.setBarSize(deltaTime);
        hpB.setTextHp();
        hpB.setBarSize(deltaTime);
        mpB.setTextMp();
        mpB.setBarSize(deltaTime);
        expB.setTextExp();
        expB.setBarSize(deltaTime);
    }
}//백엔드와 연결된 직접적인 로직
void roomScene::updateTurnLog() {
    battleGD.selectText(static_cast<int>(battleState));
    if (!startGD.isFading()) {
        switch (battleState) {
        case BattleState::NotStarted:
            break;
        case BattleState::PlayerTurn:
            if (!turnLog.player) {
                turnLog = TurnLog{ true,false };
                battleGD.startAppear();
                oneTurn = true;
            }
            break;
        case BattleState::EnemyTurn:
            if (!turnLog.enemy) {
                turnLog = TurnLog{ false,true };
                battleGD.startAppear();
                oneTurn = true;
            }
            break;
        case BattleState::Ended:
            break;
        case BattleState::BackToMap:
            break;
        case BattleState::restart:
            break;
        default:
            break;
        }
        if (!battleGD.isAppearing() && oneTurn) {
            battleGD.startFade();
            oneTurn = false;
        }
    }
}
void roomScene::levelUp() { // levelUp 했을 시 다음으로 눌렀을 때 반응
    if (isNext()) {
        up.nextColor();
        next = false;
        colorChange = true;
    }
    if (isClose()) {
        up.close();
        upBtn.close();
        battleBackBtn.startSliding();
        close = false;
    }
}
