#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

bool correct_ans(std::string ans) {
    if (ans == "begin" || ans == "end" || ans == "status" || ans == "exit")
        return true;
    else {
        std::cout << "Error, unknown operation, please try again\n";
        return false;
    }
}

std::string answer() {
    std::string ans;
    do {
        std::cout << "Input operation(begin, end, status or exit): ";
        std::cin >> ans;
        std::transform(ans.begin(), ans.end(), ans.begin(), tolower);
    } while (!correct_ans(ans));
    return ans;
}

void end_operation(std::time_t &start, std::string &name_task) {
    if (start == 0) return;

    std::ofstream tasks("data_tasks.txt", std::ios::app);
    std::time_t finish = std::time(nullptr);

    double result = std::difftime(finish, start);

    tasks << name_task << " " << result << "\n";

    start = 0;
    finish = 0;
    name_task = "";

    tasks.close();
}

void new_operation(std::time_t &start, std::string &name_task) {
    if (start != 0) end_operation(start, name_task);

    std::cout << "Input name task:";
    std::cin >> name_task;

    start = time(nullptr);
}

void status_task(std::time_t start, std::string name_task) {
    std::ifstream tasks("data_tasks.txt");

    std::string str;
    while (std::getline(tasks, str)) {
        std::stringstream data_task;
        data_task << str;

        std::string name_finish_task;
        double time_finish_task;
        data_task >> name_finish_task >> time_finish_task;

        std::cout << "The \"" << name_finish_task << "\" task was completed in "
                  << time_finish_task << " second\n";
    };
    tasks.close();

    if (start != 0) std::cout << "Current task: " << name_task << "\n";
}

int main() {
    std::cout << "Timer simulation\n\n";
    std::string name_task;
    std::time_t start = 0;

    std::string ans;
    do {
        ans = answer();
        if (ans == "end") end_operation(start, name_task);
        if (ans == "begin") new_operation(start, name_task);
        if (ans == "status") status_task(start, name_task);
    } while (ans != "exit");

    return 0;
}
