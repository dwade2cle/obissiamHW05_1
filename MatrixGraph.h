// MatrixGraph.h

#include <vector>
#include "Graph.h"

#pragma once

typedef std::list<NWPair> EList;

class MatrixGraph : public Graph {
 public:
  MatrixGraph(unsigned num_nodes);
  ~MatrixGraph();

  // Modifiers
  virtual void addEdge(NodeID u, NodeID v, EdgeWeight weight);
  
  // Inspectors
  virtual EdgeWeight weight(NodeID u, NodeID v) const;
  virtual std::list<NWPair> getAdj(NodeID u) const;
  virtual unsigned degree(NodeID u) const;
  virtual unsigned size() const;
  virtual unsigned numEdges() const;

 private:
  MatrixGraph() {;}

  std::vector<std::vector<EdgeWeight> > M;
  int num_edges;
};
