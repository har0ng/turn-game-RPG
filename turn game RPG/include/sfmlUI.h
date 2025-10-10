//sfmlUI.h
#pragma once
#include "resourceManager.h"
#include "map.h"
#include "player.h"
#include <SFML/Graphics.hpp>

//UI는 화면에서 나오는 기능들을 부품화시켜 따로 분류해놓는 곳임
//버튼, 체력창, 체력바, 옵션버튼, 마우스 생김새 등등 따로 분류

class title {
private:
	sf::Text text;
	float alpha{ 255.0f };
	bool fading{ false };
	bool appear{ false };
	sf::Clock clock;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	title(const std::string& title, sf::Font& font, sf::Texture& tex);

	void draw(sf::RenderWindow& win);
	void startFade();
	void updateFade();
	void startAppear();
	void updateAppear();
	bool getAppear();
	bool getFading();
	float getAlpha();
};

class floorTitle{
private:
	sf::Text text;
	float alpha{ 255.0f };
	bool fading{ false };
	bool appear{ false };
	sf::Clock clock;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	floorTitle(const std::wstring& title, sf::Font& font, sf::View& view, const int& floor);
	void draw(sf::RenderWindow& win);
	void startFade();
	void updateFade();
	void startAppear();
	void updateAppear();
	bool getAppear();
	void setTitle(const int& floor, const std::wstring& title);
	void setView(sf::View& view);
};

class button {
protected:
	sf::Text text; //button text
	sf::RectangleShape background; //버튼 배경화
	float alpha{ 255.0f };   // 현재 알파값
	bool appear{ false };	// 불러낼지 상태 여부
	bool fading{ false };    // 페이드인 상태 여부
	sf::Clock clock;        // 버튼마다 시간 관리

public:
	button() = default;
	virtual ~button() = default;
	//virtual
	virtual void draw(sf::RenderWindow& win) = 0; // 가상
	virtual bool isClicked(sf::Vector2f& mousePos) = 0;//가상
	virtual void outlineColormanager(sf::Vector2f& mousePos) = 0; //가상
	
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
	bool isClicked(sf::Vector2f& mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f& mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class classSelectButton : public button { //부품 - 버튼
public:
	classSelectButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f& mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f& mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class backButton : public button { //부품 - 버튼
public:
	backButton(const std::string& label, float x, float y, sf::Font& font);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f& mousePos) override;//클릭 이벤트
	void outlineColormanager(sf::Vector2f& mousePos) override; //버튼 호버시 아웃라인 색 변경
};

class assortMapSelectButton : public button {
private:
	sf::Sprite button;
	sf::FloatRect bounds;
	sf::Texture& rest;
	sf::Texture& enemy;
	sf::Texture& boss;
	room roomInformation;
	struct index {
		int row; //가로 인덱스로 구분해서 방 정보를 찾기 위함 
		int col; //세로
	}indexPos;
public:
	assortMapSelectButton(room roomInfo,resourceManager& res, index indexPos);
	void draw(sf::RenderWindow& win) override; // 모든버튼 그리기
	bool isClicked(sf::Vector2f& mousePos) override;//이 클래스에서 못씀으로 버려지는 함수
	bool isClickedExtra(sf::Vector2f& mousePos, std::vector<int>& connectedRoom);
	void outlineColormanager(sf::Vector2f& mousePos) override; //버튼 호버시 아웃라인 색 변경
	void spriteScaleManager(const sf::Vector2f& mousePos, const std::vector<std::pair<int, int>>& visitedRoom);
	void startAppear();
	void updateAppear(std::vector<std::pair<int, int>>& visitedRoom);
	
	//set
	void setPosition(sf::Vector2f pos); //맵 하나하나 위치

	//get
	sf::Vector2f getPosition();
	sf::Sprite& getButton(); // 버튼 정보
	const room& getRoomInformation() const; //struct room의 정보 불러오기
	int getIndexRow() const;
	int getIndexCol() const;
};

class assortMapLine { //세부층과 세부층을 잇는 라인
private:
	struct lineInfo {
		size_t id;
		std::vector<sf::RectangleShape> thickLineClone;
		/*id 와 id에 종속된 thickLine을 vector 혹은 map에 넣어서
		button sprite에 마우스를 올렸을 떄 그 sprite의 id왜 해당되는
		id가 map 혹은 vector에 있다면 거기에 종속된 thickLine을 모두 색 변환.
		*/
	};
	sf::RectangleShape thickLine; // 선으로써 직사각형 사용
	std::map<size_t, lineInfo> lineGroup; //아이디당 라인(선) 저장소
	std::vector<std::vector<assortMapSelectButton>> assortBtns;
	float alpha{ 255.0f };   // 현재 알파값
	bool appear{ false };	// 불러낼지 상태 여부
	bool fading{ false };    // 페이드인 상태 여부
	sf::Clock clock;        // 버튼마다 시간 관리
public:
	assortMapLine(std::vector<std::vector<assortMapSelectButton>>& assortBtns);
	void draw(sf::RenderWindow& win);
	void createLine();
	void startAppear();
	void updateAppear();
	void setFillColor(sf::Vector2f& mousePos, assortMapSelectButton& roomInfo); //선 색 바꾸기
	void setAssortBtns(const std::vector<std::vector<assortMapSelectButton>>& srcBtns); //버튼 초기화 할때 문제되서 우회 경로
};

class mouse { //마우스
private:
	sf::Sprite sprite;
	bool visible{ false }; //마우스 스프라이트 감출지 안감출지
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

class status { 
private:
	sf::Text level; //level text
	sf::RectangleShape background; //버튼 배경화
	sf::Sprite hpmp;
public:
	status(resourceManager& res);
	void draw(sf::RenderWindow& win);
	const sf::Vector2f& getHpmpPosition();
	void setPosition(const sf::Vector2f& characterP, const sf::Vector2f& expbarP, resourceManager& res);
	std::string getPlayerLevel(const int& level);
};

class hpBar {
private:
	sf::RectangleShape bar;
	int maxHp; //player에서 값 받아올것
	int hp;
public:
	hpBar(sf::RenderWindow& win, resourceManager& res);
	void draw(sf::RenderWindow& win);
	void position(const sf::Vector2f& hpmpP);
	void setBarValue(float barSizeX);
};

class mpBar {
private:
 sf::RectangleShape bar;
	int maxMp;
	int mp;
public:
	mpBar(sf::RenderWindow& win, resourceManager& res);
	void draw(sf::RenderWindow& win);
	void position(const sf::Vector2f& hpmpP);
};

class expBar{
private:
	sf::Sprite expbar;
	sf::RectangleShape greenBar;
	int MaxExp;
	int exp;
public:
	expBar(sf::RenderWindow& win, resourceManager& res);
	void draw(sf::RenderWindow& win);
	void position(sf::RenderWindow& win);
	const sf::Vector2f& getPosition();
};

class character {
protected:
	sf::Sprite characterImg;
public:
	character() = default;
	virtual ~character() = default;
	virtual void draw(sf::RenderWindow& win) = 0;
	virtual void position(sf::RenderWindow& win);
	const sf::Vector2f& getPosition();

};


class tiferetImg : public character{
public:
	tiferetImg(sf::RenderWindow& win, resourceManager& res);
	void draw(sf::RenderWindow& win) override;
	
};