#include "delete.h"

void DeleteMenu(sqlite3* db) {
    int choice;
    while (true) {
        std::cout << "Choose table to delete information: \n"
            << "1.Horses\n"
            << "2.Jockeys\n"
            << "3.Owners\n"
            << "4.Races\n"
            << "5.Users\n"
            << "6.Return\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            DeleteFromTable(db, "horses");
            break;
        case 2:
            DeleteFromTable(db, "jockeys");
            break;
        case 3:
            DeleteFromTable(db, "owners");
            break;
        case 4:
            DeleteFromTable(db, "races");
            break;
        case 5:
            DeleteFromTable(db, "users");
            break;
        case 6:
            return;
        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void DeleteFromTable(sqlite3* db, std::string table) {
    int id;

    do {
        std::cout << "Choose id to delete";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from ? where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, table.c_str(), table.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully";
}
