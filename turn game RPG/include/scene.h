//scene.h
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sfmlLog.h"
#include "sfmlUI.h"

class scene {
protected:
	bool finished = false;
	bool back = false;
public:
	virtual ~scene() = default;
	//입력(키보드/마우스/창 이벤트)을 처리.
	//virtual void handleEvent(sf::RenderWindow::Window& window,const sf::Event& event) = 0;// 순수 가상함수
	
	//상태 갱신
	//역할: 물리 / 타이머 / 애니메이션 / 게임 로직 갱신.
	//권장 : float dt(델타타임)를 받게 하자.프레임 독립성 위해 거의 필수.
	//주의점 : update() 안에서 heavy I/O(파일 로드 등)는 피하자 — 프레임 끊김 유발.
	virtual void update(sf::RenderWindow& window) = 0; // 순수 가상함수

	//프린팅
	//역할: 현재 씬을 화면에 그림(모든 draw 호출).
	/*권장: sf::RenderTarget& 나 sf::RenderWindow& 를 받음.sf::RenderTarget& 를
			쓰면 sf::RenderTexture에도 재사용 가능*/
	/*render()는 화면을 직접 수정(상태 변경) 하지 말고,
	그리기만 하도록 유지하는 게 좋음(디버깅 쉬움).*/
	virtual void render(sf::RenderWindow& window) = 0;// 순수 가상함수

	//씬이 끝났는지 여부
	virtual bool isFinished() { return finished; }

	//뒤로 돌아가기
	virtual bool isBack() { return back; }
};

class menuScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Texture texture; //이미지
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	sfmlLog log; // 빈 도화지가 없으면 로그를 못 뽑아냄(타이틀)
	menuButton startBtn; //버튼 이라는 부품 들고옴
	menuButton endBtn; //이하동문

public:
	menuScene(sf::RenderWindow& win, sf::Font& font); //빈 도화지와 폰트를 받아와야함
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
};

class classSelectScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Texture texture; //이미지
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	sfmlLog log; // 직업 설명
	classSelectButton tiferetBtn; // 티페리트 버튼
	classSelectButton malkuthBtn; // 말쿠트(아도나이) 버튼
	backButton backBtn; // 뒤로가기 버튼

public:
	classSelectScene(sf::RenderWindow& win, sf::Font& font);//빈 도화지와 폰트
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기

};

class mapScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Texture texture; //이미지
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	//mapButton selectFloorBtn; //세부 층 버튼


public:
};

class battleScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Texture texture; //이미지
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	sfmlLog log; // 빈 도화지가 없으면 로그를 못 뽑아냄
	//battleButton attackBtn; //버튼 이라는 부품 들고옴
	//battleButton defenseBtn; //이하동문
	//battleButton skillBtn;
	// 이하 세부 스킬 버튼 만들어야함

public:

};

