#include <iostream>
#include <ctime>
#include <regex>
#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>

#define INPUT_ERROR "Error when entering timer value. Use the required format(MM:SS)\n"

bool correct_input(std::string time_str) {
    std::regex time("([0-5]?\\d)(:)([0-5]?\\d)");
    std::cmatch result;

    if (std::regex_match(time_str.c_str(), result, time)) {
        std::cout << "Input success\n";
        return true;
    }

    std::cout << INPUT_ERROR;
    std::cerr << "Try again\n";

    return false;
}

std::tm input_timer() {
    std::time_t t = std::time(nullptr);
    std::tm timer = *std::localtime(&t);
    std::cout << std::asctime(&timer);

    std::string str;
    do {
        std::cout << "Enter timer value(format MM:SS): ";
        std::cin >> str;
    } while (!correct_input(str));

    std::stringstream buffer;
    buffer << str;

    buffer >> std::get_time(&timer, "%M:%S");
    std::cout << std::put_time(&timer, "%M:%S") << "\n";

    return timer;
}

int main() {
    std::tm timer = input_timer();

    std::time_t t = std::time(nullptr);
    while (timer.tm_min > 0 || timer.tm_sec > 0) {
        double d = std::time(nullptr) - t;
        if (d >= 1) {

            t = std::time(nullptr);
            timer.tm_sec--;
            std::cout << std::put_time(&timer, "%M:%S") << "\n";
            if (timer.tm_sec < 1 && timer.tm_min >= 1) {
                timer.tm_sec = 60;
                timer.tm_min--;
            }
        }
    }

    std::cout << "DING! DING! DING!\n";
    for (int i = 100; i < 500; i+=75) {
        Beep( i+300, 250 );
    }

    return 0;
}