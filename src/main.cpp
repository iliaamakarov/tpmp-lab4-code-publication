#include <iostream>
#include <string>
#include <limits>
#include "database.h"
#include "auth.h"
#include "queries.h"

void display_captain_menu() {
    std::cout << "\n--- Captain Menu ---\n"
              << "1. Show trips by trawler\n"
              << "2. Show fish by bank\n"
              << "3. Show trips with max low-quality fish\n"
              << "4. Show captain of top trawler\n"
              << "5. Show retiring crew members\n"
              << "6. Add new crew member\n"
              << "7. Calculate bonus for unplanned catch\n"
              << "8. Calculate bonus for crew member\n"
              << "0. Logout\n"
              << "Enter choice: ";
}

void display_crewman_menu() {
    std::cout << "\n--- Crewman Menu ---\n"
              << "1. View my data (Not Implemented)\n"
              << "0. Logout\n"
              << "Enter choice: ";
}

void handle_captain_menu(QueryService& qs) {
    int choice;
    while (std::cin >> choice && choice != 0) {
        // Dummy data for demonstration
        std::string trawler = "Морской Волк";
        std::string start_date = "2023-10-01";
        std::string end_date = "2023-11-30";
        std::string bank = "Северная";
        std::string retirement_date = "2045-01-01";

        switch (choice) {
            case 1: qs.show_trips_by_trawler_in_period(trawler, start_date, end_date); break;
            case 2: qs.show_fish_by_bank(bank); break;
            case 3: qs.show_low_quality_fish_trips(); break;
            case 4: qs.show_captain_of_top_trawler(); break;
            case 5: qs.show_crew_retiring_by_date(retirement_date); break;
            case 6: qs.add_crew_member("Новиков", "sailor", "2024-01-01", 2000); break;
            case 7: qs.calculate_bonus_for_unplanned_catch(start_date, end_date, 2000, 5.5); break;
            case 8: qs.calculate_bonus_for_crew_member_in_period("Петров", start_date, end_date); break;
            default: std::cout << "Invalid choice.\n";
        }
        display_captain_menu();
    }
}

void handle_crewman_menu(const User& user) {
     int choice;
    while (std::cin >> choice && choice != 0) {
        switch (choice) {
            case 1: std::cout << "Displaying data for " << user.crew_surname << std::endl; break;
            default: std::cout << "Invalid choice.\n";
        }
        display_crewman_menu();
    }
}

int main() {
    // Recreate database on start
    system("make db");

    Database db("flotilla.db");
    AuthService auth(db);
    QueryService queries(db);

    while (true) {
        std::cout << "\n--- Welcome to Fishing Flotilla Management System ---\n";
        std::string username, password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        User user = auth.login(username, password);

        if (user.isAuthenticated) {
            std::cout << "\nLogin successful. Welcome, " << user.username << " (" << user.role << ")\n";
            if (user.role == "captain") {
                display_captain_menu();
                handle_captain_menu(queries);
            } else {
                display_crewman_menu();
                handle_crewman_menu(user);
            }
             // Clear buffer after menu loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cout << "Login failed. Please try again.\n";
        }
    }

    return 0;
}
