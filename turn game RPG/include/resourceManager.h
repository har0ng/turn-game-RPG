//resourceManager.h
#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class resourceManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    void loadTexture(const std::string& key, const std::string& file); //텍스쳐 외부에서 불러오기
    sf::Texture& getTexture(const std::string& key); //텍스쳐 get

    void unloadTexture(const std::string& key);

    bool countTexture(const std::string& key);

    void loadFont(const std::string& key, const std::string& file); //폰트 외부에서 불러오기
    sf::Font& getFont(const std::string& key);//폰트 get

    void loadAll(); // 게임 시작 시 모든 리소스 로드
    void tiferetEffect();
};
