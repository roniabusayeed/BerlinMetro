#include "routes.h"

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

void Network::createRoute(gl::Node& src, gl::Node& dst, double distance, double duration)
{
	new Route(*this, src, dst, distance, duration);
	new Route(*this, dst, src, distance, duration);
}

Network::Network()
{
	//TODO: Import Network from file

	Station* alexanderplatz = new Station(*this, "Alexanderplatz");
	Station* ostkreuz = new Station(*this, "Ostkreuz");
	Station* ostbahnhof = new Station(*this, "Ostbahnhof");
	Station* erkner = new Station(*this, "Erkner");

	createRoute(*alexanderplatz, *ostkreuz, 12.0, 15.0);
	createRoute(*ostkreuz, *erkner, 20.0, 12.0);
}
