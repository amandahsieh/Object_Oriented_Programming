#include "role.h"
#include <string>
#include <iostream>
using namespace std;

Role::Role(string roleID, int roleLevel, int roleMoney, int roleHp): ID(roleID), level(roleLevel), money(roleMoney), hp(roleHp){
	this->ID = roleID;
	this->level = roleLevel;
	this->money = roleMoney;
	this->hp = roleHp;
}
string Role::getID() {
	// TODO : refer to spec
	return this->ID;
}
void Role::printAllInfo() {
	// TODO : refer to spec
	cout << "ID is : " << this->ID << endl;
	cout << "Level is : " << this->level << endl;
	cout << "Money is : " << this->money << endl;
	cout << "Hp is : " << this->hp << endl;
}


