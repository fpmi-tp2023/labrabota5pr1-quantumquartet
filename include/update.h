#ifndef UPDATE_H
#define UPDATE_H

#include "menu.h"

void UpdateMenu(sqlite3* db);

void UpdateHorses(sqlite3* db);

void UpdateJockeys(sqlite3* db);

void UpdateOwners(sqlite3* db);

void UpdateRaces(sqlite3* db);

#endif // UPDATE_H