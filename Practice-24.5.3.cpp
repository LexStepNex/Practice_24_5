#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <iomanip>
#include <fstream>
#include <regex>
#include <algorithm>

struct calendar {
    std::map<int, std::vector<std::string>> birthday;
    std::map<int, std::vector<std::tm>> day_by_date;

    void add(int number_day, std::string &name) {
        birthday[number_day].push_back(name);
    }

    void next_birthday() {
        std::time_t t = time(nullptr);
        std::tm *local = std::localtime(&t);
        std::cout << asctime(local);

        if (birthday.find(local->tm_yday) != birthday.end()) {
            int size_vec_name = birthday[local->tm_yday].size();
            std::cout << "Today's " << std::put_time(local, "%m/%d") << " birthdays are celebrated: ";
            for (int i = 0; i < size_vec_name; i++) {
                std::cout << birthday[local->tm_yday][i] << (i == size_vec_name - 1 ? "\n" : ", ");
            }
            return;
        }

        int today = local->tm_yday;
        birthday[today].push_back("Today");

        std::cout << "Today: " << today << "\n";
        std::map<int, std::vector<std::string>>::iterator it = birthday.find(today);
        it++;
        if (it == birthday.end()) {
            it = birthday.begin();
        }

        std::cout <<"Next birthday: " << it->first << " " << it->second[0] << "\n";

        for (std::map<int, std::vector<std::string>>::iterator tt = birthday.begin(); tt != birthday.end(); tt++) {
            int size_vec_name = tt->second.size();
            std::cout <<"day in year: " << tt->first << " Birthday: ";
            for (int i = 0; i < size_vec_name; i++) {
                std::cout << tt->second[i] << (i == size_vec_name - 1 ? "\n" : ", ");
            }
        }
    }
};

bool dateControl(std::string date) {
    std::cmatch result;
    std::regex is31Day(
            "(\\d+)/([0]?[13578]|[1][02])/([0]?[1-9]|[1-2]?[0-9]|[3]?[0-1])");
    std::regex is30Day(
            "(\\d+)/([0]?[469]|[1][1])/([0]?[1-9]|[1-2]?[0-9]|[3]?[0])");
    std::regex february("(\\d+)/(0?2)/([0]?[1-9]|[1-2]?[0-9])");

    if (std::regex_match(date.c_str(), result, february)) {
        int dd = stoi(result[3]);
        int yyyy = stoi(result[0]);

        if ((yyyy % 400 == 0) || (yyyy % 4 == 0 && yyyy % 100 != 0)) {
            if (dd <= 29) {
                return true;
            } else
                std::cerr << "This month is 29 days\n";
            return false;
        } else {
            if (dd <= 28) {
                return true;
            } else
                std::cerr << "This month is 28 days\n";
            return false;
        }
    } else if (std::regex_match(date.c_str(), is30Day)) {
        return true;
    } else if (std::regex_match(date.c_str(), is31Day)) {
        return true;
    } else {
        std::cerr << "More days entered than in month\n";
        return false;
    }
}

int day_in_year() {
    std::time_t t = time(nullptr);
    std::tm *date = localtime(&t);

    std::string date_str;
    do {
        std::cout << "Input date of birth(format YYYY/MM/DD): ";
        std::cin >> date_str;
    } while (!dateControl(date_str));
    std::stringstream buffer;

    buffer << date_str;
    buffer >> std::get_time(date, "%Y/%m/%d");

    std::cout << std::asctime(date);

    int day_year = date->tm_yday;
    int year = date->tm_year + 1900;

    if (!((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) && (date->tm_mon > 1)) day_year++;
    std::cout << "Day in year: " << day_year << "\n";
    return day_year;
}

bool exit(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), tolower);
    if (name != "end") return true;
    else return false;
}

int main() {
    std::cout << "Birthday reminders\n";
    std::cout << "To exit to the name input field, enter \"end\"\n";
    calendar reminders;

    std::string name;
    while (exit(name)) {

        std::cout << "Enter the name of the birthday person: ";
        std::cin >> name;
        if (!exit(name)) continue;

        int number_day = day_in_year();
        reminders.add(number_day, name);
    }

    reminders.next_birthday();
    return 0;
}