#include "../include/update.h"

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

void UpdateHorses(sqlite3* db) {
    const char* sql =
        "update horses set name=?, age=?, experience=?, paid_price=?, owner_id=?\n"
        "WHERE id=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string name;
    int id, age, experience, owner_id;
    double paid_price;

    do {
        std::cout << "Choose name to update: ";
        std::cin >> name;
        if (!NameCheck(name)) {
            std::cout << "\nNot a name!\n";
        }
        if (name == "exit") {
            return;
        }
    } while (!NameCheck(name));

    do {
        std::cout << "Choose age to update: ";
        std::cin >> age;
        if (age < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (age == 0) {
            return;
        }
    } while (age <= 0);

    do {
        std::cout << "Choose experience to update: ";
        std::cin >> experience;
        if (experience < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (experience == 0) {
            return;
        }
    } while (experience <= 0);

    do {
        std::cout << "Choose paid price to update: ";
        std::cin >> paid_price;
        if (paid_price < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (paid_price == 0) {
            return;
        }
    } while (paid_price <= 0);

    do {
        std::cout << "Choose owner id to update: ";
        std::cin >> owner_id;
        if (owner_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (owner_id == 0) {
            return;
        }
    } while (owner_id <= 0);

    do {
        std::cout << "Choose id to update: ";
        std::cin >> id;
        if (id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (id == 0) {
            return;
        }
    } while (id <= 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, age);
        sqlite3_bind_int(res, 3, experience);
        sqlite3_bind_double(res, 4, paid_price);
        sqlite3_bind_int(res, 5, owner_id);
        sqlite3_bind_int(res, 6, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Updated succesfully\n";
}

void UpdateJockeys(sqlite3* db) {
    const char* sql =
        "update jockeys set surname=?, experience=?, birth_date=?, address=?\n"
        "WHERE id=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string date, surname, address;
    int id, experience;

    do {
        std::cout << "Input birth date (YYYY-mm-dd): ";
        std::cin >> date;
        if (date == "exit") {
            return;
        }
        if (!DateCheck(date)) {
            std::cout << "\nWrong date, try again\n";
        }
    } while (!DateCheck(date));

    do {
        std::cout << "Choose experience to update: ";
        std::cin >> experience;
        if (experience < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (experience == 0) {
            return;
        }
    } while (experience <= 0);

    do {
        std::cout << "Choose surname to update: ";
        std::cin >> surname;
        if (!NameCheck(surname)) {
            std::cout << "\nNot a surname!\n";
        }
        if (surname == "exit") {
            return;
        }
    } while (!NameCheck(surname));

        std::cout << "Choose adress to update: ";
        std::cin >> address;
        if (address == "exit") {
            return;
        }

    do {
        std::cout << "Choose id to update: ";
        std::cin >> id;
        if (id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (id == 0) {
            return;
        }
    } while (id <= 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, experience);
        sqlite3_bind_text(res, 3, date.c_str(), date.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 4, address.c_str(), address.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 5, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Updated succesfully\n";
}

void UpdateOwners(sqlite3* db) {
    const char* sql =
        "update owners set surname=?, name=?\n"
        "WHERE id=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string surname,name;
    int id;

    do {
        std::cout << "Choose surname to update: ";
        std::cin >> surname;
        if (!NameCheck(surname)) {
            std::cout << "\nNot a surname\n";
        }
        if (surname == "exit") {
            return;
        }
    } while (!NameCheck(surname));

    do {
        std::cout << "Choose name to update: ";
        std::cin >> name;
        if (!NameCheck(name)) {
            std::cout << "\nNot a name!\n";
        }
        if (name == "exit") {
            return;
        }
    } while (!NameCheck(name));

    do {
        std::cout << "Choose id to update: ";
        std::cin >> id;
        if (id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (id == 0) {
            return;
        }
    } while (id <= 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 3, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Updated succesfully\n";
}

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
        std::cout << "Choose id to update: ";
        std::cin >> id;
        if (id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (id == 0) {
            return;
        }
    } while (id <= 0);

    do {
        std::cout << "Choose number of race to update: ";
        std::cin >> number_of_race;
        if (number_of_race < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (number_of_race == 0) {
            return;
        }
    } while (number_of_race <= 0);

    do {
        std::cout << "Choose horse id to update: ";
        std::cin >> horse_id;
        if (horse_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (horse_id == 0) {
            return;
        }
    } while (horse_id <= 0);

    do {
        std::cout << "Choose jockey id to update: ";
        std::cin >> jockey_id;
        if (jockey_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (jockey_id == 0) {
            return;
        }
    } while (jockey_id <= 0);

    do {
        std::cout << "Choose taken place to update: ";
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
    std::cout << "Updated succesfully\n";
}