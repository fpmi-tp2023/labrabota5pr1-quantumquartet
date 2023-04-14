#ifndef DELETE_H
#define DELETE_H

#include "menu.h"

void DeleteMenu(sqlite3* db);

void DeleteFromHorses(sqlite3* db);

void DeleteFromJockeys(sqlite3* db);

void DeleteFromOwners(sqlite3* db);

void DeleteFromRaces(sqlite3* db);

void DeleteFromUsers(sqlite3* db);

#endif // DELETE_H