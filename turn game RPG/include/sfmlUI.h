//sfmlUI.h
#pragma once

#include <SFML/Graphics.hpp>

//UI는 화면에서 나오는 기능들을 부품화시켜 따로 분류해놓는 곳임
//버튼, 체력창, 체력바, 옵션버튼, 마우스 생김새 등등 따로 분류

class button {
protected:
	sf::Text text; //button text
	sf::RectangleShape background; //버튼 배경화
	float alpha = 255.0f;   // 현재 알파값
	bool fading = false;    // 페이드인 상태 여부
	sf::Clock clock;        // 버튼마다 시간 관리

public:
	button() = default;

	virtual ~button() = default;
	virtual void draw(sf::RenderWindow& win) = 0; // 가상
	virtual bool isClicked(sf::Vector2i mousePos) = 0;//가상
	
	void startFade(); // 페이드 시작 
	void updateFade(); // 페이드 계속 업데이트
	sf::FloatRect getBackgroundGlobalBounds() const;
	
};

class menuButton : public button { //부품 - 버튼
public:
	menuButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2i mousePos) override;//클릭 이벤트
	

};

class classSelectButton : public button { //부품 - 버튼
public:
	classSelectButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2i mousePos) override;//클릭 이벤트

};

class backButton : public button { //부품 - 버튼
public:
	backButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2i mousePos) override;//클릭 이벤트

};

class assortMapSelectButton : public button {
public:
	assortMapSelectButton(sf::Texture texture, float x, float y);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2i mousePos) override;//클릭 이벤트
};