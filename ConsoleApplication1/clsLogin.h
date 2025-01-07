#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsMainUser.h"
#include "clsMainScreens.h"
#include "clsLoginRigister.h"


class clsLogin:protected clsScreen
{

	static void _Login() {

		string UserName, Password;

		int Counter = 3;

		do {

			cout << "Schreiben Sie bitte UserName : ";
			UserName = clsString::ReadString();
			cout << "Schreiben Sie bitte Password : ";
			Password = clsString::ReadString();

			MainUser = clsUsers::Find(UserName, Password);


			if (!MainUser.IsEmpty()) {

				break;

			}
			else {


				Counter--;


				cout << "Falsch , versuchen Sie noch mal bitte!!!\n";
				cout << "Sie haben noch " << Counter << " mal ubrig\n";

				if (Counter == 0) {

					cout << "Sie haben drei mal ihre Informationen falsch geschrieben\n";

					Stop = true;

					return;

				}
			
			}


		} while (0 != 1);


		clsLoginRigister::SaveUserRigisterInfo();
		

		clsMainScreen::PrintMainMeneu();

	}

public:


	static void LogingScreen() {

		system("cls");
		

		cout << setw(37) << left << "" << "===========================================\n";
		MainScreen("Login Screen");
		cout << setw(37) << left << "" << "===========================================\n";

		_Login();


	}



};

