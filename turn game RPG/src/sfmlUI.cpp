//sfmlUI.cpp

#include "sfmlUI.h"

#include <iostream>

using std::cout;
using std::endl;

button::button(const std::string& label, float x, float y, sf::Font& font)
	:text(label, font, 60)
{
	// 버튼 크기는 텍스트 크기 + 여백
	sf::FloatRect bounds = text.getLocalBounds();//멤버 변수 text의 경계 혹은 테두리 저장 
	background.setSize(sf::Vector2f(bounds.width + 80, bounds.height + 20));//버튼 배경 사이즈를 text에 맞춰 조절

	// 위치 설정
	background.setPosition(x, y); // 버튼 배경 위치를 먼저 조절, 배경 먼저 해야 글자가 아래로 안감
	text.setPosition(x + 30, y - 10); //이후에 배경에 맞춰 위치를 조절 
}
//button
void button::draw(sf::RenderWindow& win){ //화면에 그리기
	sf::Color black(0, 0, 0, 0);
	background.setFillColor(black); //내부 색
	background.setOutlineColor(sf::Color::White); //테두리 색
	background.setOutlineThickness(2.f); //테두리 두께

	win.draw(background); //버튼 배경 그리기, 무조건 순서 생각해서 draw하기
	win.draw(text); //텍스트 그리기
}
bool button::isClicked(sf::Vector2i mousePos){ //마우스 위치를 알려주는 int 형의 x,y
	sf::FloatRect bound = background.getGlobalBounds();//버튼 배경의 전체를 기준으로 잡아버림
	if (bound.contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
		//버튼 배경 전체가 기준이니 버튼배경 안에서 마우스의 움직임이나 이벤트를 인정해준다는 의미
		return true; //버튼 배경안에 마우스 좌표가 있으면 true
	}
	return false;
}

