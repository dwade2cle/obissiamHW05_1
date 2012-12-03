/*****
 * Author   : karroje
 * Date     : 2011-04-10
 * Sources  : All code is original
 * Purpose  : A set of methods used to test the MatrixGraph and ListGraph classes.  Specify which type
 *            of graph is being tested in the constructor, then run each test.  Completetion of a test
 *            is *evidence* that your graph is working, but will not necesarily test for all possible
 *            bugs (which can still result in loss of points if I find them later).
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */


#include "Graph.h"

#pragma once

int randInt(int a, int b);

class Tester {
 public:
  Tester(bool matrix_graph) {this->matrix_graph = matrix_graph;}
  bool run_test(int i);
  void test_all();

  /*********************************************************************/
  /* Test 1: Tests constructor and destructor.                         */
  /*         This always reutrns true -- the pupose is to see if it    */
  /*         finishes without a crash.                                 */
  /*                                                                   */
  /*         Note: if it does finish, it means your constructor        */
  /*         don't seg. fault.  That does NOT mean it works correctly. */
  /*                                                                   */
  /*         Comment: You are not necessarily going to need a          */
  /*         destructor.  Depending on your design, you may well not   */
  /*         have -- in which call this test is doing is deleting      */
  /*         a pointer.                                                */
  bool test_1();  

  /*********************************************************************/
  /* Test 2: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         and checks that there is no edge betwwen nodes i and j    */
  /*         for all i, j < n.                                         */
  /*                                                                   */
  /*         Note: if this fails, the problem could be in either (or   */
  /*         both) methods.                                            */
  bool test_2();  

  /*********************************************************************/
  /* Test 3: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         picks two random nodes i,j (i != j), adds an edge between */
  /*         them of random weight, and checks that they graph then    */
  /*         has an edge betwen nodes i and j of the correct weight.   */
  bool test_3();  

  /*********************************************************************/
  /* Test 4: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         picks two random nodes i,j (i != j), adds an edge between */
  /*         them of random weight, and checks that they graph then    */
  /*         has an edge betwen nodes j and i of the correct weight.   */
  /*         (In otherwords: making sure your graph is directed.)      */
  bool test_4();

  /*********************************************************************/
  /* Test 5: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         picks twothe random nodes i,j,k, adds an edge (i,j) of    */
  /*         random weight and an edge (i,k) of random weight,  and    */
  /*         used Graph::weight(...) to make sure both edges exist in  */
  /*         the graph in both directions.                             */
  bool test_5();


  /*********************************************************************/
  /* Test 6: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         add an edge between two random nodes, and checkes that    */
  /*         the graph now has *only* that edge (in both directions).  */
  bool test_6();

  /*********************************************************************/
  /* Test 7: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*         Picks a random value of n, creates a graph of n nodes,    */
  /*         adds every possible (legal) edge, and checks that each    */
  /*         is in the graph with the correct weight.                  */
  bool test_7();

  /*********************************************************************/
  /* Test 8: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*          Picks a random value of n, creates a graph of n nodes,   */
  /*          and checks that Graph::size() returns the correct        */
  /*          value.                                                   */
  bool test_8();

  /*********************************************************************/
  /* Test 9: Tests Graph::addEdge(...) and Graph::weight(...).         */
  /*          Picks a random value of n, creates a graph of n nodes,   */
  /*          randomly adds edges, and checks that Graph::numEdges()   */
  /*          returns the correct value.                               */
  bool test_9();

  /*********************************************************************/
  /* Test 10: Tests Graph::addEdge(...) and Graph::getAdj(...).        */
  /*          Picks a random value of n, creates a graph of n nodes,   */
  /*          pick random nodes u and v, adds an edge between u and    */
  /*          v, and checks that Graph::adjEdges()  returns a correct  */
  /*          list for both nodes u and v.                             */
  bool test_10();

  /*********************************************************************/
  /* Test 11: Tests Graph::addEdge(...) and Graph::getAdj(...).       */
  /*          Picks a random value of n, creates a graph of n nodes,   */
  /*          picks a random node u, adds all possible edges to u,     */
  /*          and checks Graph::adjEdge(...) for every node in the     */
  /*          Graph.                                                   */
  bool test_11();
  
  /*********************************************************************/
  /* Test 12: Tests Graph::addEdge(...) and Graph::getAdj(...).        */
  /*          Picks a random value of n, creates a graph of n nodes,   */
  /*          add all possible edges, and checks Graph::getAdj(...)    */
  /*          for every node.                                          */
  bool test_12();  


 private: 
  Graph* createGraph(int n);
  bool cleanAndExit(Graph* G, bool b);

  bool matrix_graph;
};
