// listGraph.h

#include <vector>
#include "Graph.h"

#pragma once

typedef std::list<NWPair> EList;

class ListGraph : public Graph {
 public:
  ListGraph(int numNodes);
  ~ListGraph();

  // Modifiers
  virtual void addEdge(NodeID u, NodeID v, EdgeWeight weight);
  
  // Inspectors
  virtual EdgeWeight weight(NodeID u, NodeID v) const;
  virtual std::list<NWPair> getAdj(NodeID u) const;
  virtual unsigned degree(NodeID u) const;
  virtual unsigned size() const;
  virtual unsigned numEdges() const;

 private:
  ListGraph() {;}

  std::vector<EList> edgeList;
  int num_edges;
};
