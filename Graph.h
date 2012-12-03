/*****
 * Author   : karroje
 * Date     : 2011-04-10
 * Sources  : All code is original
 * Purpose  : This class is intended to serve as the (abstract) base class for implementatons of a basic
 *            weighted, undirectly graph class.  It is intended that any such is static in terms of node size 
 *            (that is, the number of nodes of a particular object is specified at construction and never changed), 
 *            with nodes index by consecurive integers.  Weights will be positive doubles; edges may nt have a weight of 0.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */




#include <utility>
#include <list>

#pragma once

 /*
 * Useful typedefs, primarily for the purpose of read-ability.
 */
typedef unsigned NodeID;
typedef double EdgeWeight;
typedef std::pair<NodeID, EdgeWeight> NWPair;


class Graph {
 public:
  virtual ~Graph() {}

  /*
   * Add a weighted, undirected edge between nodes u and v.
   * 
   * Preconditions: 
   *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
   *     u != v
   *     There is no edge between u and v.
   *     weight > 0
   */
  virtual void addEdge(NodeID u, NodeID v, EdgeWeight weight) = 0;
  

  /*
   * Get the weight between nodes u and v; return 0 if there is no edge.
   *
   * Preconditions: 
   *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
   */
  virtual EdgeWeight weight(NodeID u, NodeID v) const = 0;

  /*
   * Return a list of NodeID/EdgeWeight pairs describing the nodes adjacent to edge w.
   *
   * Preconditions: u is a legal label.
   */
  virtual std::list<NWPair> getAdj(NodeID u) const = 0;

  /*
   * Return the degree (i.e. the number of neighorbs) of node u.
   *
   * Preconditions: u is a legal label;
   */
  virtual unsigned degree(NodeID u) const = 0;

  /*
   * Return the number of nodes in the graph.
   */
  virtual unsigned size() const = 0;

  /* 
   * Return the number of edges in the graph.
   */
  virtual unsigned numEdges() const = 0;
};
