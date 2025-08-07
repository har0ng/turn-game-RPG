//magician.cpp

#include <iostream>
#include "main.h"

using std::cout;
using std::cin;

magician::magician(): magician_health(getPlayer_health()+5)// 35
					 ,magician_attack(getBasic_attack()+1)// 6
					 ,magician_defense(getPlayer_defense()+1)// 6
					 ,magician_mana(25)// 25
{}