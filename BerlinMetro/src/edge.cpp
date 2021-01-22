#include "graph.h"
#include <iostream>
#include "edge.h"
#include "routes.h"

namespace gl
{
    Edge::Edge(Graph& graph, Node& src, Node& dst)
        : m_graph(graph), m_src(src), m_dst(dst)
    {
        // check if nodes are in the same graph
        if (!inSameGraph(m_src) || !inSameGraph(m_dst))
            throw GraphLibException("Edge constructor: Edge not in same Graph as Nodes");
        else
        {
            // register the Edge with the connected Nodes
            m_src.outEdges().push_back(this);
            m_dst.inEdges().push_back(this);
            // register edge with graph, graph now owns this edge
            m_graph.edges().push_back(this);
        }
    }

    Edge::Edge(const Edge& other)
        : m_graph(other.m_graph), m_src(other.m_src), m_dst(other.m_dst)
    {
        // check if nodes are in the same graph
        if (!inSameGraph(m_src) || !inSameGraph(m_dst))
            throw GraphLibException("Edge contructor: Edge not in same Graph as Nodes");
        else
        {
            // register the Edge with the connected Nodes
            m_src.outEdges().push_back(this);
            m_dst.inEdges().push_back(this);
            // register edge with graph, graph now owns this edge
            m_graph.edges().push_back(this);
        }
    }

    Edge::~Edge()
    {
        //m_graph.reportLists("~Edge started");

        // remove this Edge from outgoing edges list of source Node
        m_src.outEdges().remove(this);

        // remove this Edge from incoming edges list of destination Node
        m_dst.inEdges().remove(this);

        // remove this Edge from the edges list of Graph
        m_graph.edges().remove(this);

        //m_graph.reportLists("~Edge completed");
    }

    bool Edge::isConnectedTo(const Node& node) const
    {
        // - gibt true zur�ck, wenn rNode entweder m_rSrc oder m_rDst ist.
        // Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
        return ((&node == &m_src) || (&node == &m_dst));
    }

    const std::string Edge::name() const
    {
        std::string result;
        result = m_src.name() + " -> " + m_dst.name();
        return result;
    }

    // friend function implementation
    std::ostream& operator<<(std::ostream& os, const Edge& edge)
    {
        os << edge.name();
        return os;
    }
}
