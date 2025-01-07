#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>

using namespace std;

class clsCurrency
{

	enum enMode { enEmptyCurrency = 1, enUpdateCurrency = 2 };

	enMode _Mode;

	string _Land;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _LineToclsCurrency(string S1) {

		vector <string> TimpCurrency = clsString::SplitString(S1 , "#//#");

		return clsCurrency(enMode::enUpdateCurrency, TimpCurrency[0], TimpCurrency[1], TimpCurrency[2], stof(TimpCurrency[3]));

	}

	static vector <clsCurrency> _AlleCurrencyVonFile() {

		fstream CurrencyFile;

		CurrencyFile.open("Currencies.txt", ios::in);

		vector <clsCurrency> AlleCurrency;

		string S1 = "";

		if (CurrencyFile.is_open()) {

			while (getline(CurrencyFile, S1)) {

				clsCurrency EinCurrency = _LineToclsCurrency(S1);

				AlleCurrency.push_back(EinCurrency);

			}


			CurrencyFile.close();
		}

		return AlleCurrency;

	}

	static clsCurrency _ReturnEmptyCurrency() {

		return clsCurrency(enMode::enEmptyCurrency, "", "", "", 0);

	}

	static string _VonClsCurrencyZuString(clsCurrency C , string Speretor = "#//#") {

		string S1 = C._Land + Speretor + C._CurrencyCode + Speretor + C._CurrencyName + Speretor + to_string(C._Rate);

		return S1;

	}

	static void _SaveAlleCurrencyInFile(vector <clsCurrency> AlleCurrencys) {

		fstream OpenFile("Currencies.txt", ios::out);

		if (OpenFile.is_open()) {

			string S1 = "";

			for (clsCurrency C : AlleCurrencys) {

				S1 = _VonClsCurrencyZuString(C);

				OpenFile << S1 << endl;

			}

			OpenFile.close();

		}

	}

	 void _Update() {

		vector <clsCurrency> AlleCurrency = _AlleCurrencyVonFile();

		for (clsCurrency& C : AlleCurrency) {

			if (C._CurrencyCode == _CurrencyCode) {

				C = *this;
				
				break;

			}

		}

		_SaveAlleCurrencyInFile(AlleCurrency);

	}



public:

	clsCurrency(enMode Mode , string Land, string CurrencyCode, string CurrencyName, float Rate) {

		_Mode = Mode;

		_Land = Land;

		_CurrencyCode = CurrencyCode;

		_CurrencyName = CurrencyName;

		_Rate = Rate;

	}

	string GetLand() {
		return _Land;
	}


	string GetCurrencyCode() {
		return _CurrencyCode;
	}

	string GetCurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float Rate) {
		_Rate = Rate;
	}
	float GetRate() {
		return _Rate;
	}

	__declspec(property(get = GetRate, put = UpdateRate)) float Rate;

	 bool IstEmpty() {
		
		 return (_Mode == enMode::enEmptyCurrency);

	}

	 static bool IstCurrencyExictiert(string CurrencyCode) {

		 clsCurrency C1 = FindBeiCode(CurrencyCode);

		 return (!C1.IstEmpty());

	 }


	 static clsCurrency FindBeiCode(string CurrencyCode) {

		 CurrencyCode = clsString::ToUpper(CurrencyCode);

		 vector <clsCurrency> AlleCurrencys = _AlleCurrencyVonFile();

		 for (clsCurrency& C : AlleCurrencys) {

			 if (C._CurrencyCode == CurrencyCode) {

				 return C;

			 }

		 }

		 return _ReturnEmptyCurrency();

	 }

	 static clsCurrency FindBeiLand(string CurrencyLand) {

		 CurrencyLand = clsString::ToUpper(CurrencyLand);

		 vector <clsCurrency> AlleCurrencys = _AlleCurrencyVonFile();

		 for (clsCurrency C : AlleCurrencys) {

			 if (clsString::ToUpper(C._Land) == CurrencyLand) {

				 return C;

			 }

		 }

		 return _ReturnEmptyCurrency();

	 }

	 static vector <clsCurrency> LoadAlleCurencyData() {

		 return _AlleCurrencyVonFile();

	 }

	
	 void Update() {

		 return _Update();

	 }


};

