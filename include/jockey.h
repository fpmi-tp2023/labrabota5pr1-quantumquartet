#ifndef JOCKEY_H
#define JOCKEY_H

#include "menu.h"

void JockeyInterface(sqlite3* db, std::string surname);

void JockeyAllRaces(sqlite3* db, std::string surname);

void JockeyRacesInInterval(sqlite3* db, std::string surname);

#endif // JOCKEY_H