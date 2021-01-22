#pragma once
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <exception>
#include <iostream>
#include "node.h"
#include "edge.h"

//! @file graph.h
//! @version 1.0
//! @author Carsten Thomas
//! @date December 2020

namespace gl
{

	//! @brief Graph is the base clase representing a graph as parent of nodes and edges
	class Graph
	{
	public:
		//! @brief Virtual destructor for graph
		//! The destructor destroys all remaining edges and nodes connected for this graph
		virtual ~Graph();

		//! @brief Member function returning a reference to the list of nodes connected to this graph
		//! @return @b std::list<Node*>& reference of the list of nodes
		std::list<Node*>& nodes() { return m_nodes; }

		//! @brief Member function returning a reference to the list of edges connected to this graph
		//! @return @b std::list<Edge*>& reference of the list of edges
		std::list<Edge*>& edges() { return m_edges; }

		//! @brief Member function returning the pointer to the node with the given name, if such node exists
		//! @return @b Node* pointer to the node with the specified name if such nodes exists, or nullptr otherwise
		Node* findNode(const std::string& name) const;

		//! @brief Member function returning a vector of pointers to all edges connecting the source and destination node, and an empty vector if no such edges exist
		//! @return @b std::vector<Edge*> vector of pointers to all edges connecting the given node, or empty vector
		std::vector<Edge*> findEdges(const Node& src, const Node& dst) const;

		//! @brief Member function returning a vector of pointers to all edges connecting the source and destination node, and an empty vector if no such edges exist
		//! @return @b std::vector<Edge*> vector of pointers to all edges connecting the given node, or empty vector	
		std::deque<Edge*> dijkstra(const Node& src, const Node& dst) const;

	protected:
		std::list<Node*> m_nodes;
		std::list<Edge*> m_edges;
	};

	//! @brief GraphLibException is a specific exception class for this library
	class GraphLibException
	{
	public:
		//! @brief Constructor to create a library exception carrying the error string
		//! @param error error string
		GraphLibException(const char* error) : m_error(error) {}

		//! @brief Member function returning reason for error
		const char* what() const { return m_error; }
	private:
		const char* m_error;
	};
}
