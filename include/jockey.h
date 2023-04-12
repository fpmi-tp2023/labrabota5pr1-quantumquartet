#pragma once
#include "menu.h"

void JockeyInterface(sqlite3* db, std::string surname);

void JockeyAllRaces(sqlite3* db, std::string surname);

void JockeyRacesInInterval(sqlite3* db, std::string surname);

bool DateCheck(std::string date);