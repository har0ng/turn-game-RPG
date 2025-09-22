//sfmlUI.cpp

#include "sfmlUI.h"

#include <iostream>

using std::cout;
using std::endl;

//text 중앙 잡기 : x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
//y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top

//공용
sf::FloatRect button::getBackgroundGlobalBounds() const{
	return background.getGlobalBounds();
}
void button::startFade() { //장면 전환 시작
	fading = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void button::updateFade() { //프레임 매초 갱신
	if (fading == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 255 - (elapsed / 3.0f) * 255; // 3초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
	}
	text.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));
}


//menuButton
menuButton::menuButton(const std::string& label, float x, float y, sf::Font& font)
{
	text.setString(label); // 글자
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(70); // 글자크기
	sf::Color color(64, 64, 64);
	text.setOutlineThickness(2.f);
	text.setOutlineColor(color);
	
	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절

	// 위치 설정
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
bool menuButton::isClicked(sf::Vector2i mousePos){ //마우스 위치를 알려주는 int 형의 x,y
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}

//classSelectButton
classSelectButton::classSelectButton(const std::string& label, float x, float y, sf::Font& font) 
{	
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
	sf::Color color(0, 0, 51, 155);
	background.setFillColor(color); //내부 색
	background.setOutlineColor(sf::Color::White); //테두리 색
	background.setOutlineThickness(3.f); //테두리 두께

	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool classSelectButton::isClicked(sf::Vector2i mousePos){
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}

//backButton
backButton::backButton(const std::string& label, float x, float y, sf::Font& font){
	text.setString(label); // 글자
	text.setFont(font); // 글자 폰트
	text.setCharacterSize(30); // 글자크기
	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절

	// 위치 설정
	background.setPosition(x, y); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	text.setPosition(x + (background.getSize().x - text.getLocalBounds().width) / 2.f,
		y + (background.getSize().y - text.getLocalBounds().height) / 2.f - text.getLocalBounds().top); //이후에 배경에 맞춰 위치를 조절 

}
void backButton::draw(sf::RenderWindow& win) {
	sf::Color color(204, 0, 0, 200);
	sf::Color outline(51, 0, 0, 155);
	background.setFillColor(color); //내부 색
	background.setOutlineColor(outline); //테두리 색
	background.setOutlineThickness(2.0f); //테두리 두께

	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool backButton::isClicked(sf::Vector2i mousePos) {
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}

//assortMapSelectButton(미완성)
assortMapSelectButton::assortMapSelectButton(sf::Texture texture, float x, float y) {
	//texture.loadFromFile();
	sf::Sprite sprite;
	sprite.setTexture(texture);
}
void assortMapSelectButton::draw(sf::RenderWindow& win){

}
bool assortMapSelectButton::isClicked(sf::Vector2i mousePos){
	return false;
}
