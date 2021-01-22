#pragma once
#include "edge.h"
#include "node.h"
#include "graph.h"

class Route : public gl::Edge
{
public:
	Route(std::string line, gl::Graph& graph, gl::Node& src, gl::Node& dst, double distance, double duration)
		: gl::Edge(graph, src, dst),m_line(line), m_distance(distance), m_duration(duration)
	{}

	virtual double weight() const;

	double distance() const { return m_distance; }
	double duration() const;
	std::string line() const;

	void optimizeForDuration(bool optimize_for_duration) { m_optimize_for_duration = optimize_for_duration; }

private:
	double m_distance;
	double m_duration;
	std::string m_line;

	static bool m_optimize_for_duration;
};

using Station = gl::Node;

class Network : public gl::Graph
{
public:
	Network();
	void createRoute(std::string line, gl::Node& src, gl::Node& dst, double distance, double duration);
};