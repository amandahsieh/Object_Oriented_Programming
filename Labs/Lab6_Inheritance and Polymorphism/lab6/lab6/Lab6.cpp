#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main() {
	
	// TODO : Read the file
	// 1. Read the input file to get the imformation
	int num;
	ifstream inputFile;
	ifstream input ("input2.txt");
	input >> num;
	string id[100], who[100];
	int number[100][4] = { 0 };
	//cout << num << endl;
	for (int i = 0; i < num; i++) {
		input >> id[i] >> who[i];
		id[i][id[i].size() - 1] = '\0';
		who[i][who[i].size() - 1] = '\0';
		int j = 0, which = 1, h = 0, tmp = 0;
		for (int j = 0; j < 3; j++) {
			string s;
			input >> s;
			for (unsigned int k = 0; k < s.size() -1; k++) {
				number[i][j] = number[i][j] * 10 + (s[k] - '0');
			}
			if (j == 2)
				number[i][j] = number[i][j] * 10 + (s[s.size() - 1] - '0');
		}
		//cout << id << endl << who << endl << number[0] << "    " << number[1] << "    " << number[2] << endl << endl;
		if (who[i][0] == 'w' || who[i][0] == 'W') {
			Role* warrior = new Warrior(id[i], number[i][0], number[i][1], number[i][2]);
			warrior->printAllInfo();
			warrior->ShowRole();
		}
		else if (who[i][0] == 'm' || who[i][0] == 'M') {
			Role* magician = new Magician(id[i], number[i][0], number[i][1], number[i][2]);
			magician->printAllInfo();
			magician->ShowRole();
		}
		else{
			Role * archer = new Archer(id[i], number[i][0], number[i][1], number[i][2]);
			archer->printAllInfo();
			archer->ShowRole();
		}
		std::cout << endl;
	}
	
	// TODO : Create the Role according to the input file
	// 1. Create the role
	// 2. Print this role's Infomation
	// 3. Show Role ( refer to spec )
	// Example :
	// -------------------------------------------------------
	// Role* warrior = new Warrior( warrior's Name, warrior's Level, warrior's Money, warrior's HP);
	// warrior->printAllInfo();
	// warrior->ShowRole();
	// cout << endl;
	// 
	// Role* archer = new Archer(archer's Name, archer's Level, archer's Money, archer's HP);
	// archer->printAllInfo();
	// archer->ShowRole();
	// cout << endl;
	// 
	// Role* magician = new Magician(magician's Name, magician's Level, magician's Money, magician's HP);
	// magician->printAllInfo();
	// magician->ShowRole();
	// cout << endl;
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles


	Staff* staff = new Staff("flame");
	std::cout << "Checking whether the role can equip a staff.." << endl;
	for (int i = 0; i < num; i++) {
		if (who[i][0] == 'w' || who[i][0] == 'W') {
			Role* warrior = new Warrior(id[i], number[i][0], number[i][1], number[i][2]);
			staff->equipable(warrior);
		}
		else if (who[i][0] == 'm' || who[i][0] == 'M') {
			Role* magician = new Magician(id[i], number[i][0], number[i][1], number[i][2]);

			staff->equipable(magician);
		}
		else {
			Role* archer = new Archer(id[i], number[i][0], number[i][1], number[i][2]);
			staff->equipable(archer);
		}
		//cout << endl;
	}
	//
	// TODO : Check wheather all characters can get staff or not
	// Example :
	// -------------------------------------------------------
	// staff->equipable(warrior);
	// staff->equipable(archer);
	// staff->equipable(magician);
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	std::cout << endl;




	std::system("PAUSE");
	return 0;
}