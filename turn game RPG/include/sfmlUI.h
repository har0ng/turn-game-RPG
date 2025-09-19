//sfmlUI.h
#pragma once

#include <SFML/Graphics.hpp>

//UI는 화면에서 나오는 기능들을 부품화시켜 따로 분류해놓는 곳임
//버튼, 체력창, 체력바, 옵션버튼, 마우스 생김새 등등 따로 분류

class button { //부품 - 버튼
private:
	sf::Text text; //button text
	sf::RectangleShape background; //버튼 배경화면

public:
	button(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win); // 모든 로그 화면에 그리기
	bool isClicked(sf::Vector2i mousePos);//클릭 이벤트
};