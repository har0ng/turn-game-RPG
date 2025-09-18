//sfmlUI.cpp

#include "sfmlUI.h"

#include <iostream>

using std::cout;
using std::endl;

button::button(const std::string& label, float x, float y, sf::Font& font)
	:text(label, font, 40)
{
	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();
	background.setSize(sf::Vector2f(bounds.width + 40, bounds.height + 20));

	// 위치 설정
	//텍스트 위치로 버튼 배경 놓기임(텍스트 정렬)
	background.setPosition(x, y);
	text.setPosition(x + 20, y);
}
//button
void button::draw(sf::RenderWindow& win){
	background.setFillColor(sf::Color::Black); //내부 색
	background.setOutlineColor(sf::Color::White); //테두리 색
	background.setOutlineThickness(2.f); //테두리 두께

	win.draw(background);
	win.draw(text);
}
bool button::isClicked(sf::Vector2i mousePos){ //마우스 위치를 알려주는 int 형의 x,y
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경 좌표 및 가로 세로 크기
	if (bound.contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
		return true; //버튼 배경 좌표에 걸맞는 가로세로 크기에 마우스 좌표가 있으면 true
	}
	return false;
}

