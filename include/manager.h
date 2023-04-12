#pragma once
#include "menu.h"

void ManagerInterface(sqlite3* db, std::string surname);

void ManagerSelectRaces(sqlite3* db);

void ManagerSelectBestJockey(sqlite3* db);

void PrizePoolDistribution(sqlite3* db);

void Update();

void Insert();

void Delete();

void UpdateMenu();

void InsertMenu();

void DeleteMenu();

static int callback(void* NotUsed, int argc, char** argv, char** azColName);