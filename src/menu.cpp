#include "menu.h"

void SignIn(sqlite3* db) {
    std::string surname;
    std::string password;
    std::string user_type;
    int user_type_id;
    int type_choice;
    std::cout << "Enter your surname: ";
    std::cin >> surname;
    if (surname == "exit") {
        return;
    }
    std::cout << "\nEnter password: ";
    std::cin >> password;
    if (password == "exit") {
        return;
    }
    const char* sql = "SELECT * from Users where surname=? and password=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, password.c_str(), password.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << "Wrong surname or password, try again\n\n";
        sqlite3_finalize(res);
    }
    else {
        user_type_id = sqlite3_column_int(res, 1);
        const char* sqlType = "Select type_name from User_type where id=? ";
        sqlite3_stmt* resType;
        int rcType = sqlite3_prepare_v2(db, sqlType, -1, &resType, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_int(resType, 1, user_type_id);
        }
        else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }
        int stepType = sqlite3_step(resType);
        user_type = std::string(
            reinterpret_cast<const char*>(sqlite3_column_text(resType, 0)));
        sqlite3_finalize(resType);

        if (user_type == "owner") {
            OwnerInterface(db, surname);
        }
        else if (user_type == "jockey") {
            JockeyInterface(db, surname);
        }
        else {
            ManagerInterface(db, surname);
        }

        sqlite3_finalize(res);
    }
}

void SignUp(sqlite3* db) {
    std::string surname;
    std::string password;
    int type_choice;
    std::cout << "Enter your surname: ";
    std::cin >> surname;
    if (surname == "exit") {
        return;
    }
    std::cout << "\nEnter password: ";
    std::cin >> password;
    if (password == "exit") {
        return;
    }

    const char* sql = "SELECT * from Users where surname=? and password=?;";
    sqlite3_stmt* res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
            SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, password.c_str(), password.length(),
            SQLITE_TRANSIENT);
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);
    if (step != SQLITE_ROW) {
        std::cout << "\nChoose user type:\n";

        const char* sqlType = "Select * from User_type";
        sqlite3_stmt* resType;
        int rcType = sqlite3_prepare_v2(db, sqlType, -1, &resType, 0);
        int stepType = sqlite3_step(resType);
        while (stepType == SQLITE_ROW) {
            for (int i = 0; i < sqlite3_column_count(resType); ++i) {
                std::cout << sqlite3_column_text(resType, i) << " ";
            }
            std::cout << "\n";
            stepType = sqlite3_step(resType);
        }
        sqlite3_finalize(resType);

        do {
            std::cin >> type_choice;
            if (type_choice == 0) {
                return;
            }
            if (type_choice > 3) {
                std::cout << "There is no such option, try again! \n";
            }
        } while (type_choice > 3);
        sqlite3_finalize(res);

        sql =
            "INSERT INTO users (surname, password, user_type_id) VALUES (?, ?, ?);";

        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

        if (rc == SQLITE_OK) {
            sqlite3_bind_text(res, 1, surname.c_str(), surname.length(),
                SQLITE_TRANSIENT);
            sqlite3_bind_text(res, 2, password.c_str(), password.length(),
                SQLITE_TRANSIENT);
            sqlite3_bind_int(res, 3, type_choice);
        }
        else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_step(res);
        sqlite3_finalize(res);

        std::cout << "You are succesfully registered\n";
    }
    else {
        std::cout << "This user already exist\n\n";
        sqlite3_finalize(res);
    }
}

void MainMenu(sqlite3* db) {
    int start_choice;
    while (true) {
        std::cout << "Welcome to the hippodrome! \n"
            << "Enter the desired number to continue: \n"
            << "1.Sign in \n"
            << "2.Sign up \n"
            << "3.Leave the hippodrome \n";
        std::cin >> start_choice;
        switch (start_choice) {
        case 1:
            SignIn(db);
            break;

        case 2:
            SignUp(db);
            break;

        case 3:
            return;

        default:
            std::cout << "There is no such action, try again! \n";
            break;
        }
    }
}
