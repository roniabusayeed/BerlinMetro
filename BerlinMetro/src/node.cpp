#include <string>
#include <sstream>
#include <iomanip>

#include "node.h"
#include "graph.h"

namespace gl
{
	// static initialization
	int Node::s_instance_number = 0;

	Node::Node(Graph& graph) : m_graph{ graph }
	{
		// create a unique name for node
		bool name_is_unique = false;
		while (!name_is_unique)
		{
			s_instance_number++;
			std::stringstream s;
			s << "Node_" << std::setw(4) << std::setfill('0') << s_instance_number;
			m_name = s.str();
			name_is_unique = isUnique(m_name);
		}

		// register node with graph, graph now owns this edge
		m_graph.nodes().push_back(this);
	}

	Node::Node(Graph& graph, std::string name) : m_graph{ graph }, m_name(name)
	{
		// make sure node name is unique
		if (!isUnique(name))
		{
			GraphLibException e("Node constructor: Node name is not unique");
			throw e;
		}

		// register node with graph, graph now owns this edge
		m_graph.nodes().push_back(this);
	}

	Node::~Node()
	{
		//m_graph.reportLists("~Node started " + m_name);

		// delete all Edges connected to this Node (Edges cannot exist without src or dst)
		// note: a 'for' loop does not work here, because 'delete e' changes the list
		while (m_in_edges.size() > 0)
		{
			auto e = m_in_edges.begin();
			delete* e;
		}
		while (m_out_edges.size() > 0)
		{
			auto e = m_out_edges.begin();
			delete* e;
		}

		// remove this Node from the nodes list of Graph
		m_graph.nodes().remove(this);

		//m_graph.reportLists("~Node completed " + m_name);

	}

	bool operator==(const Node& lhs, const Node& rhs)
	{
		return (&lhs == &rhs);
	}

	bool Node::isUnique(std::string name)
	{
		// check if there is a node in graph that has the same name
		for (auto n : m_graph.nodes())
			if (n->name() == name)
				return false;
		return true;
	}

	// friend function implementation
	std::ostream& operator<<(std::ostream& os, const Node& node)
	{
		os << node.name();
		return os;
	}
}
