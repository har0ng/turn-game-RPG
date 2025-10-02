//sfmlUI.h
#pragma once
#include "resourceManager.h"
#include "map.h"

#include <SFML/Graphics.hpp>

//UI는 화면에서 나오는 기능들을 부품화시켜 따로 분류해놓는 곳임
//버튼, 체력창, 체력바, 옵션버튼, 마우스 생김새 등등 따로 분류

class title {
private:
	sf::Text text;
	float alpha = 255.0f;
	bool fading = false;
	bool appear = false;
	sf::Clock clock;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	title(const std::string& title, sf::Font& font);

	void draw(sf::RenderWindow& win);
	void startFade();
	void updateFade();
	void startAppear();
	void updateAppear();
	bool getAppear();
};

class button {
protected:
	sf::Text text; //button text
	sf::RectangleShape background; //버튼 배경화
	float alpha = 255.0f;   // 현재 알파값
	bool appear = false;	// 불러낼지 상태 여부
	bool fading = false;    // 페이드인 상태 여부
	sf::Clock clock;        // 버튼마다 시간 관리

public:
	button() = default;
	virtual ~button() = default;
	//virtual
	virtual void draw(sf::RenderWindow& win) = 0; // 가상
	virtual bool isClicked(sf::Vector2f mousePos) = 0;//가상
	virtual void outlineColormanager(sf::Vector2f mousePos) = 0; //가상
	
	//공용
	void startFade(); // 페이드 시작 
	void updateFade(); // 페이드 계속 업데이트
	void startAppear(); // 불러내는 타이머 가동
	void updateAppear(); // 타이머 시간 계산

	//get
	bool getAppear();
	bool getFading(); //페이드 상태 알아보는 함수
	float getAlpha(); //페이딩이 됐는지 확인 위함
	sf::FloatRect getBackgroundGlobalBounds() const; //배경 크기를 알기 위함
	//set
	void setOutlineColor(sf::Color color);
};

class menuButton : public button { //부품 - 버튼
public:
	menuButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class classSelectButton : public button { //부품 - 버튼
public:
	classSelectButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class backButton : public button { //부품 - 버튼
public:
	backButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class assortMapSelectButton : public button {
private:
	sf::Sprite button;
	sf::FloatRect bounds;
	sf::Texture& rest;
	sf::Texture& enemy;
	sf::Texture& boss;
	room roomInformation;
public:
	assortMapSelectButton(room roomInfo,resourceManager& res);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f mousePos) override; //버튼 호버시 아웃라인 색 변경
	void spriteScaleManager(const sf::Vector2f& mousePos);
	void setPosition(sf::Vector2f pos); //맵 하나하나 위치
	sf::Vector2f getPosition();
	sf::Sprite getButton();
	room getRoomInformation();
};

class assortMapLine { //세부층과 세부층을 잇는 라인
private:
	sf::RectangleShape thickLine; // 선으로써 직사각형 사용
	std::vector<std::vector<assortMapSelectButton>>& assortBtns;
public:
	assortMapLine(std::vector<std::vector<assortMapSelectButton>>& assortBtns);
	void draw(sf::RenderWindow& win);
	void setFillColor(sf::Vector2f& mousePos);
	void setAssortBtns(const std::vector<std::vector<assortMapSelectButton>>& srcBtns);
};

class mouse { //마우스
private:
	sf::Sprite sprite;
	bool visible = false; //마우스 스프라이트 감출지 안감출지
public:
	mouse(sf::RenderWindow& win, sf::Texture& tex);
	float getSizeX();
	float getSizeY();
	bool getVisible();
	void draw(sf::RenderWindow& window);
	void position(sf::Vector2f worldPos);
	void updatePositionFromWindow(sf::RenderWindow& window); //
	void mapSceneVisible();//전체 맵땐 마우스 안보이게
	void mapSceneUnvisible(); //세부 맵일땐 마우스 보이게
};