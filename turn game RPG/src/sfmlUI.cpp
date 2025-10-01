//sfmlUI.cpp

#include "sfmlUI.h"

#include <iostream>

using std::cout;
using std::endl;

//text 중앙 잡기 : x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
//y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top

//title
title::title(const std::string& title, sf::Font& font)
{
	if (!texture.loadFromFile("assets/images/1.png")) { //이니셜라이저로 초기화 불가능이라 여기서 넣어 초기화
		throw std::runtime_error("image load failed");
	}
	sprite.setTexture(texture); // 텍스처를 스프라이트에 연결
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
bool menuButton::isClicked(sf::Vector2f mousePos){ //마우스 위치를 알려주는 int 형의 x,y
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}
void menuButton::outlineColormanager(sf::Vector2f mousePos){
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
bool classSelectButton::isClicked(sf::Vector2f mousePos){
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false; 
}
void classSelectButton::outlineColormanager(sf::Vector2f mousePos){
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
bool backButton::isClicked(sf::Vector2f mousePos) {
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}
void backButton::outlineColormanager(sf::Vector2f mousePos){
	if (background.getGlobalBounds().contains(mousePos)) {
		sf::Color color(224, 224, 224);
		background.setOutlineColor(color); //버튼 컬러
	}
	else {
		sf::Color outline(51, 0, 0, 155);
		background.setOutlineColor(outline);//버튼 컬러
	}
}

//assortMapSelectButton(미완성)
assortMapSelectButton::assortMapSelectButton(room roomInfo, resourceManager& res) :
	rest(res.getTexture("heal")),
	enemy(res.getTexture("enemy")), 
	boss(res.getTexture("boss")),
	roomInformation(roomInfo)

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
}
void assortMapSelectButton::draw(sf::RenderWindow& win){
	win.draw(button);
}
bool assortMapSelectButton::isClicked(sf::Vector2f mousePos){
	return false;
}
void assortMapSelectButton::outlineColormanager(sf::Vector2f mousePos) {
	return;
}
void assortMapSelectButton::spriteScaleManager(sf::Vector2f mousePos){
	bounds = button.getLocalBounds();
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
void assortMapSelectButton::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}
sf::Vector2f assortMapSelectButton::getPosition() {
	return button.getPosition();
}
sf::Sprite assortMapSelectButton::getButton() {
	return button;
}
room assortMapSelectButton::getRoomInformation() {
	return roomInformation;
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