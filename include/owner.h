#ifndef OWNER_H
#define OWNER_H

#include "menu.h"
void OwnerInterface(sqlite3* db, std::string surname);

void OwnerSelectData(sqlite3* db, std::string surname);

void OwnerSelectBestHorse(sqlite3* db, std::string surname);

#endif // OWNER_H

