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

void resourceManager::unloadTexture(const std::string& key) {
    if (textures.count(key)) {
        textures.erase(key);
    }
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
    //background
    loadTexture("menuBg", "assets/images/1.png");
    loadTexture("mapBg", "assets/images/map.png");
    loadTexture("floorBg", "assets/images/1Floor.png");
    loadTexture("1floorBattleRoomBg", "assets/images/1floorBattleRoom.png");
    loadTexture("1floorTiferetRestSprite", "assets/images/1floorTiferetRestSprite.png");

    //UI
    loadTexture("cursor", "assets/images/mouse.png");
    loadTexture("heal", "assets/images/heal.png");
    loadTexture("boss", "assets/images/boss.png");
    loadTexture("enemy", "assets/images/enemy.png");
    loadTexture("expbar", "assets/images/exp.png");
    loadTexture("hpmp", "assets/images/hpmp.png");
    loadTexture("enemyHp", "assets/images/enemyHp.png");
    loadTexture("attack", "assets/images/attack.png"); //크기 제기 용
    loadTexture("defense", "assets/images/defense.png");
    loadTexture("skill", "assets/images/skill.png");
    loadTexture("attackSprite", "assets/images/attackSheet.png");
    loadTexture("defenseSprite", "assets/images/defenseSheet.png");
    loadTexture("skillSprite", "assets/images/skillSheet.png");
    loadTexture("battleBack", "assets/images/battleBack.png");
    loadTexture("battleSkill", "assets/images/battleSkill.png");
    loadTexture("battleSkillBack", "assets/images/battleSkillBack.png");
    loadTexture("skillIcon", "assets/images/skillIcon.png");
    //tiferet
    loadTexture("tiferet", "assets/images/tiferet.png");
    loadTexture("tiferetSprite", "assets/images/tiferetSheet.png");
    loadTexture("tiferetAttack", "assets/images/tiferetAttack.png");
    loadTexture("tiferetDefense", "assets/images/tiferetDefense.png");

    //enemy
    loadTexture("normal1", "assets/images/normal1.png");
    loadTexture("normal1Sprite", "assets/images/normal1Sheet.png");
    loadTexture("normal1Attack", "assets/images/normal1Attack.png");
    loadTexture("normal1EffectSheet", "assets/effects/normal1/attackSheet.png");

    loadTexture("elite1", "assets/images/elite1.png");
    loadTexture("elite1Sprite", "assets/images/elite1Sheet.png");
    loadTexture("elite1Attack", "assets/images/elite1Attack.png");
    loadTexture("elite1EffectSheet", "assets/effects/elite1/attackSheet.png");

    loadTexture("boss1", "assets/images/boss1.png");
    loadTexture("boss1Sprite", "assets/images/boss1Sheet.png");
    loadTexture("boss1Attack", "assets/images/boss1Attack.png");
    loadTexture("boss1EffectSheet", "assets/effects/boss1/attackSheet.png");

    //font
    loadFont("normal", "assets/fonts/smartfont.otf");
    loadFont("fantasy", "assets/fonts/Nosutaru-dotMPlusH-10-Regular.ttf");
}

void resourceManager::tiferetEffect() {
    loadTexture("attackEffectSheet", "assets/effects/tiferet/default/attackSheet.png");
    loadTexture("powerStrike", "assets/effects/tiferet/powerStrike/powerStrikeSheet.png");
    loadTexture("powerStrikeIcon", "assets/effects/tiferet/powerStrike/skillIcon.png");
    loadTexture("healIcon", "assets/effects/tiferet/heal/skillIcon.png");
}
