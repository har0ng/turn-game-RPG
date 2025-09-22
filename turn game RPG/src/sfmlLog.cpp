//sfmlLog.cpp

#include "sfmlLog.h"
#include "scene.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

sfmlLog::sfmlLog(sf::RenderWindow& win, float x, float y, unsigned int Size)
				:window(win),startX(x),startY(y),charSize(Size)	
{
	try {
		if (!normalFont.loadFromFile("assets/fonts/smartfont.otf")) {
			throw std::runtime_error("Font load failed"); //생성자에 만듦으로써 예외처리
		}
		if (!fantasyFont.loadFromFile("assets/fonts/Nosutaru-dotMPlusH-10-Regular.ttf")) {
			throw std::runtime_error("Font load failed"); //생성자에 만듦으로써 예외처리
		}
	}
	catch (const std::runtime_error& err) {
		cout << "フォントエーラー" << err.what() << endl;
	}
}

sf::Text sfmlLog::title(const std::string& title, sf::Sprite sprite) {
	// 중앙 정렬된 텍스트
	sf::Text text;
	text.setFont(fantasyFont);
	text.setString(title);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);

	// 배경(sprite)을 기준으로 중앙 정렬
	sf::FloatRect bgBounds = sprite.getGlobalBounds();
	sf::FloatRect txtBounds = text.getLocalBounds();

	text.setPosition(
		bgBounds.left + (bgBounds.width - txtBounds.width) / 2.f,
		bgBounds.top + 250.f - txtBounds.top  // 원하는 y 위치 조절
	);
	return text;
}

sf::Text sfmlLog::tiferetDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds){
	// 중앙 정렬된 텍스트
	sf::Text text;
	text.setString(description);
	text.setFont(normalFont);
	text.setCharacterSize(26);
	text.setFillColor(sf::Color::White);

	// 배경(sprite)을 기준으로 중앙 정렬
	sf::FloatRect btnBounds = BtnGlobalBounds;
	sf::FloatRect txtBounds = text.getLocalBounds();

	text.setPosition(
		btnBounds.left + (btnBounds.width - txtBounds.width) / 2.f,
		btnBounds.top + 200.f - txtBounds.top  // 원하는 y 위치 조절
	);
	return text;
}

sf::Text sfmlLog::malkuthDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds){
	// 중앙 정렬된 텍스트
	sf::Text text;
	text.setString(description);
	text.setFont(normalFont);
	text.setCharacterSize(26);
	text.setFillColor(sf::Color::White);

	// 배경(sprite)을 기준으로 중앙 정렬
	sf::FloatRect btnBounds = BtnGlobalBounds;
	sf::FloatRect txtBounds = text.getLocalBounds();

	text.setPosition(
		btnBounds.left + (btnBounds.width - txtBounds.width) / 2.f,
		btnBounds.top + 200.f - txtBounds.top  // 원하는 y 위치 조절
	);
	return text;
}

void sfmlLog::addlog(const std::string& log, sf::Color color) {
	sf::Text text(log, normalFont, 30); //로그, 폰트, 크기
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

