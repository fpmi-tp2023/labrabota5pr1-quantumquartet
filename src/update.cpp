#include "update.h"

void UpdateMenu(sqlite3* db) {
    int choice;
    while (true) {
        std::cout << "Choose table to update information: \n"
            << "1.Horses\n"
            << "2.Jockeys\n"
            << "3.Owner\n"
            << "4.Races\n"
            << "5.Return\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            UpdateHorses(db);
            break;
        case 2:
            UpdateJockeys(db);
            break;
        case 3:
            UpdateOwners(db);
            break;
        case 4:
            UpdateRaces(db);
            break;
        case 5:
            return;
        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void UpdateHorses(sqlite3* db) {}

void UpdateJockeys(sqlite3* db) {}

void UpdateOwners(sqlite3* db) {}

void UpdateRaces(sqlite3* db) {
    const char* sql =
        "update races set date=?, number_of_race=?, horse_id=?, jockey_id=?, "
        "taken_place=?\n"
        "WHERE id=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string date;
    int id, number_of_race, horse_id, jockey_id, taken_place;

    do {
        std::cout << "Input date (YYYY-mm-dd): ";
        std::cin >> date;
        if (date == "exit") {
            return;
        }
        if (!DateCheck(date)) {
            std::cout << "\nWrong date, try again\n";
        }
    } while (!DateCheck(date));

    do {
        std::cout << "Choose id to delete";
        std::cin >> id;
        if (id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (id == 0) {
            return;
        }
    } while (id <= 0);

    do {
        std::cout << "Choose number of race to delete";
        std::cin >> number_of_race;
        if (number_of_race < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (number_of_race == 0) {
            return;
        }
    } while (number_of_race <= 0);

    do {
        std::cout << "Choose horse id to delete";
        std::cin >> horse_id;
        if (horse_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (horse_id == 0) {
            return;
        }
    } while (horse_id <= 0);

    do {
        std::cout << "Choose jockey id to delete";
        std::cin >> jockey_id;
        if (jockey_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (jockey_id == 0) {
            return;
        }
    } while (jockey_id <= 0);

    do {
        std::cout << "Choose taken place to delete";
        std::cin >> taken_place;
        if (taken_place < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (taken_place == 0) {
            return;
        }
    } while (taken_place <= 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, date.c_str(), date.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, number_of_race);
        sqlite3_bind_int(res, 3, horse_id);
        sqlite3_bind_int(res, 4, jockey_id);
        sqlite3_bind_int(res, 5, taken_place);
        sqlite3_bind_int(res, 6, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Updated succesfully";
}