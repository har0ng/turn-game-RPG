//sfmlLog.h
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
class sfmlLog {
protected:
	sf::Text log;
	sf::RenderWindow& window; //창
	sf::Font normalFont; // 폰트 1
	sf::Font fantasyFont;
	sf::Clock clock;
//	std::vector <sf::Text> logLines; //로그 담는 배열
	float alpha = 0.0f;
	unsigned int charSize = 20; //글자 크기
	bool fading = false;
	bool appear = false;
public:
	sfmlLog(sf::RenderWindow& win);
	virtual ~sfmlLog() = default;
	//void addlog(const std::wstring& log, sf::Color color = sf::Color::White); //로그 추가
	//virtual
	virtual void draw(sf::RenderWindow& win); // 모든 로그 화면에 그리기
	virtual void clear(); //화면 내 모든 로그 삭제
	//공용
	void startFade();
	void updateFade();
	void startAppear();
	void updateAppear();
};


class tiferetDescription : public sfmlLog {
public:
	tiferetDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds, sf::RenderWindow& win);
	
	void draw(sf::RenderWindow& win) override;
	void clear() override; // 필요없는데 가상함수라 return으로 넘김
};

class malkuthDescription : public sfmlLog {
public:
	malkuthDescription(const std::wstring& description, sf::FloatRect BtnGlobalBounds, sf::RenderWindow& win);
	
	void draw(sf::RenderWindow& win) override;
	void clear() override; // 필요없는데 가상함수라 return으로 넘김
};
