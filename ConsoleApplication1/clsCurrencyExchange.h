#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyExchange :public clsScreen
{

	enum eCurrencyChoises{eListCurrency = 1 , eFindCurrency = 2 , eUpdateRate = 3 , eCurrencyCalculater = 4 , eMainMenue = 5};

	static eCurrencyChoises _WahlenSieBitteEineNummer() {

		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Falsch!!! Enter Number between 1 to 5? ");
		return eCurrencyChoises(Choice);

	}

	static void _DruckenGefundeneCurrency(clsCurrency GefundeneCurrency) {

		cout << setw(37) << left << "" << "========================================================\n";
		cout << setw(37) << left << "" << "Land : " << GefundeneCurrency.GetLand() << endl;
		cout << setw(37) << left << "" << "Rate($) : " << GefundeneCurrency.GetRate() << endl;
		cout << setw(37) << left << "" << "Currency Name : " << GefundeneCurrency.GetCurrencyName() << endl;
		cout << setw(37) << left << "" << "Code : " << GefundeneCurrency.GetCurrencyCode() << endl;
		cout << setw(37) << left << "" << "========================================================\n";


	}

	static void _WelcheScreen(eCurrencyChoises TheChoise) {

		switch (TheChoise)
		{
		case clsCurrencyExchange::eListCurrency:

			_ListCurrencys();

			_clsCurrencyExchangeScreen();

			break;

		case clsCurrencyExchange::eFindCurrency:

			_FindCurrency();

			_clsCurrencyExchangeScreen();

			break;

		case clsCurrencyExchange::eUpdateRate:

			_UpdateRate();

			_clsCurrencyExchangeScreen();

			break;

		case clsCurrencyExchange::eCurrencyCalculater:

			_CurrencyCalculater();

			_clsCurrencyExchangeScreen();

			break;

		case clsCurrencyExchange::eMainMenue:

			_MainMenue();

			break;

		default:
			break;
		}

	}

	static void _OneCurrencyDrucken(clsCurrency C) {

		cout << left << "\t\t" << "|" << setw(27) << C.GetLand();
		cout << left << "|" << setw(15) << C.GetCurrencyCode();
		cout << left << "|" << setw(40) << C.GetCurrencyName();
		cout << left << "|" << setw(20) << C.GetRate() << endl;

	}

	static void _ListCurrencys() {

		system("cls");

		vector <clsCurrency> AllCurrencyFromTheFile = clsCurrency::LoadAlleCurencyData();


		cout << left << "\t\t============================================================================\n";


		cout << left << setw(15) << "|" << "Currency Zahl (" << AllCurrencyFromTheFile.size() << ")" << endl;
		MainScreen("List Currency Screen");
		

		cout << left << "\t\t" << "|" << setw(27) << "Land";
		cout << left << "|" << setw(15) << "Currency Code";
		cout << left << "|" << setw(40) << "Currency Name";
		cout << left << "|" << setw(20) << "Rate" << endl;

		if (AllCurrencyFromTheFile.size() == 0) {

			cout << "Es gibt kein Currency!!" << endl;

			return;

		}


		for (clsCurrency& C : AllCurrencyFromTheFile) {

			_OneCurrencyDrucken(C);

		}

		cout << "\t\t=====================================================================================\n";


		cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
		system("pause > 0");


	}

	static void _FindCurrency() {


		system("cls");

		short x = 0;
		cout << setw(37) << left << "Wollen Sie den Currency beim [1] Code oder beim [2] Land finden : ";
		x = clsInputValidate::ReadIntNumberBetween(1 , 2 , "Falsch!!! 1 oder 2 ? ");

		if (x == 1) {
			

			cout << setw(37) << left << "Schreiben Sie bitte das Code : ";


			string Code = clsString::ReadString();

			clsCurrency C = clsCurrency::FindBeiCode(Code);

			_DruckenGefundeneCurrency(C);

		}
		else if (x == 2) {


			cout << setw(37) << left << "Schreiben Sie bitte das Land : ";

			string Land = clsString::ReadString();

			clsCurrency C = clsCurrency::FindBeiLand(Land);

			_DruckenGefundeneCurrency(C);

		}


		cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
		system("pause > 0");


	}

	static void _UpdateRate() {


		system("cls");

		vector <clsCurrency> AllCurrencyFromTheFile = clsCurrency::LoadAlleCurencyData();

		string Code = "";
		bool JaOderNein = true;

		do {

			if (JaOderNein == false) {

				cout << "Falsche Code !!!\n";

			}

			cout << setw(37) << left << "Schreiben Sie bitte den Code : ";
			Code = clsString::ReadString();

			JaOderNein == false;

		} while (!clsCurrency::IstCurrencyExictiert(Code));


		


		for (clsCurrency& C : AllCurrencyFromTheFile) {

			if (C.GetCurrencyCode() == clsString::ToUpper(Code)) {

				_DruckenGefundeneCurrency(C);

				float NeueRate = 0;
				cout << "Schreiben Sie bitte den neuen Wert des Rates : ";
				NeueRate = clsInputValidate::ReadDoubleNumber();

				char DasWillIchNicht = 'Y';

				cout << "Wollen Sie den Wert des Rates andern (Y/N) ? ";
				cin >> DasWillIchNicht;

				if (DasWillIchNicht == 'N' || DasWillIchNicht == 'n') {

					cout << "Der Wert wird nicht verandert.\n";

					break;

				}


				C.Rate = NeueRate;

				C.Update();



				cout << "Die Veranderung wird erfolgreich durchgefuhrt :)\n";

				_DruckenGefundeneCurrency(C);

				break;

			}

		}


		cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
		system("pause > 0");

	}

	static clsCurrency _SuchenCurrency() {

		string Currency = "";
		Currency = clsString::ReadString();

		while (!clsCurrency::IstCurrencyExictiert(Currency)) {

			cout << endl << left << setw(37) << "" << "Currency existiert nicht !! \n";

			cout << endl << left << setw(37) << "" << "Versuchen Sie es noch mal : ";
			Currency = clsString::ReadString();

		}

		clsCurrency C = clsCurrency::FindBeiCode(Currency);


		return C;

	}

	static void _CurrencyCalculater() {


		system("cls");

		MainScreen("Currency Calculater Screen");

		vector <clsCurrency> AllCurrencyFromTheFile = clsCurrency::LoadAlleCurencyData();


		/* Find Currency 1 */
		cout << endl << left << setw(37) << "" << "Schreiben Sie bitte Currency1 : ";
		clsCurrency Currency1 = _SuchenCurrency();

		/* Find Currency 2 */
		cout << endl << left << setw(37) << "" << "Schreiben Sie bitte Currency2 : ";
		clsCurrency Currency2 = _SuchenCurrency();

		float DieSumme = 0;
		cout << endl << left << setw(37) << "" << "Geben Sie Die Summe zum Umtausch : ";
		DieSumme = clsInputValidate::ReadIntNumber();

		cout << endl << left << setw(37) << "" << "Die Umtausch von : " << endl;

		_DruckenGefundeneCurrency(Currency1);

		float DieSummeInDoller = DieSumme / Currency1.GetRate();

		cout << endl << left << setw(37) << "" << DieSumme << " " << Currency1.GetCurrencyCode() << " = " << DieSummeInDoller << " USD" << endl;

	
		if (Currency2.GetCurrencyCode() != "USD") {

			cout << endl << left << setw(37) << "" << "Umtausch von USD zu : " << endl;

			_DruckenGefundeneCurrency(Currency2);

			cout << endl << left << setw(37) << "" << DieSumme << " " << Currency1.GetCurrencyCode() << " = " << DieSummeInDoller * Currency2.GetRate() << " " << Currency2.GetCurrencyCode() << endl;


		}


		cout << endl << left << setw(37) << "" << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
		system("pause > 0");

	}

	static void _MainMenue() {


	};


public:

	static void _clsCurrencyExchangeScreen() {

		system("cls");


		MainScreen("Currency Exchange Screen");

		cout << setw(37) << left << "" << "[1] List Currencys\n";
		cout << setw(37) << left << "" << "[2] Find Currency\n";
		cout << setw(37) << left << "" << "[3] Update Rate\n";
		cout << setw(37) << left << "" << "[4] Currency Calculater\n";
		cout << setw(37) << left << "" << "[5] Main Menue\n";
		cout << setw(37) << left << "" << "===================================================\n";

		_WelcheScreen(_WahlenSieBitteEineNummer());

	}

};

