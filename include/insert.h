#ifndef INSERT_H
#define INSERT_H

#include "menu.h"

void InsertMenu(sqlite3* db);

void InsertIntoHorses(sqlite3* db);

void InsertIntoJockeys(sqlite3* db);

void InsertIntoOwners(sqlite3* db);

void InsertIntoRaces(sqlite3* db);

bool CheckHorseExistance(sqlite3* db, int id);

bool CheckJockeyExistance(sqlite3* db, int id);

#endif // INSERT_H
