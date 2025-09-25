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
    loadTexture("menuBg", "assets/images/1.png");
    loadTexture("mapBg", "assets/images/map2.png");
    loadTexture("cursor", "assets/images/mouse.png");

    loadFont("normal", "assets/fonts/smartfont.otf");
    loadFont("fantasy", "assets/fonts/Nosutaru-dotMPlusH-10-Regular.ttf");
}
