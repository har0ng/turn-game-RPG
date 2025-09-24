//sfmlLog.cpp

#include "sfmlLog.h"
#include "scene.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

sfmlLog::sfmlLog(sf::RenderWindow& win):window(win)
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

//공용

//void sfmlLog::addlog(const std::wstring& log, sf::Color color) {
//	sf::Text text(log, normalFont, 30); //로그, 폰트, 크기
//	text.setFillColor(color); //글자 컬러
//
//	float offsetX = 50.0f;
//	float offsetY = 780.0f;
//	text.setPosition(offsetX, offsetY + (charSize * logLines.size()));
//	logLines.push_back(text);
//}
void sfmlLog::draw(sf::RenderWindow & win) {
	return;
}
void sfmlLog::clear() {
	return;
}
void sfmlLog::startFade() {
	fading = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void sfmlLog::updateFade() {
	sf::Color textColor = log.getFillColor();
	if (fading == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 255 - (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 감소
	if (alpha < 0) {
		alpha = 0;
		fading = false; // 완료되면 멈춤
	}
	textColor.a = static_cast<sf::Uint8>(alpha);
	log.setFillColor(textColor); // 다시 적용
}
void sfmlLog::startAppear() {
	appear = true;
	clock.restart();// 0초로 초기화 하고 다시 경과 시간 반환
}
void sfmlLog::updateAppear() {
	sf::Color textColor = log.getFillColor();
	if (appear == false) {
		return;
	}
	float elapsed = clock.getElapsedTime().asSeconds();
	alpha = 0 + (elapsed / 0.5f) * 255; // 0.5초에 걸쳐 증가
	if (alpha > 255) {
		alpha = 255;
		appear = false; // 완료되면 멈춤
	}
	textColor.a = static_cast<sf::Uint8>(alpha);
	log.setFillColor(textColor); // 다시 적용
}


//tiferet
tiferetDescription::tiferetDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds, sf::RenderWindow& win)
	:sfmlLog(win)
{
	// 중앙 정렬된 텍스트
	log.setString(description);
	log.setFont(normalFont);
	log.setCharacterSize(26);
	log.setFillColor(sf::Color(255, 255, 255, 0)); // 처음엔 투명

	// 텍스트 크기와 오프셋 가져오기
	sf::FloatRect btnBounds = BtnGlobalBounds;
	sf::FloatRect txtBounds = log.getLocalBounds(); // 로그 텍스트 로컬 바운드
	log.setPosition(txtBounds.left+275, txtBounds.top+300); //원래 숫자로 하면 안됨
}
void tiferetDescription::draw(sf::RenderWindow& win) {
	win.draw(log);
}
void tiferetDescription::clear() {
	return;
}
//malkuth
malkuthDescription::malkuthDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds, sf::RenderWindow& win)
	:sfmlLog(win)
{
	// 중앙 정렬된 텍스트
	log.setString(description);
	log.setFont(normalFont);
	log.setCharacterSize(26);
	sf::Color color(255, 255, 255, 0);
	log.setFillColor(color);
	// 배경(sprite)을 기준으로 중앙 정렬
	sf::FloatRect btnBounds = BtnGlobalBounds;
	sf::FloatRect txtBounds = log.getLocalBounds();

	log.setPosition(txtBounds.left + 870, txtBounds.top + 300); //원래 숫자로 하면 안됨
}
void malkuthDescription::draw(sf::RenderWindow& win) {
	win.draw(log);
}
void malkuthDescription::clear() {
	return;
}

