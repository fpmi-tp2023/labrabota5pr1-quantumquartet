#include "../include/menu.h"

int main() {
    sqlite3* db;
    int rc;

    rc = sqlite3_open("../hippodrome.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else {
        MainMenu(db);
    }
    sqlite3_close(db);
    return 0;
}
