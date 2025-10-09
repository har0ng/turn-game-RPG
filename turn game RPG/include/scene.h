//scene.h
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>

#include "map.h"
#include "sfmlLog.h"
#include "sfmlUI.h"
#include "resourceManager.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"

class scene {
protected:
	bool finished{ false }; //씬이 끝났는지 여부
	bool finishedManager{ false };
	bool back{ false };
	bool transition{ false }; //씬 바뀌고 있는데 클릭 금지
	float alpha{ 255.0f };   // 현재 알파값
	bool appear{ false };	// 불러낼지 상태 여부
	bool fading{ false };    // 페이드인 상태 여부
	sf::Clock clock;        // 버튼마다 시간 관리
	float deltaTime{ 0.f }; //딜레이 계산
	float mainViewX{ 0.f }; //마우스를 위한 메인 화면 기준 x
	float mainViewY{ 0.f }; //마우스를 위한 메인 화면 기준 y
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

	//씬이 끝났는지 여부 , main에서 유니크 포인터 옮길 때 조건식으로 쓰임
	virtual bool isFinished() { return finished; }

	//뒤로 돌아가기
	virtual bool isBack() { return back; }

	//공용
	void isTransition(); //씬 바뀌고 있는데 클릭 금지
	virtual void startFade(); // 페이드 시작 
	virtual void updateFade(sf::Sprite& sprite); // 페이드 계속 업데이트
	virtual void startAppear(); // 불러내는 타이머 가동
	virtual void updateAppear(sf::Sprite& sprite); // 타이머 시간 계산
	virtual void setFinishBackDefault(); //finish랑 Back을 false로 되돌리기
	virtual void allStartAppear(); // back으로 돌아가서도 천천히 나오는 듯한 이미지는 남아있어야 했기에 만들어냄
};

class menuScene : public scene { //초기 화면
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	menuButton startBtn; //버튼 이라는 부품 들고옴
	menuButton endBtn; //이하동문
	title titleText; //타이틀
	
public:
	menuScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex); //빈 도화지와 폰트를 받아와야함
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
	void setMainView(); //마우스의 스프라이트 크기 유지를 위함
	void allStartAppear() override;
};

class classSelectScene : public scene {// 직업 선택
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Sprite sprite;   // 이미지를 표시할 스프라이트
	tiferetDescription tiferetDc; // tiferet직업 설명
	malkuthDescription malkuthDc; // malkuth직업 설명
	classSelectButton tiferetBtn; // 티페리트 버튼
	classSelectButton malkuthBtn; // 말쿠트(아도나이) 버튼
	backButton backBtn; // 뒤로가기 버튼
	bool selectBtn; //back 눌렸는지 직업 눌렸는지 확인

public:
	classSelectScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex);//빈 도화지와 폰트
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
	void allStartAppear() override;
};

class mapScene : public scene { //전체 맵 보여주기
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Sprite background;   // 이미지를 표시할 스프라이트
	sfmlLog log; // 필요할수도 있으니.
	float elapsed{ 0.f };
	
public:
	mapScene(sf::RenderWindow& win, sf::Font& font, sf::Texture& tex);
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
	void updateFade(sf::Sprite& sprite) override;
	void updateAppear(sf::Sprite& sprite) override;
	void allStartAppear() override;

};

class floorScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Sprite background; // 이미지를 표시할 스프라이트
	sf::View view;
	sfmlLog log; // 필요할수도 있으니.
	mapRoom map; //맵 정보를 만들 리소스 미리 불러오기
	assortMapLine line;
	std::vector < assortMapSelectButton > assortBtn; // 세부 층 버튼
	std::vector<std::vector<assortMapSelectButton>> assortBtns;  //세부층 버튼들의 집합 나누기
	int firstAssortMapCnt;//층별 처음 만들어지는 맵 개수, 이후 맵 개수
	int floorCnt{ 1 };// 몇층인지 세기 위함, default == 1
	floorTitle floorName;
	float scrollSpeed{ 90.f }; //스크롤 +1-1에 얼마나 움직이는지
	float elapsed{ 0.f }; // 화면 스크롤 애니메이션을 위함
	bool animationYN{ false };
	int assortBtnRow{ 0 }; //몇번째 세부층인지
	int assortBtnCol{ 0 }; // index라 0부터,현재 플레이어의 세부층 1-playerPos , 2-playerPos etc.
	std::vector<std::pair<int,int>> visitedRoom; //방문한 방 모음
	std::vector<int> connectedRoom; // 갈수 있는 방 모음
public:
	floorScene(sf::RenderWindow& win, resourceManager& res);
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
	void imageDraw(float bgWidth, float bgHeight); //이미지 그리기
	void pushAssortMap(int assortMapCnt, resourceManager& res);
	void animation(sf::Vector2f& center, float& elapsed);
	void updateAppear(sf::Sprite& sprite) override;
	void allStartAppear() override;

	//get
	std::vector<std::vector<assortMapSelectButton>>& getAssortBtns(); //line 갱신 목적
	
	//set
	void setFirstAssortMapCnt(int &floor); //첫번째 만들어질 맵 개수 저장시키기
	void setLine(std::vector<std::vector<assortMapSelectButton>>& assortBtns); //line 갱신 목적
	
	
};

class battleScene : public scene {
private:
	sf::RenderWindow& window; // 빈 도화지 받아오기
	sf::Sprite background;   // 배경화면
	sf::View view;
	sfmlLog log; // 싸울땐 로그 필수
	//battleButton attackBtn; //버튼 이라는 부품 들고옴
	//battleButton defenseBtn; //이하동문
	//battleButton skillBtn;
	// 이하 세부 스킬 버튼 만들어야함
	backButton backBtn; // 뒤로가기 버튼로 되어있는데 이름만 바꿔서 배틀 끝나고 돌아가는 버튼으로 하나 만들어 쓰기.
	status statusFrame; //왼쪽위 체력, 마나, 경험치,레벨의 틀
	//hpBar hpB; //struct 할까말까하다가 다 따로 구분
	//mpBar mpB;
	//expBar expB;
	tiferetImg eloaImg;
public:
	battleScene(sf::RenderWindow& win, resourceManager& res);
	void update(sf::RenderWindow& window) override; //메뉴 화면으로 상태갱신
	void render(sf::RenderWindow& window) override; //화면 사용자에게 보이게 하기
	void allStartAppear() override;

};

