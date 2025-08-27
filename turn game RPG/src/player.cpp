//player.cpp

#include "player.h"
#include "debuffEnum.h"
#include "skillEnum.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <json.hpp>
#include <string>


using std::cout;
using std::endl;
nlohmann::json skillData; //json 객체 선언


player::player() :player_health(30)
, player_current_health(30)
, basic_attack(5)
, basic_defense(5)
, mana(8)
, current_mana(8)
, level(1)
, level_exp(10)
, now_exp(0)
, agility(1)
, critical(99)
, debuff(debuffStatus::none)
, reference(referenceStatus::none)
{
	setBeforePlayer(); /*구조체의 내용을 들고올려면 스코프 안에서 set을 통해 복사해오는게 편함. 
					   const 변수 같은게 없기에 이니셜라이저 안해도 됌*/
	setAfterPlayer();
	initSkills();       // 스킬 벡터 채우기
} //initializing

//get
int player::getPlayer_health() const { // private에 숨긴 값 get set으로 들고오기
	return player_health;
}
int player::getPlayer_current_health() const{
	return player_current_health;
}
int player::getPlayer_defense() const {// private에 숨긴 값 get set으로 들고오기
	return basic_defense;
}
int player::getBasic_attack() const {// private에 숨긴 값 get set으로 들고오기
	return basic_attack;
}
int player::getLevel() const { // private에 숨긴 값 get 으로 들고오기
	return level;
}
int player::getLevel_exp() const { // private에 숨긴 값 get 으로 들고오기
	return level_exp;
}
int player::getNow_exp() const { // private에 숨긴 값 get 으로 들고오기
	return now_exp;
}
int player::getMana() const {
	return mana;
}
int player::getCurrent_mana() const {
	return current_mana;
}
int player::getAgility() const {
	return agility;
}
int player::getCritical() const {
	return critical;
}
std::vector<skill> player::getSkills() const {
	if (skills.empty()) {
		return {};
	}
	return skills;
}
playerStatusSnapShot player::getBeforePlayer() const {
	return beforePlayer;
}
playerStatusSnapShot player::getAfterPlayer() const {
	return afterPlayer;
}
debuffStatus player::getDebuff() const {
	return debuff;
}

//set
void player::setPlayer_health(int hp) {
	player_health = hp;
}
void player::setPlayer_current_health(int hp) {
	player_current_health = hp;
};
void player::setPlayer_defense(int defense) {
	basic_defense = defense;
};
void player::setBasic_attack(int attack) {
	basic_attack = attack;
};
void player::setMana(int mp){
	mana = mp;
}
void player::setCurrent_mana(int mp) {
	current_mana = mp;
}
void player::setLevel(int lev){
	level = lev;
}
void player::setLevel_exp(int lev) {
	level_exp = lev;
}
void player::setNow_exp(int lev){
	now_exp = lev;
}
void player::setAgility(int agi) {
	agility = agi;
}
void player::setCritical(int cri) {
	critical = cri;
}
void player::setBeforePlayer() {
	beforePlayer.health = player_health;
	beforePlayer.current_health = player_current_health;
	beforePlayer.attack = basic_attack;
	beforePlayer.defense = basic_defense;
	beforePlayer.level = level;
	beforePlayer.level_exp = level_exp;
	beforePlayer.now_exp = now_exp;
	beforePlayer.mana = mana;
	beforePlayer.current_mana = current_mana;
	beforePlayer.agility = agility;
	beforePlayer.critical = critical;
}
void player::setAfterPlayer() {
	afterPlayer.health = player_health;
	afterPlayer.current_health = player_current_health;
	afterPlayer.attack = basic_attack;
	afterPlayer.defense = basic_defense;
	afterPlayer.level = level;
	afterPlayer.level_exp = level_exp;
	afterPlayer.now_exp = now_exp;
	afterPlayer.mana = mana;
	afterPlayer.current_mana = current_mana;
	afterPlayer.agility = agility;
	afterPlayer.critical = critical;
}
void player::setDebuff(int debuffnum) {
	debuff = static_cast<debuffStatus>(debuffnum);
}

//other
int player::playerTakeDamage(int dmg) { //현재 체력 - 받은 데미지 계산
	player_current_health = std::max(0, player_current_health - dmg); // 0이하로 떨어져서 오버플로우 안일어나게 막기
	return player_current_health;
}
void player::levelup() { //레벨 업.
	level++;
	level_exp *= 2; //필요 경험치 2배씩 증가
	player_current_health = player_health; //체력 회복
	current_mana = mana; //마나 회복
	debuff = debuffStatus::none;
}
int player::playerTakeExp(int take_exp) { //take exp
	if (now_exp + take_exp< getLevel_exp()) { //not level up
		now_exp += take_exp;
		return now_exp;
	}
	else { //level up , exp cal
		now_exp += take_exp - getLevel_exp();
		levelup();
		return now_exp;
	}
}
bool player::classChangeYN() const { //전직하면 false로 바꾸게 해주면 됨,
	return true;
}
void player::initSkills() {
	roadSkillsToJson();
	skillClear(); //다른 cpp에도 쓰기 위해 함수화
	 //skillData는 skill.json임
	if (skillData.empty()) { // 스킬데이터에 스킬이 없는데 무언가 넣을려하면 에러(기저 조건)
		return;
	}
	for (const auto& s : skillData) { //skillData의 데이터를 s 객체로 자동 데이터 타입으로 맞춰서 참조해서 들고온다는 이야기
		std::string charClass = s.value("charactorClass", ""); //json 에서 key, vlaue 값을 들고오는걸로 charactorClass가 key값
		skill sk; //skill 구조체에 json에서의 파일을 각 key값에 맞게 대입함													   // 조건에 맞지 않으면 스킬 추가하지 않고 다음 반복으로 (기저 조건)
		// !!만약 key 에 맞는 value 값이 존재하지 않을 시 default 값을 아래와 같이 하여 에러 방지 !!

		if (charClass == "common" || charClass == this->getClassName()) {
			sk.charactorClass = s.value("charactorClass", "");
			sk.name = s.value("name", "unknown");
			sk.targetObject = s.value("targetObject", "player");
			sk.power = s.value("power", 0);
			sk.TDMultiplier = s.value("TDMultiplier", 1.0);
			sk.playerMultiplier = s.value("playerMultiplier", 0.0);
			sk.referenceStatus = stringToReference(s.value("referenceStatus", "none"));
			sk.hpCost = s.value("hpCost", 0);
			sk.mpCost = s.value("mpCost", 0);
			sk.activeTime = s.value("activeTime", 1);
			sk.turn = s.value("turn", 1);
			sk.levelReq = s.value("levelReq", 1);
			sk.enemyCnt = s.value("enemyCnt", 1);
			sk.passiveActive = s.value("passiveActive", false);
			sk.debuff = stringToDebuff(s.value("debuff", "none"));
		}
		else {
			continue;  // 바로 다음 JSON 스킬항목으로 넘어감
		}
		// 안전하게 벡터에 이동 추가
		skills.push_back(std::move(sk));
	}
}
std::string player::getClassName() {//자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함, player.cpp 니깐 클래스 함수는 player
	return "player";
}
void player::skillClear(){
	skills.clear();
}
void player::roadSkillsToJson() { //직업에 필요한 스킬들을 json에서 빼오기 위해 필요
	std::ifstream file("assets/skill.json");
	if (file.is_open()) {
		file >> skillData; // JSON 파일 전체 읽어서 skillData에 저장
		
	}
}
debuffStatus player::stringToDebuff(const std::string& str){ //string → enum 변환용
	if (str == "none") { return debuffStatus::none; }
	if (str == "disarray") { return debuffStatus::disarray; }
	if (str == "weekness") { return debuffStatus::weekness; }
	if (str == "bleed") { return debuffStatus::bleed; }
	if (str == "burn") { return debuffStatus::burn; }
	if (str == "wet") { return debuffStatus::wet; }
	if (str == "freeze") { return debuffStatus::freeze; }
	if (str == "electricShock") { return debuffStatus::electricShock; }
	if (str == "agiDown") { return debuffStatus::agiDown; }
	if (str == "criDown") { return debuffStatus::criDown; }
	if (str == "defDown") { return debuffStatus::defDown; }
	if (str == "atkDown") { return debuffStatus::atkDown; }
	return debuffStatus::none; // default
}
std::string player::debuffToString(debuffStatus debuff){ //enum -> string 변환용
	switch (debuff){
	case debuffStatus::none:
		return "none";
	case debuffStatus::disarray:
		return "disarray";
	case debuffStatus::weekness:
		return "weekness";
	case debuffStatus::bleed:
		return "bleed";
	case debuffStatus::burn:
		return "burn";
	case debuffStatus::wet:
		return "wet";
	case debuffStatus::freeze:
		return "freeze";
	case debuffStatus::electricShock:
		return "electricShock";
	case debuffStatus::agiDown:
		return "agiDown";
	case debuffStatus::criDown:
		return "criDown";
	case debuffStatus::defDown:
		return "defDown";
	case debuffStatus::atkDown:
		return "atkDown";
	default:
		return "none";
	}
}
referenceStatus player::stringToReference(const std::string& str){
	if (str == "none") { return referenceStatus::none; }
	if (str == "attack") { return referenceStatus::attack; }
	if (str == "defense") { return referenceStatus::defense; }
	if (str == "totalDamage") { return referenceStatus::totalDamage; }
	if (str == "maxHp") { return referenceStatus::maxHp; }
	if (str == "playerDebuff") { return referenceStatus::playerDebuff; }
	if (str == "tatalDamageAndAttack") { return referenceStatus::tatalDamageAndAttack; }
	return referenceStatus::none;
}
std::string player::referenceToString(referenceStatus reference){
	switch (reference){
	case referenceStatus::none:
		return "none";
	case referenceStatus::attack:
		return "attack";
	case referenceStatus::defense:
		return "defense";
	case referenceStatus::totalDamage:
		return "totalDamage";
	case referenceStatus::maxHp:
		return "maxHp";
	case referenceStatus::playerDebuff:
		return "playerDebuff";
	case referenceStatus::tatalDamageAndAttack:
		return "tatalDamageAndAttack";
	default:
		return "none";
	}
}
