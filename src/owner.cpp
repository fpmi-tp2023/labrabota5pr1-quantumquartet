#include "../include/owner.h"

void OwnerInterface(sqlite3* db, std::string surname) {
    int manager_choice;

    while (true) {
        std::cout << "\nWelcome back " << surname << "\n"
            << "Choose actions: \n"
            << "1.Show best horse \n"
            << "2.Show all horses \n"
            << "3.Return to the main menu \n";
        std::cin >> manager_choice;
        switch (manager_choice) {
        case 1:
            OwnerSelectBestHorse(db, surname);
            break;

        case 2:
            OwnerSelectData(db, surname);
            break;

        case 3:
            return;

        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void OwnerSelectData(sqlite3* db, std::string surname) {
    const char* sql =
        "Select O.surname as owner_surname, R.date as date_of_race, H.name as "
        "horse_name, R.taken_place\n"
        "from Races R\n"
        "inner join Horses H on R.horse_id = H.id\n"
        "inner join Owners O on R.jockey_id = O.id\n"
        "where O.surname like ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << surname << " don't have horses\n";
    }

    while (step == SQLITE_ROW) {
        for (int i = 0; i < sqlite3_column_count(res); ++i) {
            std::cout << sqlite3_column_name(res, i) << '='
                << sqlite3_column_text(res, i) << '\n';
        }
        std::cout << '\n';
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);
}

void OwnerSelectBestHorse(sqlite3* db, std::string surname) {
    const char* sql =
        "SELECT h.name as horse_name, h.age as horse_age, h.experience as "
        "horse_experience, h.paid_price as horse_price"
        ", owner_id as horse_owner_id, r.date as race_date, j.id as jockey_id, "
        "j.surname as jockey_surname"
        ", j.experience as jockey_experience, j.birth_date as jockey_birth_date, "
        "j.address as jockey_address\n"
        "FROM Horses h\n"
        "INNER JOIN Races r ON h.id = r.horse_id\n"
        "INNER JOIN Jockeys j ON j.id = r.jockey_id\n"
        "INNER JOIN Owners o ON o.id = h.owner_id\n"
        "WHERE r.taken_place = 1 \n"
        "AND h.id = (\n"
        "SELECT horse_id\n"
        "FROM Races\n"
        "WHERE taken_place = 1 and o.surname like ?\n"
        "GROUP BY horse_id\n"
        "ORDER BY COUNT(*) DESC\n"
        "limit 1\n"
        ");";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << surname << " don't have horses with first places\n";
    }

    while (step == SQLITE_ROW) {
        for (int i = 0; i < sqlite3_column_count(res); ++i) {
            std::cout << sqlite3_column_name(res, i) << '='
                << sqlite3_column_text(res, i) << '\n';
        }
        std::cout << '\n';
        step = sqlite3_step(res);
    }

    sqlite3_finalize(res);
}
