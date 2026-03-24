#include "queries.h"
#include <iostream>
#include <iomanip>
#include <vector>

QueryService::QueryService(Database& db) : db(db) {}

void QueryService::print_results(const std::vector<std::vector<std::string>>& results, const std::vector<std::string>& headers) {
    if (results.empty()) {
        std::cout << "No results found." << std::endl;
        return;
    }

    // Print headers
    for (const auto& header : headers) {
        std::cout << std::left << std::setw(20) << header;
    }
    std::cout << std::endl;
    std::cout << std::string(headers.size() * 20, '-') << std::endl;

    // Print rows
    for (const auto& row : results) {
        for (const auto& col : row) {
            std::cout << std::left << std::setw(20) << col;
        }
        std::cout << std::endl;
    }
}

void QueryService::show_trips_by_trawler_in_period(const std::string& trawler_name, const std::string& start_date, const std::string& end_date) {
    std::cout << "\n--- Trips for Trawler: " << trawler_name << " from " << start_date << " to " << end_date << " ---\n";
    std::string sql = "SELECT T.id, T.exit_date, T.return_date, SUM(TR.fish_quantity_kg) as total_catch "
                      "FROM TRIPS T "
                      "JOIN TRIP_RESULTS TR ON T.id = TR.trip_id "
                      "WHERE T.trawler_name = '" + trawler_name + "' "
                      "AND T.exit_date >= '" + start_date + "' AND T.return_date <= '" + end_date + "' "
                      "GROUP BY T.id;";
    auto results = db.query(sql);
    print_results(results, {"Trip ID", "Exit Date", "Return Date", "Total Catch (kg)"});
}

void QueryService::show_fish_by_bank(const std::string& bank_name) {
    std::cout << "\n--- Fish caught at bank: " << bank_name << " ---\n";
    std::string sql = "SELECT fish_name, fish_quality, SUM(fish_quantity_kg) as total_quantity "
                      "FROM TRIP_RESULTS "
                      "WHERE bank_name = '" + bank_name + "' "
                      "GROUP BY fish_name, fish_quality;";
    auto results = db.query(sql);
    print_results(results, {"Fish Name", "Quality", "Total Quantity (kg)"});
}

void QueryService::show_low_quality_fish_trips() {
    std::cout << "\n--- Trips with max low-quality fish ---\n";
    std::string sql = "SELECT T.trawler_name, T.exit_date, T.return_date "
                      "FROM TRIPS T JOIN TRIP_RESULTS TR on T.id = TR.trip_id "
                      "WHERE TR.fish_quality = 'low' AND TR.bank_name = ("
                      "  SELECT bank_name FROM TRIP_RESULTS WHERE fish_quality = 'low' "
                      "  GROUP BY bank_name ORDER BY SUM(fish_quantity_kg) DESC LIMIT 1"
                      ");";
    auto results = db.query(sql);
    print_results(results, {"Trawler", "Exit Date", "Return Date"});
}

void QueryService::show_captain_of_top_trawler() {
    std::cout << "\n--- Captain of the trawler with the most catch ---\n";
    std::string sql = "SELECT C.surname, C.position, TS.trawler_name, TS.total_fish_caught "
                      "FROM TRAWLER_STATS TS "
                      "JOIN CREW C ON C.position = 'captain' "
                      "ORDER BY TS.total_fish_caught DESC LIMIT 1;";
    auto results = db.query(sql);
    print_results(results, {"Captain", "Position", "Trawler", "Total Catch (kg)"});
}

void QueryService::show_crew_retiring_by_date(const std::string& date) {
    int current_year = std::stoi(date.substr(0, 4));
    int retirement_age = 65;
    std::cout << "\n--- Crew members retiring by " << date << " ---\n";
    std::string sql = "SELECT surname, position, birth_year FROM CREW WHERE "
                      + std::to_string(current_year) + " - birth_year >= " + std::to_string(retirement_age) + ";";
    auto results = db.query(sql);
    print_results(results, {"Surname", "Position", "Birth Year"});
}

bool QueryService::add_crew_member(const std::string& surname, const std::string& position, const std::string& hire_date, int birth_year) {
    std::string sql = "INSERT INTO CREW (surname, position, hire_date, birth_year) VALUES ('" +
                      surname + "', '" + position + "', '" + hire_date + "', " + std::to_string(birth_year) + ");";
    return db.execute(sql);
}

bool QueryService::update_crew_member(const std::string& old_surname, const std::string& new_surname) {
    std::string sql = "UPDATE CREW SET surname = '" + new_surname + "' WHERE surname = '" + old_surname + "';";
    return db.execute(sql);
}

bool QueryService::delete_crew_member(const std::string& surname) {
    std::string sql = "DELETE FROM CREW WHERE surname = '" + surname + "';";
    return db.execute(sql);
}

void QueryService::calculate_bonus_for_unplanned_catch(const std::string& start_date, const std::string& end_date, int plan_kg, double cost_per_kg) {
    std::cout << "\n--- Calculating bonus for unplanned catch ---\n";
    // This is a simplified example. A real implementation would be more complex.
    std::string get_total_catch_sql = "SELECT SUM(TR.fish_quantity_kg) FROM TRIP_RESULTS TR "
                                      "JOIN TRIPS T ON TR.trip_id = T.id WHERE "
                                      "T.exit_date >= '" + start_date + "' AND T.return_date <= '" + end_date + "';";
    auto results = db.query(get_total_catch_sql);
    if (results.empty() || results[0][0] == "NULL") {
        std::cout << "No catch found in the period." << std::endl;
        return;
    }
    int total_catch = std::stoi(results[0][0]);
    if (total_catch > plan_kg) {
        double unplanned_catch = total_catch - plan_kg;
        double total_bonus = unplanned_catch * cost_per_kg * 0.1; // 10% bonus pool
        std::cout << "Total unplanned catch: " << unplanned_catch << " kg." << std::endl;
        std::cout << "Total bonus pool to distribute: " << total_bonus << std::endl;
        // Logic to distribute among crew and insert into BONUSES table would go here
    } else {
        std::cout << "Plan was not exceeded. No bonus." << std::endl;
    }
}

void QueryService::calculate_bonus_for_crew_member_in_period(const std::string& surname, const std::string& start_date, const std::string& end_date) {
    std::cout << "\n--- Calculating bonus for " << surname << " ---\n";
    // Dummy implementation
    double bonus = 123.45; // Placeholder
    std::string sql = "INSERT INTO BONUSES (crew_surname, bonus_amount, calculation_date) VALUES ('" +
                      surname + "', " + std::to_string(bonus) + ", date('now'));";
    if (db.execute(sql)) {
        std::cout << "Bonus of " << bonus << " calculated and saved for " << surname << std::endl;
    } else {
        std::cout << "Failed to save bonus." << std::endl;
    }
}
