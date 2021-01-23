#include "routes.h"
#include "edge.h"
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
	//Read train, origin-station, destination-station, duration, distance from file... doesn't work yet:
	/*
	std::string line;

	std::ifstream myfile("Berlin.txt");
	std::string trainRead, originRead, destinationRead, arrow;
	double durationRead, distanceRead;


	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			//std::cout << line << '\n';
			std::stringstream ss{ line };
			ss >> trainRead >> originRead >> arrow >> destinationRead >> durationRead >> distanceRead;

			//One problem is that some stations contain more than one word so reading only works, if the are no whitespaces in between one station name.
			//The other problem is that the following code doesn't work. So Probably there has to be a different way to create the stations (nodes) with the reading from file.

			Station* originRead = new Station(*this, "");
			Station* destinationRead = new Station(*this, "");
			createRoute(trainRead, *originRead, *destinationRead, durationRead, distanceRead);
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
	*/

	//Examples for creating Nodes (Stations) and Routes (Edges):
	
	Station* alexanderplatz = new Station(*this, "Alexanderplatz");
	Station* ostkreuz = new Station(*this, "Ostkreuz");
	Station* ostbahnhof = new Station(*this, "Ostbahnhof");
	Station* erkner = new Station(*this, "Erkner");

	createRoute("U5 ", *alexanderplatz, *ostkreuz, 12.0, 15.0);
	createRoute("U5 ", *ostkreuz, *erkner, 20.0, 12.0);
	createRoute("U1 ", *alexanderplatz, *erkner, 90.0, 5.0);
}
