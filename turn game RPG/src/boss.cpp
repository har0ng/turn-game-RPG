//boss.cpp

#include "enemy.h"
#include <iostream>

using std::cout;
using std::cin;

//not random parameter!

boss::boss(const enemy& e) :enemy(e), gen(rd()) {
}