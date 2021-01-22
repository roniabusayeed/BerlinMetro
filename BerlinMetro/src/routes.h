#pragma once
#include "edge.h"
#include "node.h"
#include "graph.h"

class Route : public gl::Edge
{
public:
	Route(gl::Graph& graph, gl::Node& src, gl::Node& dst, double distance, double duration)
		: gl::Edge(graph, src, dst), m_distance(distance), m_duration(duration)
	{}

	virtual double weight() const;

	double distance() const { return m_distance; }
	double duration() const;



private:
	double m_distance;
	double m_duration;

	static bool m_optimize_for_duration;
};

using Station = gl::Node;

class Network : public gl::Graph
{
public:
	Network();
	void createRoute(gl::Node& src, gl::Node& dst, double distance, double duration);
};