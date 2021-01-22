#pragma once
#include <string>
#include <list>
#include <iostream>

//! @file node.h
//! @version 1.0
//! @author Carsten Thomas
//! @date December 2020

namespace gl
{
	// forward-declarations
	class Edge;
	class Graph;

	//! @brief Node is the base clase representing nodes (vertices) in a graph
	class Node
	{
	public:
		//! @brief Constructor to create a new named node
		//! The constructor registers the node with the parent graph
		//! @param graph parent graph
		//! @param name name of the node
		Node(Graph& graph, std::string name);

		//! @brief Constructor to create a new node and assign a auto-generated name to it
		//! The constructor registers the node with the parent graph
		//! The auto-generated name follows the "Node_0001", "Node_0002", etc. convention
		//! @param graph parent graph
		Node(Graph& graph);

		//! @brief Virtual destructor for node
		//! The destructor destroys the connected edges and deregisters the node from the parent graph before destroying
		virtual ~Node();

		//! @brief Virtual constant member function returning the name (description) of the node as string
		//! @return @b std::string the name of the node
		virtual std::string name() const { return m_name; }

		//! @brief Member function returning a reference to the list of outgoing edges
		//! @return @b std::list<Edge*>& reference of the list of outgoing edges
		std::list<Edge*>& outEdges() { return m_out_edges; }

		//! @brief Member function returning a reference to the list of incoming edges
		//! @return @b std::list<Edge*>& reference of the list of incoming edges
		std::list<Edge*>& inEdges() { return m_in_edges; }

		//! @brief Constant member function returning a const reference to the parent graph of the node
		//! @return @b Graph& const reference to the parent graph of the node
		const Graph& graph() const { return m_graph; }

		//! @brief Comparison operator as friend function, returning true if two nodes are identical (not just having the same member variable content)
		//! @return @b bool true if the two nodes are identical, false otherwise
		friend bool operator==(const Node& lhs, const Node& rhs);

		//! @brief Streaming operator as friend function, streaming the return value of the name() function to the output stream
		//! @return @b std::ostream& reference to the output stream
		friend std::ostream& operator<<(std::ostream& os, const Node& node);

	protected:
		// instance number is used to create unique names for nodes that do not get a custom name
		static int s_instance_number;

	private:
		// helper functions
		bool isUnique(std::string name);

		Graph& m_graph;
		std::string m_name;

		std::list<Edge*> m_out_edges;
		std::list<Edge*> m_in_edges;
	};
}
