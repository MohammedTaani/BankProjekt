#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include "clsDate.h"
#include <ctime>
#include <iomanip>

using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(int from, int to, int TheNumber) {

		return (TheNumber >= from && TheNumber <= to);


	}

	static bool IsNumberBetween(double from, double to, double TheNumber) {

		return (TheNumber >= from && TheNumber <= to);


	}

	static bool IsDateBetween(clsDate Date, clsDate from, clsDate to) {


		if (clsDate::IstDate1AfterDate2(from, to)) {

			clsDate::SwapClsDate(from, to);

		}

		return (clsDate::IstDate1AfterDate2(Date , from) && clsDate::IstDate1BeforeDate2(Date , to));

	}

	static int ReadIntNumber(string Message = "Falsch!!! versuchen Sie noch mal : ") {


		int x = 0;

		cin >> x;

		while (cin.fail()) {

			cin.clear();

			cin.ignore(numeric_limits <streamsize>::max(), '\n');

			cout << Message << endl;
		
			cin >> x;

		}

		return x;

	}

	static int ReadIntNumberBetween(int from, int to, string Message) {

		int x = ReadIntNumber();

		while (x < from || x > to) {

			cout << Message << endl;

			x = ReadIntNumber();



		}

		return x;
	}

	static double ReadDoubleNumber(string Message = "Falsch , versuchen Sie noch mal!") {


		double x = 0;

		cin >> x;

		while (cin.fail()) {

			cin.clear();

			cin.ignore(numeric_limits <streamsize>::max(), '\n');

			cout << Message << endl;

			cin >> x;

		}

		return x;

	}

	static double ReadIntNumberBetween(double from, double to, string Message) {

		double x = ReadIntNumber("Invalid Number!!");

		while (x < from && x > to) {

			cout << Message << endl;

			x = ReadIntNumber("Invaled Number");



		}

		return x;
	}

	static bool IstVaildDate(clsDate Date) {

		return clsDate::IstVaild(Date);

	}


};

