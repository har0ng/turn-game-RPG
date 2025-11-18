#pragma once
//debuggingLog.h
#pragma once

#include <fstream>
#include <iomanip>
#include <chrono>

class hpDebug {
public:
	hpDebug() = default;
	static void enemyLog(float deltaTime, float oldWidth, float newWidth, bool triggered);
	static void playerLog(float deltaTime, float oldWidth, float newWidth, bool triggered);
	static void initLogFiles();
};