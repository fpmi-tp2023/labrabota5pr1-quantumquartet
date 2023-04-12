#pragma once
#include "menu.h"

void ManagerInterface(sqlite3* db, std::string surname);

void ManagerSelectRaces(sqlite3* db);

void ManagerSelectBestJockey(sqlite3* db);

void PrizePoolDistribution(sqlite3* db, double prize_pool);

void TableInteractions(sqlite3* db);

static int callback(void* NotUsed, int argc, char** argv, char** azColName);