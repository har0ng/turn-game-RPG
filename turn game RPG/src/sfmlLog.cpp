//sfmlLog.cpp

#include "sfmlLog.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

sfmlLog::sfmlLog(sf::RenderWindow& win, float x, float y, unsigned int Size)
				:window(win),startX(x),startY(y),charSize(Size)	
{
	try {
		if (!font.loadFromFile("assets/fonts/smartfont.otf")) {
			throw std::runtime_error("Font load failed"); //생성자에 만듦으로써 예외처리
		}
	}
	catch (const std::runtime_error& err) {
		cout << "フォントエーラー" << err.what() << endl;
	}
}

void sfmlLog::title(const std::string& title, float x, float y) {
	sf::Text text(title, font, 100); //로그, 폰트, 사이즈
	text.setFillColor(sf::Color::White); //글자 컬러

	text.setPosition(x, y);
	window.draw(text);
}

void sfmlLog::addlog(const std::string& log, sf::Color color) {
	sf::Text text(log, font, 30); //로그, 폰트, 크기
	text.setFillColor(color); //글자 컬러

	float offsetX = 50.0f;
	float offsetY = 780.0f;
	text.setPosition(offsetX, offsetY + (charSize * logLines.size()));
	logLines.push_back(text);
}

void sfmlLog::draw() {
	for (auto& line : logLines)
		window.draw(line);
}

void sfmlLog::clear() {
	logLines.clear();
}

