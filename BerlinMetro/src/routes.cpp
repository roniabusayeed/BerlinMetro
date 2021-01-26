#include "routes.h"
#include "edge.h"
#include "read.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Route::m_optimize_for_duration = true;

double Route::weight() const
{
	if (Route::m_optimize_for_duration)
		return duration();
	else
		return m_distance;
}

double Route::duration() const
{
	return m_duration;

	//TODO: take care of additional 10 min change train time
}

std::string Route::line() const
{
	return m_line;
}

void Network::createRoute(std::string line, gl::Node& src, gl::Node& dst, double distance, double duration)
{
	new Route(line, *this, src, dst, distance, duration);
	new Route(line, *this, dst, src, distance, duration);
}

Network::Network()
{
	std::vector<Connection> connections = readConnections();
	std::string temp_line = connections[0].line;
	std::vector<Station*> nodes_1;
	bool station_double = false;
	bool station_double_next = false;
	int temp = 0;
	int x = 0;
	//std::vector<Station*> nodes_2;

	for (int i = 0; i < connections.size(); i++)
	{
		station_double_next = false;
		if (i == 0)
		{
			nodes_1.push_back(new Station(*this, connections[i].station_1));
			//nodes_2.push_back(new Station(*this, connections[i].station_2));
			x++;
		}
		else
		{
			if (station_double == true)
			{
				station_double = false;
				for (int y = 0; y < i; y++) {
					if (connections[y].station_1 == connections[i].station_1)
					{

						createRoute(connections[i].line, *nodes_1[y], *nodes_1[temp], connections[i].first_and_second_number, (double)connections[i].third_number);

						station_double = true;
					}
					if (station_double = false)
					{
						nodes_1.push_back(new Station(*this, connections[i].station_1));
						std::cout << temp << "\n";
						createRoute(connections[i].line, *nodes_1[temp], *nodes_1[x], connections[i].first_and_second_number, (double)connections[i].third_number);
						station_double = false;
						station_double_next = true;
						x++;
					}
			}
				}
				if (station_double_next == false)
				{

					for (int y = 0; y < i; y++) {
						if (connections[y].station_1 == connections[i].station_1)
						{
							temp = y;
							createRoute(connections[i].line, *nodes_1[x - 1], *nodes_1[temp], connections[i].first_and_second_number, (double)connections[i].third_number);

							station_double = true;
						}
					}

					if (station_double == false && station_double_next == false)
					{
						nodes_1.push_back(new Station(*this, connections[i].station_1));
						createRoute(connections[i].line, *nodes_1[x - 1], *nodes_1[x], connections[i].first_and_second_number, (double)connections[i].third_number);
						x++;
					}
				}
			
		}
	}


	//Examples for creating Nodes (Station*) and Edges (createRoute) without using the data from reading from file:
	/*
	Station* alexanderplatz = new Station(*this, "Alexanderplatz");
	Station* ostkreuz = new Station(*this, "Ostkreuz");
	Station* ostbahnhof = new Station(*this, "Ostbahnhof");
	Station* erkner = new Station(*this, "Erkner");

	createRoute("U5 ", *alexanderplatz, *ostkreuz, 12.0, 15.0);
	createRoute("U5 ", *ostkreuz, *erkner, 20.0, 12.0);
	createRoute("U1 ", *alexanderplatz, *erkner, 90.0, 5.0);
	*/
	
	
}
