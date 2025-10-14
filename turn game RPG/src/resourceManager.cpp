//resourceManager.cpp

#include "resourceManager.h"
#include <stdexcept> //에러의 명확하게 문제를 알려주고 프로그램을 멈추기 위한 라이브러리

void resourceManager::loadTexture(const std::string& key, const std::string& file) {
    sf::Texture tex;
    if (!tex.loadFromFile(file)) { throw std::runtime_error("Texture load failed: " + file); }
    textures[key] = tex;
}

sf::Texture& resourceManager::getTexture(const std::string& key) {
    return textures.at(key);
}

void resourceManager::loadFont(const std::string& key, const std::string& file) {
    sf::Font font;
    if (!font.loadFromFile(file)) { throw std::runtime_error("Font load failed: " + file); }
    fonts[key] = font;
}

sf::Font& resourceManager::getFont(const std::string& key) {
    return fonts.at(key);
}

void resourceManager::loadAll() {
    //texture
    loadTexture("menuBg", "assets/images/1.png");
    loadTexture("mapBg", "assets/images/map.png");
    loadTexture("floorBg", "assets/images/1Floor.png");
    loadTexture("cursor", "assets/images/mouse.png");
    loadTexture("heal", "assets/images/heal.png");
    loadTexture("boss", "assets/images/boss.png");
    loadTexture("enemy", "assets/images/enemy.png");
    loadTexture("1floorBattleRoomBg", "assets/images/1floorBattleRoom.png");
    loadTexture("expbar", "assets/images/exp.png");
    loadTexture("hpmp", "assets/images/hpmp.png");
    loadTexture("normal", "assets/images/normal.png");
    loadTexture("normalSprite", "assets/images/normalSheet.png");
    loadTexture("elite1", "assets/images/elite1.png");
    loadTexture("tiferet", "assets/images/tiferet.png");
    loadTexture("tiferetSprite", "assets/images/tiferetSheet.png");
    
    //font
    loadFont("normal", "assets/fonts/smartfont.otf");
    loadFont("fantasy", "assets/fonts/Nosutaru-dotMPlusH-10-Regular.ttf");
}
