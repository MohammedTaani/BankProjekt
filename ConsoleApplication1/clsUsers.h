#pragma once
#include "clsPerson.h"
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;


class clsUsers : public clsPerson
{

	enum enUsersMode{enEmptyMode = 1 , enUpdateMode = 2 , enNewMode = 3 , enDeleteMode = 4};

	enUsersMode _Mode;
	string _UserName;
	string _Password;
    int _Permissions;

    static clsUsers _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUsersData;
        vUsersData = clsString::SplitString(Line, Seperator);

        //Decription Password from the File
        string S1 = clsUtil::Decription(vUsersData[5], 8);

        return clsUsers(enUsersMode::enUpdateMode, vUsersData[0], vUsersData[1],
            vUsersData[2], vUsersData[3], vUsersData[4], S1, stoi(vUsersData[6]));

    }

    static string _ConverUserObjectToLine(clsUsers User, string Seperator = "#//#")
    {

        string stUsersRecord = "";
        stUsersRecord += User.FirstName + Seperator;
        stUsersRecord += User.LastName + Seperator;
        stUsersRecord += User.Email + Seperator;
        stUsersRecord += User.Phone + Seperator;
        stUsersRecord += User._UserName + Seperator;

        //Incription Password in the File
        string S1 = clsUtil::Incription(User._Password, 8);
        stUsersRecord += S1 + Seperator;

        stUsersRecord += to_string(User._Permissions);




        return stUsersRecord;

    }

    static  vector <clsUsers> _LoadUsersDataFromFile()
    {

        vector <clsUsers> vClients;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUsers User = _ConvertLinetoUserObject(Line);

                vClients.push_back(User);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveUsersDataToFile(vector <clsUsers> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUsers C : vUsers)
            {
                DataLine = _ConverUserObjectToLine(C);
                MyFile << DataLine << endl;

            }

            MyFile.close();

        }

    }

    static void _Update(clsUsers User) {

        vector <clsUsers> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUsers& C : _vUsers)
        {
            if (C._UserName == User._UserName)
            {
                C = User;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    static void _AddNewUser(clsUsers user) {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {


            DataLine = _ConverUserObjectToLine(user);
            MyFile << DataLine << endl;



            MyFile.close();

        }



    }

    void _Delet() {


        vector <clsUsers> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        vector <clsUsers> _vUsers2;

        for (clsUsers& C : _vUsers)
        {
            if (C._UserName != _UserName)
            {
                _vUsers2.push_back(C);
            }

        }

        _SaveUsersDataToFile(_vUsers2);

    }


public:

	clsUsers(enUsersMode Mode, string FirstName,
		string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;


	}
		 
    enum enPermissions {

        AllePermissions = -1, enShowClientListOption = 1, enAddNewClientOption = 2, enDeleteClientOption = 4,

        enUpdateClientInfoOption = 8, enFindClientOption = 16, enTransactionsOption = 32, enManageUsersOption = 64, enLoginRigisterOption = 128, enCurrencyExchange = 256

    };

     bool CheackPermissions(enPermissions Permission) {

        if (Permission == enPermissions::AllePermissions) {
            return true;
        }


        if ((Permission & Permissions) == Permission) {
            return true;
        }


        return false;


    }

    bool IsEmpty()
    {
        return (_Mode == enUsersMode::enEmptyMode);
    }

    void SetUserName(string UserName) {

        _UserName = UserName;

    }

    string GetUserName() {
        return _UserName;
    }

    __declspec(property(get = GetUsername, put = SetUsername)) string Username;

    void SetPassword(string Password) {

        _Password = Password;

    }

    string GetPassword() {
        return _Password;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions) {

        _Permissions = Permissions;

    }

     int GetPermissions() {
        return _Permissions;
    }

     __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUsers Find(string UserName)
    {


        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertLinetoUserObject(Line);
                if (User._UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }

        return GetEmptyUserObject();
    }

    static clsUsers Find(string UserName, string Password)
    {



        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertLinetoUserObject(Line);
                if (User._UserName == UserName && User._Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enUsersMode::enEmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }
        case enUsersMode::enUpdateMode:
        {

            _Update(*this);

            return enSaveResults::svSucceeded;

            break;
        }case enUsersMode::enNewMode: {



            if (IsUserExist(_UserName)) {

                cout << "User Name ist schon existiert!!!\n";

                return enSaveResults::svFaildEmptyObject;

            }
            else {

                _AddNewUser(*this);
                _Mode = enUsersMode::enUpdateMode;
                return enSaveResults::svSucceeded;

            }


            break;

        }case enUsersMode::enDeleteMode:
        {

            _Delet();

            return enSaveResults::svSucceeded;


            break;
        }


        }

    }

    static bool IsUserExist(string UserName)
    {

        clsUsers Client1 = clsUsers::Find(UserName);
        return (!Client1.IsEmpty());
    }

    static clsUsers GetEmptyUserObject()
    {
        return clsUsers(enUsersMode::enEmptyMode, "", "", "", "", "", "", 0);
    }

    static vector <clsUsers> GetUsersList() {

        return _LoadUsersDataFromFile();

    }

    static clsUsers GetNewUserObject(string UserName)
    {
        return clsUsers(enUsersMode::enNewMode, "", "", "", "", UserName, "", 0);
    }

    static clsUsers GetDeletedUserObject(string UserName)
    {
        return clsUsers(enUsersMode::enDeleteMode, "", "", "", "", UserName, "", 0);
    }

    static clsUsers GetUpdateUserObject(string UserName)
    {
        return clsUsers(enUsersMode::enUpdateMode, "", "", "", "", UserName, "", 0);
    }

};															   

