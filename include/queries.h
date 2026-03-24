#ifndef QUERIES_H
#define QUERIES_H

#include "database.h"
#include <string>

class QueryService {
public:
    QueryService(Database& db);

    void show_trips_by_trawler_in_period(const std::string& trawler_name, const std::string& start_date, const std::string& end_date);
    void show_fish_by_bank(const std::string& bank_name);
    void show_low_quality_fish_trips();
    void show_captain_of_top_trawler();
    void show_crew_retiring_by_date(const std::string& date);

    bool add_crew_member(const std::string& surname, const std::string& position, const std::string& hire_date, int birth_year);
    bool update_crew_member(const std::string& old_surname, const std::string& new_surname);
    bool delete_crew_member(const std::string& surname);

    void calculate_bonus_for_unplanned_catch(const std::string& start_date, const std::string& end_date, int plan_kg, double cost_per_kg);
    void calculate_bonus_for_crew_member_in_period(const std::string& surname, const std::string& start_date, const std::string& end_date);

private:
    Database& db;
    void print_results(const std::vector<std::vector<std::string>>& results, const std::vector<std::string>& headers);
};

#endif // QUERIES_H
