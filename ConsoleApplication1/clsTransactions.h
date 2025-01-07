#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsUtil.h"
#include <fstream>
#include "clsString.h"

using namespace std;



class clsTransactions : protected clsScreen
{

    struct TransfarInfo {

        string Date;
        string DieZeit;
        string Acc_Num_Von;
        string Acc_Num_Zu;
        double AmountTransfared;
        double Acc_Num_Von_Summe;
        double Acc_Num_Zu_Summe;
        string TransfaredBei;


    };


    static string _SaveTransfarInfoInString(TransfarInfo Info ,string Speretor = "#//#") {

        string S1 = Info.Date + Speretor + Info.DieZeit + Speretor +
            Info.Acc_Num_Von + Speretor + Info.Acc_Num_Zu + Speretor
            + to_string(Info.Acc_Num_Von_Summe) + Speretor + to_string(Info.Acc_Num_Zu_Summe)
            + Speretor + to_string(Info.AmountTransfared) + Speretor + Info.TransfaredBei;

        return S1;

    }

    static void _SaveTransfarInfoInFile(TransfarInfo AlleInfo) {

        fstream TransfarFileInfo;

        TransfarFileInfo.open("TransfarInformation.txt", ios::out | ios::app);

        string S1 = "";

        if (TransfarFileInfo.is_open()) {

            S1 = _SaveTransfarInfoInString(AlleInfo);

            TransfarFileInfo << S1 << endl;

            TransfarFileInfo.close();

        }

    }

    static TransfarInfo _VonStringZuStructInfo(string S1) {

        vector <string> Info = clsString::SplitString(S1, "#//#");

        TransfarInfo StructInfo;

        StructInfo.Date = Info[0];
        StructInfo.DieZeit = Info[1];
        StructInfo.Acc_Num_Von = Info[2];
        StructInfo.Acc_Num_Zu = Info[3];
        StructInfo.Acc_Num_Von_Summe = stoi(Info[4]);
        StructInfo.Acc_Num_Zu_Summe = stoi(Info[5]);
        StructInfo.AmountTransfared = stoi(Info[6]);
        StructInfo.TransfaredBei = Info[7];

        return StructInfo;


    }

    static vector <TransfarInfo> _SammelnDieInfosVonText() {


        fstream InfosVonFile;

        InfosVonFile.open("TransfarInformation.txt", ios::in);

        vector <TransfarInfo> InfosSammeln;


        if (InfosVonFile.is_open()) {

            TransfarInfo OneInfo;

            string S1 = "";

            while (getline(InfosVonFile, S1)) {

                OneInfo = _VonStringZuStructInfo(S1);

                InfosSammeln.push_back(OneInfo);


            }

            InfosVonFile.close();

        }

        return InfosSammeln;

    }

    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfar = 4, enTransferLog = 5, eShowMainMenue = 6
    };

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions Option) {

        switch (Option)
        {
        case clsTransactions::eDeposit:

            _Deposit();

            ShowTransactionsMenue();

            break;
        case clsTransactions::eWithdraw:

            _Withdraw();

            ShowTransactionsMenue();

            break;
        case clsTransactions::eShowTotalBalance:

            _TotalBalances();

            ShowTransactionsMenue();

            break;

        case clsTransactions::eTransfar:

            _Transfar();

            ShowTransactionsMenue();

            break;

        case clsTransactions::enTransferLog:

            _TransferLog();

            ShowTransactionsMenue();

            break;
        case clsTransactions::eShowMainMenue:

            break;
        default:
            break;
        }

    }


    static short ReadTransactionsMenueOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 4? ");
        return Choice;


    }


    static void PrintTotalBalance(clsBankClient Client) {

        cout << "|" << left << setw(30) << Client.AccountNumber();
        cout << "|" << left << setw(30) << Client.FullName();
        cout << "|" << left << setw(30) << Client.AccountBalance << endl;

    }

    static void PrintTransferLog(TransfarInfo Info) {

        cout << "|" << left << setw(15) << Info.Date;
        cout << "|" << left << setw(12) << Info.DieZeit;
        cout << "|" << left << setw(10) << Info.Acc_Num_Von;
        cout << "|" << left << setw(10) << Info.Acc_Num_Zu;
        cout << "|" << left << setw(12) << Info.AmountTransfared;
        cout << "|" << left << setw(15) << Info.Acc_Num_Von_Summe;
        cout << "|" << left << setw(15) << Info.Acc_Num_Zu_Summe;
        cout << "|" << left << setw(10) << Info.TransfaredBei << endl;

    }


    static void _Deposit() {

        system("cls");

        MainScreen("Deposit Screen");


        cout << "Schreiben Sie bitte Account Nummer : ";
        string AccountNummer = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNummer)) {

            cout << "Dieser Client existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte Account Nummer : ";
            AccountNummer = clsString::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNummer);

        Client.Print();

        cout << "Wie viel Geld wollen Sie hinterlegen : ";
        double DieSumme = clsInputValidate::ReadDoubleNumber();

        char Sicher = 'N';

        cout << "Sind Sie sicher,dass Sie diese Summe hinterlegen wollen (Y/N) ? ";
        cin >> Sicher;

        if (Sicher == 'Y' || Sicher == 'y') {

            Client.AccountBalance += DieSumme;

            Client.Save();

            cout << "Die neue Summe betra:gt bei : " << Client.AccountBalance << endl;

        }
        else {
            cout << "Die Summe wird nicht hinterlegt\n";

        }

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


    static void _Withdraw() {

        system("cls");

        MainScreen("Withdraw Screen");


        cout << "Schreiben Sie bitte Account Nummer : ";
        string AccountNummer = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNummer)) {

            cout << "Dieser Client existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte Account Nummer : ";
            AccountNummer = clsString::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNummer);

        Client.Print();

        cout << "Wie viel Geld wollen Sie einzahlen : ";
        double DieSumme = clsInputValidate::ReadDoubleNumber();

        while (DieSumme > Client.AccountBalance) {

            cout << "Falsch.Sie haben weniger Geld als das ! , versuchen Sie noch mal : \n";

            DieSumme = clsInputValidate::ReadDoubleNumber();

        }

        char Sicher = 'N';

        cout << "Sind Sie sicher,dass Sie diese Summe einzahlen wollen (Y/N) ? ";
        cin >> Sicher;

        if (Sicher == 'Y' || Sicher == 'y') {

            Client.AccountBalance -= DieSumme;

            Client.Save();

            cout << "Die neue Summe betra:gt bei : " << Client.AccountBalance << endl;

        }
        else {
            cout << "Die Summe wird nicht eingezahlt\n";

        }

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }


    static void _TotalBalances() {

        system("cls");

        MainScreen("TotalBalance Screen");



        vector <clsBankClient> Clients = clsBankClient::GetAlleClients();

        int TotalBalaneAlleClients = clsBankClient::GetTotalBalanceAlleClients(Clients);

        cout << "-----------------------------------------------------------------------------------------------------\n";
        cout << "-----------------------------------------Total Balance List (" << Clients.size() << ")-------------------------------------\n";
        cout << "-----------------------------------------------------------------------------------------------------\n";
        cout << "|" << left << setw(30) << "Account Nummer";
        cout << "|" << left << setw(30) << "Full Name";
        cout << "|" << left << setw(30) << "Account Balance" << endl;
        cout << "-----------------------------------------------------------------------------------------------------\n";
        if (Clients.size() == 0) {

            cout << "\t\tEs gibt kein konto in der Liste.\n";
            return;
        }

        for (clsBankClient C : Clients) {

            PrintTotalBalance(C);

        }

        cout << "-----------------------------------------------------------------------------------------------------\n";

        cout << "\t\t\t\t\t\tTotal Balance : " << TotalBalaneAlleClients << endl;
        cout << "\t\t\t(" << clsUtil::NumberToText(TotalBalaneAlleClients) << ")\n";


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


    static void _MainMenue() {


    }


    static void _PrintClientInfo(clsBankClient Client) {


        cout << "\n\nClient Card : " << endl;
        cout << "-----------------------------------------\n";
        cout << "Full Name : " << Client.FullName() << endl;
        cout << "Acc . Num : " << Client.AccountNumber() << endl;
        cout << "Balance   : " << Client.AccountBalance << endl;
        cout << "-----------------------------------------\n";


    }


    static void _Transfar() {

        system("cls");

        MainScreen("Transfar Screen");

        //البحث عن الحساب الاول
        cout << "Schreiben Sie bitte Account Number Transfar von : ";

        string AccountNummer1 = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNummer1)) {

            cout << "\nDieser Client existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte Account Number Transfar von : ";
            AccountNummer1 = clsString::ReadString();

        }

        clsBankClient Client1 = clsBankClient::Find(AccountNummer1);

        _PrintClientInfo(Client1);



        //البحث عن الحساب الثاني
        cout << "Schreiben Sie bitte Account Number Transfar zu : ";

        string AccountNummer2 = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNummer2)) {

            cout << "\nDieser Client existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte Account Number Transfar zu : ";
            AccountNummer2 = clsString::ReadString();

        }

        clsBankClient Client2 = clsBankClient::Find(AccountNummer2);

        _PrintClientInfo(Client2);




        //تحويل المصاري
        double TransfarAmount = 0;
        cout << "\nEnter Transfar Amount : ";
        TransfarAmount = clsInputValidate::ReadIntNumber();

        while (TransfarAmount > Client1.AccountBalance) {

            cout << "Falsch , versuchen Sie noch mal.\n";
            cout << "Enter Transfar Amount : ";
            TransfarAmount = clsInputValidate::ReadIntNumber();

        }

        
        

        //هل انت متأكد انك تريد عمل هذا

        char Sicher = 'N';

        while (0 != 1) {

            cout << "\nSind Sie sicher , den Amount zu transfaren (Y/N) ? ";
            cin >> Sicher;

            if (Sicher == 'N' || Sicher == 'n') {
                cout << "\nDer Amount wird nicht transfart\n";
                cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
                system("pause > 0");
                return;
            }
            else if (Sicher == 'Y' || Sicher == 'y') {
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits <streamsize>::max(), '\n');
                cout << "\nFalsch , versuchen Sie noch mal Y : Yes , ich will das Konto loschen , N , Nein ich will nicht\n";
            }
        }


        //عملية التحويل

        Client2.AccountBalance += TransfarAmount;
        Client1.AccountBalance -= TransfarAmount;


        Client1.Save();
        Client2.Save();

        cout << "\nDer Transfar wird erfolgreich gemacht\n\n";

        _PrintClientInfo(Client1);
        cout << "\n" << endl;
        _PrintClientInfo(Client2);
        cout << "\n" << endl;



        //حفظ المعلومات المهمة
        TransfarInfo _InfoVonTransfar;

        _InfoVonTransfar.Acc_Num_Von = Client1.AccountNumber();
        _InfoVonTransfar.Acc_Num_Von_Summe = Client1.GetAccountBalance();
        _InfoVonTransfar.Acc_Num_Zu = Client2.AccountNumber();
        _InfoVonTransfar.Acc_Num_Zu_Summe = Client2.GetAccountBalance();
        _InfoVonTransfar.AmountTransfared = TransfarAmount;
        _InfoVonTransfar.Date = clsDate::GetHeutigeDate();
        _InfoVonTransfar.DieZeit = clsDate::DieZeit();
        _InfoVonTransfar.TransfaredBei = clsScreen::UserName();
        
        _SaveTransfarInfoInFile(_InfoVonTransfar);

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }


    static void _TransferLog() {

        system("cls");

        MainScreen("Transfer Screen");

        vector <TransfarInfo> Info = _SammelnDieInfosVonText();

        cout << "-----------------------------------------------------------------------------------------------------------------\n";
        cout << "|" << left << setw(15) << "Date";
        cout << "|" << left << setw(12) << "DieZeit";
        cout << "|" << left << setw(10) << "AccNumVon";
        cout << "|" << left << setw(10) << "AccNumZu";
        cout << "|" << left << setw(12) << "Amount";
        cout << "|" << left << setw(15) << "AccNumVonSumme";
        cout << "|" << left << setw(15) << "AccNumZuSumme";
        cout << "|" << left << setw(10) << "Bei" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------\n";
      
        if (Info.size() == 0) {

            cout << "\t\tEs gibt kein Transfer in der Liste.\n";
            return;
        }

        for (TransfarInfo C : Info) {

            PrintTransferLog(C);

        }

        cout << "------------------------------------------------------------------------------------------------------------------\n";


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }


public:



    static void ShowTransactionsMenue()
    {


        system("cls");
        MainScreen("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfar.\n";
        cout << setw(37) << left << "" << "\t[5] Transfar Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }



};

