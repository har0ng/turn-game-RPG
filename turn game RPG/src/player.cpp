//player.cpp

#include "player.h"
#include "debuffEnum.h"
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <algorithm> // std::max


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
, level_exp(20)
, now_exp(0)
, agility(1)
, critical(1)
, debuff(debuffStatus::none)
, reference(referenceStatus::none)
, activeBuffTurn(0)
, buffAttack(0)
, buffDefense(0)
{
	setBeforePlayer(); /*구조체의 내용을 들고올려면 스코프 안에서 set을 통해 복사해오는게 편함. 
					   const 변수 같은게 없기에 이니셜라이저 안해도 됌*/
	setAfterPlayer();
	setTurnPlayer();
	setBattlePlayer();
	initSkills();       // 스킬 벡터 채우기
	disables.resize(skills.size(), { 0, true }); // remainTurn=0, enabled=true
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
const std::vector<skill>& player::getSkills(){
	if (skills.empty()) {
		return {};
	}
	return skills;
}
std::vector<disable> player::getDisables() const{
	if (disables.empty()) {
		return {};
	}
	return disables;
}
std::vector<buff> player::getBuff() const{
	if (buffs.empty()) {
		return {};
	}
	return buffs;
}
playerStatusSnapShot& player::getBeforePlayer()  {
	return beforePlayer;
}
playerStatusSnapShot& player::getAfterPlayer()  {
	return afterPlayer;
}
playerStatusSnapShot& player::getBattlePlayer() {
	return battlePlayer;
}
playerStatusSnapShot& player::getTurnPlayer() {
	return turnPlayer;
}
debuffStatus player::getDebuff() const {
	return debuff;
}
int player::getActiveBuffTurn() const{
	return activeBuffTurn;
}
int player::getBuffAttack() const{
	return buffAttack;
}
int player::getBuffDefense() const{
	return buffDefense;
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
	level = std::min(10,lev);
}
void player::setLevel_exp(int exp) {
	level_exp = exp;
}
void player::setNow_exp(int exp){
	now_exp = exp;
}
void player::setAgility(int agi) {
	agility = agi;
}
void player::setCritical(int cri) {
	critical = cri;
}
void player::setBeforePlayer() { // 기존 setBeforePlayer는 전투 중 버프용으로 사용
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
	beforePlayer.debuff = debuff;
	beforePlayer.skills = skills;
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
	beforePlayer.debuff = debuff;
	beforePlayer.skills = skills;
}
void player::setBattlePlayer() { // 매 턴 갱신되는 상태 (버프 미적용 스텟)
	battlePlayer.health = player_health;
	battlePlayer.current_health = player_current_health;
	battlePlayer.attack = getBeforePlayer().attack;
	battlePlayer.defense = getBeforePlayer().defense;
	battlePlayer.level = level;
	battlePlayer.level_exp = level_exp;
	battlePlayer.now_exp = now_exp;
	battlePlayer.mana = mana;
	battlePlayer.current_mana = current_mana;
	battlePlayer.agility = getBeforePlayer().agility;
	battlePlayer.critical = getBeforePlayer().critical;
	beforePlayer.debuff = debuff;
	beforePlayer.skills = skills;
}
void player::setTurnPlayer() { // 매 턴 갱신되는 상태 (버프 적용 스텟)
	turnPlayer.health = player_health;
	turnPlayer.current_health = player_current_health;
	turnPlayer.attack = getBasic_attack() + buffAttack;
	turnPlayer.defense = getPlayer_defense() + buffDefense;
	turnPlayer.level = level;
	turnPlayer.level_exp = level_exp;
	turnPlayer.now_exp = now_exp;
	turnPlayer.mana = mana;
	turnPlayer.current_mana = current_mana;
	turnPlayer.agility = agility;
	turnPlayer.critical = critical;
	beforePlayer.debuff = debuff;
	beforePlayer.skills = skills;
}
void player::setDebuff(int debuffnum) {
	debuff = static_cast<debuffStatus>(debuffnum);
}

//other
int player::playerTakeDamage(int dmg) { //현재 체력 - 받은 데미지 계산
	player_current_health = std::max(0, player_current_health - dmg); // 0이하로 떨어져서 오버플로우 안일어나게 막기
	return player_current_health;
}
void player::playerTakeExp(int take_exp) { //take exp	
	now_exp += take_exp;
	if (level < 10) {
		while (now_exp >= getLevel_exp()) { // 여러 레벨업 처리
			now_exp -= getLevel_exp();      // 레벨업에 필요한 경험치 차감
			levelup();
			if (level == 10) { return; }
		}
	}
}
void player::restPlayer(){
	int restHp = static_cast<int>(player_health * 0.3);
	player_current_health = std::min(player_health, player_current_health + restHp);
}

//virtual
void player::initSkills() {
	roadSkillsToJson();
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
			sk.contractCost = s.value("contractCost", 0);
			sk.mpCost = s.value("mpCost", 0);
			sk.activeTime = s.value("activeTime", 1);
			sk.turn = s.value("turn", 1);
			sk.levelReq = s.value("levelReq", 1);
			sk.enemyCnt = s.value("enemyCnt", 1);
			sk.passiveActive = s.value("passiveActive", false);
			sk.debuff = stringToDebuff(s.value("debuff", "none"));

			// 이미 있는 스킬이면 추가하지 않음
			auto it = skills.end();
			for (auto iter = skills.begin(); iter != skills.end(); ++iter) {
				if (iter->name == sk.name) {
					it = iter;
					break;
				}
			}
			if (level >= sk.levelReq && it == skills.end()) {// 없다면 추가
				skills.push_back(std::move(sk));
			}
			/* 검사 또한 아직 안해서 디버깅도 해줘야함 제대로 된건지	*/
		}
		else {
			continue;  // 바로 다음 JSON 스킬항목으로 넘어감
		}
	}
}
std::string player::getClassName() {//자신의 직업에 대한 클래스 함수가 무엇인지 알기 위함, player.cpp 니깐 클래스 함수는 player
	return "player";
}
void player::levelup() { //레벨 업.
	++level;
	if (level < 10) {
		level_exp *= 2; //필요 경험치 2배씩 증가
	}
	else {
		level_exp = 0;
		now_exp = 0;
	}
	player_current_health = player_health; //체력 회복
	current_mana = mana; //마나 회복
	debuff = debuffStatus::none;
}

//json
void player::roadSkillsToJson() { //직업에 필요한 스킬들을 json에서 빼오기 위해 필요
	std::ifstream file("assets/skill.json");
	if (file.is_open()) {
		file >> skillData; // JSON 파일 전체 읽어서 skillData에 저장

	}
}
debuffStatus player::stringToDebuff(const std::string& str) { //string → enum 변환용
	if (str == "none") { return debuffStatus::none; }
	if (str == "agiDown") { return debuffStatus::agiDown; }
	if (str == "criDown") { return debuffStatus::criDown; }
	if (str == "defDown") { return debuffStatus::defDown; }
	if (str == "atkDown") { return debuffStatus::atkDown; }
	if (str == "disarray") { return debuffStatus::disarray; }
	if (str == "weekness") { return debuffStatus::weekness; }
	if (str == "bleed") { return debuffStatus::bleed; }
	if (str == "burn") { return debuffStatus::burn; }
	if (str == "wet") { return debuffStatus::wet; }

	return debuffStatus::none; // default
}
std::string player::debuffToString(debuffStatus debuff) { //enum -> string 변환용
	switch (debuff) {
	case debuffStatus::none:
		return "none";
	case debuffStatus::agiDown:
		return "agiDown";
	case debuffStatus::criDown:
		return "criDown";
	case debuffStatus::defDown:
		return "defDown";
	case debuffStatus::atkDown:
		return "atkDown";
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
	default:
		return "none";
	}
}
referenceStatus player::stringToReference(const std::string& str) {
	if (str == "none") { return referenceStatus::none; }
	if (str == "notSpecified") { return referenceStatus::notSpecified; }
	if (str == "attackBuff") { return referenceStatus::attackBuff; }
	if (str == "defenseBuff") { return referenceStatus::defenseBuff; }
	if (str == "totalDamageBuff") { return referenceStatus::totalDamageBuff; }
	if (str == "totalDamage") { return referenceStatus::totalDamage; }
	if (str == "maxHp") { return referenceStatus::maxHp; }
	if (str == "dispelDebuff") { return referenceStatus::dispelDebuff; }
	if (str == "totalDamageAndAttack") { return referenceStatus::totalDamageAndAttack; }
	if (str == "contractenhanced") { return referenceStatus::contractenhanced; }
	if (str == "defenseAttack") { return referenceStatus::defenseAttack; }
	if (str == "takeDamage") { return referenceStatus::takeDamage; }
	if (str == "dispelDebuffAndMaxHp") { return referenceStatus::dispelDebuffAndMaxHp; }
	return referenceStatus::none;
}
std::string player::referenceToString(referenceStatus reference) {
	switch (reference) {
	case referenceStatus::none:
		return "none";
	case referenceStatus::notSpecified:
		return "notSpecified";
	case referenceStatus::attackBuff:
		return "attackBuff";
	case referenceStatus::defenseBuff:
		return "defenseBuff";
	case referenceStatus::totalDamageBuff:
		return "totalDamageBuff";
	case referenceStatus::totalDamage:
		return "totalDamage";
	case referenceStatus::maxHp:
		return "maxHp";
	case referenceStatus::dispelDebuff:
		return "dispelDebuff";
	case referenceStatus::totalDamageAndAttack:
		return "totalDamageAndAttack";
	case referenceStatus::contractenhanced:
		return "contractenhanced";
	case referenceStatus::defenseAttack:
		return "defenseAttack";
	case referenceStatus::takeDamage:
		return "takeDamage";
	case referenceStatus::dispelDebuffAndMaxHp:
		return "dispelDebuffAndMaxHp";
	default:
		return "none";
	}
}

//buff
void player::updateBuffedStats() {
	buffAttack = 0;
	buffDefense = 0;
	for (auto& b : buffs) {
		if (b.active) {
			buffAttack += b.attackBoost;
			buffDefense += b.defenseBoost;
		}
	}
}
void player::decreaseBuffTurns(int turn) {//남은 버프 턴 계산
	for (auto& b : buffs) {
		if (!b.active) continue;       // 이미 종료된 버프는 무시
		if (b.remainingTurn <= turn) {
			b.active = false;          // 버프 종료
		}
	}
	// 현재 유효 버프 반영
	updateBuffedStats();
}
void player::pushBuff(std::string name, int atk, int def, int stack, int remainTurn, bool check, bool amplity) {
	buffs.push_back({ name,atk,def,stack,remainTurn,check,amplity }); //버프 vector 목록에 추가
}
void player::clearBuff() {//전투 후 사용중이던 버프 전부 삭제
	buffs.clear();
	buffAttack = 0;
	buffDefense = 0;
}

//CT
void player::skillDisable(int skillSelect, int turn) {
	disables[skillSelect].remainTurn = turn; //CT 턴 기입
	disables[skillSelect].enabled = false; //사용 불가능 하게
}
void player::skillCT() {
	for (auto& status : disables) {
		if (status.remainTurn > 0) {
			status.remainTurn--;
		}
		if (status.remainTurn == 0) {
			status.enabled = true;  // 스킬 사용 가능
		}
		else {
			status.enabled = false; // 스킬 사용 불가
		}
	}
}
void player::clearDisable() { //전투 끝나고 쿨타임 모두 초기화
	disables.clear();
	disables.resize(skills.size(), { 0, true }); // remainTurn=0, enabled=true
}

//tiferet
//get
int player::getContract() const { //tiferet
	return 0;
}
bool player::getAmplifyActivate() const {
	return false;
}
 std::vector<buff> player::getImSlashYou() const{
	 return {};
}
//set
void player::setContract(int null) {
	return;
};
void player::setAmplifyActivate(bool YN) {
	return;
}
//other
bool player::noneOverclock() {
	return false;
}
bool player::noneIm() {
	return false;
}
bool player::noneSlash() {
	return false;
}
void player::pushImSlashYou(std::string name, int atk, int def, int stack, int remainTurn, bool check, bool amplity) {
	return;
}
void player::clearImSlashYou() {
	return;
}

//player poninter
std::unique_ptr<player> p = nullptr; //이런식으로 구현해줘야함
void selectClass(const std::string& className) {

	if (className == "tiferet") {
		p = std::make_unique<tiferet>();
	}
	else if (className == "malkuth") {
		p = std::make_unique<malkuth>();
	}
}
player& getPlayerPtr(){// 유니크 포인터를 넘겨야하니깐 이렇게 됨.
	return *p;
}
