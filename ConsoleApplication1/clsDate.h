#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>


using namespace std;

class clsDate
{

private:

	string _Date = "";
	int _Tag = 0;
	int _Jahr = 0;
	int _Monat = 0;


public:

	clsDate() {

		time_t t = time(nullptr);

		tm* m = localtime(&t);

		_Jahr = m->tm_year + 1900;
		_Monat = m->tm_mon + 1;
		_Tag = m->tm_mday;

		_Date = to_string(_Tag) + "/" + to_string(_Monat) + "/" + to_string(_Jahr);

	}

	clsDate(string Date) {

		_Date = Date;
		StringDateZuVectorStringDate(Date, "/");

	}

	clsDate(int Tag, int Monat, int Jahr) {

		_Tag = Tag;
		_Monat = Monat;
		_Jahr = Jahr;

		_Date = to_string(Tag) + "/" + to_string(Monat) + "/" + to_string(Jahr);

	}

	clsDate(int TageZahl, int Jahr) {

		if (TageZahl >= 365) {
			cout << "Falsch Tage mussen weniger als 365" << endl;
			return;
		}

		TageZuMonate(TageZahl, Jahr);
	}

	static bool IstDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Jahr < Date2._Jahr ? true : (Date1._Jahr == Date2._Jahr ? (Date1._Monat < Date2._Monat ? true : (Date1._Monat == Date2._Monat ? (Date1._Tag < Date2._Tag ? true : false) : false)) : false));

	}

	bool IstEsBeforeDate2(clsDate Date2)
	{

		return IstDate1BeforeDate2(*this, Date2);

	}

	static short TageImJahr(short jahr) {

		return (IstEsSchaltJahr(jahr) ? 366 : 365);

	}

	short TageImJahr() {
		return TageImJahr(_Jahr);
	}

	static int StundenImJahr(short jahr) {

		return TageImJahr(jahr) * 24;

	}

	int StundenImJahr() {

		return StundenImJahr(_Jahr);

	}

	static int MinutenImJahr(short jahr) {

		return StundenImJahr(jahr) * 60;

	}

	int MinutenImJahr() {

		return MinutenImJahr(_Jahr);

	}

	static int SekungenImJahr(short jahr) {

		return MinutenImJahr(jahr) * 60;

	}

	int SekungenImJahr() {

		return SekungenImJahr(_Jahr);

	}

	vector <string> StringDateZuVectorStringDate(string Date, string Dilimter) {

		vector <string> VectorStringDate;
		string Word = "";
		int pos = 0;

		while ((pos = Date.find(Dilimter)) != std::string::npos) {

			Word = Date.substr(0, pos);

			if (Word != "") {

				VectorStringDate.push_back(Word);

			}

			Date.erase(0, pos + Dilimter.length());

		}

		if (Date != "") {
			VectorStringDate.push_back(Date);
		}

		_Tag = stoi(VectorStringDate[0]);
		_Monat = stoi(VectorStringDate[1]);
		_Jahr = stoi(VectorStringDate[2]);


		return VectorStringDate;

	}

	static int WieVieleTageImMonat(int Monat, int Jahr) {

		if (Monat < 1 || Monat > 12)
			return 0;

		if (Monat == 2 && IstEsSchaltJahr(Jahr)) {
			return 29;
		}
		else if (Monat == 2) {
			return 28;
		}

		if (Monat == 1 || Monat == 3 || Monat == 5 || Monat == 7 || Monat == 8 || Monat == 10 || Monat == 12) {
			return 31;
		}

		return 30;

	}

	int WieVieleTageImMonat() {

		return WieVieleTageImMonat(_Monat, _Jahr);

	}

	static bool IstEsSchaltJahr(int jahr) {

		return (jahr % 4 == 0 && jahr % 100 != 0) || (jahr % 400 == 0);

	}

	void TageZuMonate(int TageZahl, int Jahr) {

		int Monat = 1;

		while (TageZahl != 0) {

			int TageCounter = WieVieleTageImMonat(Monat, Jahr);

			if (TageZahl > TageCounter) {

				Monat++;

				TageZahl -= TageCounter;

			}
			else {

				_Tag = TageZahl;

				TageZahl = 0;

			}

		}

		_Monat = Monat;
		
		if (_Tag == 0) {
			_Tag = 1;
		}

		_Jahr = Jahr;

		_Date = to_string(_Tag) + "/" + to_string(_Monat) + "/" + to_string(_Jahr);



	}

	static int WieVielStundenImMonat(int Monat , int jahr) {

		return WieVieleTageImMonat(Monat, jahr) * 24;

	}

	int WieVielStundenImMonat() {

		return WieVielStundenImMonat(_Monat, _Jahr);

	}

	static int WieVielMinuternImMonat(int Monat, int jahr) {

		return WieVielStundenImMonat(Monat, jahr) * 60;

	}

	int WieVielMinuternImMonat() {

		return WieVielMinuternImMonat(_Monat, _Jahr);

	}

	static int WieVielSekundenImMonat(int Monat, int jahr) {

		return WieVielMinuternImMonat(Monat, jahr) * 60;

	}

	int WieVielSekundenImMonat() {

		return WieVielSekundenImMonat(_Monat, _Jahr);

	}

	short StundenImTag() {
		return 24;
	}

	static bool IstVaild(clsDate Date1) {

		if (Date1._Jahr < 0)
			return 0;

		if (Date1._Monat < 1 || Date1._Monat > 12)
			return 0;

		if (Date1._Tag < 0 || Date1._Tag > WieVieleTageImMonat(Date1._Monat, Date1._Jahr))
			return 0;


		return 1;

	}

	bool IstVaild() {

		return IstVaild(*this);

	}

	static bool IstLetzteTagImMonat(clsDate Date) {

		return (Date._Tag == WieVieleTageImMonat(Date._Monat, Date._Jahr) ? true : false);

	}

	bool IstLetzteTagImMonat() {

		return  IstLetzteTagImMonat(*this);

	}

	static bool IstDate1GleichDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Jahr == Date2._Jahr && Date1._Monat == Date2._Monat && Date1._Tag == Date2._Tag);

	}

	bool IstGleichDate2(clsDate Date2) {

		return IstDate1GleichDate2(*this, Date2);

	}

	static bool IstDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return !(IstDate1BeforeDate2(Date1, Date2) || IstDate1GleichDate2(Date1 , Date2));

	}

	bool IstAfterDate2(clsDate Date2) {

		return IstDate1AfterDate2(*this, Date2);

	}

	static int WieVielTageImDate(clsDate Date1) {

		int DaysCounter = 0;

		for (int i = 1; i < Date1._Monat; i++) {
			
				DaysCounter += WieVieleTageImMonat(i, Date1._Jahr);

		}

		DaysCounter += Date1._Tag;

		return DaysCounter;

	}

	int WieVielTageImDate() {

		return WieVielTageImDate(*this);

	}

	static string MonatKleinName(short Monat) {

		string S1[] = { "Jan" , "Feb" , "Mar"  "Apr" , "May" , "Jun" , "Jul" , "Aug" , "Sep" , "Oct" , "Nov" , "Dec"};

		return S1[Monat - 1];

	}

	string MonatKleinName() {

		return MonatKleinName(_Monat);

	}

	static int WelcheTagIstEs(int Tag , int Monat , int Jahr) {

		int a = (14 - Monat) / 12;
		int y = Jahr - a;
		int m = Monat + (12 * a) - 2;

		return (5 + Tag + y + (y / 4) + (31 * m / 12)) % 7;

	}

	int WelcheTagIstEs() {

		return WelcheTagIstEs(_Tag, _Monat, _Jahr);

	}

	static string TagKleinName(short Tag) {

		string S1[] = { "Mon" , "Die" , "Mit" , "Don" , "Fri" , "Sam" , "Son" };

		return S1[Tag];

	}

	string TagKleinName() {

		return TagKleinName(WelcheTagIstEs(_Tag , _Monat , _Jahr));

	}

	static void PrintMonatCalender(int Monat , int Jahr) {
		
		cout << "=========Monat " << MonatKleinName(Monat) << " Calender========\n";

		cout << setw(5) << "Mon" << setw(5) << "Die" << setw(5) << "Mit" << setw(5) << "Don" << setw(5) << "Fri" << setw(5) << "Sam" << setw(5) << "Son" << endl;

		short counter = WelcheTagIstEs(1, Monat, Jahr);

		short MonatsTage = WieVieleTageImMonat(Monat, Jahr);

		for (int i = 0; i < counter; i++) {

			cout << setw(5) << "";

		}

		for (int i = 1; i <= MonatsTage; i++) {

			cout << setw(5) << i;

			counter++;

			if (counter == 7) {
				cout << endl;
				counter = 0;
			}

			

		}

		cout << endl;
	}

	void PrintMonatCalender() {

		return PrintMonatCalender(_Monat, _Jahr);

	}

	static void PrintJahrCalender(int jahr) {

		for (int i = 1; i <= 12; i++) {

			PrintMonatCalender(i, jahr);

		}

	}

	void PrintJahrCalender() {

		return PrintJahrCalender(_Jahr);

	}

	static clsDate AddEinTag(clsDate Date) {

		if (IstLetzteTagImMonat(Date)) {

			if (Date._Monat == 12) {
				Date._Jahr++;
				Date._Monat = 1;
				Date._Tag = 1;
			}
			else {
				Date._Monat++;
				Date._Tag = 1;
			}

		}
		else
			Date._Tag++;


		return Date;
	}

	void AddEinTag() {

		clsDate Date = AddEinTag(*this);

		_Tag = Date._Tag;
		_Monat = Date._Monat;
		_Jahr = Date._Jahr;

	}

	static clsDate AddBestimmteDays(clsDate Date , int DaysNummer) {

		for (int i = 1; i <= DaysNummer; i++) {

			Date = AddEinTag(Date);

		}

		return Date;
	}

	void AddBestimmteDays(int DaysNummer) {

		clsDate Date = AddBestimmteDays(*this, DaysNummer);

		_Tag = Date._Tag;
		_Monat = Date._Monat;
		_Jahr = Date._Jahr;

	}

	static clsDate AddEineWoche(clsDate Date) {

		for (int i = 0; i <= 7; i++) {

			Date = AddEinTag(Date);

		}
		return Date;
	}

	void AddEineWoche() {

		clsDate Date = AddEineWoche(*this);

		_Tag = Date._Tag;
		_Monat = Date._Monat;
		_Jahr = Date._Jahr;

	}

	static clsDate AddBestimmteWochen(clsDate Date, int WochenNummer) {

		for (int i = 1; i <= WochenNummer; i++) {

			Date = AddEineWoche(Date);

		}

		return Date;

	}

	void AddBestimmteWochen(int WochenNummer) {

		clsDate Date = AddBestimmteWochen(*this , WochenNummer);

		_Tag = Date._Tag;
		_Monat = Date._Monat;
		_Jahr = Date._Jahr;

	}

	static clsDate IncreaseDateBeimEinMonat(clsDate Date) {

		int Monatx = Date._Monat + 1;

		if (Monatx == 13) {
			Monatx = 1;
		}

		Date._Tag = (IstLetzteTagImMonat(Date) ? WieVieleTageImMonat(Monatx, Date._Jahr) : Date._Tag);


		if (Date._Monat == 12) {
			Date._Monat = 1;
			Date._Jahr++;
		}
		else
			Date._Monat++;

		

		return Date;

	}

	void IncreaseDateBeimEinMonat() {

		clsDate Date = IncreaseDateBeimEinMonat(*this);

		_Tag = Date._Tag;
		_Monat = Date._Monat;
		_Jahr = Date._Jahr;

	}

	static clsDate IncreaseDateBeimEinJahr(clsDate Date) { 


		if (IstEsSchaltJahr(Date._Jahr) && Date._Monat == 2 && Date._Tag == 29) {

			Date._Jahr++;
			Date._Tag = 28; 
		}
		else {
			Date._Jahr++;
		}

		return Date;

	}

	void IncreaseDateBeimEinJahr() {

		clsDate Date = IncreaseDateBeimEinJahr(*this);

		_Jahr = Date._Jahr;
		_Tag = Date._Tag;
		_Monat = Date._Monat;

	}

	static clsDate IncreaceDateBeimEinDecate(clsDate Date, int WieVielJahre) {

		for (int i = 1; i <= WieVielJahre; i++) {

			Date = IncreaseDateBeimEinJahr(Date);

		}

		return Date;

	}

	void IncreaceDateBeimEinDecate(int WieVielJahre) {

		clsDate Date = IncreaceDateBeimEinDecate(*this, WieVielJahre);

		_Jahr = Date._Jahr;
		_Monat = Date._Monat;
		_Tag = Date._Tag;

	}

	static clsDate IncreaseDateBeimEinCentury(clsDate Date) {

		if (IstEsSchaltJahr(Date._Jahr + 100) && Date._Monat == 2 && Date._Tag == 29) {

			Date._Jahr += 100;

			Date._Tag = WieVieleTageImMonat(Date._Monat, Date._Jahr);

		}
		else {
			Date._Jahr += 100;
		}

		return Date;

	}

	void IncreaseDateBeimEinCentury() {

		clsDate Date = IncreaseDateBeimEinCentury(*this);

		_Jahr = Date._Jahr;
		_Monat = Date._Monat;
		_Tag = Date._Tag;

	}

	static clsDate DecreaseDateBeimEinTag(clsDate Date) {

		if (Date._Tag == 1 && Date._Monat == 1) {

			Date._Jahr--;
			Date._Monat = 12;
			Date._Tag = 31;

		}
		else if (Date._Tag == 1) {

			Date._Monat--;
			Date._Tag = WieVieleTageImMonat(Date._Monat, Date._Jahr);

		}
		else {
			Date._Tag--;
		}

		return Date;

	}

	void DecreaseDateBeimEinTag() {

		clsDate Date = DecreaseDateBeimEinTag(*this);

		_Tag = Date._Tag;

		_Monat = Date._Monat;

		_Jahr = Date._Jahr;

	}

	static clsDate DecreaseDateBeimBestimmteTage(clsDate Date, int WieVielTage) {

		for (int i = 0; i <= WieVielTage; i++) {

			Date = DecreaseDateBeimEinTag(Date);

		}

		return Date;

	}

	static clsDate DecreaseDateBeimWeek(clsDate Date) {

		for (int i = 1; i <= 7; i++) {

			Date = DecreaseDateBeimEinTag(Date);

		}
		return Date;
	}

	static clsDate DecreaseDateBeimMonat(clsDate Date) {

		if (Date._Monat == 1) {
			Date._Jahr--;
			Date._Monat = 12;
		}
		else {
			Date._Monat--;
		}

		short monthDays = WieVieleTageImMonat(Date._Monat, Date._Jahr);

		if (Date._Tag > monthDays) {
			Date._Tag = monthDays;
		}

		return Date;
	}

	void DecreaseDateBeimMonat() {

		clsDate Date = DecreaseDateBeimMonat(Date);

		_Tag = Date._Tag;
		_Jahr = Date._Jahr;
		_Monat = Date._Monat;

	}

	static clsDate DecreaseDateBeimEinJahr(clsDate Date) {

		if (IstEsSchaltJahr(Date._Jahr) && Date._Monat == 2 && Date._Tag == 29) {

			Date._Tag = 28;

		}

		Date._Jahr--;

		return Date;

	}

	static int GetDefereneInDays(clsDate Date1, clsDate Date2) {

		int i = 0; 

		while (IstDate1BeforeDate2(Date1, Date2)) {

			Date1 = AddEinTag(Date1);

			i++;

		}

		return i;
	}

	static int RechnenMeinAlterInTage(clsDate MeinGebuhrenDatum) {

		clsDate HeutigeDatum = clsDate();

		unsigned int Tage = GetDefereneInDays(MeinGebuhrenDatum, HeutigeDatum);

		return Tage;
		
	}

	static void SwapClsDate(clsDate& Date1 , clsDate& Date2) {

		clsDate Date3 = Date1;
		Date1 = Date2;
		Date2 = Date3;

	}

	static void PrintDate(clsDate Date) {

		cout << "Day : " << Date._Tag << endl;
		cout << "Monat : " << Date._Monat << endl;
		cout << "Jahr : " << Date._Jahr << endl;

	}

	void PrintDate() {

		return PrintDate(*this);

	}

	static string GetHeutigeDate() {

		clsDate Date1 = clsDate();

		return Date1._Date;

	}



	static string DieZeit() {

		// الحصول على الوقت الحالي
		time_t currentTime = time(nullptr);

		// تحويل الوقت إلى هيكل tm (توقيت محلي)
		tm* localTime = localtime(&currentTime);

		// طباعة الساعة والدقائق والثواني
		//cout << "الساعة: " <<  localTime->tm_hour << endl;
		//cout << "الدقائق: " << localTime->tm_min << endl;
		//cout << "الثواني: " << localTime->tm_sec << endl;

		string S1 = to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min) + ":" + to_string(localTime->tm_sec);
			 
		return S1;
		
	}



};

