#pragma once
#include "node.h"

//! @file edge.h
//! @version 1.0
//! @author Carsten Thomas
//! @date December 2020

namespace gl
{
	//! @brief Edge is the base clase representing unidirectional edges (arrows, flows) in a graph
	class Edge
	{
	public:
		//! @brief Constructor to create a new edge between source and destination node
		//! The constructor registers the edge with the parent graph and with the connected nodes
		//! @param graph parent graph
		//! @param src source node
		//! @param dst destination node
		Edge(Graph& graph, Node& src, Node& dst);

		//! @brief Constructor to create a new edge as a copy of an existing edge
		//! The constructor registers the edge with the parent graph and with the connected edges
		//! @param other existing edge
		Edge(const Edge& other);

		//! @brief Virtual destructor for edge
		//! The destructor deregisters the edge from the connected nodes and from the graph before destroying
		virtual ~Edge();

		//! @brief Constant member function checking if a node is connected to this edge
		//! @param node const reference of node
		//! @return @b bool true if node is connected to this edge (either as source or destination node), and false otherwise
		bool isConnectedTo(const Node& node) const;

		//! @brief Member function returning a reference of the source node
		//! @return @b Node& reference of the source node
		Node& source() { return m_src; }

		//! @brief Member function returning a reference of the destination node 
		//! @return @b Node& reference of the destination node
		Node& destination() { return m_dst; }

		//! @brief Virtual constant member function defining the weight (or distance, or cost) of the edge
		//! Currently set to 1.0, so the shortest path algorithm searches for the path with the least number of edges involved.
		//! @todo This function must be overwritten to adapt the behavior of the Djikstra algorithm
		//! @return  @b double the value representing the weight (or distance or cost) of the edge
		virtual double weight() const { return 1.0; }

		//! @brief Streaming operator as friend function, streaming the return value of the name() function to the output stream
		//! @return @b std::ostream& reference to the output stream
		friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

		//protected:
			//! @brief Virtual constant member function returning a description of the edge as string
			//! Edge as base class does not have a name by its own, but builds the string from the names of the connected nodes
			//! @return @b std::string the description of the edge, in the format "source -> destination"
		virtual const std::string name() const;

	private:
		//! @brief Helper function checking if the node is in the same parent graph as the edge
		//! This function is used in the Edge constructor to prevent edges being created between nodes in different graphs
		bool inSameGraph(const Node& node) { return &(node.graph()) == &m_graph; }

		Node& m_src;
		Node& m_dst;
		Graph& m_graph;
	};
}
