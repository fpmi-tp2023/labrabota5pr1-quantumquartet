#include "../include/manager.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    if (argc == 0) {
        std::cout << "No information is found";
    }

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void ManagerInterface(sqlite3* db, std::string surname) {
    int manager_choice;
    while (true) {
        std::cout << "Welcome back " << surname << "\n"
            << "Choose actions: \n"
            << "1.Show all races \n"
            << "2.Show most popular jockey \n"
            << "3.Set prize pool \n"
            << "4.Table interactions\n"
            << "5.return to main menu \n";
        std::cin >> manager_choice;
        switch (manager_choice) {
        case 1:
            ManagerSelectRaces(db);
            break;

        case 2:
            ManagerSelectBestJockey(db);
            break;

        case 3:
            double prize_pool;
            std::cout << "Choose prize pool: ";

            do {
                std::cin >> prize_pool;
                if (prize_pool <= 0) {
                    std::cout << "\nPlease choose positive number\n";
                }
            } while (prize_pool <= 0);
            PrizePoolDistribution(db, prize_pool);
            break;

        case 4:
            TableInteractions(db);

        case 5:
            return;

        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void ManagerSelectRaces(sqlite3* db) {
    std::string intervalBegin;
    std::string intervalEnd;
    do {
        std::cout << "Input interval begin (YYYY-mm-dd): ";
        std::cin >> intervalBegin;
        if (intervalBegin == "exit") {
            return;
        }
        if (!DateCheck(intervalBegin)) {
            std::cout << "\nWrong date, try again\n";
        }
    } while (!DateCheck(intervalBegin));
    do {
        std::cout << "Input interval end (YYYY-mm-dd): ";
        std::cin >> intervalEnd;
        if (intervalEnd == "exit") {
            return;
        }
        if (!DateCheck(intervalEnd)) {
            std::cout << "\nWrong date, try again\n";
        }
    } while (!DateCheck(intervalEnd));
    const char* sql =
        "Select R.id as race_id, R.date as date_of_race, R.number_of_race, "
        "R.taken_place,"
        "R.jockey_id, H.id as horse_id, H.name as horse_name, H.age as horse_age,"
        "H.experience as horse_experience, H.paid_price as horse_price, "
        "H.owner_id as horse_owner_id\n"
        "from Races R\n"
        "inner join Horses H on R.horse_id = H.id\n"
        "where date between ? and ?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, intervalBegin.c_str(), intervalBegin.length(),
            SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, intervalEnd.c_str(), intervalEnd.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << "There are no races during this interval\n";
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

void ManagerSelectBestJockey(sqlite3* db) {
    const char* sql =
        "SELECT jockey_id, J.surname as jockey_surname, J.address as "
        "jockey_address,"
        "J.birth_date as jockey_birth_date, J.experience as jockey_experience, "
        "B.all_races_amount\n"
        "FROM("
        "SELECT jockey_id, count(jockey_id) as all_races_amount\n"
        "from races R\n"
        "inner join Jockeys J on R.jockey_id = J.id\n"
        "group by jockey_id"
        ") as B\n"
        "inner join Jockeys J on B.jockey_id = J.id\n"
        "where B.all_races_amount = (select max(A.all_races_amount) FROM(SELECT "
        "jockey_id, count(jockey_id) as all_races_amount\n"
        "from races R\n"
        "inner join Jockeys  J on R.jockey_id = J.id\n"
        "group by jockey_id"
        ") as A\n"
        "where(jockey_id = A.jockey_id));";

    char* zErrMsg = 0;
    const char* data = "Callback function called";

    int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
    }
}

void TableInteractions(sqlite3* db) {
    int choice;
    while (true) {
        std::cout << "Choose actions : \n"
            << "1.Insert\n"
            << "2.Update\n"
            << "3.Delete\n"
            << "4.Return\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            InsertMenu(db);
            break;
        case 2:
            UpdateMenu(db);
            break;
        case 3:
            DeleteMenu(db);
            break;
        case 4:
            return;
        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}

void PrizePoolDistribution(sqlite3* db, double prize_pool) {
    const char* sql =
        "select H.name from races R\n"
        "inner join Horses H on H.id=R.horse_id\n"
        "where date = (select max(date) from races)\n"
        "and number_of_race = (select max(number_of_race) from races)\n"
        "limit 3; ";

    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << "don't have any races in this time interval\n";
    }
    else {
        std::cout << sqlite3_column_text(res, 0) << " prize is " << prize_pool * 0.5
            << '\n';
        step = sqlite3_step(res);
        std::cout << sqlite3_column_text(res, 0) << " prize is " << prize_pool * 0.3
            << '\n';
        step = sqlite3_step(res);
        std::cout << sqlite3_column_text(res, 0) << " prize is " << prize_pool * 0.2
            << '\n';
        step = sqlite3_step(res);
        std::cout << '\n';
    }

    sqlite3_finalize(res);
}
