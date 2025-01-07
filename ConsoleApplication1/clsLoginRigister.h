#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "clsMainUser.h"
#include "clsString.h"

using namespace std;

class clsLoginRigister
{

	string _User;
	string _Date;
	string _DieZeit;
	string _Password;
	int _Permissions;

	static string _SammelnDieInfo(string Dilimter = "#//#") {

		string User = MainUser.GetUserName();
		string Date = clsDate::GetHeutigeDate();
		string DieZeit = clsDate::DieZeit();
		string Password = MainUser.Password;

		//Incription Password in the File
		string S0 = clsUtil::Incription(Password, 8);

		int Permissions = MainUser.Permissions;

		string S1 = Date + Dilimter + DieZeit + Dilimter + User + Dilimter + S0 + Dilimter + to_string(Permissions);

		return S1;

	}

	static void _UserRigister() {

		fstream RigisterFile;
		RigisterFile.open("UsersRigister.txt", ios::out | ios::app);



		if (RigisterFile.is_open()) {


			RigisterFile << _SammelnDieInfo() << endl;

			RigisterFile.close();

		}


	}

	static vector <clsLoginRigister> _GetAlleUserRigisterVonFile() {

		fstream RigisterFile;
		RigisterFile.open("UsersRigister.txt", ios::in);

		vector <clsLoginRigister> AlleUsersInVector;

		string S1 = "";

		if (RigisterFile.is_open()) {

			while (getline(RigisterFile, S1)) {

				clsLoginRigister User = _SplitUserRigisterString(S1, "#//#");

				AlleUsersInVector.push_back(User);

			}

			RigisterFile.close();

		}


		return AlleUsersInVector;

	}

	static clsLoginRigister _SplitUserRigisterString(string Line ,string Seperator) {

		vector <clsLoginRigister> AlleSatzeInVectorZuWord;

		vector<string> vLoginRigisterData;
		vLoginRigisterData = clsString::SplitString(Line, Seperator);

		//Decription Password in the File
		string S1 = clsUtil::Decription(vLoginRigisterData[3], 8);

		return clsLoginRigister(vLoginRigisterData[0], vLoginRigisterData[1], vLoginRigisterData[2], S1, vLoginRigisterData[4]);
		
	}

public:

	clsLoginRigister(string User, string Date, string DieZeit, string Password, string Permissios) {

		_User = User;

		_Date = Date;

		_DieZeit = DieZeit;

		_Password = Password;

		_Permissions = stoi(Permissios);


	}

	static void SaveUserRigisterInfo() {

		_UserRigister();

	}

	static vector <clsLoginRigister> GetAlleUserRigister() {

		return _GetAlleUserRigisterVonFile();
		

	}

	string GetUser() {

		return _User;

	}


	string GetDate() {

		return _Date;

	}



	string GetDieZeit() {

		return _DieZeit;

	}


	string GetPassword() {

		return _Password;

	}


	 int GetPermissions() {


		return _Permissions;

	};

};

