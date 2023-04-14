#ifndef MENU_H
#define MENU_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "sqlite3.h"
#include <cstring>
#include <string.h>
#include <string>
#include "jockey.h"
#include "owner.h"
#include "manager.h"
#include "update.h"
#include "delete.h"
#include "insert.h"
#include <regex>


void SignIn(sqlite3* db);

void SignUp(sqlite3* db);

void MainMenu(sqlite3* db);

bool NameCheck(std::string name);

bool DateCheck(std::string date);

#endif // MENU_H