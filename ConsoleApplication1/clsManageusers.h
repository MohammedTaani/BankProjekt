#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsUsers.h"
#include "string.h"

using namespace std;


class clsManageusers : protected clsScreen
{

    enum enManageUsers {

        enListUsers = 1, enAddNewUser = 2,
        enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enMainMenue = 6

    };

    static void _PrintUserRecordLine(clsUsers User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.GetUserName();
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }

    static void _ReadUserInfo(clsUsers& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsString::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsString::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsString::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsString::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsString::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUsers User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUsers::enPermissions::enShowClientListOption;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enAddNewClientOption;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enDeleteClientOption;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enUpdateClientInfoOption;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enFindClientOption;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enTransactionsOption;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enManageUsersOption;
        }

        cout << "\nLogin Rigister? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enLoginRigisterOption;
        }

        cout << "\nCurrency Exchange? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::enCurrencyExchange;
        }

        return Permissions;

    }

    static void _PerformManageUsersOption(enManageUsers Option) {

        switch (Option)
        {
        case clsManageusers::enListUsers:

            _ListUsers();
            MainUsersScreen();

            break;
        case clsManageusers::enAddNewUser:

            _AddNewUser();
            MainUsersScreen();

            break;
        case clsManageusers::enDeleteUser:

            _DeleteUser();
            MainUsersScreen();

            break;
        case clsManageusers::enUpdateUser:

            _UpdateUser();
            MainUsersScreen();

            break;
        case clsManageusers::enFindUser:

            _FindUser();
            MainUsersScreen();

            break;
        case clsManageusers::enMainMenue:

            _MainMenue();

            break;
        default:
            break;
        }

    }

    static enManageUsers ReadManageUsersOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return (enManageUsers)Choice;


    }

    static void _ListUsers(){
    
        system("cls");

        vector <clsUsers> vUsers = clsUsers::GetUsersList();

        MainScreen("\t  User List Screen");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUsers User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");
    
    }


    static void _AddNewUser(){
    
        system("cls");

        MainScreen("Add New User Screen");


        vector <clsUsers> vUsers = clsUsers::GetUsersList();

        string Username = "";
        cout << "Schreiben Sie bitte UserName : ";
        Username = clsString::ReadString();

        while (clsUsers::IsUserExist(Username)) {

            cout << "UserName wird benutzt!!Versuchen Sie noch mal bitte\n";
            cout << "Schreiben Sie bitte UserName : ";
            Username = clsString::ReadString();


        }

        clsUsers NewUser = clsUsers::GetNewUserObject(Username);

        _ReadUserInfo(NewUser);

        clsUsers::enSaveResults Result = NewUser.Save();

        if (Result == clsUsers::enSaveResults::svSucceeded) {

            cout << "Neue User wird erfolgreich hinzufugt\n";

            _PrintUser(NewUser);


        }
        else if (Result == clsUsers::enSaveResults::svFaildEmptyObject) {

            cout << "Falsch !!! User wird nicht hinzufugt!!!\n";

        }

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


    static void _DeleteUser(){
    
        system("cls");

        MainScreen("Delete User Screen");


        cout << "Schreiben Sie bitte User Name : ";
        string Username = clsString::ReadString();

        while (!clsUsers::IsUserExist(Username)) {

            cout << "Dieser User Name existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte User Name : ";
            Username = clsString::ReadString();

        }

        clsUsers User = clsUsers::Find(Username);

        _PrintUser(User);


        char Sicher = 'N';

        while (0 != 1) {

            cout << "Sind Sie sicher , den User zu loschen (Y/N) ? ";
            cin >> Sicher;

            if (Sicher == 'N' || Sicher == 'n') {
                cout << "Der User wird nicht geloscht\n";
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


        User = clsUsers::GetDeletedUserObject(Username);

        clsUsers::enSaveResults Result = User.Save();


        switch (Result) {

        case clsBankClient::enSaveResults::svSucceeded:
        {

            cout << "Der User wird erfolgreich geloscht\n";
            User = clsUsers::GetEmptyUserObject();
            _PrintUser(User);

            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {

            cout << "User Delet Faild, User wird nicht geloscht\n";
            break;

        }

        }


        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");
    
    
    }


    static void _UpdateUser(){
    
        system("cls");

        MainScreen("Update User Screen");



        cout << "Schreiben Sie bitte User Name : ";
        string Username = clsString::ReadString();

        while (!clsUsers::IsUserExist(Username)) {

            cout << "Dieser User Name existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte User Name : ";
            Username = clsString::ReadString();

        }

        clsUsers User = clsUsers::Find(Username);

        _PrintUser(User);


        char Sicher = 'N';

        while (0 != 1) {

            cout << "Sind Sie sicher , den User zu aktulisieren (Y/N) ? ";
            cin >> Sicher;

            if (Sicher == 'N' || Sicher == 'n') {
                cout << "Der User wird nicht aktulisiert\n";
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

        _ReadUserInfo(User);

        clsUsers::enSaveResults Result = User.Save();


        switch (Result) {

        case clsBankClient::enSaveResults::svSucceeded:
        {

            cout << "Der User wird erfolgreich geloscht\n";
            
            _PrintUser(User);

            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {

            cout << "User Delet Faild, User wird nicht geloscht\n";
            break;

        }

        }

    
    
        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


    static void _FindUser(){
    
        system("cls");

        cout << setw(37) << left << "" << "===========================================\n";
        MainScreen("Find User Screen");
        cout << setw(37) << left << "" << "===========================================\n";


        cout << "Schreiben Sie bitte User Name : ";
        string Username = clsString::ReadString();

        while (!clsUsers::IsUserExist(Username)) {

            cout << "Dieser User Name existiert nicht , versuchen Sie noch mal.\n";
            cout << "Schreiben Sie bitte User Name : ";
            Username = clsString::ReadString();

        }

        clsUsers User = clsUsers::Find(Username);

        _PrintUser(User);

    

        cout << "\t\t\tDrucken Sie bitte Irgendwelche Knopf...";
        system("pause > 0");

    }


    static void _MainMenue(){
    
    
    
    }     


public:


    static void MainUsersScreen() {

        system("cls");
        MainScreen("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
       cout << setw(37) << left << "" << "===========================================\n";
  
       _PerformManageUsersOption(ReadManageUsersOption());


    }


 
};

