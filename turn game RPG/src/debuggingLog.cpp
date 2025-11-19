//debuggingLog.cpp

#pragma warning(push)
#pragma warning(disable : 26819)
#include "json.hpp"
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4251 26812 26819 4244 4267)
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#pragma warning(pop)

#include "debuggingLog.h"

void hpDebug::enemyLog(float deltaTime, float oldWidth, float newWidth, bool triggered) {
    std::ofstream logFile("C:\\Users\\3031435\\Desktop\\IT\\wbs\\C++\\turn game clone\\test\\hp_debug\\enemy_health_log.txt", std::ios::app);
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm_now;
    localtime_s(&tm_now, &now);  
    logFile << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S")
        << " deltaTime=" << deltaTime
        << " oldWidth=" << oldWidth
        << " newWidth=" << newWidth
        << " triggered=" << triggered
        << "\n";
}
void hpDebug::playerLog(float deltaTime, float oldWidth, float newWidth, bool triggered) { //std::ios::app은 파일에 정보를 누적시킴
    std::ofstream logFile("C:\\Users\\3031435\\Desktop\\IT\\wbs\\C++\\turn game clone\\test\\hp_debug\\player_health_log.txt", std::ios::app);
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm_now;
    localtime_s(&tm_now, &now);
    logFile << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S")
        << " deltaTime=" << deltaTime
        << " oldWidth=" << oldWidth
        << " newWidth=" << newWidth
        << " triggered=" << triggered
        << "\n";
}
void hpDebug::initLogFiles() { //std::ios::trunc는 파일을 초기화 시킴.
    std::ofstream enemyLog("C:\\Users\\3031435\\Desktop\\IT\\wbs\\C++\\turn game clone\\test\\hp_debug\\enemy_health_log.txt", std::ios::trunc);
    std::ofstream playerLog("C:\\Users\\3031435\\Desktop\\IT\\wbs\\C++\\turn game clone\\test\\hp_debug\\player_health_log.txt", std::ios::trunc);
}

