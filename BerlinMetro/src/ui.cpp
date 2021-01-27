#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "ui.h"
#include "edge.h"
#include "read.h"


void UI::loop()
{
	
	unsigned choice = 0;
	do
	{
		listMenuOptions();
		choice = readChoice("> Please select menu option: ", 0, m_menu.size() - 1);
		std::cout << "\n";

		switch (choice)
		{

		case 0:
			outputAllConnections();
			break;
		case 1:
			findBestConnection();
			break;
		case 2:
			addTrainConnection();
			break;
		}
	} while (choice != 3);
	//write to file here
	//writeToFile();
	std::cout << ">Changes saved to file.\n";
	std::cout << "> Program ended.\n";
}

void UI::listMenuOptions() const
{
	unsigned i = 0;
	for (auto txt : m_menu)
	{
		std::cout << "  - " << i << ": " << txt << '\n';
		i++;
	}
}

unsigned UI::readChoice(std::string msg, unsigned min, unsigned max) const
{
	std::cout << msg;
	int choice;
	std::cin >> choice;
	while ((choice < min) || (choice > max))
	{
		std::cout << "> Error: Please provide integer between " << min << " and " << max << ": ";
		std::cin >> choice;
	}
	return choice;
}

void UI::outputAllConnections()
{
	std::vector<Connection> connections = readConnections();

	std::cout << "0. Sort by train line\n";
	std::cout << "1. Sort by alphabet\n";

	unsigned choice = readChoice("> Select optimization: ", 0, 1);
	std::cout << "\n";

	if (choice == 0)
	{
	
		//Sort by line

		for (int i = 0; i < connections.size(); i++)
		{

			std::cout << connections[i].line << " " << connections[i].station_1 << " -> "
				<< connections[i].station_2 << ": " << connections[i].first_and_second_number << " " << connections[i].third_number << std::endl;

		}
		std::cout << "\n\n";
	}
	else if (choice == 1)
	{
		//Sort by alphabet
	}

}

void UI::findBestConnection()
{
	//choose optimization for distance or optimization for duration
	std::cout << "0. Optimize for duration\n";
	std::cout << "1. Otimize for distance\n";

	unsigned choice = readChoice("> Select optimization: ", 0, 1);
	std::cout << "\n";

	if (choice == 0)
		static_cast<Route*>(*m_network.edges().begin())->optimizeForDuration(true);
	else if (choice == 1)
		static_cast<Route*>(*m_network.edges().begin())->optimizeForDuration(false);


	//Get departure station
		//List stations to choose from by entering integer
	
	unsigned i = 0;
	std::vector<Station*> stations;
	for (auto station : m_network.nodes())
	{
		std::cout << "  - " << i << ": " << station->name() << '\n';
		stations.push_back(station);
		i++;
	}
	choice = readChoice("> Select departure Station: ", 0, m_network.nodes().size() - 1);
	std::cout << "\n";

	Station& src = *stations[choice];


	//Get destination station
				//List stations to choose from by entering integer

	i = 0;
	for (auto station : m_network.nodes())
	{
		std::cout << "  - " << i << ": " << station->name() << '\n';
		stations.push_back(station);
		i++;
	}
	choice = readChoice("> Select destination Station: ", 0, m_network.nodes().size() - 1);
	std::cout << "\n";

	Station& dst = *stations[choice];

	std::deque<gl::Edge*> path = m_network.dijkstra(src, dst);

	//list path
	double total_distance = 0.0;
	double total_duration = 0.0;
	int amount_change_train = 0.0;
	std::string tempo;

	for (auto edge : path)
	{
		Route* route = static_cast<Route*>(edge);
		std::cout << "  - " << route->line() << edge->name() << " " << route->distance() << " km, " << route->duration() << " min). \n";
		if (tempo != route->line())
		{
			total_distance += route->distance();
			total_duration += route->duration() + 10.0;
			amount_change_train += 1;
		}
		else
		{
			total_distance += route->distance();
			total_duration += route->duration();
		}
		
		tempo = route->line();
	}
	total_duration -= 10.0;
	amount_change_train -= 1;
	std::cout << "> Your journey takes " << total_duration << " min and has a distance of " << total_distance << " km. " << "You need to change the train line " << amount_change_train << " times.\n\n";
}

void UI::addTrainConnection()
{
	
	std::vector<Connection> connections = readConnections();
	std::vector<Connection> connectionstemp;

	for (int i = 0; i < connections.size(); i++)
	{


		Connection conntemp;
		conntemp.line = connections[i].line;
		conntemp.station_1 = connections[i].station_1;
		conntemp.station_2 = connections[i].station_2;
		conntemp.third_number = connections[i].third_number;
		conntemp.first_and_second_number = connections[i].first_and_second_number;

		connectionstemp.push_back(conntemp);

	}
	for (int i = 0; i < connections.size(); i++)
	{
		std::cout << i << ". " << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
			<< connectionstemp[i].station_2 << ": " << "distance: " << connectionstemp[i].first_and_second_number << " km, duaration: " << connectionstemp[i].third_number << " min" << std::endl;
	}

	unsigned choice = readChoice("> Please enter connection you want to edit: ", 0, connections.size() - 1);
	std::cout << "\n\n";

	std::cout << "Editing train connection:\n";
	std::cout << connectionstemp[choice].line << " " << connectionstemp[choice].station_1 << " -> "
		<< connectionstemp[choice].station_2 << ": " << "distance: " << connectionstemp[choice].first_and_second_number << " km, duaration: " << connectionstemp[choice].third_number << " min\n\n";

	std::cout << "0. Change departure station \n";
	std::cout << "1. Change destination station \n";
	std::cout << "2. Change distance \n";
	std::cout << "3. Change duration \n";
	std::cout << "4. Change train line \n";

	unsigned choice_2 = readChoice("> Please enter option to change: ", 0, 4);
	std::string new_name;
	double new_number;

	if (choice_2 == 0)
	{
		std::cin.ignore();
		std::cout << "> Please enter new name of departure station: ";
		
		std::getline(std::cin, new_name);

		connectionstemp[choice].station_1 = new_name;
		
		std::ofstream myfile;
		myfile.open("berlin.txt");

		for (int i = 0; i < connectionstemp.size(); i++)
		{
			myfile << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
				<< connectionstemp[i].station_2 << ": " << connectionstemp[i].first_and_second_number << " " << connectionstemp[i].third_number << std::endl;
		}
		myfile.close();
		std::cout << "\n\nChanges successfully changed!\n\n";
	}

	if (choice_2 == 1)
	{
		std::cin.ignore();
		std::cout << "> Please enter new name of destination station: ";

		std::getline(std::cin, new_name);

		connectionstemp[choice].station_2 = new_name;

		std::ofstream myfile;
		myfile.open("berlin.txt");

		for (int i = 0; i < connectionstemp.size(); i++)
		{
			myfile << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
				<< connectionstemp[i].station_2 << ": " << connectionstemp[i].first_and_second_number << " " << connectionstemp[i].third_number << std::endl;
		}
		myfile.close();
		std::cout << "\n\nChanges successfully changed!\n\n";
	}

	if (choice_2 == 2)
	{
		std::cin.ignore();
		std::cout << "> Please enter new distance: ";

		std::cin >> new_number;

		connectionstemp[choice].first_and_second_number = new_number;

		std::ofstream myfile;
		myfile.open("berlin.txt");

		for (int i = 0; i < connectionstemp.size(); i++)
		{
			myfile << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
				<< connectionstemp[i].station_2 << ": " << connectionstemp[i].first_and_second_number << " " << connectionstemp[i].third_number << std::endl;
		}
		myfile.close();
		std::cout << "\n\nChanges successfully changed!\n\n";
	}

	if (choice_2 == 3)
	{
		std::cin.ignore();
		std::cout << "> Please enter new duration: ";

		std::cin >> new_number;

		connectionstemp[choice].third_number = new_number;

		std::ofstream myfile;
		myfile.open("berlin.txt");

		for (int i = 0; i < connectionstemp.size(); i++)
		{
			myfile << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
				<< connectionstemp[i].station_2 << ": " << connectionstemp[i].first_and_second_number << " " << connectionstemp[i].third_number << std::endl;
		}
		myfile.close();
		std::cout << "\n\nChanges successfully changed!\n\n";
	}

	if (choice_2 == 4)
	{
		std::cin.ignore();
		std::cout << "> Please enter new name train line: ";

		std::getline(std::cin, new_name);

		connectionstemp[choice].line = new_name;

		std::ofstream myfile;
		myfile.open("berlin.txt");

		for (int i = 0; i < connectionstemp.size(); i++)
		{
			myfile << connectionstemp[i].line << " " << connectionstemp[i].station_1 << " -> "
				<< connectionstemp[i].station_2 << ": " << connectionstemp[i].first_and_second_number << " " << connectionstemp[i].third_number << std::endl;
		}
		myfile.close();
		std::cout << "\n\nChanges successfully changed!\n\n";
	}

	std::cout << "0. No\n1. Yes\n";
	choice = readChoice("> Do you want to make more changes: ", 0, 1);
	std::cout << "\n\n";
	if (choice == 1)
	{
		addTrainConnection();
	}

}
