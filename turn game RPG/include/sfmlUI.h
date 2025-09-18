//sfmlUI.h
#pragma once

#include <SFML/Graphics.hpp>

class button {
private:
	sf::Text text; //button text
	sf::RectangleShape background; //배경화면

public:
	button(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win); // 모든 로그 화면에 그리기
	bool isClicked(sf::Vector2i mousePos);//클릭 이벤트
};