#include <iostream>
#include "ui.h"
#include "edge.h"

std::vector<std::string> m_menu{ "Output all train connections", "Find the best train connection", "Add train connection data", "Leave Program" };

void UI::loop()
{
	unsigned choice = 0;
	do
	{
		listMenuOptions();
		choice = readChoice("> Please select menu option: ", 0, m_menu.size() - 1);

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
	unsigned choice;
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
	//Sort by line

	//Sort by alphabet
}

void UI::findBestConnection()
{
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
	unsigned choice = readChoice("> Select departure Station: ", 0, m_network.nodes().size() - 1);

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

	Station& dst = *stations[choice];

	std::deque<gl::Edge*> path = m_network.dijkstra(src, dst);

	//list path
	double total_distance = 0.0;
	double total_duration = 0.0;
	for (auto edge : path)
	{
		Route* route = static_cast<Route*>(edge);
		std::cout << "  - " << edge->name() << route->distance() << " km, " << route->duration() << " min). \n";
		total_distance += route->distance();
		total_duration += route->duration();
	}
}

void UI::addTrainConnection()
{}
