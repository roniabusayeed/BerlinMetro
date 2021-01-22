#include "graph.h"
#include <list>
#include <map>
#include <fstream>
#include <algorithm>
#include <limits>
#include <string>
#include <iostream>
#include "node.h"
#include "graph.h"

namespace gl
{

	Node* Graph::findNode(const std::string& name) const
	{
		Node* p = nullptr;
		for (auto n : m_nodes)
			if (n->name() == name)
			{
				p = n;
				break;
			}
		return p;
	}

	std::vector<Edge*> Graph::findEdges(const Node& src, const Node& dst) const
	{
		// check if Edge and requested Nodes are in the same Graph
		if ((&src.graph() != this) || (&dst.graph() != this))
			throw GraphLibException("Graph::findEdges: Nodes located in different Graphs.");

		// if Edge is connected to source Node and destination Node, 
		// then place his adress into the result vector 
		std::vector<Edge*> edges;
		for (auto e : m_edges)
			if ((&e->source() == &src) && (&e->destination() == &dst))
				edges.push_back(e);
		return edges;
	}

	Graph::~Graph()
	{
		// Whilst Graph own the Edges and Nodes connected to it, 
		// it is possible that Edges and Nodes are deleted by calling operator delete
		// In this case, Edge and Node must detach themselves from Graph (done via their descturctors)
		// All Edges and Nodes still remaining in m_edges and m_nodes must be deletd in this destructor


		//reportLists("~Graph() started");

		// destruct all remaining Nodes (and thereby all remaining Edges)
		while (m_nodes.size() > 0)
		{
			Node* node = *(m_nodes.begin());
			delete node; // in destructor, Node removes itself from m_nodes
		}

		//reportLists("~Graph() completed");
	}

	std::deque<Edge*> Graph::dijkstra(const Node& src, const Node& dst) const
	{
		std::deque<Edge*> path;

		//	//create vertex set Q
		std::list<Node*> Q; // Warteschlange

		struct tDijkstraNodeEntry
		{
			double m_distance;
			Node* m_prevNode;
			Edge* m_prevEdge;
		};

		std::map<Node*, tDijkstraNodeEntry> nodeEntry;

		for (auto n : m_nodes)
		{
			Q.push_back(n); // aktuellen Knoten der Warteschlange zuf�gen
			nodeEntry[n] = { std::numeric_limits<double>::max(), nullptr, nullptr }; // assoziierte Werte in der Map initialisieren
		}

		Node* pN = const_cast<Node*>(&src);
		nodeEntry[pN].m_distance = 0;

		while (!Q.empty())
		{
			Node* u = Q.front();
			for (auto n : Q) // Liste durchgehen um den Knoten mit der kleinsten Distanz zu finden
				if (nodeEntry[n].m_distance < nodeEntry[u].m_distance)
					u = n;

			Q.remove(u); // Entferne den Knoten mit der kleinsten Distanz aus der Warteschlange

			for (auto n : u->outEdges())
			{
				Node* v = &(n->destination());
				double alt = nodeEntry[u].m_distance + n->weight();
				if (alt < nodeEntry[v].m_distance)
				{
					nodeEntry[v].m_distance = alt;
					nodeEntry[v].m_prevNode = u;
					nodeEntry[v].m_prevEdge = n;
				}
			}

		}

		Node* currentNode = const_cast<Node*>(&dst);
		while (nodeEntry[currentNode].m_prevNode != NULL)
		{
			path.push_front(nodeEntry[currentNode].m_prevEdge);
			currentNode = nodeEntry[currentNode].m_prevNode;
		}
		return path;
	}

}
