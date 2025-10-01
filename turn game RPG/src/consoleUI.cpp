//consoleUI.cpp

#include "consoleUI.h"
#include <iostream>
#include <iomanip> // setw, left, right 줄 맞추기
using std::endl;
using std::cout;
using std::cin;

void consoleUI::battleStatus(int turn, int php, int cphp, int pattack, int pdefense
                            , std::string enemyType, int ehp,int echp ,int eattack, int level, int level_exp
                            ,int now_exp, int mana, int current_mana, std::string debuff, std::vector<buff> buffs
                            ,int buffAttack, int buffDefense, std::string className) {
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << turn << " turn" << endl;
    cout << "*player";
    if (className == "player") {
        cout << "(" << "common" << ")";
    } //debug
    else {
        cout << "(" << className << ")";
    }
    cout << "\n Lv: " << level << " ,exp: " << now_exp << "/" << level_exp
            << "\n hp: " << cphp << "/" << php << "\n mp: " << current_mana << "/" << mana
            << "\n power: " << pattack;
  
    if (buffAttack != 0) {
        cout << "(" << buffAttack << "↑" << ")";
        }
    cout << "\n defense: " << pdefense;
        if (buffDefense != 0) {
            cout << "(" << buffDefense << "↑" << ")";
        }
    cout << "\n debuff: " << debuff;
    cout << "\n buff: ";
    for (auto it = buffs.begin(); it != buffs.end(); ++it) {
        if (it == prev(buffs.end()) && it->active) {
            cout << it->name << endl;
        }
        else if (it->active) {
            cout << it->name << ", ";
        }
    }
    cout << endl;
    cout << "*enemy" << "(" <<enemyType << ")" << endl;
    cout << " hp: " << echp <<"/" << ehp << "\n power : " << eattack << endl;
    cout << endl;
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::battleStatus(int turn, int php, int cphp, int pattack, int pdefense, int contract, 
                             std::string enemyType, int ehp, int echp, int eattack, int level, int level_exp, int now_exp, int mana,
                             int current_mana, std::string debuff, std::vector<buff> buffs, std::vector<buff>imSlashYou,
                             int buffAttack, int buffDefense, std::string className, bool amplifyActivate){
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << turn << " turn" << endl;
    cout << "*player";
    cout << "(" << className << ")";
    cout << "\n Lv: " << level << " ,exp: " << now_exp << "/" << level_exp
        << "\n hp: " << cphp << "/" << php << "\n mp: " << current_mana << "/" << mana
        << "\n contract: " << contract;
    if (amplifyActivate == true) {
        cout << "(強化状態)";
    }
    cout << "\n power: " << pattack;

    if (buffAttack != 0) {
        cout << "(" << buffAttack << "↑" << ")";
    }
    cout << "\n defense: " << pdefense;
    if (buffDefense != 0) {
        cout << "(" << buffDefense << "↑" << ")";
    }
    cout << "\n debuff: " << debuff;
    cout << "\n buff: ";
    for (auto it = buffs.begin(); it != buffs.end(); ++it) {
        if (it == prev(buffs.end()) && it->active) {
            cout << it->name << endl;
        }
        else if(it->active){
            cout << it->name << ", ";
        }
    }
    if (!imSlashYou.empty()) {
        cout << "\n 契約: ";
        for (auto it = imSlashYou.begin(); it != imSlashYou.end(); ++it) {
            if (it == prev(imSlashYou.end()) && it->active) {
                cout << it->name << endl;
            }
            else if (it->active) {
                cout << it->name << ", ";
            }
        }
    }
    cout << endl;
    cout << "*enemy" << "(" << enemyType << ")" << endl;
    cout << " hp: " << echp << "/" << ehp << "\n power : " << eattack << endl;
    cout << endl;
    cout << "========== Battle Status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::playerTurnUI() {
    cout << "========== playerTurn Start ==========\n" << endl;
    cout << "select player Action" << endl;
    cout << "(1)attack  " << "  (2)defense" << "  (3)skill" << endl;
}

void consoleUI::playerTurn(int cphp, int pdefense, int battleselect, int finalAttack, bool criticalYN) {
    if (battleselect == 1 && criticalYN == false) {
        cout << "attack enemy!" << endl;
        cout << "enemy takes " << finalAttack << " damage." << endl;
    }
    else if(battleselect == 1 && criticalYN == true){
        cout << "attack enemy!" << endl;
        cout << "critical!!" << "\n enemy takes " << finalAttack << " damage." << endl;
    }
    else if (battleselect == 2) {
        cout << "defense body" << endl;
        cout << "hp : " << cphp << "/(defensed)+" << pdefense << endl;
    }
    cout << "\n========== playerTurn End ==========" << endl;
    cout << endl;
    cout << endl;

}


void consoleUI::showSkill(int skillSize, std::string charactorClass, std::string name,int contract ,int contractCost,
                          int mpCost, int current_mana, int activeTime, int turn, int enemyCnt) {
    if (contractCost == 0 && current_mana >= mpCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << mpCost << endl;
    }
    else if (contractCost == 0 && current_mana < mpCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << "Mp不足" << endl;
    }
    else if (contractCost > 0 && contract >= contractCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " contract: " << contractCost << endl;
    }
    else if (contractCost > 0 && contract < contractCost) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " contract: " << "契約できません。" << endl;
    }

}

void consoleUI::showSkill(int skillSize, std::string name, int remainturn, int mpCost, int contractCost){
    if (mpCost > 0) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " MP: " << mpCost
            << " CT: " << remainturn << endl;
    }
    else if (contractCost > 0) {
        cout << skillSize << ". "
            << std::left << std::setw(20) << name
            << " contract: " << contractCost
            << " CT: " << remainturn << endl;
    }
}

void consoleUI::exitSkill(int back) {
    cout << endl;
    cout << endl;
    cout << back << ". " << "back" << endl;
}

void consoleUI::executeSkillAtk(int pattack, int activeTime){
    cout << activeTime << "turnの間powerが" << pattack << "あがります。" << endl;
}

void consoleUI::executeSkillDef(int pdefense, int activeTime){
    cout << activeTime << "turnの間defenseが" << pdefense << "あがります。" << endl;

}

void consoleUI::executeSkill(){
    cout << "デバフが消えました。" << endl;
}
void consoleUI::executeSkill(int defense, std::string skillName){
    cout << "attack enemy!" << endl;
    cout << "enemy takes " << defense << " damage." << endl;
}
void consoleUI::executeSkill(int finalAttack, bool criticalYN, std::string name){
    cout << name << "を使用しました。" << endl;
    if (criticalYN == true || name == "bladeOfOath") {
        cout << "attack enemy!" << endl;
        cout << "critical!!" << "\n enemy takes " << finalAttack << " damage." << endl;
    }
    else if (criticalYN == false) {
        cout << "attack enemy!" << endl;
        cout << "enemy takes " << finalAttack << " damage." << endl;
    }
    
}
void consoleUI::executeHeal(int heal) {
    cout << "HPを " << heal << " 回復しました。" << endl;
}

void consoleUI::skillMpcostRetry(){
    cout << "MPがないです！もう一度入力してください。" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::skillCoolTimeRetry(){
    cout << "まだこのスキルは使用できません。もう一度入力してください。" << endl;
}

void consoleUI::skillContractCostRetry(){
    cout << "contractが足りなくて契約できません！" << endl;
}


void consoleUI::enemyTurn(int enemyAction, int pdefense, int eattack, int battleselect) {
    cout << "========== enemyTurn Start ==========\n" << endl;
    if (enemyAction == 0) {
        cout << "enemy action : assess the situation" << endl;
    }
    else {
        cout << "enemy attacked!" << endl;
        if (battleselect == 2) {
            cout << "Player defends and takes " << eattack << " damage." << endl;
            
        }
        else {
            cout << "Player takes " << eattack << " damage." << endl;
        }
    }
    cout << "\n========== enemyTurn End ==========" << endl;
    cout << endl;
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::battleEnd(int cphp, int exp) {
	cout << "========== Battle End =============" << endl;
	if (cphp <= 0) { // user hp == 0
        cout << "バトルで負け倒れました..." << endl;
	}
    else { //enemy hp == 0
        cout << "バトルで勝ちました！" << endl;
        cout << exp << "経験値を獲得した！" << endl;
        cout << endl;
        cout << endl;
        cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
        cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
        cin.get();
	}
}

void consoleUI::selectClassUI() { // 1레벨 직업 정하기
        cout << endl;
        cout << "========== select Class =============" << endl;
        cout << "select your class!" << "\n (1)tiferet (2)chesed (3)gevurah (4)malkuth (5)yesod (6)binah" << endl;
        cout << "\n(1)tiferet" << endl;
        cout << "max hp + 10 / +1 level : max hp +5" << endl;
        cout << "max mp + 10 / +1 level : max mp +2" << endl;
        cout << "attack + 3  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +2 level : defense + 1" << endl;
        cout << "\n(2)chesed" << endl;
        cout << "max hp + 10 / +1 level : max hp +5" << endl;
        cout << "max mp + 10 / +1 level : max mp +2" << endl;
        cout << "attack + 3  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +2 level : defense + 1" << endl;
        cout << "\n(3)gevurah" << endl;
        cout << "max hp + 5  / +1 level : max hp +2" << endl;
        cout << "max mp + 25 / +1 level : max mp +5" << endl;
        cout << "attack + 1  / +3 level : attack + 1" << endl;
        cout << "defense + 1" << endl;
        cout << "\n(4)malkuth" << endl;
        cout << "max hp + 5  / +1 level : max hp +2" << endl;
        cout << "max mp + 25 / +1 level : max mp +5" << endl;
        cout << "attack + 1  / +3 level : attack + 1" << endl;
        cout << "defense + 1" << endl;
        cout << "\n(5)yesod" << endl;
        cout << "max hp + 4  / +1 level : max hp +2" << endl;
        cout << "max mp + 15 / +1 level : max mp +2" << endl;
        cout << "attack + 4  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +3 level : defense + 1" << endl;
        cout << "agility + 4" << endl;
        cout << "\n(6)binah" << endl;
        cout << "max hp + 4  / +1 level : max hp +2" << endl;
        cout << "max mp + 15 / +1 level : max mp +2" << endl;
        cout << "attack + 4  / +2 level : attack + 1" << endl;
        cout << "defense + 3 / +3 level : defense + 1" << endl;
        cout << "agility + 4" << endl;
}

void consoleUI::selectClass(int level, int selectClass) {
    if (selectClass == 1) {
        cout << "your class is tiferet! " << endl;
    } 
    else if (selectClass == 3) {
        cout << "your class is gevurah! " << endl;
    }
    else if (selectClass == 5) {
        cout << "your class is yesod! " << endl;
    }
    cout << "========== class change =============" << endl;
    cout << endl;
}

void consoleUI::levelup_playerStatus(int php, int cphp, int pattack, int pdefense
                                    ,int level, int level_exp, int now_exp
                                    ,int mana, int current_mana) {
    cout << "========== current player status ==========" << endl;
    cout << "*player\n Lv: " << level << " ,exp: " << now_exp << "/" << level_exp
        << "\n hp: " << cphp << "/" << php << "\n mp: " << current_mana << "/" << mana
        << "\n power: " << pattack << "\n defense: " << pdefense << endl;
    cout << endl;
    cout << "========== current player status ==========" << endl;
}

void consoleUI::enterToContinue() { //enter을 누를시 다음 화면으로 넘어가게끔 조정
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::showStatusChange(playerStatusSnapShot beforePlayer, playerStatusSnapShot afterPlayer) {
    cout << "========== Current Player Status ==========" << endl;
    cout << "* Player" << endl;

    // 헤더
    cout << std::left << std::setw(12) << "Status"
        << std::setw(20) << "Before"
        << "-> "
        << std::setw(20) << "After"
        << endl;

    cout << std::string(60, '-') << endl; // 구분선

    // 레벨 / 경험치
    cout << std::left << std::setw(12) << "Level"
        << std::setw(20) << ("Lv: " + std::to_string(beforePlayer.level) +
            " exp: " + std::to_string(beforePlayer.now_exp) + "/" + std::to_string(beforePlayer.level_exp))
        << "-> "
        << std::setw(20) << ("Lv: " + std::to_string(afterPlayer.level) +
            " exp: " + std::to_string(afterPlayer.now_exp) + "/" + std::to_string(afterPlayer.level_exp))
        << endl;

    // HP
    cout << std::left << std::setw(12) << "HP"
        << std::setw(20) << (std::to_string(beforePlayer.current_health) + "/" + std::to_string(beforePlayer.health))
        << "-> "
        << std::setw(20) << (std::to_string(afterPlayer.current_health) + "/" + std::to_string(afterPlayer.health))
        << endl;

    // MP
    cout << std::left << std::setw(12) << "MP"
        << std::setw(20) << (std::to_string(beforePlayer.current_mana) + "/" + std::to_string(beforePlayer.mana))
        << "-> "
        << std::setw(20) << (std::to_string(afterPlayer.current_mana) + "/" + std::to_string(afterPlayer.mana))
        << endl;

    // Power
    cout << std::left << std::setw(12) << "Power"
        << std::setw(20) << std::to_string(beforePlayer.attack)
        << "-> "
        << std::setw(20) << std::to_string(afterPlayer.attack)
        << endl;

    // Defense
    cout << std::left << std::setw(12) << "Defense"
        << std::setw(20) << std::to_string(beforePlayer.defense)
        << "-> "
        << std::setw(20) << std::to_string(afterPlayer.defense)
        << endl;

    cout << "========== current player status ==========" << endl;
    cout << endl;
    cout << endl;
}

void consoleUI::showGetSkill(std::string name) {
    cout << name << "を習得しました。" << endl;
}

void consoleUI::executeContract() {
    cout << "次の一回に限り契約スキルが強化されます。" << endl;
}

void consoleUI::executeChain(){
    cout << "鎖が掛かりました。" << endl;
}

void consoleUI::activeChain(int enemyTakeDamage, int remainTurn){
    cout << "契約の鎖が発動しました。" << endl;
    cout << "契約の効果で敵が" << enemyTakeDamage << "のダメージを受けました。" << endl;
    cout << "鎖は" << remainTurn << "ターンになる時に消えます。" << endl;
    cout << endl;
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::activeLightofTruth(){
    cout << "2ターンの間デバフにかかりません。" << endl;
}

void consoleUI::activeGuardian(){
    cout << "ガーディアンがプレイヤーの近くを回ります。" << endl;
}

void consoleUI::activeWeaponMaster(){
    cout << "万兵の王の契約が繋がりました。" << endl;
}

void consoleUI::executeGuardian() {
    cout << "========== enemyTurn Start ==========\n" << endl;
    cout << "enemy attacked!" << endl;
    cout << "contractOfGuardianが発動しました。" << endl;
    cout << "攻撃が塞がれました。" << endl;
    cout << "\n========== enemyTurn End ==========" << endl;
    cout << endl;
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::setOverclockUI(){
    cout << "使う契約の数を選んでください。(1~6)" << endl;
    cout << "10%づつ最終ダメージがあがります。(max 60%)" << endl;
    cout << "戻る(0)" << endl;
}

void consoleUI::executeOverclock() {
    cout << "overclockの契約が繋がりました。" << endl;
}

void consoleUI::activeCovenantUltima(){
    cout << "最後の契約が繋がりました。" << endl;
}

void consoleUI::executeCovenantUltima(){
    cout << "========== enemyTurn Start ==========\n" << endl;
    cout << "enemy attacked!" << endl;
    cout << "契約に守られます。" << endl;
    cout << "攻撃が塞がれました。" << endl;
    cout << "\n========== enemyTurn End ==========" << endl;
    cout << endl;
    cout << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}

void consoleUI::activeIm(){
    cout << "契約する。私は" << endl;
}

void consoleUI::activeSlash(){
    cout << "契約する。必ず" << endl;
}


void consoleUI::acitveYou(int finalAttack){
    cout << "契約する。私は必ず切る" << endl;
    cout << "attack enemy!" << endl;
    cout << "enemy takes " << finalAttack << " damage." << endl;
}

void consoleUI::connectMap(int optionNumber, const room& nextRoom) {
    std::cout << optionNumber << ": room ID " << nextRoom.id
        << " / roomType: " << nextRoom.name
        << " / 説明: " << nextRoom.description << "\n";
    cout << endl;
    cout << endl;
}

void consoleUI::restMap(){
    cout << "HPを回復しました。" << endl;
    cout << "Press Enter to continue..." << endl; //사용자 임의대로 화면 넘기기
    cin.ignore();//ignore과 get으로 enter을 쳤을 때 넘어갈 수 있게 조절.
    cin.get();
}
