#include "stdafx.h"
#include "MatrixGraph.h"
MatrixGraph::MatrixGraph(unsigned num_nodes)	{
	M.resize(num_nodes);
	for(int i = 0; i < num_nodes; i++)	{
		M[i].resize(num_nodes);
	}
	for(int i = 0; i < num_nodes; i++)	{
		for(int j = 0; j < num_nodes; j++)	{
			M[i][j] = -1;
		}
	}
	num_edges = 0;
}

MatrixGraph::~MatrixGraph(){}

void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight)	{
	M[u][v] = weight; M[v][u] = weight;
	num_edges++;
}

EdgeWeight MatrixGraph::weight(NodeID u, NodeID v)	const{
	if(M[u][v] != -1) return M[u][v];
	else return 0.0;
}

std::list<NWPair> MatrixGraph::getAdj(NodeID u)	const{
	EList out; int count = 0;
	std::vector<EdgeWeight>::const_iterator vecIterator; 
	for(vecIterator = M[u].begin(); vecIterator != M[u].end(); vecIterator++)	{
		if((*(vecIterator)) != -1)	{
			NWPair p; p.first = count; p.second = *(vecIterator);
			out.push_back(p);
		} count++;
	}
	return out;
}

unsigned MatrixGraph::degree(NodeID u) const{
	std::vector<EdgeWeight>::const_iterator vecIterator;
	int deg = 0;
	for(vecIterator = M[u].begin(); vecIterator != M[u].end(); vecIterator++)	
		if((*(vecIterator)) != -1) deg++;
	return deg;
}

unsigned MatrixGraph::size() const{
	return M.size();
}

unsigned MatrixGraph::numEdges() const{
	return num_edges;
}