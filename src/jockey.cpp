#include "jockey.h"

bool DateCheck(std::string date) {


	std::regex rgx("(((19[0-9]{2})|(20[0-1][0-9])|(202[0-3]))-((0[13578])|(1[02]))-(([0-2][0-9])|(3[01])))"
		"|(((19[0-9]{2})|(20[0-1][0-9])|(202[0-3]))-(0[469]|(11))-(([0-2][0-9])|(30)))"
		"|(((19[0-9]{2})|(20[0-1][0-9])|(202[0-3]))-02-[0-2][0-8])");
	return std::regex_match(date, rgx);

}

void JockeyInterface(sqlite3* db, std::string surname) {
	
		int manager_choice;
		while (true)
		{
			std::cout << "\nWelcome back " << surname << "\n" << "Choose actions: \n"
				<< "1.Show all races \n" << "2.Show races in time interval \n" << "3.Return to the main menu \n";
			std::cin >> manager_choice;
			switch (manager_choice)
			{
			case 1:
				JockeyAllRaces(db, surname);
				break;

			case 2:
				JockeyRacesInInterval(db, surname);
				break;

			case 3:
				return;

			default:
				std::cout << "There is no such action, try again!\n";
				break;

			}
		}
	
}

void JockeyAllRaces(sqlite3* db, std::string surname) {
	const char* sql = "Select J.surname as jockey_surname,H.name as horse_name,R.date as date_of_race,R.taken_place\n"
		"from Races R\n"
		"inner join Horses H on R.horse_id = H.id\n"
		"inner join Jockeys j on R.jockey_id = J.id\n"
		"where J.surname like ?;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, surname.c_str(), surname.length(), SQLITE_TRANSIENT);
	}
	else {
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW) {
		std::cout << surname << "don't have any races\n";
	}
	while (step == SQLITE_ROW) {
		for (int i = 0; i < sqlite3_column_count(res); ++i) {
			std::cout << sqlite3_column_name(res, i) << '=' << sqlite3_column_text(res, i) << '\n';
		}
		std::cout << '\n';
		step = sqlite3_step(res);
	}

	sqlite3_finalize(res);
}

void JockeyRacesInInterval(sqlite3* db, std::string surname) {
	std::string intervalBegin;
	std::string intervalEnd;
	do{ 
		std::cout << "Input interval begin (YYYY-mm-dd): ";
		std::cin >> intervalBegin;
		if (intervalBegin == "exit") {
			return;
		}
		if (!DateCheck(intervalBegin))
		{
		std::cout << "\nWrong date, try again\n";
		}
	} while (!DateCheck(intervalBegin));
	do {
		std::cout << "Input interval end (YYYY-mm-dd): ";
		std::cin >> intervalEnd;
		if (intervalEnd == "exit") {
			return;
		}
		if (!DateCheck(intervalEnd))
		{
			std::cout << "\nWrong date, try again\n";
		}
	} while (!DateCheck(intervalEnd));
	const char* sql = "Select  R.jockey_id,J.surname as jockey_surname,"
		"J.experience as jockey_experience,J.birth_date as jockey_birth_date,"
		"j.address as jockey_address,"
		"R.id as race_id, R.date as race_date, R.number_of_race, R.horse_id, R.taken_place\n"
		"from Races R\n"
		"inner join Horses H on R.horse_id = H.id\n"
		"inner join Jockeys j on R.jockey_id = J.id\n"
	"where J.surname like ? and date between ? and ?;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, surname.c_str(), surname.length(), SQLITE_TRANSIENT);
		sqlite3_bind_text(res, 2, intervalBegin.c_str(), intervalBegin.length(), SQLITE_TRANSIENT);
		sqlite3_bind_text(res, 3, intervalEnd.c_str(), intervalEnd.length(), SQLITE_TRANSIENT);
	}
	else {
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW) {
		std::cout << surname << "don't have any races in this time interval\n";
	}
	while (step == SQLITE_ROW) {
		for (int i = 0; i < sqlite3_column_count(res); ++i) {
			std::cout << sqlite3_column_name(res, i) << '=' << sqlite3_column_text(res, i) << '\n';
		}
		std::cout << '\n';
		step = sqlite3_step(res);
	}

	sqlite3_finalize(res);

}