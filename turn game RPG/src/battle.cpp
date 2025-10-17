//battle.cpp

#include "player.h"
#include "enemy.h"
#include "consoleUI.h"
#include "battle.h"
#include "buff.h"

#include <iostream>
#include <random>
#include <algorithm> // std::max
#include <memory> // smart pointer
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::unique_ptr;


battle::battle(std::unique_ptr<player>& playerP, std::unique_ptr<enemy>& EnemyP)
	:p(playerP), e(EnemyP), gen(rd()) { //정보 받아옴.
	
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
	echp = e->getEnemyCurrentHealth();
	eattack = e->getPower(); //enemy 공격력은 private 이니 0으로 미리 초기화
	
	
	//battletime
	turn = 0; // 몇번째 턴인지 알려주기위함.
	//gameover(Y/N)
	play = true;

	//tiferet
	contract = p->getContract();
	amplifyActivate = p->getAmplifyActivate();
};

void battle::statusManager() {
	turn++; //몇턴 째인지 셈
	p->decreaseBuffTurns(turn); //버프 삭제 카운터 다운
	if (p->getClassName() == "tiferet") { //턴마다 1씩 회복
		const int MAX_CONTRACT = 12;
		p->setContract(std::min(MAX_CONTRACT, contract + 1));
		contract = p->getContract();
	}
}

void battle::showGetSkill(std::vector<skill> beforeSkill, std::vector<skill> afterSkill) { // 레벨 업 후 얻은 스킬 목록
	std::vector<skill> returnTest;
	std::sort(beforeSkill.begin(), beforeSkill.end()); 
	std::sort(afterSkill.begin(), afterSkill.end()); 

	std::set_difference(afterSkill.begin(), afterSkill.end(),
						beforeSkill.begin(), beforeSkill.end(),
						std::back_inserter(returnTest));
	for (auto it = returnTest.begin(); it != returnTest.end(); ++it) {
		ui.showGetSkill(it->name);
	}
	/*iterator은 참조해서 쓸 때 그 데이터값이 바뀔 염려가 있어 알고리즘에 관한 기술을 사용못함
	그러니 이를 쓰기위해선 본래의 값을 그대로 쓸 필요가 있음. 그래서 새로운 객체를 만들어 복사본으로
	비교하는 것으로함.*/
	//set_difference에서 서로의 비교를 위해 operator>,operator==을 struct에 구현 필요 
}

void battle::battleStatus() {
	p->skillCT(); //쿨타임 백터 전체 쿨 다운
	if (p->getClassName() == "tiferet") {
		ui.battleStatus(turn, php, cphp, p->getTurnPlayer().attack, p->getTurnPlayer().defense,
			p->getContract(), e->getEnemyType(), ehp, echp ,eattack, level, level_exp, now_exp, mana, current_mana,
			p->debuffToString(debuff),p->getBuff(), p->getImSlashYou(),p->getBuffAttack(), p->getBuffDefense(),
			p->getClassName(),amplifyActivate);
	}
	else {
		ui.battleStatus(turn, php, cphp, p->getTurnPlayer().attack, p->getTurnPlayer().defense,
			e->getEnemyType(), ehp, echp, eattack, level, level_exp, now_exp, mana, current_mana,
			p->debuffToString(debuff), p->getBuff(), p->getBuffAttack(), p->getBuffDefense(),
			p->getClassName()); //log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
	}
}

void battle::playerTurn(int input, int skillInput) {
	attackInfo res = atkInfo();
	int finalAttack = 0;
	bool activeWeaponMaster = false;
	if (p->getClassName() == "tiferet" && level > 8) {
		for (const auto b : p->getBuff()) {
			if (b.name == "weaponMaster" && b.active) {
				activeWeaponMaster = true;
			}
		}
	}
	while (true) {
		ui.playerTurnUI();
		battleselect = input;
		if (battleselect == 1) { // 1. 공격 2. 방어 3.스킬
			finalAttack = attackEnemy(res.criticalYN, res.criattack, res.attack);
			break;
		}
		if (battleselect == 2) { // 방어
			break;
		}
		if (battleselect == 3) { //스킬창
			const auto& skill = p->getSkills(); //heal, powerStrike, antiDebuff가 나옴
			const auto& disable = p->getDisables();
			bool skillCheck = false;
			while (true) {
				int skSize = 0;
				for (size_t i = 0; i < skill.size(); ++i) {
					if (level >= (int)skill[i].levelReq) {
						skSize++;
						bool enabled = disable[i].enabled;

						if (enabled == true && activeWeaponMaster == true) {
							ui.showSkill(skSize, skill[i].charactorClass, skill[i].name,
								contract, (std::max(0, skill[i].contractCost - 1)), skill[i].mpCost, current_mana,
								skill[i].activeTime, skill[i].turn, skill[i].enemyCnt);
						}
						else if (enabled == true) {
							ui.showSkill(skSize, skill[i].charactorClass, skill[i].name,
								contract, skill[i].contractCost, skill[i].mpCost, current_mana,
								skill[i].activeTime, skill[i].turn, skill[i].enemyCnt);
						}
						else {
							ui.showSkill(skSize, skill[i].name, disable[i].remainTurn, skill[i].mpCost, skill[i].contractCost);
						}
					}
				}
				ui.exitSkill(0);

				skillSelect = input;
				if (skillSelect == -1) { // 0을 입력했을 때 무한 반복 깨기
					break;
				}
				if (current_mana < skill[skillSelect].mpCost) { //현재 마나가 스킬 필요 마나보다 모자를 경우
					ui.skillMpcostRetry();
					continue;
				}
				if (disable[skillSelect].enabled == false) { //스킬 쿨타임일 경우
					ui.skillCoolTimeRetry();
					continue;
				}
				if (contract < skill[skillSelect].contractCost) { //tiferet한정
					ui.skillContractCostRetry();
					continue;
				}
				finalAttack = getSkillSelect(skillSelect, skill, res); //스킬이 정상적으로 써질 때

				if (p->getClassName() == "tiferet" && skill[skillSelect].name == "overclock") {
					if (p->noneOverclock() == false) {
						continue;
					}
				}
				if (p->getClassName() == "tiferet" && skill[skillSelect].name == "slash") {
					if (p->noneIm() == false) {
						continue;
					}
				}
				if (p->getClassName() == "tiferet" && skill[skillSelect].name == "you") {
					if (p->noneSlash() == false) {
						continue;
					}
				}

				skillCheck = true; //쿨타임이 돌게끔 해주고
				p->skillDisable(skillSelect, skill[skillSelect].turn); //스킬 쿨타임 vector에 집어넣기
				
				if (skill[skillSelect].name == "you") { //tiferet
					p->clearImSlashYou();
				}
				
				
				break;
			}
			if (skillCheck == false) { //무한 반복을 깨고 나왔으니 그냥 넘어가게끔해서 battleSelect부터 다시 하게끔 하기.
				continue;
			}
			/*
			08/22 1636 -> 08/28
				스킬 추가

				스킬을 적중 시켰을 때 그 디버프가 로그와 디버프의 상황이 남도록 만들어야함.
				(에너미 디버프 만들 필요)

				최종데미지 UI어떡하지
			*/
		}
		break;
	}
	ui.playerTurn(cphp, p->getTurnPlayer().defense, battleselect, finalAttack, res.criticalYN);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
}

void battle::enemyTurn() {
	int enemy_action = e->enemyAction();
	// 전투 로직 (데미지 계산 등)
	if (enemy_action == 0) {
		// 상황 살피기 (출력은 UI에서)
		ui.enemyTurn(enemy_action, 0, 0, battleselect);
		return;
	}
	//공격 전
	int guardian = 0; // 0이면 x, 1이면 기본, 2면 강화  / tiferet의 contractOfGuardian
	for (const auto b : p->getBuff()) {
		if (b.name == "contractOfGuardian" && b.active == true && b.amplify == false) {
			guardian = 1;
		}
		else if(b.name == "contractOfGuardian" && b.active == true && b.amplify == true){
			guardian = 2;
		}
		if (b.name == "covenantUltima" && b.active) {
			ui.executeCovenantUltima();
			return;
		}
	}

	if (guardian == 2) { // 완전 무효화
		ui.executeGuardian();
		return;
	}

	if (battleselect == 2 && guardian == 1 && std::max(0, eattack - pdefense) >= static_cast<int>(cphp * 0.4)) { //부분 무효화
		ui.executeGuardian();
		return;
	}
	if (battleselect != 2 && guardian == 1 && eattack >= static_cast<int>(cphp * 0.4)) { //부분 무효화
		ui.executeGuardian();
		return;
	}

	if (battleselect == 2) { //방어
		eattack = std::max(0, eattack - pdefense);
		p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
		cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
	}
	else { // 공격 혹은 스킬
		p->playerTakeDamage(eattack);   // player 내부 체력 갱신, (*p).playerTakeDamage(eattack) 주소값이 나타내는 값을 바꿈
		cphp = p->getPlayer_current_health(); // battle 내 체력도 동기화
	}

	ui.enemyTurn(enemy_action, pdefense, eattack, battleselect);//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
	//적의 공격 후	
	for (const auto a : p->getBuff()) { 
		if (a.name == "chainOfPact" && a.active == true &&a.amplify == false) {//계약의 사슬 관련
			echp = e->enemyTakeDamage(echp,static_cast<int>(eattack*0.5));
			ui.activeChain(static_cast<int>(eattack * 0.5), a.remainingTurn);
		}
		else if (a.name == "chainOfPact" && a.active == true && a.amplify == true) {//계약의 사슬 관련
			echp = e->enemyTakeDamage(echp, static_cast<int>(eattack*0.6));
			ui.activeChain(static_cast<int>(eattack * 0.6), a.remainingTurn);
		}

		if (a.name == "theLightOfTruth" && a.active && a.amplify == false) { //remainTurn + turn 동안 debuff 무효화
			//now(09/08) enemy debuff skill is none , need to enemy.cpp develop
		}
		else if (a.name == "theLightOfTruth" && a.active && a.amplify == true) { //remainTurn + turn 동안 debuff 무효화
			//now(09/08) enemy debuff skill is none , need to enemy.cpp develop
		}
	}
}

void battle::battleEnd() {
	if (cphp <= 0) {
		play = false;
		ui.battleEnd(cphp, e->getExpReward());//log를 불러오기위해 log에서 필요로 하는 값 다 넘겨주기
		exit(0);
	}
	p->clearBuff();
	if (p->getClassName() == "tiferet") {
		p->setContract(std::min(p->getContract() + 3, 12));
		contract = p->getContract();
	}
	if (level < 10) {
		p->playerTakeExp(e->getExpReward()); //player안의 nowexp 값 갱신
		ui.battleEnd(cphp, e->getExpReward());
		now_exp = p->getNow_exp(); // 갱신된 값으로 초기화
		level_exp = p->getLevel_exp(); //레벨업 시 총 경험치 갱신된 값으로 초기화
	}
}

void battle::battleEndManager() {
	std::vector<skill> beforeSkill; //레벨업 전 스킬
	for (auto s : p->getSkills()) { //레벨에 따른 스킬이 아닌 직업 스킬 다 들고와서 레벨 따라 들고오게 막음
		if (p->getBeforePlayer().level >= s.levelReq) {
			beforeSkill.push_back(s);
		}
	}

	p->setAfterPlayer(); //전투 후 플레이어 정보 저장

	std::vector<skill> afterSkill; //레벨업 후 스킬
	for (auto s : p->getSkills()) { //레벨에 따른 스킬이 아닌 직업 스킬 다 들고와서 레벨 따라 들고오게 막음
		if (p->getAfterPlayer().level >= s.levelReq) {
			afterSkill.push_back(s);
		}
	}

	if (p->getBeforePlayer().level != p->getAfterPlayer().level) { //레벨 업을 했다면
		ui.showStatusChange(p->getBattlePlayer(), p->getAfterPlayer()); // 능력치 변화 보여주기
		showGetSkill(beforeSkill, afterSkill);
	}
	p->clearDisable(); //전투 끝나고 쿨타임 모두 초기화
}
//void battle::selectClass() { // selectClass
//
//	ui.selectClassUI();
//	int selectClass;
//	cin >> selectClass;
//	ui.selectClass(level, selectClass);
//	
//	if (selectClass == 1) { // tiferet
//		p = std::make_unique<tiferet>(*p); // player 객체를 tiferet로 복사 생성
//	}
//	else if (selectClass == 2) { // chesed
//		p = std::make_unique<chesed>(*p);
//	}
//	else if (selectClass == 3) { // gevurah
//		p = std::make_unique<gevurah>(*p);
//	}
//	else if (selectClass == 4) { // malkuth
//		p = std::make_unique<malkuth>(*p);
//	}
//	else if (selectClass == 5) { // yesod
//		p = std::make_unique<yesod>(*p);
//	}
//	else if (selectClass == 6) { // binah
//		p = std::make_unique<binah>(*p);
//	}
//
//}

bool battle::getPlay() const { //게임이 지속 가능한지 플레이어의 체력이 남아있는지 확인
	return play;
}

//std::unique_ptr<player> battle::getPlayerPtr() { // 유니크 포인터를 넘겨야하니깐 이렇게 됨.
//	return std::move(p);
//}

//int battle::inputCheck(int min, int max, int input) { //battleselect, skillselect 구분 문구
//	int input;
//	while (true) {
//		cin >> input;
//		if (cin.fail()) {// 숫자가 아닌 입력 감지
//			cin.clear(); // fail 상태 초기화
//			cin.ignore(1000, '\n'); // 입력 버퍼 비우기 , cin.ignore(무시할수 있는 최대 문자수,	무시를 멈출 기준이 되는 문자)
//			cout << "please input number." << endl;
//			continue; // 유효하지 않은 값으로 초기화
//		}
//		if (input == 0) {
//			return 0;
//		}
//		if (input >= min && input <= max) {
//			return input;
//		}
//		cout << "do not import. retry please" << endl;
//	}
//} 

int battle::getSkillSelect(int skillSelect, std::vector<skill> const& skill, attackInfo res) {
	if (skill[skillSelect].passiveActive == false) {
		passiveSkill(skillSelect, skill, res);
		getSkillReference(skillSelect, skill, res, 0);
		return 0;
	}
	else {
		int finalAttackInfo = activeSkill(skillSelect, skill, res);
		getSkillReference(skillSelect, skill, res, finalAttackInfo);
		return finalAttackInfo;
	}
	//08/28 1637
	//switch(debuff) 추가해야함 enemy에 debuff 스테이터스 아직 없어서 추가 안함..
}

void battle::getSkillReference(int skillSelect, std::vector<skill> const& skill, attackInfo res, int finalAttack) {
	switch ((int)skill[skillSelect].referenceStatus) {
		case (int)referenceStatus::none:
			cout << "Error : skillReferenceStatus is none" << endl; //디버그용 릴리스 넘어갈 떄 반드시 삭제
			return;
		case (int)referenceStatus::notSpecified: //어디에도 포함 안 될 때
			if (skill[skillSelect].name == "contractOfGuardian") {
				ui.activeGuardian();
			}
			else if (skill[skillSelect].name == "weaponMaster") {
				ui.activeWeaponMaster();
			}
			else if (skill[skillSelect].name == "im") {
				ui.activeIm();
			}
			else if (skill[skillSelect].name == "slash") {
				ui.activeSlash();
			}
			else if (skill[skillSelect].name == "you") {
				ui.acitveYou(finalAttack);
			}
			return;
		case (int)referenceStatus::attackBuff:
			ui.executeSkillAtk(p->getBuffAttack() + p->getTurnPlayer().attack - pattack, skill[skillSelect].activeTime);
			return;
		case (int)referenceStatus::defenseBuff:
			ui.executeSkillDef(p->getBuffDefense() + p->getTurnPlayer().defense - pdefense, skill[skillSelect].activeTime);
			return;
		case (int)referenceStatus::totalDamageBuff:
			return;
		case (int)referenceStatus::totalDamage:
			if (skill[skillSelect].name == "halfSlash") {
				ui.executeSkill(finalAttack, attackData.criticalYN, skill[skillSelect].name); //res.criticalYN으로 하면 아래서 바꿔도 인수 넣은 시점으로 구분해서 바뀌지 않음.
				return;
			}
			if (skill[skillSelect].name == "bladeOfOath") {
				ui.executeSkill(finalAttack, res.criticalYN, skill[skillSelect].name);
				return;
			}
			ui.executeSkill(finalAttack, res.criticalYN, skill[skillSelect].name);
			return;
		case (int)referenceStatus::maxHp:
			if (skill[skillSelect].name == "covenantUltima") {
				ui.activeCovenantUltima();
			}
			ui.executeHeal(static_cast<int>(php * skill[skillSelect].playerMultiplier));
			return;
		case (int)referenceStatus::dispelDebuff:
			ui.executeSkill();
			return;
		case (int)referenceStatus::totalDamageAndAttack:
			ui.executeSkill(finalAttack, res.criticalYN, skill[skillSelect].name);
			return;
		case (int)referenceStatus::contractenhanced: //다음 계약 증폭
			ui.executeContract();
			return;
		case (int)referenceStatus::defenseAttack: //크리티컬 없음 얜
			ui.executeSkill(finalAttack, skill[skillSelect].name);
			return;
		case (int)referenceStatus::takeDamage:
			ui.executeChain();
			return;
		case (int)referenceStatus::dispelDebuffAndMaxHp:
			ui.activeLightofTruth();
			return;
		default:
			return;
	}
}

void battle::passiveSkill(int skillSelect, std::vector<skill> const& skill, attackInfo res) { //false

	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::attackBuff) {
		if (amplifyActivate != true) {
			p->pushBuff(skill[skillSelect].name, static_cast<int>(skill[skillSelect].playerMultiplier * pattack),
				0, 0,this->turn + skill[skillSelect].activeTime, true, false);
			p->updateBuffedStats();
		}
		else { //계약 강화 중이라면
			p->pushBuff(skill[skillSelect].name, static_cast<int>(skill[skillSelect].playerMultiplier * pattack),
				0, 0,this->turn + skill[skillSelect].activeTime + 1, true, true);
			p->updateBuffedStats();
			p->setAmplifyActivate(false);
			amplifyActivate = p->getAmplifyActivate();
		}
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::defenseBuff) {
		p->pushBuff(skill[skillSelect].name, 0, static_cast<int>(skill[skillSelect].playerMultiplier * pdefense),
			0,this->turn + skill[skillSelect].activeTime, true, false);
		p->updateBuffedStats();
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::takeDamage) { //chainOfPact
		if (amplifyActivate != true) {
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else {//계약 강화 중이라면
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime, true, true);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
			p->setAmplifyActivate(false);
			amplifyActivate = p->getAmplifyActivate();
		}
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::notSpecified &&
		skill[skillSelect].name == "contractOfGuardian") { //contractOfGuardian
		if (amplifyActivate != true) { // 강화 전
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime, true, false); //enemyTurn()함수에 관련성 추가 할 것
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else { // 강화 후
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime, true, true); //enemyTurn()함수에 관련성 추가 할 것
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::notSpecified &&
		skill[skillSelect].name == "weaponMaster") { //weaponMaster
		p->pushBuff(skill[skillSelect].name, 0, 0, 0,
			this->turn + skill[skillSelect].activeTime, true, false);
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::totalDamageBuff) {
		int useContract = 0; //이걸 attackenemy로 넘겨서 몇개인지 알아야 최종데미지 10% ~ 60% 까지 계산 가능
		ui.setOverclockUI();
		cin >> useContract;
		if (useContract == 0) {
			return;
		}
		else {
			p->pushBuff(skill[skillSelect].name, 0,
				0, useContract, this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(useContract, 0); 
			ui.executeOverclock();
		}
	}
}

int battle::activeSkill(int skillSelect, std::vector<skill> const& skill, attackInfo res) { //true
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::totalDamage &&
		skill[skillSelect].name != "bladeOfOath" && skill[skillSelect].name != "halfSlash") {
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		
		return attackEnemy(res.criticalYN,
			static_cast<int>(res.criattack * skill[skillSelect].TDMultiplier),
			static_cast<int>(res.attack * skill[skillSelect].TDMultiplier));
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::totalDamage &&
		skill[skillSelect].name == "bladeOfOath") {
		if (amplifyActivate != true) { //기존 bladeOfOath
			return attackEnemy(true,
				static_cast<int>(res.criattack * skill[skillSelect].TDMultiplier),
				static_cast<int>(res.attack * skill[skillSelect].TDMultiplier));
		}
		else {//강화 bladeOfOath
			return attackEnemy(true,
				static_cast<int>(res.criattack * 2.2),
				static_cast<int>(res.attack * skill[skillSelect].TDMultiplier));
		}
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::totalDamage &&
		skill[skillSelect].name == "halfSlash") {
		if (amplifyActivate != true) { //기존 halfSlash
			attackData.criticalYN = ((p->getCritical() + 20) >= res.criticalLine) ? true : false; //치명타율 재설정
			p->pushBuff(skill[skillSelect].name, static_cast<int>(skill[skillSelect].playerMultiplier * pattack),
				0, 0, this->turn + skill[skillSelect].activeTime, true, false);// 1회용 공격력 증가
			p->updateBuffedStats();
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);

			return attackEnemy(res.criticalYN, static_cast<int>(res.criattack), static_cast<int>(res.attack)); // 공격력이 증가한거지 총합데미지가 증가한게 아니라 원본
		}
		else {//강화 halfSlash
			attackData.criticalYN = ((p->getCritical() + 40) >= res.criticalLine) ? true : false; //치명타율 재설정
			p->pushBuff(skill[skillSelect].name, static_cast<int>(skill[skillSelect].playerMultiplier+0.5 * pattack),
				0, 0, this->turn + skill[skillSelect].activeTime, true, true); // 1회용 공격력 증가
			p->updateBuffedStats();
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);

			return attackEnemy(res.criticalYN, static_cast<int>(res.criattack), static_cast<int>(res.attack));// 공격력이 증가한거지 총합데미지가 증가한게 아니라 원본
		}
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::maxHp &&
		skill[skillSelect].name == "covenantUltima") {
		if (amplifyActivate != true) { // 강화 전
			p->setPlayer_current_health(std::min(p->getPlayer_health(), static_cast<int>(cphp + (php * skill[skillSelect].playerMultiplier))));
			cphp = p->getPlayer_current_health();
			p->pushBuff(skill[skillSelect].name, 0,
				0, 0, this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else { // 강화 후
			p->setPlayer_current_health(std::min(p->getPlayer_health(), static_cast<int>(cphp + (php * 0.65))));
			cphp = p->getPlayer_current_health();
			p->pushBuff(skill[skillSelect].name, 0,
				0, 0, this->turn + skill[skillSelect].activeTime, true, true);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::maxHp) { 
		p->setPlayer_current_health(std::min(p->getPlayer_health(), static_cast<int>(cphp + (php * skill[skillSelect].playerMultiplier))));
		cphp = p->getPlayer_current_health();
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::dispelDebuff) { 
		p->setDebuff(0);//none
		debuff = p->getDebuff();
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::contractenhanced) {
		p->setAmplifyActivate(true);
		amplifyActivate = p->getAmplifyActivate();
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::defenseAttack) {
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		
		return attackEnemy(false, 0, static_cast<int>(
			skill[skillSelect].playerMultiplier * (pdefense + (pdefense * skill[skillSelect].playerMultiplier))));
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::totalDamageAndAttack) {
		skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		return attackEnemy(res.criticalYN,
			static_cast<int>(res.criattack) * skill[skillSelect].TDMultiplier,
			static_cast<int>(res.attack) * skill[skillSelect].TDMultiplier);
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::dispelDebuffAndMaxHp) {//theLightOfTruth
		if (amplifyActivate != true) { //기본
			p->setDebuff(0);//none
			debuff = p->getDebuff();
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else { //강화 중
			p->setDebuff(0);//none
			debuff = p->getDebuff();
			p->pushBuff(skill[skillSelect].name, 0, 0, 0,
				this->turn + skill[skillSelect].activeTime + 1, true, true); //남은 턴 +1
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
	}
	if ((int)skill[skillSelect].referenceStatus == (int)referenceStatus::notSpecified) {
		if (skill[skillSelect].name == "im") {
			p->pushImSlashYou(skill[skillSelect].name, 0,
				0, 0, this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else if (skill[skillSelect].name == "slash") {
			bool check = false;
			for (const auto i: p->getImSlashYou()) {
				if (i.name == "im") {
					check = true;
					break;
				}
			}
			if (check == false) { return 0;}
			p->pushImSlashYou(skill[skillSelect].name, 0,
				0, 0, this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
		}
		else if (skill[skillSelect].name == "you") {
			bool check = false;
			for (const auto i : p->getImSlashYou()) {
				if (i.name == "im") {
					check = true;
					break;
				}
			}
			if (check == false) { return 0; }
			p->pushImSlashYou(skill[skillSelect].name, 0,
				0, 0, this->turn + skill[skillSelect].activeTime, true, false);
			skillCost(skill[skillSelect].contractCost, skill[skillSelect].mpCost);
			return attackEnemy(false, 0,
				static_cast<int>(ehp* skill[skillSelect].playerMultiplier));
		}
	}
	return 0;
}

int battle::attackEnemy(bool criticalYN,int criattack, int attack, float totalDamageBuff) {
	// 특수 버프 적용
	if (totalDamageBuff <= 1.1f) {
		for (const auto& b : p->getBuff()) {
			if (b.name == "overclock" && b.active) {
				totalDamageBuff += 0.1f * b.stack;
			}
		}
	}
	if(p->getClassName() == "tiferet" && p->getLevel() >= 10){
		for (const auto& i : p->getImSlashYou()) {
			if (i.name == "you" && i.active) { // 이 기술엔 최종데미지 버프 안붙음
				totalDamageBuff = 1.0f;
				break;
			}
		}
	}

	// 최대 1.6배 제한
	totalDamageBuff = std::min(totalDamageBuff, 1.6f);

	int baseDamage = criticalYN ? criattack : attack;
	echp = e->enemyTakeDamage(echp, static_cast<int>(baseDamage * totalDamageBuff)); //소수점 이하 버림,크리티컬시 1.3배
	e->setEnemyCurrentHealth(echp);
	return static_cast<int>(baseDamage * totalDamageBuff);
}

attackInfo battle::atkInfo() {
	attackData.criticalYN = false;
	std::uniform_int_distribution<unsigned int> dmg(pattack - 2, pattack + 1);
	std::uniform_real_distribution<float> randomDmg(0.05, 0.1);
	std::uniform_int_distribution<unsigned int> cri(1, 100);

	attackData.criticalLine = cri(gen);
	if (attackData.criticalLine <= p->getCritical()) {
		attackData.criticalYN = true;
	}
	int damage = dmg(gen);
	float randomDamage = randomDmg(gen);
	attackData.attack = static_cast<int>(damage + (damage * (damage * randomDamage)));
	attackData.criattack = static_cast<int>(attackData.attack * 1.3);

	return attackData; // 구조체 통째로 반환
}

void battle::skillCost(int contractCost, int mpCost) { //이 skillCost 자체가 tiferet.cpp의 기능이라 battle.cpp엔 함수로 불러와야하는데 잘못 만듦
	bool activeWeaponMaster = false;
	if (p->getClassName() == "tiferet" && level > 8) {
		for (const auto b : p->getBuff()) {
			if (b.name == "weaponMaster" && b.active) {
				activeWeaponMaster = true;
			}
		}
	}
	if (contractCost == 0 && mpCost == 0) {//teferit의 계약 스킬 제외
		//없음
	}
	else if (contractCost == 0 && mpCost > 0) {//teferit의 계약 스킬 제외
		p->setCurrent_mana(std::max(0, current_mana - mpCost));
		current_mana = p->getCurrent_mana();
	}
	else if (contractCost > 0 && activeWeaponMaster == true) { // 계약 스킬
		p->setContract(std::max(0, contract - (contractCost -1)));
		contract = p->getContract();
	}
	else if (contractCost > 0 && mpCost == 0) { // 계약 스킬
		p->setContract(std::max(0, contract - contractCost));
		contract = p->getContract();
	}
}

