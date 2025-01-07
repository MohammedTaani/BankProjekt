#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsString.h"
#include "clsTransactions.h"
#include "clsManageusers.h"
#include "clsMainUser.h"
#include "clsUsers.h"
#include "clsLoginRigister.h"
#include "clsCurrencyExchange.h"


using namespace std;

class clsMainScreen : protected clsScreen
{

private:

    enum enPermissions {

        AllePermissions = -1, enShowClientListOption = 1, enAddNewClientOption = 2, enDeleteClientOption = 4,

        enUpdateClientInfoOption = 8, enFindClientOption = 16, enTransactionsOption = 32, enManageUsersOption = 64 , enLoginRigisterOption = 128

    };
    
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsString::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsString::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsString::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsString::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsString::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsString::ReadFloatNumber();
    }

    static void _PrintClietFromTheList(clsBankClient Client) {

        cout << "|" << left << setw(15) << Client.AccountNumber();
        cout << "|" << left << setw(20) << Client.FullName();
        cout << "|" << left << setw(15) << Client.Phone;
        cout << "|" << left << setw(27) << Client.Email;
        cout << "|" << left << setw(10) << Client.PinCode;
        cout << "|" << left << setw(15) << Client.AccountBalance << endl;

    }

    static void _PrintUserRigisterFromTheList(clsLoginRigister User) {

        cout << "|" << left << setw(15) << User.GetDate();
        cout << "|" << left << setw(20) << User.GetDieZeit();
        cout << "|" << left << setw(15) << User.GetUser();
        cout << "|" << left << setw(15) << User.GetPassword();
        cout << "|" << left << setw(10) << User.GetPermissions() << endl;

    }

    enum WelcheList{
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRigister = 8 ,  eCurrencyExchange = 9 , eExit = 10
    };

    static WelcheList _ReadNummer() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 10 ? ");
        return WelcheList(Choice);

    }

    static void _RufenBestimmteList(WelcheList enList) {
        

        switch (enList)
        {
        case clsMainScreen::eListClients:

            _ShowClientList();

            PrintMainMeneu();

            break;
        case clsMainScreen::eAddNewClient:

            _AddNewClient();

            PrintMainMeneu();

            break;
        case clsMainScreen::eDeleteClient:

            _DeleteClient();

            PrintMainMeneu();

            break;
        case clsMainScreen::eUpdateClient:

            _UpdateClientInfo();

            PrintMainMeneu();

            break;
        case clsMainScreen::eFindClient:

            _FindClient();

            PrintMainMeneu();

            break;
        case clsMainScreen::eShowTransactionsMenue:

            _Transactions();

            PrintMainMeneu();

            break;
        case clsMainScreen::eManageUsers:

            _ManageUsers();

            PrintMainMeneu();

            break;

        case clsMainScreen::eLoginRigister:

            _LoginRigisterScreen();

            PrintMainMeneu();

            break;

        case clsMainScreen::eCurrencyExchange:

            _CurrencyExchange();

            PrintMainMeneu();

            break;

        case clsMainScreen::eExit:

            MainUser = clsUsers::Find("", "");
            system("cls");

            break;
        default:
            break;
        }

    }

    static void _AddNewClient() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enAddNewClientOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }

        MainScreen("Add New Client Screen");


        string AccountNumber = "";
        cout << "Schreiben Sie bitte AccountNummer : ";
        getline(cin >> ws, AccountNumber);


        while (clsBankClient::IsClientExist(AccountNumber)) {

            cout << "This Client ist vorhanden , versuchen Sie noch mal bitte\n";

            cout << "Schreiben Sie bitte AccountNummer : ";
            getline(cin >> ws, AccountNumber);

        }


        clsBankClient Client = clsBankClient::GetNewClientObject(AccountNumber);

        cout << "\n\New Client Info:";
        cout << "\n____________________\n";

        _ReadClientInfo(Client);


        clsBankClient::enSaveResults Result = Client.Save();


        switch (Result)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }

        }



        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");
        

    }

    static void _ShowClientList() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enShowClientListOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }



        vector <clsBankClient> Clients = clsBankClient::GetAlleClients();

        MainScreen("Show Client List Screen");

        cout << "----------------------------------------------------------------------------------------------------------------------\n";
        cout << "-----------------------------------------Clients List (" << Clients.size() << ")---------------------------------------------------------\n";
        cout << "----------------------------------------------------------------------------------------------------------------------\n";


        cout << "|" << left << setw(15) << "Account Nummer";
        cout << "|" << left << setw(20) << "Full Name";
        cout << "|" << left << setw(15) << "Phone";
        cout << "|" << left << setw(27) << "Email";
        cout << "|" << left << setw(10) << "Pin Code";
        cout << "|" << left << setw(15) << "Account Balance" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------\n";
      
        if (Clients.size() == 0) {

            cout << "\t\tEs gibt kein konto in der Liste.\n";
            return;
        }

        for (clsBankClient C : Clients) {

            _PrintClietFromTheList(C);

        }

        cout << "-----------------------------------------------------------------------------------------------------------------\n";
        
        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");
        

    }

    static void _DeleteClient() {

        system("cls");



        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enDeleteClientOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }

        MainScreen("Delete Client Screen");


        cout << "Schreiben Sie bitte Account Nummer : ";
        string AccountNummer = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNummer)) {

            cout << "Dieser Client existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte Account Nummer : ";
            AccountNummer = clsString::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNummer);

        Client.Print();

        char Sicher = 'N';

        while (0 != 1) {

            cout << "Sind Sie sicher , den Account zu loschen (Y/N) ? ";
            cin >> Sicher;

            if (Sicher == 'N' || Sicher == 'n') {
                cout << "Das Konto wird nicht geloscht\n";
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
                cout << "Falsch , versuchen Sie noch mal Y : Yes , ich will das Konto loschen , N , Nein ich will nicht\n";
            }
        }


        Client = clsBankClient::DeletedClientObjeckt(AccountNummer);

        clsBankClient::enSaveResults Result = Client.Save();


        switch (Result) {

        case clsBankClient::enSaveResults::svSucceeded:
        {

            cout << "Das Konto wird erfolgreich geloscht\n";
            Client = clsBankClient::GetEmptyClientObject();
            Client.Print();

            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {

            cout << "Account Delet Faild\n";
            break;

        }

        }


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }

    static void _UpdateClientInfo() {


        system("cls");



        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enUpdateClientInfoOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }

        MainScreen("Update Client Info Screen");


        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsString::ReadString();
        }


        char Sicher = 'N';

        while (0 != 1) {

            cout << "Sind Sie sicher , den Account zu aktulisieren (Y/N) ? ";
            cin >> Sicher;

            if (Sicher == 'N' || Sicher == 'n') {
                cout << "Das Konto wird nicht aktulisiert\n";
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
                cout << "Falsch , versuchen Sie noch mal Y : Yes , ich will das Konto aktulisieren , N , Nein ich will nicht\n";
            }
        }


        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        Client1.Print();

        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";


        _ReadClientInfo(Client1);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = Client1.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            Client1.Print();
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }

        }


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }

    static void _FindClient() {

        system("cls");



        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enFindClientOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }

        MainScreen("Find Client Screen");


        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsString::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        Client1.Print();

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }

    static void _Transactions() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enTransactionsOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }


        clsTransactions::ShowTransactionsMenue();


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }

    static void _ManageUsers() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enManageUsersOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }


        clsManageusers::MainUsersScreen();

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");


    }

    static void _LoginRigisterScreen() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enLoginRigisterOption)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }



        vector <clsLoginRigister> LoginedUsers = clsLoginRigister::GetAlleUserRigister();

        MainScreen("Show Client List Screen");

        cout << "----------------------------------------------------------------------------------------------------------------------\n";
        cout << "-----------------------------------------Clients List (" << LoginedUsers.size() << ")---------------------------------------------------------\n";
        cout << "----------------------------------------------------------------------------------------------------------------------\n";


        cout << "|" << left << setw(15) << "Date";
        cout << "|" << left << setw(20) << "Die Zeit";
        cout << "|" << left << setw(15) << "User";
        cout << "|" << left << setw(15) << "Password";
        cout << "|" << left << setw(10) << "Permissions"  << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------\n";

        if (LoginedUsers.size() == 0) {

            cout << "\t\tEs gibt kein User in der Liste.\n";
            return;
        }

        for (clsLoginRigister C : LoginedUsers) {

            _PrintUserRigisterFromTheList(C);

        }

        cout << "-----------------------------------------------------------------------------------------------------------------\n";

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }

    static void _CurrencyExchange() {

        system("cls");


        if (!MainUser.CheackPermissions(clsUsers::enPermissions::enCurrencyExchange)) {

            cout << "Access Dinaid , Contact your Admin!!!\n";

            cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
            system("pause > 0");

            return;

        }


        clsCurrencyExchange::_clsCurrencyExchangeScreen();

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


public:

	static void PrintMainMeneu() {

        system("cls");
        MainScreen("MainScreen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Rigister.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _RufenBestimmteList(_ReadNummer());


	}

    

};

