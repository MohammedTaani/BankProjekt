#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{

private:
	string _Value;

public:

	clsString() {
		_Value = "";
	}

	clsString(string S1) {

		_Value = S1;

	}

	void SetValue(string S1) {

		_Value = S1;

	}

	string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;


	static short CounterWords(string S1) {


		string Dilimiter = " ";
		int pos = 0;
		string Word = "";
		int counter = 0;

		while ((pos = S1.find(Dilimiter)) != std::string::npos) {

			Word = S1.substr(pos);

			if (Word != "") {
				counter++;
			}

			S1.erase(0, pos + Dilimiter.length());

		}

		if (S1 != "") {
			counter++;
		}

		return counter;

	}

	short CounterWords() {


		return CounterWords(_Value);

	}

	static string ToLower(string S1) {

		for (int i = 0; i < S1.length(); i++) {

			S1[i] = tolower(S1[i]);

		}
		
		return S1;

	}

	void ToLower() {

		_Value = ToLower(_Value);

	}

	static string ToUpper(string S1) {

		for (int i = 0; i < S1.length(); i++) {

			S1[i] = toupper(S1[i]);

		}

		return S1;
	}

	void ToUpper() {

		_Value = ToUpper(_Value);

	}

	static vector <string> SplitString(string S1 , string Dilimiter = " ") {

		vector <string> JedesWortIstAllein;

		
		string Word = "";
		short pos = 0;

		while ((pos = S1.find(Dilimiter)) != std::string::npos) {

			Word = S1.substr(0, pos);

			if (Word != "") {

				JedesWortIstAllein.push_back(Word);

			}

			S1.erase(0, pos + Dilimiter.length());

		}

		if (S1 != "") {


			JedesWortIstAllein.push_back(S1);

		}

		return JedesWortIstAllein;

	}

	vector <string> SplitString() {

		return SplitString(_Value);

	}

	static string UpperAlleErsteWort(string S1) {

		bool IstEsDieErsteBuchstabe = true;

		for (int i = 0; i < S1.length(); i++) {

			if (S1[i] != ' ' && IstEsDieErsteBuchstabe) {

				S1[i] = toupper(S1[i]);

			}

			IstEsDieErsteBuchstabe = (S1[i] == ' ' ? true : false);

		}

		return S1;

	}

	void UpperAlleErsteWort() {

		_Value = UpperAlleErsteWort(_Value);

	}

	static string LowerAlleErsteWort(string S1) {

		bool IstEsErsteWort = true;

		for (int i = 0; i < S1.length(); i++) {

			if (S1[i] != ' ' && IstEsErsteWort) {

				S1[i] = tolower(S1[i]);

			}

			IstEsErsteWort = (S1[i] == ' ' ? true : false);

		}
		return S1;
	}

	void LowerAlleErsteWort() {

		_Value = LowerAlleErsteWort(_Value);

	}

	static char InvertLetterCase(char char1) {

		return (isupper(char1) ? tolower(char1) : toupper(char1));

	}

	static string InvertAllLetterCase(string S1) {

		for (int i = 0; i < S1.length(); i++) {

			S1[i] = (isupper(S1[i]) ? tolower(S1[i]) : toupper(S1[i]));

		}

		return S1;

	}

	void InvertAllLetterCase() {

		_Value = InvertAllLetterCase(_Value);

	}

	enum enWasZuZahlen { KleineBuchStaben = 1, GrosseBuchStaben = 2, Alle = 3 };

	static int CountAlleKleineBuchStaben(string S1) {

		int counter = 0;

		for (int i = 0; i < S1.length(); i++) {

			if (islower(S1[i])) {
				counter++;
			}

		}

		return counter;

	}

	int CountAlleKleineBuchStaben() {

		return CountAlleKleineBuchStaben(_Value);

	}

	static int CounterAlleGrosseBuchStaben(string S1) {

		int counter = 0;

		for (int i = 0; i < S1.length(); i++) {

			if (isupper(S1[i])) {
				counter++;
			}

		}

		return counter;

	}

	int CounterAlleGrosseBuchStaben() {

		return CounterAlleGrosseBuchStaben(_Value);

	}

	static int CountAlleBuchStaben(string S1) {

		return CountAlleKleineBuchStaben(S1) + CounterAlleGrosseBuchStaben(S1);

	}

	int CountAlleBuchStaben() {

		return CountAlleKleineBuchStaben(_Value) + CounterAlleGrosseBuchStaben(_Value);

	}

	static void WasZuCounten(string S1) {

		int WelcheNummer = 0;

		cout << "Wahlen Sie : " << endl;
		cout << "------------------------------" << endl;
		cout << "1.Zahlen kleine Buchstaben" << endl;
		cout << "2.Zahlen grosse Buchstaben" << endl;
		cout << "3.Alle Buchstaben" << endl;
		cout << "------------------------------\n";
		cout << "Welche Nummer : ";
		cin >> WelcheNummer;

	
		switch (enWasZuZahlen(WelcheNummer))
		{
		case enWasZuZahlen::GrosseBuchStaben:

			cout << "Die Zahl alle Grosse Buchstaben von ' " << S1 << " ' betragt : " << CounterAlleGrosseBuchStaben(S1) << endl;

			break;
		case enWasZuZahlen::KleineBuchStaben:

			cout << "Die Zahl alle kleine Buchstaben von ' " << S1 << " ' betragt : " << CountAlleKleineBuchStaben(S1) << endl;

			break;
		case enWasZuZahlen::Alle:

			cout << "Die Zahl alle Buchstaben von ' " << S1 << " ' betragt : " << CountAlleBuchStaben(S1) << endl;

			break;
		default:
			break;
		}

	}

	static string TrimRicht(string S1) {

		while (S1[0] == ' ') {

			S1 = S1.erase(0, 1);

		}

		return S1;

	}

	string TrimRicht() {

		return TrimRicht(_Value);

	}

	static string TrimLinks(string S1) {

		int StringLength = S1.length();

		while (S1[StringLength - 1] == ' ') {

			S1 = S1.erase(StringLength - 1);
			StringLength--;

		}
		return S1;
	}

	string TrimLinks() {

		return TrimLinks(_Value);

	}

	static string Trim(string S1) {

		S1 = TrimRicht(S1);

		S1 = TrimLinks(S1);

		return S1;

	}

	string Trim() {

		return Trim(_Value);

	}


	static string JoinString(vector <string> vString, string Dilimiter) {

		string S1 = "";

		for (string& i : vString) {

			S1 += i;
			S1 += Dilimiter;

		}

		S1 = S1.erase(S1.length() - Dilimiter.length());

		return S1;

	}

	static string JoinArrString(string ArrString[], short lang, string Dilem) {

		string S1 = "";

		for (int i = 0; i < lang; i++) {

			S1 += ArrString[i];
			S1 += Dilem;

		}

		S1 = S1.erase(S1.length() - Dilem.length());

		return S1;

	}

	static string StringVonAndereRichtung(string S1) {

		vector <string> JedesWortAllein = SplitString(S1);

		S1 = "";

		for (int i = JedesWortAllein.size() - 1; i >= 0; i--) {

			S1 += JedesWortAllein[i];
			S1 += " ";

		}
		return S1.substr(0, S1.length() - 1);
	}

	string StringVonAndereRichtung() {

		return  StringVonAndereRichtung(_Value);

	}

	static string WorterErSetzen(string S1, string sToErzetzen, string ErsetzenZu, bool MachCase = true) {


		vector <string> vSplitString = SplitString(S1);

		if (MachCase) {

			for (string& i : vSplitString) {

				if (i == sToErzetzen) {
					i = ErsetzenZu;
				}

			}

		}
		else {

			for (string& i : vSplitString) {

				if (ToLower(i) == ToLower(sToErzetzen)) {

					i = ErsetzenZu;
				}

			}

		}


		S1 = JoinString(vSplitString, " ");

		return S1;

	}

	string WorterErSetzen(string sToErzetzen, string ErsetzenZu) {

		return WorterErSetzen(_Value, sToErzetzen, ErsetzenZu);

	}

	static string RemovePunctions(string S1) {

		string S2 = "";

		for (int i = 0; i < S1.length(); i++) {

			if (!ispunct(S1[i])) {

				S2 += S1[i];

			}

		}

		return S2;

	}

	string RemovePunctions() {

		return RemovePunctions(_Value);

	}


	static string ReadString() {

		string S1 = "";
		getline(cin >> ws, S1);

		return S1;

	}

	static float ReadFloatNumber() {

		float x = 0;

		cin >> x;

		return x;

	}


};
