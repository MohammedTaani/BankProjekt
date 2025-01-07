#pragma once
#include "clsMainUser.h"
#include "clsDate.h"
#include <iostream>

using namespace std;

class clsScreen
{

protected:


	static void MainScreen(string Print) {

		cout << setw(37) << left << "" << "-------------------------------------------\n";
		cout << setw(37) << left << "\t\t" << Print << endl;
		cout << setw(37) << left << "" << "-------------------------------------------\n";

		cout << left << setw(37) << "" << "User : " << MainUser.GetUserName() << endl;
		cout << left << setw(37) << "" << "Date : " << clsDate::GetHeutigeDate() << endl;
		cout << setw(37) << left << "" << "-------------------------------------------\n";




	}


public:


	static  string UserName() {
		return MainUser.GetUserName();
	}

};

