#include "../include/delete.h"

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
            DeleteFromHorses(db);
            break;
        case 2:
            DeleteFromJockeys(db);
            break;
        case 3:
            DeleteFromOwners(db);
            break;
        case 4:
            DeleteFromRaces(db);
            break;
        case 5:
            DeleteFromUsers(db);
            break;
        case 6:
            return;
        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void DeleteFromHorses(sqlite3* db) {
    int id;
    do {
        std::cout << "Choose id to delete: ";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from horses where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully\n";
}

void DeleteFromJockeys(sqlite3* db) {
    int id;
    do {
        std::cout << "Choose id to delete: ";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from jockeys where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully\n";
}

void DeleteFromOwners(sqlite3* db) {
    int id;
    do {
        std::cout << "Choose id to delete: ";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from owners where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully\n";
}

void DeleteFromRaces(sqlite3* db) {
    int id;
    do {
        std::cout << "Choose id to delete: ";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from races where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully\n";
}

void DeleteFromUsers(sqlite3* db) {
    int id;
    do {
        std::cout << "Choose id to delete: ";
        std::cin >> id;
        if (id <= 0) {
            std::cout << "\nPlease choose positive number\n";
        }
    } while (id <= 0);

    const char* sql = "delete from users where id = ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Deleted succesfully\n";
}
