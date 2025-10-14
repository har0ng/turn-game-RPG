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
	hpmp.setPosition(characterP.x , characterP.y + res.getTexture("tiferet").getSize().y);

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
	
	
	//hp log
	convertHp(p->getPlayer_current_health());
	convertMaxHp(p->getPlayer_health());
	hpLog.setString(hp + "/" + maxHp);
	hpLog.setFont(res.getFont("fantasy"));
	hpLog.setCharacterSize(40);
	hpLog.setFillColor(sf::Color::White);
	hpLog.setOutlineColor(sf::Color::White);
	hpLog.setOutlineThickness(1.f);
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
void hpBar::convertHp(const int& hp) {
	std::string stringHp = std::to_string(hp);
	this->hp = stringHp;
}
void hpBar::convertMaxHp(const int& maxHp) {
	std::string stringHp = std::to_string(maxHp);
	this->maxHp = stringHp;
}

//mpBar
mpBar::mpBar(sf::RenderWindow& win, resourceManager& res)
	:maxMp(0), mp(0)
{
	bar.setSize(sf::Vector2f(res.getTexture("hpmp").getSize().x, //x크기 0이 mp 0%임 현재는 100%
		res.getTexture("hpmp").getSize().y / 2.f));
	bar.setFillColor(sf::Color(130, 130, 250));
}
void mpBar::draw(sf::RenderWindow& win) {
	win.draw(bar);
}
void mpBar::position(const sf::Vector2f& hpmpP) {
	bar.setPosition(hpmpP.x, hpmpP.y + bar.getSize().y);
}

//expBar
expBar::expBar(sf::RenderWindow& win, resourceManager& res) :
	MaxExp(0), exp(0)
{
	//expbar
	expbar.setTexture(res.getTexture("expbar"));
	
	//greenBar
	greenBar.setSize(sf::Vector2f(
		256.f, //static_cast<float>(res.getTexture("expbar").getSize().x) 까지
		static_cast<float>(res.getTexture("expbar").getSize().y)));
	greenBar.setFillColor(sf::Color(91, 180, 102));

	//position
	position(win);
}
void expBar::draw(sf::RenderWindow& win) {
	win.draw(greenBar);
	win.draw(expbar);
}
void expBar::position(sf::RenderWindow& win) {
	expbar.setPosition(0,1440.f - expbar.getTexture()->getSize().y);
	greenBar.setPosition(expbar.getPosition());
	
}
const sf::Vector2f& expBar::getPosition() {
	return expbar.getPosition();
}

//character 공용
void character::position(sf::RenderWindow& win) {
	characterImg.setPosition(win.getSize().x / 5.f, win.getSize().y / 2.f);
}
const sf::Vector2f& character::getPosition(){
	return characterImg.getPosition();
}

//tiferet
tiferetImg::tiferetImg(sf::RenderWindow& win, resourceManager& res)
{
	frameWidth = res.getTexture("tiferet").getSize().x;
	frameHeight = res.getTexture("tiferet").getSize().y;
	characterImg.setTexture(res.getTexture("tiferetSprite"));
	characterImg.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	position(win);
}
void tiferetImg::draw(sf::RenderWindow& win) {
	win.draw(characterImg);
}
void tiferetImg::updateFrame(float& dt) { //장면 변화
	elapsed += dt;
	if (elapsed >= frameDuration) { //elapsed가 0.15f 보다 커지면 초기화 시키고 장면 변화
		elapsed = 0.f;
		currentFrame++;
		int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
		if (currentFrame >= framesPerAction)
			currentFrame = 0;

		characterImg.setTextureRect(
			sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight)
		);
	}
}

//homunculus 공용
void homunculus::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 7.f) , win.getSize().y / 2.f);
}
const sf::Vector2f& homunculus::getPosition() {
	return enemyImg.getPosition();
}

//normalOne
normalOne::normalOne(sf::RenderWindow& win, resourceManager& res)
{
	frameWidth = res.getTexture("normal1").getSize().x;
	frameHeight = res.getTexture("normal1").getSize().y;
	enemyImg.setTexture(res.getTexture("normal1Sprite"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	position(win);
}
void normalOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void normalOne::updateFrame(float& dt) {
	elapsed += dt;
	if (elapsed >= frameDuration) { //elapsed가 0.15f 보다 커지면 초기화 시키고 장면 변화
		elapsed = 0.f;
		currentFrame++;
		int framesPerAction = 2; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
		if (currentFrame >= framesPerAction)
			currentFrame = 0;

		enemyImg.setTextureRect(
			sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight)
		);
	}
}

//eliteOne
eliteOne::eliteOne(sf::RenderWindow& win, resourceManager& res)
{
	frameWidth = res.getTexture("elite1").getSize().x;
	frameHeight = res.getTexture("elite1").getSize().y;
	enemyImg.setTexture(res.getTexture("elite1"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	position(win);
}
void eliteOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void eliteOne::updateFrame(float& dt) {
	elapsed += dt;
	if (elapsed >= frameDuration) { //elapsed가 0.15f 보다 커지면 초기화 시키고 장면 변화
		elapsed = 0.f;
		currentFrame++;
		int framesPerAction = 1; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
		if (currentFrame >= framesPerAction)
			currentFrame = 0;

		enemyImg.setTextureRect(
			sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight)
		);
	}
}
void eliteOne::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 5.f), win.getSize().y / 1.4f);
}

//bossOne
bossOne::bossOne(sf::RenderWindow& win, resourceManager& res)
{
	frameWidth = res.getTexture("boss1").getSize().x;
	frameHeight = res.getTexture("boss1").getSize().y;
	enemyImg.setTexture(res.getTexture("boss1"));
	enemyImg.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	position(win);
}
void bossOne::draw(sf::RenderWindow& win) {
	win.draw(enemyImg);
}
void bossOne::updateFrame(float& dt) {
	elapsed += dt;
	if (elapsed >= frameDuration) { //elapsed가 0.15f 보다 커지면 초기화 시키고 장면 변화
		elapsed = 0.f;
		currentFrame++;
		int framesPerAction = 1; // 마지막 액션 + 1이 몇인지. 장면변화 index를 제일 처음으로 초기화
		if (currentFrame >= framesPerAction)
			currentFrame = 0;

		enemyImg.setTextureRect(
			sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight)
		);
	}
}
void bossOne::position(sf::RenderWindow& win) {
	enemyImg.setPosition(win.getSize().x - (win.getSize().x / 7.f), win.getSize().y / 2.5f);
}
