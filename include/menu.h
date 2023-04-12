#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "sqlite3.h"
#include <cstring>
#include <string.h>
#include <string>
#include "jockey.h"
#include "owner.h"
#include "manager.h"
#include <regex>


void SignIn(sqlite3* db);

void SignUp(sqlite3* db);

void MainMenu(sqlite3* db);
