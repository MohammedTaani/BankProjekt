#pragma once
#include <string>
#include <iostream>
#include "clsDate.h"
#include <iomanip>

using namespace std;


class clsUtil
{


public:

	static void sRand() {

		srand((unsigned)time(NULL));

	}

	static int GetRandomNummer(int from, int to) {

		int RandomNummer = rand() % (to - from + 1) + from;

		return RandomNummer;

	}

	enum enCharType {CapitalLatter = 1 , SmallLatter , Digits , SpicalCaractar , Mix};

	static char getRandomChar(enCharType chartype) {

		switch (chartype)
		{
		case clsUtil::CapitalLatter:
			return char(GetRandomNummer(65, 90));
		case clsUtil::SmallLatter:
			return char(GetRandomNummer(97, 122));
		case clsUtil::Digits:
			return char(GetRandomNummer(48, 57));
		case clsUtil::SpicalCaractar:
			return char(GetRandomNummer(32, 47));
		default:
			getRandomChar(enCharType(GetRandomNummer(1, 4)));
			break;
		}

	}

	static string GenerateWord(enCharType charType , short Wordlenght) {

		string Word = "";

		for (int i = 1; i <= Wordlenght; i++) {

			Word += getRandomChar(charType);

		}

		return Word;

	}

	static string GenerateKey(enCharType charType) {

		string Key = "";

		for (int i = 1; i <= 4; i++) {

			Key += GenerateWord(charType, 4) + "-";

		}

		Key = Key.substr(0, Key.length() - 1);

		return Key;

	}

	static string Formating(short number) {

		if (number < 10)
			return "     : ";

		else if (number < 100)
			return "    : ";

		else if (number < 1000)
			return "   : ";

		else if (number < 10000)
			return "  : ";

		else if (number < 100000)
			return " : ";

	}

	static void GenerateKeys(short KeysNummer, enCharType charType) {

		for (int i = 1; i <= KeysNummer; i++) {

			cout << "[" << i << "]" << Formating(i) << GenerateKey(charType) << endl;

		}



	}

	static void swap(int& number1, int& number2)
	{
		int temp;

		temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(double& number1, double& number2)
	{
		double temp;

		temp = number1;
		number1 = number2;
		number2 = temp;
	}

	static void swap(bool& flag1, bool& flag2)
	{
		bool temp;

		temp = flag1;
		flag1 = flag2;
		flag2 = temp;
	}

	static void swap(string& text1, string& text2)
	{
		string temp;

		temp = text1;
		text1 = text2;
		text2 = temp;
	}

	static void swap(clsDate& date1, clsDate& date2)
	{
		clsDate tempDate;

		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	static void SwapArray(int arr[] , int lenght) {

		for (int i = 1; i <= lenght; i++) {


			swap(arr[GetRandomNummer(0, lenght -1)], arr[GetRandomNummer(0, lenght-1)]);

		}

	}

	static void SwapArray(string arr[], int lenght) {

		for (int i = 0; i < lenght; i++) {

			swap(arr[GetRandomNummer(0, lenght - 1)], arr[0, lenght - 1]);

		}

	}

	static void FillArrayWithRandomNummbers(int arr[], int lenght, int from, int to) {

		for (int i = 0; i < lenght; i++) {

			arr[i] = GetRandomNummer(from, to);

		}

	}

	static void FillArrayWithRandomWords(string arr[], enCharType CharType, int Lenght) {

		for (int i = 0; i < Lenght; i++) {

			arr[i] = GenerateWord(CharType, Lenght);

		}

	}

	static string Incription(string text, short key) {

		string IncriptionText = "";

		for (int i = 0; i < text.length(); i++) {

			IncriptionText += text[i] + key;

		}

		return IncriptionText;

	}

	static string Decription(string text, short key) {

		string DecriptionText = "";

		for (int i = 0; i < text.length(); i++) {

			DecriptionText += text[i] - key;

		}

		return DecriptionText;

	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}


};

