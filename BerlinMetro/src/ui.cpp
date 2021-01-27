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
	std::cout << "1. Sort by alphabet of departure station\n";
	std::cout << "2. Sort by alphabet of destination station\n";
	std::cout << "3. Sort by duration\n";
	std::cout << "4. Sort by distance\n";

	unsigned choice = readChoice("> Select optimization: ", 0, 4);
	std::cout << "\n";

	//sort by train line
	if (choice == 0)
	{
		std::vector<Connection> connections = readConnections();
		std::vector<Connection> connectionstemp2;

		for (int i = 0; i < connections.size(); i++)
		{


			Connection conntemp2;
			conntemp2.line = connections[i].line;
			conntemp2.station_1 = connections[i].station_1;
			conntemp2.station_2 = connections[i].station_2;
			conntemp2.third_number = connections[i].third_number;
			conntemp2.first_and_second_number = connections[i].first_and_second_number;

			connectionstemp2.push_back(conntemp2);

		}


		for (int i = 0; i < connectionstemp2.size(); i++)
		{
			std::string a = connectionstemp2[i].line;
			std::string b = connectionstemp2[i].station_1;
			std::string c = connectionstemp2[i].station_2;
			int d = connectionstemp2[i].third_number;
			double e = connectionstemp2[i].first_and_second_number;


			int j = i - 1;

			while (j >= 0 && a >= connectionstemp2[j].line)
			{
				connectionstemp2[j + 1].line = connectionstemp2[j].line;
				connectionstemp2[j + 1].station_1 = connectionstemp2[j].station_1;
				connectionstemp2[j + 1].station_2 = connectionstemp2[j].station_2;
				connectionstemp2[j + 1].third_number = connectionstemp2[j].third_number;
				connectionstemp2[j + 1].first_and_second_number = connectionstemp2[j].first_and_second_number;

				j -= 1;
			}

			connectionstemp2[j + 1].line = a;
			connectionstemp2[j + 1].station_1 = b;
			connectionstemp2[j + 1].station_2 = c;
			connectionstemp2[j + 1].third_number = d;
			connectionstemp2[j + 1].first_and_second_number = e;
		}

		for (int i = 0; i < connectionstemp2.size(); i++)
		{
			std::cout << connectionstemp2[i].line << " " << connectionstemp2[i].station_1 << " -> "
				<< connectionstemp2[i].station_2 << ": distance: " << connectionstemp2[i].first_and_second_number << " km, duration: " << connectionstemp2[i].third_number << " min" << std::endl;
		}
		
		std::cout << "\n\n";
	}
	else if (choice == 1)
	{
		//Sort by alphabet for departure stations
		std::vector<Connection> connectionstemp3;

		for (int i = 0; i < connections.size(); i++)
		{


			Connection conntemp3;
			conntemp3.line = connections[i].line;
			conntemp3.station_1 = connections[i].station_1;
			conntemp3.station_2 = connections[i].station_2;
			conntemp3.third_number = connections[i].third_number;
			conntemp3.first_and_second_number = connections[i].first_and_second_number;

			connectionstemp3.push_back(conntemp3);

		}


		for (int i = 0; i < connectionstemp3.size(); i++)
		{
			std::string a = connectionstemp3[i].line;
			std::string b = connectionstemp3[i].station_1;
			std::string c = connectionstemp3[i].station_2;
			int d = connectionstemp3[i].third_number;
			double e = connectionstemp3[i].first_and_second_number;


			int j = i - 1;

			while (j >= 0 && b >= connectionstemp3[j].station_1)
			{
				connectionstemp3[j + 1].line = connectionstemp3[j].line;
				connectionstemp3[j + 1].station_1 = connectionstemp3[j].station_1;
				connectionstemp3[j + 1].station_2 = connectionstemp3[j].station_2;
				connectionstemp3[j + 1].third_number = connectionstemp3[j].third_number;
				connectionstemp3[j + 1].first_and_second_number = connectionstemp3[j].first_and_second_number;

				j -= 1;
			}

			connectionstemp3[j + 1].line = a;
			connectionstemp3[j + 1].station_1 = b;
			connectionstemp3[j + 1].station_2 = c;
			connectionstemp3[j + 1].third_number = d;
			connectionstemp3[j + 1].first_and_second_number = e;
		}

		for (int i = 0; i < connectionstemp3.size(); i++)
		{
			std::cout << connectionstemp3[i].line << " " << connectionstemp3[i].station_1 << " -> "
				<< connectionstemp3[i].station_2 << ": distance: " << connectionstemp3[i].first_and_second_number << "km, duration: " << connectionstemp3[i].third_number << " min" << std::endl;
		}

		std::cout << "\n\n";
		

	}


	// Sort by alphabet for destination stations

	else if (choice == 2)
	{
	std::vector<Connection> connectionstemp4;

	for (int i = 0; i < connections.size(); i++)
	{


		Connection conntemp4;
		conntemp4.line = connections[i].line;
		conntemp4.station_1 = connections[i].station_1;
		conntemp4.station_2 = connections[i].station_2;
		conntemp4.third_number = connections[i].third_number;
		conntemp4.first_and_second_number = connections[i].first_and_second_number;

		connectionstemp4.push_back(conntemp4);

	}


	for (int i = 0; i < connectionstemp4.size(); i++)
	{
		std::string a = connectionstemp4[i].line;
		std::string b = connectionstemp4[i].station_1;
		std::string c = connectionstemp4[i].station_2;
		int d = connectionstemp4[i].third_number;
		double e = connectionstemp4[i].first_and_second_number;


		int j = i - 1;

		while (j >= 0 && c >= connectionstemp4[j].station_2)
		{
			connectionstemp4[j + 1].line = connectionstemp4[j].line;
			connectionstemp4[j + 1].station_1 = connectionstemp4[j].station_1;
			connectionstemp4[j + 1].station_2 = connectionstemp4[j].station_2;
			connectionstemp4[j + 1].third_number = connectionstemp4[j].third_number;
			connectionstemp4[j + 1].first_and_second_number = connectionstemp4[j].first_and_second_number;

			j -= 1;
		}

		connectionstemp4[j + 1].line = a;
		connectionstemp4[j + 1].station_1 = b;
		connectionstemp4[j + 1].station_2 = c;
		connectionstemp4[j + 1].third_number = d;
		connectionstemp4[j + 1].first_and_second_number = e;
	}

	for (int i = 0; i < connectionstemp4.size(); i++)
	{
		std::cout << connectionstemp4[i].line << " " << connectionstemp4[i].station_1 << " -> "
			<< connectionstemp4[i].station_2 << ": distance: " << connectionstemp4[i].first_and_second_number << " km, duration: " << connectionstemp4[i].third_number << " min" << std::endl;
	}

	std::cout << "\n\n";


	}


	// Sort by duration
	
	else if (choice == 3)
	{
	std::vector<Connection> connectionstemp5;

	for (int i = 0; i < connections.size(); i++)
	{


		Connection conntemp5;
		conntemp5.line = connections[i].line;
		conntemp5.station_1 = connections[i].station_1;
		conntemp5.station_2 = connections[i].station_2;
		conntemp5.third_number = connections[i].third_number;
		conntemp5.first_and_second_number = connections[i].first_and_second_number;

		connectionstemp5.push_back(conntemp5);

	}


	for (int i = 0; i < connectionstemp5.size(); i++)
	{
		std::string a = connectionstemp5[i].line;
		std::string b = connectionstemp5[i].station_1;
		std::string c = connectionstemp5[i].station_2;
		double d = connectionstemp5[i].third_number;
		double e = connectionstemp5[i].first_and_second_number;


		int j = i - 1;

		while (j >= 0 && d >= connectionstemp5[j].third_number)
		{
			connectionstemp5[j + 1].line = connectionstemp5[j].line;
			connectionstemp5[j + 1].station_1 = connectionstemp5[j].station_1;
			connectionstemp5[j + 1].station_2 = connectionstemp5[j].station_2;
			connectionstemp5[j + 1].third_number = connectionstemp5[j].third_number;
			connectionstemp5[j + 1].first_and_second_number = connectionstemp5[j].first_and_second_number;

			j -= 1;
		}

		connectionstemp5[j + 1].line = a;
		connectionstemp5[j + 1].station_1 = b;
		connectionstemp5[j + 1].station_2 = c;
		connectionstemp5[j + 1].third_number = d;
		connectionstemp5[j + 1].first_and_second_number = e;
	}

	for (int i = 0; i < connectionstemp5.size(); i++)
	{
		std::cout << connectionstemp5[i].line << " " << connectionstemp5[i].station_1 << " -> "
			<< connectionstemp5[i].station_2 << ": distance: " << connectionstemp5[i].first_and_second_number << " km, duration: " << connectionstemp5[i].third_number << "min" << std::endl;
	}

	std::cout << "\n\n";


	}

	// Sort by distance

	else if (choice == 4)
	{
	std::vector<Connection> connectionstemp6;

	for (int i = 0; i < connections.size(); i++)
	{


		Connection conntemp6;
		conntemp6.line = connections[i].line;
		conntemp6.station_1 = connections[i].station_1;
		conntemp6.station_2 = connections[i].station_2;
		conntemp6.third_number = connections[i].third_number;
		conntemp6.first_and_second_number = connections[i].first_and_second_number;

		connectionstemp6.push_back(conntemp6);

	}


	for (int i = 0; i < connectionstemp6.size(); i++)
	{
		std::string a = connectionstemp6[i].line;
		std::string b = connectionstemp6[i].station_1;
		std::string c = connectionstemp6[i].station_2;
		double d = connectionstemp6[i].third_number;
		double e = connectionstemp6[i].first_and_second_number;


		int j = i - 1;

		while (j >= 0 && e >= connectionstemp6[j].first_and_second_number)
		{
			connectionstemp6[j + 1].line = connectionstemp6[j].line;
			connectionstemp6[j + 1].station_1 = connectionstemp6[j].station_1;
			connectionstemp6[j + 1].station_2 = connectionstemp6[j].station_2;
			connectionstemp6[j + 1].third_number = connectionstemp6[j].third_number;
			connectionstemp6[j + 1].first_and_second_number = connectionstemp6[j].first_and_second_number;

			j -= 1;
		}

		connectionstemp6[j + 1].line = a;
		connectionstemp6[j + 1].station_1 = b;
		connectionstemp6[j + 1].station_2 = c;
		connectionstemp6[j + 1].third_number = d;
		connectionstemp6[j + 1].first_and_second_number = e;
	}

	for (int i = 0; i < connectionstemp6.size(); i++)
	{
		std::cout << connectionstemp6[i].line << " " << connectionstemp6[i].station_1 << " -> "
			<< connectionstemp6[i].station_2 << ": distance: " << connectionstemp6[i].first_and_second_number << " km, duration: " << connectionstemp6[i].third_number << "min" << std::endl;
	}

	std::cout << "\n\n";


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
