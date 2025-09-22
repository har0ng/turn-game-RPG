//sfmlLog.h
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class sfmlLog {
private:
	sf::RenderWindow& window; //창
	sf::Font normalFont; // 폰트 1
	sf::Font fantasyFont;
	std::vector <sf::Text> logLines; //로그 담는 배열
	float startX; // 로그 창 위치
	float startY; //로그 창 위치
	unsigned int charSize; //글자 크기
public:
	sfmlLog(sf::RenderWindow& win, float x = 10, float y = 10, unsigned int charSize = 40);
	sf::Text title(const std::string& title, sf::Sprite sprite);
	sf::Text tiferetDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds);
	sf::Text malkuthDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds);
	void addlog(const std::string& log, sf::Color color = sf::Color::White); //로그 추가
	void draw(); // 모든 로그 화면에 그리기
	void clear(); //화면 내 모든 로그 삭제
};
