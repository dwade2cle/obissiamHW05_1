#include "stdafx.h"
#include "ListGraph.h" 

ListGraph::ListGraph(int numNodes)	{
	edgeList.resize(numNodes);
	num_edges = 0;
}

ListGraph::~ListGraph(){}

void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight)	{
	NWPair val; val.first = v; val.second = weight;
	edgeList[u].push_back(val);
	val.first = u; 
	edgeList[v].push_back(val);
	num_edges++;
}

EdgeWeight ListGraph::weight(NodeID u, NodeID v)	const{
	EList::const_iterator listIterator;
	for(listIterator = edgeList[u].begin(); listIterator != edgeList[u].end(); listIterator++)	{
		if((*(listIterator)).first == v) return (*(listIterator)).second;
	}
	return 0.0;
}

std::list<NWPair> ListGraph::getAdj(NodeID u)	const{
	return edgeList[u];
}

unsigned ListGraph::degree(NodeID u) const{
	return edgeList[u].size();
}

unsigned ListGraph::size() const{
	return edgeList.size();
}

unsigned ListGraph::numEdges() const{
	return num_edges;
}
