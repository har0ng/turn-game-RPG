//mainManager.h
#pragma once
#include "battle.h"
#include "sfmlUI.h"
#include "sfmlLog.h"
#include "scene.h"
#include "resourceManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

class init {
private:
	std::unique_ptr<scene> currentScene;
	// 씬 히스토리 스택
	std::vector<std::unique_ptr<scene>> history;
	enum class game {
		playing, // 플레이 중
		gameover, // 게임오버
	}GAME{ game::playing };
	bool deleter{ false };
	bool exit{ false };
public:
	init() = default;
	void restart();
	void setDeleter();
	void run();
};