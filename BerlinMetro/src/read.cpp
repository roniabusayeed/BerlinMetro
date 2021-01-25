#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "read.h"




std::vector<std::string> split(const std::string& str, const std::string& delim);

std::vector<Connection> readConnections()
{
    std::vector<Connection> connections;
    const char* input_file_path = "Berlin.txt";
    std::ifstream infile(input_file_path);
    if (!infile.is_open())
    {
        std::cout << "Couldn't open " << input_file_path << std::endl;
        return connections;
    }


    std::string data;
    while (std::getline(infile, data))
    {
        // Parse the line read in 'data'
        auto two_parts = split(data, ":");
        auto line_station_1_and_station_2 = split(two_parts[0], "->");
        std::string line_station_1 = line_station_1_and_station_2[0];
        std::string station_2 = line_station_1_and_station_2[1];
        std::string line = split(line_station_1, " ")[0];
        std::string station_1 = line_station_1.substr(line_station_1.find(' ') + 1);
        std::stringstream ss;
        ss << two_parts[1];
        int first_number;
        ss >> first_number;
        ss.get();
        int second_number;
        ss >> second_number;
        int third_number;
        ss >> third_number;
        double first_and_second_number = (double)first_number + ((double)second_number / 10);

        // Create the object containg all the parsed data.
        Connection conn;
        conn.line = line;
        conn.station_1 = station_1;
        conn.station_2 = station_2;
        conn.first_number = first_number;
        conn.second_number = second_number;
        conn.third_number = third_number;
        conn.first_and_second_number = first_and_second_number;

        // Add the object to the list of connection.
        connections.push_back(conn);
    }

    return connections;

    // Print all connections from memory to check if read correctly.
    /*for (int i = 0; i < connections.size(); i++)
    {
 
        std::cout << connections[i].line << " " << connections[i].station_1 << " -> "
            << connections[i].station_2 << ": " << connections[i].first_and_second_number << " " << connections[i].third_number << std::endl;
        
   }*/
}


std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
