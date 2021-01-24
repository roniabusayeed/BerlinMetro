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
	
	//Getting the data from the connections vector doesn't work yet.
	std::string temp_line = connections[0].line;

	//Creating the Nodes with data read from file
	for (int i = 0; i < connections.size(); i++)
	{
		//While the last train connection of a train line is not reached only station_1 becomes a Node otherwise some Nodes would be double
		if (connections[i+1].line == temp_line) 
		{
			//Here_has_to_be_a_name below has to change every time because every Node has to have a different name
			Station* Here_has_to_be_a_station_name = new Station(*this, connections[i].station_1);
			temp_line = connections[i].line;
			
			
		}
		//When the last train connection of a train line is reached station_1 and station_2 become Nodes in order to not skip the last station of a train line
		else
		{
			//Here_has_to_be_a_name below has to change every time because every Node has to have a different name
			Station* Here_has_to_be_a_station_name = new Station(*this, connections[i].station_1);
			Station* Here_has_to_be_a_station_name = new Station(*this, connections[i].station_2);
			temp_line = connections[i + 1].line;
		}			

		//creating the edges for data read from file
		for (int i = 0; i < connections.size(); i++)
		{
			//Here_has_to_be_a_name has to change everytime when starting the for loop again as described above at Station*
			createRoute(connections[i].line, *Here_has_to_be_a_name, *Here_has_to_be_a_name, connections[i].first_and_second_number, (double)connections[i].third_number);
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
