#pragma once
#include <iostream>
#include "clsUsers.h"


clsUsers MainUser = clsUsers::Find("", "");

static bool Stop = false;


static string GetUser() {

	return MainUser.GetUserName();

}