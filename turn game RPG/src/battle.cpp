//battle.cpp

#include "player.h"
#include "enemy.h"
#include "consoleUI.h"
#include "battle.h"

#include <iostream>
#include <random>
#include <algorithm> // std::max
#include <memory> // smart pointer
#include<string>

using std::cout;
using std::endl;
using std::cin;
using std::unique_ptr;



battle::battle(unique_ptr<player> _p , unique_ptr<enemy> _e)
	: p(std::move(_p)), e(std::move(_e)), gen(rd()) { //정보 받아옴.
	
	//player
	php = p->getPlayer_health(); // user 체력 get으로 받아오기
	cphp = p->getPlayer_current_health(); //user 현재 체력 가져오기
	pattack = p->getBasic_attack(); // user 공격력 get으로 받아오기
	pdefense = p->getPlayer_defense(); // user 방어력 get으로 받아오기
	level = p->getLevel(); // 플레이어 레벨
	level_exp = p->getLevel_exp();//총 경험치
	now_exp = p->getNow_exp(); //현재 경험치
	mana = p->getMana();
	current_mana = p->getCurrent_mana();
	agility = p->getAgility();
	critical = p->getCritical();
	debuff = p->getDebuff();

	battleselect = 0; // battle menu select 값 또한 실행하면서 값을 받아와야하니, private이기도 하고 0 으로 미리 초기화
	skillSelect = 0;

	//enemy
	ehp = e->getEnemy_health(); //enemy 체력 get으로 받아오기
	eattack = 0; //enemy 공격력은 private 이니 0으로 미리 초기화
	
	
	//battletime
	turn = 0; // 몇번째 턴인지 알려주기위함.
	//gameover(Y/N)
	play = true;
};

void battle::startBattle() { //배틀 시작
	while (cphp > 0 && ehp > 0) { //체력이 0 이하가 되는 순간 종료
		p->setBeforePlayer(); //전투 전 플레이어 정보 저장

		battleStatus(); //유저와 적의 상황(체력 공격력 등)
		playerTurn(); //유저 턴
		if (ehp <= 0) { //무승부 방지
			break;
		}
		enemyTurn(); //enemy 턴
	}
	battleEnd(); // 전투 종료

	if (p->getLevel() == 2 && p -> classChangeYN()){ // 2레벨 전직, 만약 전직했으면 안뜸
		levelup_selectClass(); //전직
	}

	p->setAfterPlayer(); //전투 후 플레이어 정보 저장

	if (p->getBeforePlayer().level != p->getAfterPlayer().level) { //레벨 업을 했다면
		ui.showStatusChange(p->getBeforePlayer(), p->getAfterPlayer()); // 능력치 변화 보여주기
		ui.enterToContinue(); //엔터 누르면 넘어가는 기능
	}
}

void battle::battleStatus() {
	std::uniform_int_distribution<unsigned int> enemyDamage(4, 7); //랜덤 범위 조정
	eattack = enemyDamage(gen); //적의 공격력을 범위 내 초기화된 수로 랜덤화
	turn++; //몇턴 째인지 셈
	
	ui.battleStatus(turn, php, cphp, pattack, pdefense, ehp, eattack, level, level_exp, now_exp, mana, current_mana, p->debuffToString(debuff)); //log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}	

void battle::playerTurn() {
	ui.playerTurnUI();
	attackInfo res = atkInfo();
	 do{
		 battleselect = inputCheck(1,3);
		if (battleselect == 1) { // 1. 공격 2. 방어 3.스킬
			attackEnemy(res.criticalYN, res.criticalLine , res.criattack, res.attack);
		}

		if (battleselect == 3) { //스킬창
			const auto& skill = p->getSkills(); //heal, powerStrike, antiDebuff가 나옴
			int skSize = 0;
			for (const auto& sk : skill) {  
				if (level >= (int)sk.levelReq) {
					skSize++;
					ui.showSkill(skSize, sk.charactorClass, sk.name, sk.hpCost,
								 sk.mpCost, sk.activeTime, sk.turn, sk.enemyCnt);
				}
			}
			skillSelect = inputCheck(1, skSize) -1;
			getSkillSelect(skillSelect, skill ,res);
			
			
			/*
			08/22 1636 -> 08/25
			skillSelect가 옳바른 값이 되면 그 스킬이 활성화되서 스킬이 이뤄지게끔 하기
			*/


		}
	 } while (battleselect != 1 && battleselect != 2 && battleselect != 3);

	ui.playerTurn(cphp, pdefense, battleselect, res.attack, res.criattack, res.criticalYN);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::enemyTurn() {
	std::uniform_int_distribution<unsigned int> dist(0, 2); //0. 상황 살피기, 1. 공격, 2. 공격
	int enemy_action = dist(gen);

	// 전투 로직 (데미지 계산 등)
	if (enemy_action == 0) {
		// 상황 살피기 (출력은 UI에서)
	}
	else { 
		if (battleselect == 2) { //player가 방어를 선택 했을 때
			eattack = std::max(0, eattack - pdefense);
			p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
			cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
		}
		else { //player가 방어가 아닌 다른걸 선택 했을 때
			p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
			cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
		}
	}

	ui.enemyTurn(enemy_action, pdefense, eattack, battleselect);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::battleEnd() {
	ui.battleEnd(cphp);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
	if (cphp <= 0) {
		play = false;
		exit(0);
	}	
	else {
		int instance_exp = 5;  // 몬스터의 종류, 레벨에따라 차등 적용해야하는데 임의로 경험치를 설정하고 테스트
		p->playerTakeExp(instance_exp); //player안의 nowexp 값 갱신
		now_exp = p->getNow_exp(); // 갱신된 값으로 초기화
		level_exp = p->getLevel_exp(); //레벨업 시 총 경험치 갱신된 값으로 초기화
	}
}

void battle::levelup_selectClass() { // class change , 전직
	ui.levelup_selectClassUI();
	int selectClass;
	cin >> selectClass;
	ui.levelup_selectClass(level, selectClass);
	if (selectClass == 1) { // Warrior
		p = std::make_unique<warrior>(*p); // player 객체를 warrior로 복사 생성
	}
	else if (selectClass == 2) { // Magician
		p = std::make_unique<magician>(*p);
	}
	else if (selectClass == 3) { // Assassin
		p = std::make_unique<assassin>(*p);
	}
}

bool battle::getPlay() const { //게임이 지속 가능한지 플레이어의 체력이 남아있는지 확인
	return play;
}

std::unique_ptr<player> battle::getPlayerPtr() { // 유니크 포인터를 넘겨야하니깐 이렇게 됨.
	return std::move(p);
}

int battle::inputCheck(int min, int max) { //battleselect, skillselect 구분 문구
	int input;
	while (true) {
		cin >> input;
		if (cin.fail()) {// 숫자가 아닌 입력 감지
			cin.clear(); // fail 상태 초기화
			cin.ignore(1000, '\n'); // 입력 버퍼 비우기 , cin.ignore(무시할수 있는 최대 문자수,	무시를 멈출 기준이 되는 문자)
			cout << "please input number." << endl;
			continue; // 유효하지 않은 값으로 초기화
		}
		if (input >= min && input <= max) {
			return input;
		}
		cout << "do not imoport. retry please" << endl;
	}
} 

void battle::getSkillSelect(int skillSelect, std::vector<skill> const& skill, attackInfo res) {
	if (skill[skillSelect].passiveActive == false) {
		passiveSkill(skillSelect, skill, res);
	}
	else {
		activeSkill(skillSelect, skill, res);
	}
	
}

void battle::passiveSkill(int skillSelect, std::vector<skill> const& skill, attackInfo res) { //false
	if (skill[skillSelect].referenceStatus == "attack") {
	
	}
	else if(skill[skillSelect].referenceStatus == "defense") {

	}

}

void battle::activeSkill(int skillSelect, std::vector<skill> const& skill, attackInfo res) { //true
	if (skill[skillSelect].referenceStatus == "totalDamage") {
		attackEnemy(res.criticalYN, res.criticalLine,
					static_cast<int>(res.criattack * skill[skillSelect].TDMultiplier),
					static_cast<int>(res.attack * skill[skillSelect].TDMultiplier));
		
	}
	else if (skill[skillSelect].referenceStatus == "maxHp") {

	}
	else if (skill[skillSelect].referenceStatus == "playerDebuff") {

	}
	else if (skill[skillSelect].referenceStatus == "totalDamage&attack") {

	}
	else if (skill[skillSelect].referenceStatus == "defense") {

	}
}

void battle::attackEnemy(bool criticalYN,int criticalLine ,int criattack, int attack) {
	if (criticalLine <= p->getCritical()) { // 크리티컬 시 1.3배 데미지
		criticalYN = true;
		ehp = e->enemyTakeDamage(ehp, criattack); // 소수점 이하 버림
	}
	else {
		ehp = e->enemyTakeDamage(ehp, attack);
	}
}

attackInfo battle::atkInfo() {
	attackData.criticalYN = false;
	std::uniform_int_distribution<unsigned int> dmg(pattack - 2, pattack + 1);
	std::uniform_real_distribution<float> randomDmg(0.05, 0.1);
	std::uniform_int_distribution<unsigned int> cri(1, 100);

	attackData.criticalLine = cri(gen);
	int damage = dmg(gen);
	float randomDamage = randomDmg(gen);
	attackData.attack = static_cast<int>(damage + (damage * (damage * randomDamage)));
	attackData.criattack = static_cast<int>(attackData.attack * 1.3);

	return attackData; // 구조체 통째로 반환
}