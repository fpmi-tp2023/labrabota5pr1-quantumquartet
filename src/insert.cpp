#include "../include/insert.h"

void InsertMenu(sqlite3* db) {
    int choice;
    while (true) {
        std::cout << "Choose table to insert information: \n"
            << "1.Horses\n"
            << "2.Jockeys\n"
            << "3.Owner\n"
            << "4.Races\n"
            << "5.Return\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            InsertIntoHorses(db);
            break;
        case 2:
            InsertIntoJockeys(db);
            break;
        case 3:
            InsertIntoOwners(db);
            break;
        case 4:
            InsertIntoRaces(db);
            break;
        case 5:
            return;
        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void InsertIntoHorses(sqlite3* db) {
    const char* sql =
        "insert into horses (name, age, experience, paid_price, owner_id)\n"
        "values(?, ?, ?, ?, ?);";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string name;
    int age, experience, owner_id;
    double paid_price;

    do {
        std::cout << "Choose name to insert: ";
        std::cin >> name;
        if (!NameCheck(name)) {
            std::cout << "\nNot a name!\n";
        }
        if (name == "exit") {
            return;
        }
    } while (!NameCheck(name));

    do {
        std::cout << "Choose age to insert: ";
        std::cin >> age;
        if (age < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (age == 0) {
            return;
        }
    } while (age <= 0);

    do {
        std::cout << "Choose experience to insert: ";
        std::cin >> experience;
        if (experience < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (experience == 0) {
            return;
        }
    } while (experience <= 0);

    do {
        std::cout << "Choose paid price to insert: ";
        std::cin >> paid_price;
        if (paid_price < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (paid_price == 0) {
            return;
        }
    } while (paid_price <= 0);

    do {
        std::cout << "Choose owner id to insert: ";
        std::cin >> owner_id;
        if (owner_id < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (owner_id == 0) {
            return;
        }
    } while (owner_id <= 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, age);
        sqlite3_bind_int(res, 3, experience);
        sqlite3_bind_double(res, 4, paid_price);
        sqlite3_bind_int(res, 5, owner_id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Inserted succesfully\n";
}

void InsertIntoJockeys(sqlite3* db) {
    const char* sql =
        "insert into jockeys (surname, experience, birth_date, address\n"
        "values(?, ?, ?, ?);";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string date, surname, address;
    int experience;

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
        std::cout << "Choose experience to insert: ";
        std::cin >> experience;
        if (experience < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (experience == 0) {
            return;
        }
    } while (experience <= 0);

    do {
        std::cout << "Choose surname to insert: ";
        std::cin >> surname;
        if (!NameCheck(surname)) {
            std::cout << "\nNot a surname!\n";
        }
        if (surname == "exit") {
            return;
        }
    } while (!NameCheck(surname));

    std::cout << "Choose adress to insert: ";
    std::cin >> address;
    if (address == "exit") {
        return;
    }

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, experience);
        sqlite3_bind_text(res, 3, date.c_str(), date.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 4, address.c_str(), address.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Inserted succesfully\n";
}

void InsertIntoOwners(sqlite3* db) {
    const char* sql =
        "insert into owners (surname, name)\n"
        "values (?, ?);";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string surname, name;

    do {
        std::cout << "Choose surname to insert: ";
        std::cin >> surname;
        if (!NameCheck(surname)) {
            std::cout << "\nNot a surname\n";
        }
        if (surname == "exit") {
            return;
        }
    } while (!NameCheck(surname));

    do {
        std::cout << "Choose name to insert: ";
        std::cin >> name;
        if (!NameCheck(name)) {
            std::cout << "\nNot a name!\n";
        }
        if (name == "exit") {
            return;
        }
    } while (!NameCheck(name));

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Inserted succesfully\n";
}

void InsertIntoRaces(sqlite3* db) {
    const char* sql =
        "insert into races (date, race_number, horse_id, jockey_id, "
        "taken_place)\n"
        "values (?, ?, ?, ?, ?);";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    std::string date;
    int number_of_race, horse_id, jockey_id, taken_place;

    do {
        std::cout << "Choose horse id to insert: ";
        std::cin >> horse_id;
        if (horse_id == 0) {
            return;
        }
    } while (!CheckHorseExistance(db, horse_id));

    do {
        std::cout << "Choose jockey id to insert: ";
        std::cin >> jockey_id;
        if (jockey_id == 0) {
            return;
        }
    } while (!CheckJockeyExistance(db, jockey_id));

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
        std::cout << "Choose number of race to insert: ";
        std::cin >> number_of_race;
        if (number_of_race < 0) {
            std::cout << "\nPlease choose positive number\n";
        }
        if (number_of_race == 0) {
            return;
        }
    } while (number_of_race <= 0);

    do {
        std::cout << "Choose taken place to insert: ";
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
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    sqlite3_finalize(res);
    std::cout << "Inserted succesfully\n";
}

bool CheckHorseExistance(sqlite3* db, int id) {
    const char* sql = "select id from horses where id = ?";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);
    if (step != SQLITE_ROW) {
        std::cout << "No such horse\n";
        return false;
    }
    else {
        sqlite3_finalize(res);
        return true;
    }
}

bool CheckJockeyExistance(sqlite3* db, int id) {
    const char* sql = "select id from jockey where id = ?";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, id);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    sqlite3_finalize(res);
    if (step != SQLITE_ROW) {
        std::cout << "No such jockey\n";
        return false;
    }
    else {
        sqlite3_finalize(res);
        return true;
    }
}