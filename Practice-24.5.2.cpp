#include <iostream>
#include <ctime>
#include <map>

int main() {
    std::time_t t = 10;
    std::cout << std::ctime(&t);
    return 0;
}