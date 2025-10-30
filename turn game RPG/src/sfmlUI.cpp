//sfmlUI.cpp

#include "sfmlUI.h"

#include <iostream>

using std::cout;
using std::endl;

/* middle point : x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top */

//title
title::title(const std::string& title, sf::Font& font, sf::Texture& tex)
{
	sprite.setTexture(tex); // 텍스처를 스프라이트에 연결
	text.setString(title); // 글자
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(100); // 글자크기
	sf::Color color(255, 255, 255, 0);
	text.setFillColor(color);
	sf::FloatRect bgBounds = sprite.getGlobalBounds();
	sf::FloatRect txtBounds = text.getLocalBounds();
	text.setPosition(
		bgBounds.left + (bgBounds.width - txtBounds.width) / 2.f,
		bgBounds.top + 250.f - txtBounds.top  // 원하는 y 위치 조절
	);
}
void title::draw(sf::RenderWindow& win) {
	win.draw(text);
}
void title::startFade() { //장면 전환 시작
	fading = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void title::updateFade() { //프레임 매초 갱신
	if (fading == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 255 - (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
	}
	text.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));
}
void title::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void title::updateAppear() {
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 증가
	if (alpha > 255) {
		alpha = 255;
		appear = false; // 완료되면 멈춤
	}
	text.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));
}
bool title::getAppear() {
	return appear;
}
bool title::getFading() {
	return fading;
}
float title::getAlpha() {
	return alpha;
}

//floorTitle
floorTitle::floorTitle(const std::wstring& floorTitle, sf::Font& font,sf::View& view, const int& floor)
{
	setTitle(floor, floorTitle);
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(150); // 글자크기
	text.setOutlineThickness(2.f);
	setView(view);
}
void floorTitle::draw(sf::RenderWindow& win) {
	win.draw(text);
}
void floorTitle::startFade() { //장면 전환 시작
	fading = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void floorTitle::updateFade() { //프레임 매초 갱신
	if (fading == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 255 - (elapsed / 1.f) * 255; // 1초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
	}
	text.setFillColor(sf::Color(51, 0, 102, (sf::Uint8)alpha));
	text.setOutlineColor(sf::Color(240, 240, 240, (sf::Uint8)alpha));
}
void floorTitle::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void floorTitle::updateAppear() {
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 1.0f) * 255; //2초에 걸쳐 증가
	if (alpha > 255) {
		alpha = 255;
		appear = false; // 완료되면 멈춤
	}
	text.setFillColor(sf::Color(51, 0, 102, (sf::Uint8)alpha));
	text.setOutlineColor(sf::Color(240, 240, 240, (sf::Uint8)alpha));
}
bool floorTitle::getAppear() {
	return appear;
}
void floorTitle::setTitle(const int& floor, const std::wstring& title) { //floorScene 층 이름 수정
	switch (floor){ //여기서 테마에 맞게 글자 색 조정도 이뤄짐
	case 1:
		text.setString(title); // 글자
		text.setFillColor(sf::Color(51, 0, 102, 0));
		text.setOutlineColor(sf::Color(240, 240, 240,0));
		break;
	case 2:
		text.setString(L"2F: 赤い砂漠");
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
}
void floorTitle::setView(sf::View& view) { // floorTitle 위치 설정
	sf::FloatRect viewBounds(view.getCenter(), view.getSize());
	sf::FloatRect txtBounds = text.getLocalBounds();
	text.setPosition((viewBounds.width - txtBounds.width) /2.f,
					  viewBounds.top - (txtBounds.height / 2.f));
}

//button 공용
void button::startFade() {
	fading = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void button::updateFade() {
	sf::Color textOutline = text.getOutlineColor(); // 현재 색상
	sf::Color textIn = text.getFillColor();
	sf::Color bgOutline = background.getOutlineColor();
	sf::Color bgIn = background.getFillColor();
	if (fading == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 255 - (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
	}
	textIn.a = static_cast<sf::Uint8>(alpha);
	textOutline.a = static_cast<sf::Uint8>(alpha);  // 알파값만 변경
	bgIn.a = static_cast<sf::Uint8>(alpha);
	bgOutline.a = static_cast<sf::Uint8>(alpha);
	text.setFillColor(textIn); // 다시 적용
	text.setOutlineColor(textOutline); // 다시 적용              
	background.setFillColor(bgIn); // 다시 적용
	background.setOutlineColor(bgOutline); // 다시 적용
}
void button::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void button::updateAppear() {
	sf::Color textOutline = text.getOutlineColor(); // 현재 색상
	sf::Color textIn = text.getFillColor();
	sf::Color bgOutline = background.getOutlineColor();
	sf::Color bgIn = background.getFillColor();
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 증가
	if (alpha > 255) {
		alpha = 255;
		appear = false; // 완료되면 멈춤
	}
	textIn.a = static_cast<sf::Uint8>(alpha);
	textOutline.a = static_cast<sf::Uint8>(alpha);  // 알파값만 변경
	bgIn.a = static_cast<sf::Uint8>(alpha);
	bgOutline.a = static_cast<sf::Uint8>(alpha);
	text.setFillColor(textIn); // 다시 적용
	text.setOutlineColor(textOutline); // 다시 적용              
	background.setFillColor(bgIn); // 다시 적용
	background.setOutlineColor(bgOutline); // 다시 적용
}
bool button::getAppear() {
	return appear;
}
bool button::getFading() {
	return fading;
}
float button::getAlpha() {
	return alpha;
}
sf::FloatRect button::getBackgroundGlobalBounds() const {
	return background.getGlobalBounds();
}
void button::setOutlineColor(sf::Color color){
	text.setOutlineColor(color);
}

//menuButton
menuButton::menuButton(const std::string& label, float x, float y, sf::Font& font)
{
	text.setString(label); // 글자
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(70); // 글자크기
	text.setOutlineThickness(2.f);

	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절

	// 버튼 텍스트 위치 설정
	background.setPosition(x, y); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	text.setPosition(x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
		y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top); //이후에 배경에 맞춰 위치를 조절 
}
void menuButton::draw(sf::RenderWindow& win){ //화면에 그리기
	sf::Color black(0, 0, 0, 0);
	background.setFillColor(black); //내부 색
	//background.setOutlineColor(sf::Color::White); //테두리 색
	//background.setOutlineThickness(2.f); //테두리 두께
	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool menuButton::isClicked(sf::Vector2f& mousePos){ //마우스 위치를 알려주는 int 형의 x,y
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}
void menuButton::outlineColormanager(sf::Vector2f& mousePos){
	if (background.getGlobalBounds().contains(mousePos)) {
		sf::Color color(224, 224, 224);
		text.setOutlineColor(color); //버튼 컬러
	}
	else {
		text.setOutlineColor(sf::Color::Black);//버튼 컬러
	}
}

//classSelectButton
classSelectButton::classSelectButton(const std::string& label, float x, float y, sf::Font& font) 
{	
	//직업 배경
	sf::Color color(0, 0, 51, 155);
	background.setFillColor(color); //내부 색
	background.setOutlineThickness(3.f); //테두리 두께

	//직업 이름
	text.setString(label); //직업 이름
	text.setFont(font); // 폰트
	text.setCharacterSize(50); //글자 크기
	sf::Color charactorClass(0, 153, 153); //직업 글자 색
	text.setFillColor(charactorClass); //글자 색
	

	//버튼 크기
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(400, bounds.height + 600));//버튼 배경 사이즈를 text에 맞춰 조절
	//위치 설정
	background.setPosition(x, y); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	text.setPosition(x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
		y + (background.getSize().y - text.getLocalBounds().height) / 10.f - text.getLocalBounds().top); //이후에 배경에 맞춰 위치를 조절 
}
void classSelectButton::draw(sf::RenderWindow& win){
	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool classSelectButton::isClicked(sf::Vector2f& mousePos){
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false; 
}
void classSelectButton::outlineColormanager(sf::Vector2f& mousePos){
	if (background.getGlobalBounds().contains(mousePos)) {
		sf::Color color(224, 224, 224);
		background.setOutlineColor(color); //버튼 컬러
	}
	else {
		sf::Color color(128, 128, 128);
		background.setOutlineColor(color);//버튼 컬러
	}
}

//backButton
backButton::backButton(const std::string& label, float x, float y, sf::Font& font){
	//text
	text.setString(label); // 글자
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(30); // 글자크기
	//background
	sf::Color color(204, 0, 0, 200);
	background.setFillColor(color); //내부 색
	background.setOutlineThickness(2.0f); //테두리 두께

	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절

	// 위치 설정
	background.setPosition(x, y); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	text.setPosition(x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
		y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top); //이후에 배경에 맞춰 위치를 조절 

}
void backButton::draw(sf::RenderWindow& win) {
	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool backButton::isClicked(sf::Vector2f& mousePos) {
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}
void backButton::outlineColormanager(sf::Vector2f& mousePos){
	if (background.getGlobalBounds().contains(mousePos)) {
		sf::Color color(224, 224, 224);
		background.setOutlineColor(color); //버튼 컬러
	}
	else {
		sf::Color outline(51, 0, 0, 155);
		background.setOutlineColor(outline);//버튼 컬러
	}
}

//assortMapSelectButton
assortMapSelectButton::assortMapSelectButton(room roomInfo, resourceManager& res, index indexPos) :
	rest(res.getTexture("heal")),
	enemy(res.getTexture("enemy")),
	boss(res.getTexture("boss")),
	roomInformation(roomInfo),
	indexPos(indexPos)

{
	if (roomInfo.name == "rest") {
		button.setTexture(rest); //texture를 sprite화 시킴
	}
	else if (roomInfo.name == "boss") {
		button.setTexture(boss); //texture를 sprite화 시킴
	}
	else if (roomInfo.name == "enemy") {
		button.setTexture(enemy); //texture를 sprite화 시킴
	}
	sf::Color buttonColor = button.getColor();
	buttonColor.a = ((sf::Uint8)0);
	button.setColor(buttonColor);
}
void assortMapSelectButton::draw(sf::RenderWindow& win){
	win.draw(button);
}
bool assortMapSelectButton::isClicked(sf::Vector2f& mousePos){return false;}
bool assortMapSelectButton::isClickedExtra(sf::Vector2f& mousePos, std::vector<int>& connectedRoom){
	sf::FloatRect bound = button.getGlobalBounds();
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))&& connectedRoom.empty()) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	for (auto& connected : connectedRoom) {
		if (getRoomInformation().id == connected && bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			return true; //버튼 배경안에 마우스 좌표가 있으면 true
		}
	}
	return false;
}
void assortMapSelectButton::outlineColormanager(sf::Vector2f& mousePos) {
	return;
}
void assortMapSelectButton::spriteScaleManager(const sf::Vector2f& mousePos, const std::vector<std::pair<int, int>>& visitedRoom) {
	bounds = button.getLocalBounds();
	//기저 조건
	for (auto& visited : visitedRoom) {
		if (visited.first == getIndexRow()) { return; }
	}

	//기저 조건에 해당 되지 않았을 경우
    if (button.getGlobalBounds().contains(mousePos) && roomInformation.name != "boss") {
		button.setScale(1.05f, 1.05f);  // 절대값
	}
	else if (button.getGlobalBounds().contains(mousePos) && roomInformation.name == "boss") {
		button.setScale(1.02f, 1.02f);
	}
	else {
        button.setScale(1.f, 1.f);  // 원래 크기
    }
}
void assortMapSelectButton::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void assortMapSelectButton::updateAppear(std::vector<std::pair<int, int>>& visitedRoom) {
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 2.0f) * 255; // 2초에 걸쳐 증가
	if (alpha > 255) {
		alpha = 255;
		appear = false; // 완료되면 멈춤
	}
	sf::Uint8 buttonAlphaColor = sf::Uint8(alpha);
	for (auto& visited : visitedRoom) {
		if (visited.first == getIndexRow() && visited.second == getIndexCol()) {
			button.setColor(sf::Color(255,255,153,buttonAlphaColor));
			return;
		}
		if (visited.first == getIndexRow()) {
			button.setColor(sf::Color(192, 192, 192, buttonAlphaColor));
			return;
		}
	}
	if (getRoomInformation().name == "rest") {
		button.setColor(sf::Color(170, 255, 170, buttonAlphaColor));
	}
	else if (getRoomInformation().name == "enemy") {
		button.setColor(sf::Color(255, 160, 160, buttonAlphaColor));
	}
	else if (getRoomInformation().name == "boss") {
		button.setColor(sf::Color(255, 204, 204, buttonAlphaColor));
	}
}
void assortMapSelectButton::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}
sf::Vector2f assortMapSelectButton::getPosition() {
	return button.getPosition();
}
sf::Sprite& assortMapSelectButton::getButton() {
	return button;
}
const room& assortMapSelectButton::getRoomInformation() const {
	return roomInformation;
}
int assortMapSelectButton::getIndexRow() const {
	return indexPos.row;
}
int assortMapSelectButton::getIndexCol() const {
	return indexPos.col;
}

//assortMapLine
assortMapLine::assortMapLine(std::vector<std::vector<assortMapSelectButton>>& assortBtns)
	:thickLine(sf::Vector2f(0.f, 0.f)), assortBtns(assortBtns)
{
}
void assortMapLine::draw(sf::RenderWindow& win) {
	for (auto& pair : lineGroup) {
		for (auto& line : pair.second.thickLineClone) {
			win.draw(line);
		}
	}
}
void assortMapLine::createLine() {
	for (auto it = assortBtns.begin(); it != assortBtns.end(); ++it) {
		for (auto& roomInfo : *it) { //roomInfo == assortMapSelectButton
			sf::Vector2f start = roomInfo.getButton().getPosition() + sf::Vector2f(
				roomInfo.getButton().getGlobalBounds().width / 2.f,
				roomInfo.getButton().getGlobalBounds().height / 2.f
			);
			auto nextIt = std::next(it); // 다음층 정보
			if (nextIt == assortBtns.end()) { continue; }

			for (int targetId : roomInfo.getRoomInformation().connectedRoom) {
				for (auto& nextRoom : *nextIt) {
					if (nextRoom.getRoomInformation().id == targetId) {
						sf::Vector2f end = nextRoom.getButton().getPosition() + sf::Vector2f(
							nextRoom.getButton().getGlobalBounds().width / 2.f,
							nextRoom.getButton().getGlobalBounds().height / 2.f
						);

						// 두 점 사이의 벡터
						sf::Vector2f direction = end - start;
						float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
						float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;

						// 굵은 직사각형으로 선 그리기
						thickLine.setSize(sf::Vector2f(length, 2.5f * 1.f)); // 2배 굵기
						thickLine.setPosition(start);
						thickLine.setRotation(angle);
						thickLine.setFillColor(sf::Color(122, 122, 122, 0));
						if (lineGroup.count(roomInfo.getRoomInformation().id) > 0) {
							sf::RectangleShape lineRect(thickLine); // 현재 thickLine 복사
							lineGroup[roomInfo.getRoomInformation().id].thickLineClone.push_back(lineRect);
						}
						else {
							lineGroup.insert({ roomInfo.getRoomInformation().id,
											lineInfo({roomInfo.getRoomInformation().id,
												{thickLine} }) });
						}
					}
				}
			}
		}
	}
}
void assortMapLine::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void assortMapLine::updateAppear() {
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 2.0f) * 130; // 2초에 걸쳐 증가
	if (alpha > 130) {
		alpha = 130;
		appear = false; // 완료되면 멈춤
	}
	sf::Color thickLineColor = thickLine.getFillColor();
	thickLineColor.a = ((sf::Uint8)alpha);
	for (auto& pair : lineGroup) {
		for (auto& line : pair.second.thickLineClone) {
			line.setFillColor(thickLineColor);
		}
	}
}
void assortMapLine::setFillColor(sf::Vector2f& mousePos, assortMapSelectButton& roomInfo) {
	if (roomInfo.getButton().getGlobalBounds().contains(mousePos)) {
		sf::Color color(255, 102, 70);
		for (auto& line : lineGroup[roomInfo.getRoomInformation().id].thickLineClone) { // 선 컬러
			line.setFillColor(color);
		}
	}
	else {
		sf::Color color(122, 122, 122, 130);
		for (auto& line : lineGroup[roomInfo.getRoomInformation().id].thickLineClone) { // 선 컬러
			line.setFillColor(color);
		}
	}
}
void assortMapLine::setAssortBtns(const std::vector<std::vector<assortMapSelectButton>>& srcBtns) {//버튼 초기화 할때 문제되서 우회 경로
	for (auto& assortBtn : srcBtns) {
		std::vector<assortMapSelectButton> test;
		for (auto& roomInfo : assortBtn) {
			test.push_back(roomInfo);
		}
		assortBtns.push_back(test);
	}
}

//mouse
mouse::mouse(sf::RenderWindow& window, sf::Texture& tex)
{
	sprite.setTexture(tex);// 마우스
	window.setMouseCursorVisible(false);
	sprite.setOrigin( getSizeX()/3.0f, getSizeY()/4.0f);
}
float mouse::getSizeX() {
	return sprite.getLocalBounds().width;
}
float mouse::getSizeY() {
	return sprite.getLocalBounds().height;
}
bool mouse::getVisible() {
	return visible;
}
void mouse::draw(sf::RenderWindow& window) {
	sf::View currentView = window.getView(); //마우스를 위해 현재 view를 저장
	sf::View uiView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)); //마우스를 위해 view가 아닌 게임 창크기 저장
	window.setView(uiView);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);// 마우스 좌표: 픽셀 그대로 사용 
	sprite.setPosition(sf::Vector2f(pixelPos)); // worldPos 아님! 
	window.draw(sprite);
	window.setView(currentView); // 화면 업데이트전 창크기 기준에서 view 기준으로 그려질 화면 크기 돌리기
}
void mouse::position(sf::Vector2f worldPos) {
	sprite.setPosition(worldPos);
}
void mouse::updatePositionFromWindow(sf::RenderWindow& window){
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	position(worldPos);
}
void mouse::mapSceneVisible() {
	visible = true;
}
void mouse::mapSceneUnvisible() {
	visible = false;
}

//status
status::status(resourceManager& res)
{
	//hpmp
	hpmp.setTexture(res.getTexture("hpmp"));

	//level 기본 설정
	level.setString("Lv." + getPlayerLevel(p->getLevel())); // 글자
	level.setFont(res.getFont("fantasy")); // 글자 폰트
	level.setCharacterSize(40); // 글자크기
	level.setOutlineThickness(1.f);
	level.setFillColor(sf::Color(192, 160, 127));

	// level 배경 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = level.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절
	background.setFillColor(sf::Color(0, 0, 0, 0));
}
void status::draw(sf::RenderWindow& win) {
	win.draw(hpmp);
	win.draw(background);
	win.draw(level);
}
const sf::Vector2f& status::getHpmpPosition() {
	return hpmp.getPosition();
}
void status::setPosition(const sf::Vector2f& characterP,const sf::Vector2f& expbarP, resourceManager& res) {
	//hpmp
	hpmp.setPosition(characterP.x , characterP.y + res.getTexture("tiferet").getSize().y /1.15f);

	// level 텍스트 위치 설정
	sf::Vector2f pos = sf::Vector2f(expbarP.x, expbarP.y - background.getSize().y);
	background.setPosition(pos); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	level.setPosition(background.getPosition().x + (background.getSize().x / 4.f)
		, background.getPosition().y - (background.getSize().y / 4.f)); //이후에 배경에 맞춰 위치를 조절 
}
std::string status::getPlayerLevel(const int& level) {
	switch (level){
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	case 11:
		return "11";
	default:
		break;
	}
	std::cout << "status getPlayerLevel() error." << std::endl;
}

//hpBar
hpBar::hpBar(sf::RenderWindow& win, resourceManager& res)
{
	//bar
	bar.setSize(sf::Vector2f(res.getTexture("hpmp").getSize().x, //x크기 0이 hp 0%임 현재는 100%
		res.getTexture("hpmp").getSize().y / 2.f));
	bar.setFillColor(sf::Color(207, 66, 62));
	maxWidth = bar.getGlobalBounds().width;
	//hp log
	hpLog.setFont(res.getFont("fantasy"));
	hpLog.setCharacterSize(40);
	hpLog.setFillColor(sf::Color(250, 250, 250));
	hpLog.setOutlineColor(sf::Color(250, 250, 250));
	hpLog.setOutlineThickness(1.f);

	//setSize , 제일 처음 피 깎여 있는거까지 구현
	maxWidth = bar.getLocalBounds().width; // HP 바 최대 길이
	changeWidth = (static_cast<float>(p->getPlayer_current_health()) / p->getPlayer_health()) * maxWidth;
	if (changeWidth < maxWidth) {
		newWidth = changeWidth;
	}
	else {
		newWidth = maxWidth;
	}
}
void hpBar::draw(sf::RenderWindow& win) {
	win.draw(bar);
	win.draw(hpLog);
}
void hpBar::position(const sf::Vector2f& hpmpP) {
	bar.setPosition(hpmpP);
	// 텍스트 중앙 origin 설정
	sf::FloatRect textBounds = hpLog.getLocalBounds();
	hpLog.setOrigin(textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f);

	// bar 중앙 위치에 텍스트 배치
	hpLog.setPosition(
		bar.getPosition().x + bar.getSize().x / 2.f,
		bar.getPosition().y + bar.getSize().y / 2.f);
}
void hpBar::setTextHp() {
	convertHp(p->getPlayer_current_health());
	convertMaxHp(p->getPlayer_health());
	hpLog.setString(hp + "/" + maxHp);
}
void hpBar::convertHp(const int& hp) {
	std::string stringHp = std::to_string(hp);
	this->hp = stringHp;
}
void hpBar::convertMaxHp(const int& maxHp) {
	std::string stringHp = std::to_string(maxHp);
	this->maxHp = stringHp;
}
void hpBar::setBarSize(float& dt) {
	changeWidth = (static_cast<float>(p->getPlayer_current_health()) / p->getPlayer_health()) * maxWidth;
	//레벨업을 하거나 모종의 방법으로 회복했을 때
	if (newWidth < changeWidth) {
		newWidth = changeWidth;
		startUp = true;
	}
	if (startUp) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime > 1.0f) {
			upTime = 1.0f;
			startUp = false;
		}
		bar.setSize(sf::Vector2f(newWidth * upTime, bar.getLocalBounds().height));
	}

	//hp가 줄어들 떄
	if (newWidth > changeWidth) {
		decrease = newWidth - changeWidth;
		startDown = true;
	}
	if (startDown) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime >= 1.0f) {
			upTime = 1.0f; 
			startDown = false;
			newWidth -= decrease * upTime;
		}
		else if (upTime < 1.0f) {
			bar.setSize(sf::Vector2f(newWidth - decrease * upTime, bar.getLocalBounds().height));
		}
	}

	//변화가 없을 때
	if (!startUp && !startDown) {
		elapsedTime = 0.f;
		bar.setSize(sf::Vector2f(newWidth, bar.getLocalBounds().height));
	}
}

//mpBar
mpBar::mpBar(sf::RenderWindow& win, resourceManager& res)
{
	bar.setSize(sf::Vector2f(res.getTexture("hpmp").getSize().x, //x크기 0이 mp 0%임 현재는 100%
		res.getTexture("hpmp").getSize().y / 2.f));
	bar.setFillColor(sf::Color(130, 130, 250));
	mpLog.setFont(res.getFont("fantasy"));
	mpLog.setCharacterSize(40);
	mpLog.setFillColor(sf::Color(250, 250, 250));
	mpLog.setOutlineColor(sf::Color(250, 250, 250));
	mpLog.setOutlineThickness(1.f);

	//setSize , 제일 처음 마나 깎여 있는거까지 구현
	maxWidth = bar.getLocalBounds().width; // MP 바 최대 길이
	changeWidth = (static_cast<float>(p->getCurrent_mana()) / p->getMana()) * maxWidth;
	if (changeWidth < maxWidth) {
		newWidth = changeWidth;
	}
	else {
		newWidth = maxWidth;
	}
}
void mpBar::draw(sf::RenderWindow& win) {
	win.draw(bar);
	win.draw(mpLog);
}
void mpBar::position(const sf::Vector2f& hpmpP) {
	bar.setPosition(hpmpP.x, hpmpP.y + bar.getSize().y);

	// bar 중앙 위치에 텍스트 배치
	mpLog.setPosition(
		bar.getPosition().x + bar.getSize().x / 2.7f,
		bar.getPosition().y + bar.getSize().y / 14.f);

}
void mpBar::setTextMp() {
	convertMp(p->getCurrent_mana());
	convertMaxMp(p->getMana());
	mpLog.setString(mp + "/" + maxMp);
}
void mpBar::convertMp(const int& mp) {
	std::string stringMp = std::to_string(mp);
	this->mp = stringMp;
}
void mpBar::convertMaxMp(const int& maxMp) {
	std::string stringMp = std::to_string(maxMp);
	this->maxMp = stringMp;
}
void mpBar::setBarSize(float& dt) {
	changeWidth = (static_cast<float>(p->getCurrent_mana()) / p->getMana()) * maxWidth;
	//레벨업을 하거나 모종의 방법으로 회복했을 때
	if (newWidth < changeWidth) {
		newWidth = changeWidth;
		startUp = true;
	}
	if (startUp) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime > 1.0f) {
			upTime = 1.0f;
			startUp = false;
		}
		bar.setSize(sf::Vector2f(newWidth * upTime, bar.getLocalBounds().height));
	}

	//Mp가 줄어들 떄
	if (newWidth > changeWidth) {
		decrease = newWidth - changeWidth;
		startDown = true;
	}
	if (startDown) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime >= 1.0f) {
			upTime = 1.0f;
			startDown = false;
			newWidth -= decrease * upTime;
		}
		else if (upTime < 1.0f) {
			bar.setSize(sf::Vector2f(newWidth - decrease * upTime, bar.getLocalBounds().height));
		}
	}

	//변화가 없을 때
	if (!startUp && !startDown) {
		elapsedTime = 0.f;
		bar.setSize(sf::Vector2f(newWidth, bar.getLocalBounds().height));
	}
}

//expBar
expBar::expBar(sf::RenderWindow& win, resourceManager& res)
{
	//expbar
	expbar.setTexture(res.getTexture("expbar"));
	
	//greenBar
	greenBar.setSize(sf::Vector2f(
		256.f, //static_cast<float>(res.getTexture("expbar").getSize().x) 까지
		static_cast<float>(res.getTexture("expbar").getSize().y)));
	greenBar.setFillColor(sf::Color(91, 180, 102));

	//exp log
	expLog.setFont(res.getFont("fantasy"));
	expLog.setCharacterSize(20);
	expLog.setFillColor(sf::Color(250, 250, 250));
	expLog.setOutlineColor(sf::Color(250, 250, 250));
	expLog.setOutlineThickness(1.f);

	//position
	position(win);

	//setSize , 제일 처음 경험치가 있다면 있는거까지 구현
	maxWidth = expbar.getLocalBounds().width; // exp 바 최대 길이
	changeWidth = (static_cast<float>(p->getNow_exp()) / p->getLevel_exp()) * maxWidth;
	if (changeWidth < maxWidth) {
		newWidth = changeWidth;
	}
	else {
		newWidth = maxWidth;
	}
}
void expBar::draw(sf::RenderWindow& win) {
	win.draw(greenBar);
	win.draw(expbar);
	win.draw(expLog);
}
void expBar::position(sf::RenderWindow& win) {
	expbar.setPosition(0,1440.f - expbar.getTexture()->getSize().y);
	greenBar.setPosition(expbar.getPosition());
	// bar 중앙 위치에 텍스트 배치
	expLog.setPosition(
		expbar.getPosition().x + expbar.getLocalBounds().width / 2.f,
		expbar.getPosition().y + expbar.getLocalBounds().top / 2.f);
}
const sf::Vector2f& expBar::getPosition() {
	return expbar.getPosition();
}
void expBar::setTextExp() {
	convertExp(p->getNow_exp());
	convertMaxExp(p->getLevel_exp());
	expLog.setString(exp + "/" + maxExp);
}
void expBar::convertExp(const int& exp) {
	std::string stringExp = std::to_string(exp);
	this->exp = stringExp;
}
void expBar::convertMaxExp(const int& maxExp) {
	std::string stringExp = std::to_string(maxExp);
	this->maxExp = stringExp;
}
void expBar::setBarSize(float& dt) {
	changeWidth = (static_cast<float>(p->getNow_exp()) / p->getLevel_exp()) * maxWidth;	
	
	//경험치를 얻었을 때
	if (newWidth < changeWidth) {
		newWidth = changeWidth;
		startUp = true;
	}
	if (startUp) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime > 1.0f) {
			upTime = 1.0f;
			startUp = false;
		}
		greenBar.setSize(sf::Vector2f(newWidth * upTime, expbar.getLocalBounds().height));
	} 

	//레벨업을 했을때
	if (newWidth > changeWidth) {
		decrease = newWidth - changeWidth;
		startDown = true;
	}
	if (startDown) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime >= 1.0f) {
			upTime = 1.0f; 
			startDown = false;
			newWidth -= decrease * upTime;
		}
		else if (upTime < 1.0f) {
			greenBar.setSize(sf::Vector2f(newWidth - decrease * upTime, expbar.getLocalBounds().height));
		}
	}

	//변화가 없을 때
	if (!startUp && !startDown) {
		elapsedTime = 0.f;
		greenBar.setSize(sf::Vector2f(newWidth, expbar.getLocalBounds().height));
	}
}

//levelUp
levelUp::levelUp(sf::RenderWindow& win, resourceManager& res, const sf::View& view) {
	//text
	levUp.setString(L"レベルアップ！");
	levUp.setFont(res.getFont("fantasy"));
	levUp.setCharacterSize(30);
	levUp.setFillColor(sf::Color(192, 160, 127));
	//textground
	sf::FloatRect textBounds = levUp.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	textBackground.setSize(sf::Vector2f(400, textBounds.height + 200));//버튼 배경 사이즈를 text에 맞춰 조절
	textBackground.setFillColor(sf::Color(0, 0, 51)); //내부 색
	textBackground.setOutlineColor(sf::Color(224, 224, 224)); //버튼 컬러
	textBackground.setOutlineThickness(3.f); //테두리 두께
	//statusground
	sf::FloatRect statusBounds = levUp.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	statusBackground.setSize(sf::Vector2f(1200, statusBounds.height + 900));//버튼 배경 사이즈를 text에 맞춰 조절
	statusBackground.setFillColor(sf::Color(0, 0, 51)); //내부 색
	statusBackground.setOutlineColor(sf::Color(224, 224, 224)); //버튼 컬러
	statusBackground.setOutlineThickness(3.f); //테두리 두께
	//position
	setPosition(win, view);
}
void levelUp::draw(sf::RenderWindow& win) {
	win.draw(statusBackground);
	win.draw(textBackground);
	win.draw(levUp);
}
void levelUp::startFade(){

}
void levelUp::updateFade(){

}
void levelUp::startAppear(){

}
void levelUp::updateAppear(){

}
void levelUp::setPosition(sf::RenderWindow& win, const sf::View& view) {
	//textBackground 
	textBackground.setPosition(view.getSize().x / 2.f - (textBackground.getSize().x / 2.f)
							, view.getSize().y / 10.f); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	//levUp
	levUp.setPosition(textBackground.getPosition().x + (textBackground.getSize().x - levUp.getLocalBounds().width) / 2.f
		, textBackground.getPosition().y + (textBackground.getSize().y - levUp.getLocalBounds().height) / 2.f);
	//statusBackground
	statusBackground.setPosition(textBackground.getPosition().x - (statusBackground.getLocalBounds().width - textBackground.getLocalBounds().width) / 2.f
							,textBackground.getPosition().y + textBackground.getLocalBounds().height /2.f);

}

//character 공용
void character::position(sf::RenderWindow& win) {
	characterImg.setPosition(win.getSize().x / 5.f, win.getSize().y / 1.7f);
}
const sf::Vector2f& character::getPosition(){
	return characterImg.getPosition();
}
const sf::Sprite& character::getSprite() {
	return characterImg;
}
void character::setEffectPosition(const sf::Vector2f& homunculusPos){
	attackEffect.setPosition(homunculusPos);
}

//tiferet
tiferetImg::tiferetImg(sf::RenderWindow& win, resourceManager& res)
{
	characterWidth = res.getTexture("tiferet").getSize().x;
	characterHeight = res.getTexture("tiferet").getSize().y;
	
	characterImg.setTexture(res.getTexture("tiferetSprite"));
	characterImg.setTextureRect(sf::IntRect(0, 0, characterWidth, characterHeight));

	effectWidth = 504;
	effectHeight = 600;

	attackEffect.setTexture(res.getTexture("attackEffectSheet"));
	attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
	
	tex = Tex::none;
	position(win);
}
void tiferetImg::draw(sf::RenderWindow& win) {
	win.draw(characterImg);
}
void tiferetImg::effectDraw(sf::RenderWindow& win) {
	win.draw(attackEffect);
}
void tiferetImg::updateFrame(const float& dt , resourceManager& res) { //장면 변화
	elapsed += dt;
	switch (tex){
	case Tex::none:
		if (elapsed >= frameDuration) { //elapsed가 0.45f 보다 커지면 초기화 시키고 장면 변화
			elapsed = 0.f;
			currentFrame++;
			int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				currentFrame = 0;
			}
			characterImg.setTextureRect(
				sf::IntRect(characterWidth * currentFrame, 0, characterWidth, characterHeight)
			);
		}
		break;
	case Tex::attack:
		if (elapsed >= 0.05f) {
			elapsed = 0.f;
			currentEffectFrame++;
			int framesPerAction = 6;
			if (currentEffectFrame >= framesPerAction) {
				currentEffectFrame = 0;
				tex = Tex::none;
				updateTexture(res);
				break;
			}
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		break;
	case Tex::defense:
		updateTexture(res);
		break;
	case Tex::hit:
		updateTexture(res);
		break;
	default:
		break;
	}
}
void tiferetImg::updateTexture(resourceManager& res, const int& playerSelect) {
	tex = static_cast<Tex>(playerSelect);
	elapsed = 0.f;
	switch (tex){
	case Tex::none:
		characterImg.setTexture(res.getTexture("tiferetSprite"));
		characterImg.setTextureRect(sf::IntRect(0, 0, characterWidth, characterHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		currentFrame = 0;  // 프레임 초기화 추가
		currentEffectFrame = 0;
		break;
	case Tex::attack:
		characterImg.setTexture(res.getTexture("tiferetAttack"));
		characterImg.setTextureRect(sf::IntRect(0, 0, characterWidth, characterHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		break;
	case Tex::defense: //임시 , 이미지가 없어서
		characterImg.setTexture(res.getTexture("tiferetSprite"));
		characterImg.setTextureRect(sf::IntRect(0, 0, characterWidth, characterHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		break;
	case Tex::hit://임시 , 이미지가 없어서
		characterImg.setTexture(res.getTexture("tiferetSprite"));
		characterImg.setTextureRect(sf::IntRect(0, 0, characterWidth, characterHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		break;
	default:
		break;
	}
}

//homunculus 공용
void homunculus::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 7.f) , win.getSize().y / 2.f);
}
const sf::Vector2f& homunculus::getPosition() {
	return enemyImg.getPosition();
}
const sf::FloatRect& homunculus::getEnemyImg() {
	return enemyImg.getLocalBounds();
}
void homunculus::setEffectPosition(const sf::Vector2f& playerPos) {
	attackEffect.setPosition(playerPos);
}
void homunculus::homunculusStartFade() {
	fading = true;
}
void homunculus::homunculusUpdateFade(bool& BattleEnd) {
	sf::Color homunculusColor = enemyImg.getColor(); // 현재 색상
	if (fading == false) {
		BattleEnd = true;
		return;
	}
	alpha -= 0.05f * 255; // 2.0초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
		BattleEnd = true;
		return;
	}
	homunculusColor.a = static_cast<sf::Uint8>(alpha);// 알파값만 변경
	enemyImg.setColor(homunculusColor); // 다시 적용
}

//normalOne
normalOne::normalOne(sf::RenderWindow& win, resourceManager& res)
{
	enemyWidth = res.getTexture("normal1").getSize().x;
	enemyHeight = res.getTexture("normal1").getSize().y;

	enemyImg.setTexture(res.getTexture("normal1Sprite"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));

	effectWidth = 496;
	effectHeight = 496;

	attackEffect.setTexture(res.getTexture("normal1EffectSheet"));
	attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
	tex = Tex::none;

	position(win);
}
void normalOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void normalOne::effectDraw(sf::RenderWindow& win) {
	win.draw(attackEffect);
}
void normalOne::updateFrame(float& dt, resourceManager& res, sf::RenderWindow& win) {
	elapsed += dt;
	switch (tex){
	case homunculus::Tex::none:
		if (elapsed >= frameDuration) { //elapsed가 0.45f 보다 커지면 초기화 시키고 장면 변화
			elapsed = 0.f;
			currentFrame++;
			int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				currentFrame = 0;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack1:
		if (elapsed >= 0.06f) {
			subElapsed += 0.06f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.14f) { //elapsed가 0.48f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res,win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack2:
		if (elapsed >= 0.06f) {
			subElapsed += 0.06f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.16f) { //elapsed가 0.48f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res,win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::hit:
		break;
	default:
		break;
	}
}
void normalOne::updateTexture(resourceManager& res, sf::RenderWindow& win, const int& enemyAction) {
	tex = static_cast<Tex>(enemyAction);
	currentFrame = 0;  // 움직임 모션 프레임 초기화
	currentEffectFrame = 0; //공격 모션 프레임 초기화
	elapsed = 0.f;
	switch (tex) { //스킬 추가시 case 업데이트
	case Tex::none:
		enemyImg.setTexture(res.getTexture("normal1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		break;
	case Tex::attack1:
		enemyImg.setTexture(res.getTexture("normal1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		break;
	case Tex::attack2:
		enemyImg.setTexture(res.getTexture("normal1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		break;
	case Tex::hit://임시 , 이미지가 없어서
		enemyImg.setTexture(res.getTexture("normal1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		break;
	default:
		break;
	}

}

//eliteOne
eliteOne::eliteOne(sf::RenderWindow& win, resourceManager& res)
{
	enemyWidth = res.getTexture("elite1").getSize().x;
	enemyHeight = res.getTexture("elite1").getSize().y;

	enemyImg.setTexture(res.getTexture("elite1Sprite"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));

	effectWidth = 496;
	effectHeight = 496;

	attackEffect.setTexture(res.getTexture("elite1EffectSheet"));
	attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
	tex = Tex::none;

	position(win);
}
void eliteOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void eliteOne::effectDraw(sf::RenderWindow& win) {
	win.draw(attackEffect);
}
void eliteOne::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 4.f), win.getSize().y / 1.65f);
}
void eliteOne::updateFrame(float& dt, resourceManager& res, sf::RenderWindow& win) {
	elapsed += dt;
	switch (tex){
	case homunculus::Tex::none:
		if (elapsed >= frameDuration) { //elapsed가 0.45f 보다 커지면 초기화 시키고 장면 변화
			elapsed = 0.f;
			currentFrame++;
			int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction)
				currentFrame = 0;

			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack1:
		if (elapsed >= 0.06f) {
			subElapsed += 0.06f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.2f) { //elapsed가 0.1f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res,win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack2:
		if (elapsed >= 0.06f) {
			subElapsed += 0.06f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.2f) { //elapsed가 0.1f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res,win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::hit:
		break;
	default:
		break;
	}
}
void eliteOne::updateTexture(resourceManager& res, sf::RenderWindow& win, const int& enemyAction) {
	tex = static_cast<Tex>(enemyAction);
	currentFrame = 0;  // 움직임 모션 프레임 초기화
	currentEffectFrame = 0; //공격 모션 프레임 초기화
	elapsed = 0.f;
	switch (tex) { //스킬 추가시 case 업데이트
	case Tex::none:
		enemyHeight = res.getTexture("elite1").getSize().y;
		enemyImg.setTexture(res.getTexture("elite1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		position(win);
		break;
	case Tex::attack1:
		enemyHeight = res.getTexture("elite1Attack").getSize().y;
		enemyImg.setTexture(res.getTexture("elite1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		position(win);
		break;
	case Tex::attack2:
		enemyHeight = res.getTexture("elite1Attack").getSize().y;
		enemyImg.setTexture(res.getTexture("elite1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		position(win);
		break;
	case Tex::hit://임시 , 이미지가 없어서
		enemyHeight = res.getTexture("elite1").getSize().y;
		enemyImg.setTexture(res.getTexture("elite1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		position(win);
		break;
	default:
		break;
	}
}

//bossOne
bossOne::bossOne(sf::RenderWindow& win, resourceManager& res)
{
	enemyWidth = res.getTexture("boss1").getSize().x;
	enemyHeight = res.getTexture("boss1").getSize().y;

	enemyImg.setTexture(res.getTexture("boss1Sprite"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));

	effectWidth = 496;
	effectHeight = 496;

	attackEffect.setTexture(res.getTexture("boss1EffectSheet"));
	attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
	tex = Tex::none;

	position(win);
}
void bossOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void bossOne::effectDraw(sf::RenderWindow& win) {
	win.draw(attackEffect);
}
void bossOne::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 2.4f), win.getSize().y / 3.2f);
}
void bossOne::updateFrame(float& dt, resourceManager& res, sf::RenderWindow& win) {
	elapsed += dt;
	switch (tex){
	case homunculus::Tex::none:
		if (elapsed >= frameDuration) { //elapsed가 0.15f 보다 커지면 초기화 시키고 장면 변화
			elapsed = 0.f;
			currentFrame++;
			int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				currentFrame = 0;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack1:
		if (elapsed >= 0.08f) {
			subElapsed += 0.08f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.1f) { //elapsed가 0.1f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res, win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::attack2:
		if (elapsed >= 0.08f) {
			subElapsed += 0.08f;
			elapsed = 0.f;
			currentEffectFrame++;
			attackEffect.setTextureRect(
				sf::IntRect(effectWidth * currentEffectFrame, 0, effectWidth, effectHeight)
			);
		}
		if (subElapsed >= 0.1f) { //elapsed가 0.1f 보다 커지면 초기화 시키고 장면 변화
			subElapsed = 0.f;
			currentFrame++;
			int framesPerAction = 3; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
			if (currentFrame >= framesPerAction) {
				tex = Tex::none;
				updateTexture(res, win);
				break;
			}
			enemyImg.setTextureRect(
				sf::IntRect(enemyWidth * currentFrame, 0, enemyWidth, enemyHeight)
			);
		}
		break;
	case homunculus::Tex::hit:
		break;
	default:
		break;
	}
}
void bossOne::updateTexture(resourceManager& res, sf::RenderWindow& win, const int& enemyAction) {
	tex = static_cast<Tex>(enemyAction);
	currentFrame = 0;  // 움직임 모션 프레임 초기화
	currentEffectFrame = 0; //공격 모션 프레임 초기화
	elapsed = 0.f;
	switch (tex) { //스킬 추가시 case 업데이트
	case Tex::none:
		enemyImg.setTexture(res.getTexture("boss1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		position(win);
		break;
	case Tex::attack1:
		enemyImg.setTexture(res.getTexture("boss1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		position(win);
		break;
	case Tex::attack2:
		enemyImg.setTexture(res.getTexture("boss1Attack"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, effectWidth, effectHeight));
		position(win);
		break;
	case Tex::hit://임시 , 이미지가 없어서
		enemyImg.setTexture(res.getTexture("boss1Sprite"));
		enemyImg.setTextureRect(sf::IntRect(0, 0, enemyWidth, enemyHeight));
		attackEffect.setTextureRect(sf::IntRect(0, 0, 0, 0));
		position(win);
		break;
	default:
		break;
	}
	return;
}

//homunculusHpbar
homunculusHpbar::homunculusHpbar(sf::RenderWindow& win, resourceManager& res)
{
	//enemyHp
	enemyHp.setTexture(res.getTexture("enemyHp"));

	//bar
	bar.setFillColor(sf::Color(207, 66, 62));
	//hp log
	hpLog.setFont(res.getFont("fantasy"));
	hpLog.setCharacterSize(40);
	hpLog.setFillColor(sf::Color::White);
	hpLog.setOutlineColor(sf::Color::White);
	hpLog.setOutlineThickness(1.f);

	//setSize , 제일 처음 피 깎여 있는거까지 구현
	maxWidth = enemyHp.getLocalBounds().width; // HP 바 최대 길이
	changeWidth = (static_cast<float>(e->getEnemyCurrentHealth()) / e->getEnemy_health()) * maxWidth;
	if (changeWidth < maxWidth) {
		newWidth = changeWidth;
	}
	else {
		newWidth = maxWidth;
	}

}
void homunculusHpbar::draw(sf::RenderWindow& win) {
	win.draw(bar);
	win.draw(enemyHp);
	win.draw(hpLog);
}
const sf::Vector2f& homunculusHpbar::getEnemyHpPosition() {
	return enemyHp.getPosition();
}
void homunculusHpbar::position(const sf::Vector2f& enemyP, const sf::FloatRect& enemyImg) {
	// HP바 배경 위치: 적 이미지 아래
	enemyHp.setPosition(1536.f, 1110.f); // 1536,1110

	// bar 위치
	bar.setPosition(enemyHp.getPosition());
	// 텍스트 중앙 정렬
	sf::FloatRect textBounds = hpLog.getGlobalBounds();
	hpLog.setOrigin(
		textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f
	);
	hpLog.setPosition(
		enemyHp.getPosition().x + (enemyHp.getLocalBounds().width / 2.5f),
		enemyHp.getPosition().y - 7.f);
}
void homunculusHpbar::setTextHp() {
	convertHp(e->getEnemyCurrentHealth());
	convertMaxHp(e->getEnemy_health());
	hpLog.setString(hp + "/" + maxHp);
}
void homunculusHpbar::convertHp(const int& hp) {
	std::string stringHp = std::to_string(hp);
	this->hp = stringHp;
}
void homunculusHpbar::convertMaxHp(const int& maxHp) {
	std::string stringHp = std::to_string(maxHp);
	this->maxHp = stringHp;
}
void homunculusHpbar::setBarSize(float& dt) {
	changeWidth = (static_cast<float>(e->getEnemyCurrentHealth()) / e->getEnemy_health()) * maxWidth;
	//레벨업을 하거나 모종의 방법으로 회복했을 때
	if (newWidth < changeWidth) {
		newWidth = changeWidth;
		startUp = true;
	}
	if (startUp) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime > 1.0f) {
			upTime = 1.0f;
			startUp = false;
		}
		bar.setSize(sf::Vector2f(newWidth * upTime, enemyHp.getLocalBounds().height));
	}

	//hp가 줄어들 떄
	if (newWidth > changeWidth) {
		decrease = newWidth - changeWidth;
		startDown = true;
	}
	if (startDown) {
		elapsedTime += dt;
		float upTime = elapsedTime / 1.0f; // 1.0f초 동안 변화
		if (upTime >= 1.0f) {
			upTime = 1.0f;
			startDown = false;
			newWidth -= decrease * upTime;
		}
		else if (upTime < 1.0f) {
			bar.setSize(sf::Vector2f(newWidth - decrease * upTime, enemyHp.getLocalBounds().height));
		}
	}

	//변화가 없을 때
	if (!startUp && !startDown) {
		elapsedTime = 0.f;
		bar.setSize(sf::Vector2f(newWidth, enemyHp.getLocalBounds().height));
	}
}
void homunculusHpbar::homunculusHpStartFade() {
	fading = true;
}
void homunculusHpbar::homunculusHpUpdateFade(bool& BattleEnd) {
	sf::Color enemyHpColor = enemyHp.getColor(); // 현재 색상
	sf::Color hpLogColor = hpLog.getFillColor(); //현재 텍스트 색상
	if (fading == false) {
		BattleEnd = true;
		return;
	}
	alpha -= 0.05f * 255; // 2.0초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
		BattleEnd = true;
		return;
	}
	enemyHpColor.a = static_cast<sf::Uint8>(alpha);// 알파값만 변경
	hpLogColor.a = static_cast<sf::Uint8>(alpha);

	enemyHp.setColor(enemyHpColor); // 다시 적용
	hpLog.setFillColor(hpLogColor);
	hpLog.setOutlineColor(hpLogColor);
}

//selectAction
selectAction::selectAction(sf::RenderWindow& win, resourceManager& res)
{
	//sprite
	frameWidth = res.getTexture("attack").getSize().x;
	frameHeight = res.getTexture("attack").getSize().y;

	attack.setTexture(res.getTexture("attackSprite"));
	defense.setTexture(res.getTexture("defenseSprite"));
	skill.setTexture(res.getTexture("skillSprite"));

	attack.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	defense.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	skill.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));

	sf::Uint8 alpha = static_cast<sf::Uint8>(180);
	attack.setColor(sf::Color(240,240,240, alpha));
	defense.setColor(sf::Color(240, 240, 240, alpha));
	skill.setColor(sf::Color(240, 240, 240, alpha));

	//background
	background.setSize(sf::Vector2f(attack.getLocalBounds().width,
		attack.getLocalBounds().height + defense.getLocalBounds().height + skill.getLocalBounds().height));
	background.setFillColor(sf::Color(0, 0, 0, 80));

	//text
	attackText.setFont(res.getFont("fantasy"));
	defenseText.setFont(res.getFont("fantasy"));
	skillText.setFont(res.getFont("fantasy"));

	attackText.setCharacterSize(50);
	defenseText.setCharacterSize(50);
	skillText.setCharacterSize(50);

	attackText.setString("attack");
	defenseText.setString("defense");
	skillText.setString("skill");
	
	attackText.setFillColor(sf::Color(232, 220, 192));
	defenseText.setFillColor(sf::Color(232, 220, 192));
	skillText.setFillColor(sf::Color(232, 220, 192));

}
void selectAction::draw(sf::RenderWindow& win) {
	win.draw(background);
	win.draw(attack);
	win.draw(defense);
	win.draw(skill);
	win.draw(attackText);
	win.draw(defenseText);
	win.draw(skillText);
}
bool selectAction::isClicked(sf::Vector2f& mousePos, bool& a, bool& d, bool& s) {
	sf::FloatRect attackBound = attack.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	sf::FloatRect defenseBound = defense.getGlobalBounds();
	sf::FloatRect skillBound = skill.getGlobalBounds();
	if (attackBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))){
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		a = true;
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	else if (defenseBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		d = true;
		return true;
	}
	else if (skillBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		s = true;
		return true;
	}
	return false;
}
void selectAction::setPosition(const sf::Vector2f& characterP, const sf::Sprite& characterImg) {
	//sprite
	attack.setPosition(characterP.x + characterImg.getLocalBounds().width / 2.f,
		characterP.y + 100.f);
	defense.setPosition(characterP.x + characterImg.getLocalBounds().width / 2.f,
		attack.getPosition().y + attack.getLocalBounds().height);
	skill.setPosition(characterP.x + characterImg.getLocalBounds().width / 2.f,
		defense.getPosition().y + defense.getLocalBounds().height);

	//background
	background.setPosition(attack.getPosition());

	//text
	attackText.setPosition(attack.getPosition().x + (attack.getLocalBounds().width - attackText.getLocalBounds().width) / 1.5f,
		attack.getPosition().y + (attack.getLocalBounds().height - attackText.getLocalBounds().height) / 2.f - attackText.getLocalBounds().height /2.f);
	defenseText.setPosition(defense.getPosition().x + (defense.getLocalBounds().width - defenseText.getLocalBounds().width) / 1.5f,
		defense.getPosition().y + (defense.getLocalBounds().height - defenseText.getLocalBounds().height) / 2.f - defenseText.getLocalBounds().height / 2.f);
	skillText.setPosition(skill.getPosition().x + (skill.getLocalBounds().width - skillText.getLocalBounds().width) / 1.5f,
		skill.getPosition().y + (skill.getLocalBounds().height - skillText.getLocalBounds().height) / 2.f - skillText.getLocalBounds().height / 2.f);
}
void selectAction::ActionManager(sf::Vector2f& mousePos) {
	int currentFrame = 0;
	int holdFrame = 1;
	//attack
	attack.getGlobalBounds().contains(mousePos) ? 
		attack.setTextureRect(sf::IntRect(0, frameHeight * holdFrame, frameWidth, frameHeight))
	   : attack.setTextureRect(sf::IntRect(0, frameHeight * currentFrame, frameWidth, frameHeight));
	//defense
	defense.getGlobalBounds().contains(mousePos) ?
		defense.setTextureRect(sf::IntRect(0, frameHeight * holdFrame, frameWidth, frameHeight))
	   : defense.setTextureRect(sf::IntRect(0, frameHeight * currentFrame, frameWidth, frameHeight));
	//skill
	skill.getGlobalBounds().contains(mousePos) ?
		skill.setTextureRect(sf::IntRect(0, frameHeight * holdFrame, frameWidth, frameHeight))
		: skill.setTextureRect(sf::IntRect(0, frameHeight * currentFrame, frameWidth, frameHeight));
}

//gradation 공용
void gradation::startFade() {
	if (fading) { return; } // appear 중이면 무시
	fading = true;
	elapsedTime = 0.f;
}
void gradation::updateFade(float& dt) {
	sf::Color textColor = text.getFillColor();
	if (fading == false) {
		return;
	}
	elapsedTime += dt;
	float fadeTime = elapsedTime / 0.7f; // 0.7f초 동안 페이드
	if (fadeTime > 0.7f) {
		fadeTime = 0.7f;
	}

	sideAlpha = static_cast<sf::Uint8>(std::max(0.f, 100.f * (0.7f - fadeTime)));
	centerAlpha = static_cast<sf::Uint8>(std::max(0.f, 170.f * (0.7f - fadeTime)));
	startAlpha = static_cast<sf::Uint8>(std::max(0.f, 255.f * (0.7f - fadeTime)));

	for (int i = 0; i < 4; i++) {
		sideGrad[i].color.a = static_cast<sf::Uint8>(sideAlpha);
		centerGrad[i].color.a = static_cast<sf::Uint8>(centerAlpha);
	}

	textColor.a = static_cast<sf::Uint8>(startAlpha);
	text.setFillColor(textColor);

	if (fadeTime >= 0.7f) {
		fading = false;
		elapsedTime = 0.f;
	}
}
bool gradation::isFading() {
	return fading;
}
void gradation::startAppear() {
	if (appear) { return; }// appear 중이면 무시
	appear = true;
	elapsedTime = 0.f;
}
void gradation::updateAppear(float& dt) {
	sf::Color textColor = text.getFillColor();

	if (!appear) {
		return;
	}
	
	elapsedTime += dt;
	float appearTime = elapsedTime / 0.5f; // 1.0초 동안 appear
	if (appearTime > 0.5f) {
		appearTime = 0.5f;
	}

	sideAlpha = static_cast<sf::Uint8>(std::max(0.f, 100.f * (appearTime * 2.f)));
	centerAlpha = static_cast<sf::Uint8>(std::max(0.f, 170.f * (appearTime * 2.f)));
	startAlpha = static_cast<sf::Uint8>(std::max(0.f, 255.f * (appearTime * 2.f)));

	for (int i = 0; i < 4; i++) {
		sideGrad[i].color.a = static_cast<sf::Uint8>(sideAlpha);
		centerGrad[i].color.a = static_cast<sf::Uint8>(centerAlpha);
	}

	textColor.a = static_cast<sf::Uint8>(startAlpha);
	text.setFillColor(textColor);

	if (appearTime >= 0.5f) {
		appear = false;
		elapsedTime = 0.f;
	}
}
bool gradation::isAppearing() {
	return appear;
}

//startGradtion
startGradation::startGradation(resourceManager& res) {
	width = static_cast<float>(res.getTexture("1floorBattleRoomBg").getSize().x);
	height = static_cast<float>(res.getTexture("1floorBattleRoomBg").getSize().y);
	centerY = height / 2.f;
	barHeight = 200.f; // 띠의 높이

	//text입력
	text.setString("START");
	text.setFont(res.getFont("fantasy"));
	text.setCharacterSize(130);

	//사이드 그라데이션 정의
	sideGrad.setPrimitiveType(sf::Quads);
	sideGrad.resize(4);
	//센터 그라데이션 정의
	centerGrad.setPrimitiveType(sf::Quads);
	centerGrad.resize(4);
	//위치와 색 정의
	setPosition();
	setColor();
}
void startGradation::draw(sf::RenderWindow& win) {
	win.draw(sideGrad);
	win.draw(centerGrad);
	win.draw(text);
}
void startGradation::setPosition() {
	//sideGrad
	sideGrad[0].position = sf::Vector2f(0.f, centerY - barHeight / 2.f);     // 왼쪽 위
	sideGrad[1].position = sf::Vector2f(width, centerY - barHeight / 2.f);   // 오른쪽 위
	sideGrad[2].position = sf::Vector2f(width, centerY + barHeight / 2.f);   // 오른쪽 아래
	sideGrad[3].position = sf::Vector2f(0.f, centerY + barHeight / 2.f);     // 왼쪽 아래
	//centerGrad
	centerGrad[0].position = sf::Vector2f(width / 4.f, centerY - barHeight / 2.f);		 // 왼쪽 위
	centerGrad[1].position = sf::Vector2f(width / 4.f * 3.f, centerY - barHeight / 2.f); // 오른쪽 위
	centerGrad[2].position = sf::Vector2f(width / 4.f * 3.f, centerY + barHeight / 2.f); // 오른쪽 아래
	centerGrad[3].position = sf::Vector2f(width / 4.f, centerY + barHeight / 2.f);		 // 왼쪽 아래
	//start
	text.setPosition(sf::Vector2f(centerGrad.getBounds().width - text.getLocalBounds().width / 2.f,
		centerY - barHeight / 2.f + 20.f));
}		//620 + 248 = 868
void startGradation::setColor() {
	//sideGrad
	sideGrad[0].color = sf::Color(0, 0, 0, sideAlpha);   // 왼쪽 위
	sideGrad[3].color = sf::Color(0, 0, 0, sideAlpha);   // 왼쪽 아래
	sideGrad[1].color = sf::Color(0, 0, 0, sideAlpha);   // 오른쪽 위
	sideGrad[2].color = sf::Color(0, 0, 0, sideAlpha);   // 오른쪽 아래
	//centerGrad
	centerGrad[0].color = sf::Color(0, 0, 0, centerAlpha); // 왼쪽 위
	centerGrad[3].color = sf::Color(0, 0, 0, centerAlpha); // 왼쪽 아래
	centerGrad[1].color = sf::Color(0, 0, 0, centerAlpha); // 오른쪽 위
	centerGrad[2].color = sf::Color(0, 0, 0, centerAlpha); // 오른쪽 아래
	//start
	text.setFillColor(sf::Color(97, 0, 0, 255));
}

//battleGradation
battleGradation::battleGradation(resourceManager& res) {
	width = static_cast<float>(res.getTexture("1floorBattleRoomBg").getSize().x);
	height = static_cast<float>(res.getTexture("1floorBattleRoomBg").getSize().y);
	centerY = height / 4.f;
	barHeight = 100.f; // 띠의 높이

	//text입력
	text.setFont(res.getFont("fantasy"));
	text.setCharacterSize(60);

	//사이드 그라데이션 정의
	sideGrad.setPrimitiveType(sf::Quads);
	sideGrad.resize(4);
	//센터 그라데이션 정의
	centerGrad.setPrimitiveType(sf::Quads);
	centerGrad.resize(4);
	//위치와 색 정의
	setPosition();
	setColor();
}
void battleGradation::draw(sf::RenderWindow& win) {
	win.draw(sideGrad);
	win.draw(centerGrad);
	win.draw(text);
}
void battleGradation::setPosition() {
	//sideGrad
	sideGrad[0].position = sf::Vector2f(0.f, centerY - barHeight / 2.f);     // 왼쪽 위
	sideGrad[1].position = sf::Vector2f(width, centerY - barHeight / 2.f);   // 오른쪽 위
	sideGrad[2].position = sf::Vector2f(width, centerY + barHeight / 2.f);   // 오른쪽 아래
	sideGrad[3].position = sf::Vector2f(0.f, centerY + barHeight / 2.f);     // 왼쪽 아래
	//centerGrad
	centerGrad[0].position = sf::Vector2f(width / 4.f, centerY - barHeight / 2.f);		 // 왼쪽 위
	centerGrad[1].position = sf::Vector2f(width / 4.f * 3.f, centerY - barHeight / 2.f); // 오른쪽 위
	centerGrad[2].position = sf::Vector2f(width / 4.f * 3.f, centerY + barHeight / 2.f); // 오른쪽 아래
	centerGrad[3].position = sf::Vector2f(width / 4.f, centerY + barHeight / 2.f);		 // 왼쪽 아래
	//text
	text.setPosition(sf::Vector2f(centerGrad.getBounds().width - 200.f,
		centerY - barHeight / 2.f + 5.f));
}		
void battleGradation::setColor() {
	//sideGrad
	sideGrad[0].color = sf::Color(0, 0, 0, sideAlpha);   // 왼쪽 위
	sideGrad[3].color = sf::Color(0, 0, 0, sideAlpha);   // 왼쪽 아래
	sideGrad[1].color = sf::Color(0, 0, 0, sideAlpha);   // 오른쪽 위
	sideGrad[2].color = sf::Color(0, 0, 0, sideAlpha);   // 오른쪽 아래
	//centerGrad
	centerGrad[0].color = sf::Color(0, 0, 0, centerAlpha); // 왼쪽 위
	centerGrad[3].color = sf::Color(0, 0, 0, centerAlpha); // 왼쪽 아래
	centerGrad[1].color = sf::Color(0, 0, 0, centerAlpha); // 오른쪽 위
	centerGrad[2].color = sf::Color(0, 0, 0, centerAlpha); // 오른쪽 아래
	//start
	text.setFillColor(sf::Color(255,255,255,0));
}
void battleGradation::selectText(const int& battleTurn) {
	switch (battleTurn){
	case 1:
		text.setString("player turn!");
		break;
	case 2:
		text.setString("enemy turn!");
		break;
	default:
		break;
	}
}
bool& battleGradation::convertPlayerTurn() {
	return playerTurn;
}
bool& battleGradation::convertEnemyTurn() {
	return enemyTurn;
}

