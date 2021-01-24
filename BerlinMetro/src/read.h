#pragma once
#include <vector>;
#include <string>;

int readConnections();
struct Connection
{
    std::string line;
    std::string station_1;
    std::string station_2;
    int first_number;
    int second_number;
    int third_number;
    double first_and_second_number;
};

