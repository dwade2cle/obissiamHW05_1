// Tester

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
#include "stdafx.h"
#include "Tester.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;

int randInt(int a, int b) {
  return a + (rand() % (b-a));
}

vector<NodeID> randNodeList(int n) {
  vector<NodeID> V(n);
  for (int i=0; i < n; i++)
    V[i] = i;

  for (int i=0; i < n-1; i++)
    swap(V[i], V[randInt(i, n)]);
  
  return V;
}

Graph* Tester::createGraph(int n) {
  Graph* G;
  if (matrix_graph)
    G = new MatrixGraph(n);
  else
    G = new ListGraph(n);

  return G;
}

bool Tester::cleanAndExit(Graph* G, bool b) {
  if (matrix_graph)
    delete (MatrixGraph*)G;
  else
    delete (ListGraph*)G;
  
  return b;
}

bool Tester::test_1() {
  Graph* G = createGraph(10);
  return cleanAndExit(G, true);
}

bool Tester::test_2() {
  Graph* G = createGraph(15);
  for (NodeID i=0; i < 15; i++)
    for (NodeID j=0; j < 15; j++)
      if (i != j && G->weight(i, j) != 0) 
	return cleanAndExit(G, false);

  return cleanAndExit(G, true);
}

bool Tester::test_3() {
  unsigned n = randInt(40,60);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  EdgeWeight w = (1.0*rand()) / rand();
  G->addEdge(V[0], V[1], w);

  return cleanAndExit(G, G->weight(V[0], V[1]) == w);
}

bool Tester::test_4() {
  unsigned n = randInt(40,60);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  EdgeWeight w = (1.0*rand()) / rand();
  G->addEdge(V[0], V[1], w);

  return cleanAndExit(G, G->weight(V[1], V[0]) == w);
}

bool Tester::test_5() {
  unsigned n = randInt(40,60);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  EdgeWeight w1 = (1.0*rand()) / rand();
  EdgeWeight w2 = (1.0*rand()) / rand();
  G->addEdge(V[0], V[1], w1);
  G->addEdge(V[0], V[2], w2);

  return cleanAndExit(G, G->weight(V[0], V[1]) == w1 && G->weight(V[1], V[0]) == w1 && 
		      G->weight(V[0], V[2]) == w2 && G->weight(V[2], V[0]) == w2);
}

bool Tester::test_6() {
  unsigned n = randInt(40,60);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  EdgeWeight w = (1.0*rand()) / rand();
  G->addEdge(V[0], V[1], w);
  for (unsigned i=0; i < n; i++)
    for (unsigned j=0; j < n; j++) {
      if (i == V[0]  && j == V[1]) {
	if (G->weight(i, j) != w)
	  return cleanAndExit(G, false);
      }
      else if (i == V[1]  && j == V[0]) {
	if (G->weight(i, j) != w)
	  return cleanAndExit(G, false);
      }
      else if (G->weight(i, j) != 0)
	return cleanAndExit(G, false);
    }

  return cleanAndExit(G, true);
}

bool Tester::test_7() {
  unsigned n = randInt(50,6);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);  

  for (unsigned i=0; i < n-1; i++)
    for (unsigned j=i+1; j < n; j++)
      G->addEdge(V[i], V[j],  ((i << 8) | j) + 1);

  for (unsigned i=0; i < n-1; i++)
    for (unsigned j=0; j < n; j++) {
      if (i==j && G->weight(i,j) != 0)
	return cleanAndExit(G, false);
      else if (i != j && G->weight(V[i],V[j]) != ((min(i,j) << 8) | max(i,j)) + 1)
	return cleanAndExit(G, false);
    }

  return cleanAndExit(G, true);
}
      
bool Tester::test_8() {
  unsigned n = randInt(40, 70);
  Graph* G = createGraph(n);
  return cleanAndExit(G, G->size() == n);
}

bool Tester::test_9() {
  unsigned n = randInt(40, 70);
  Graph* G =createGraph(n);
  unsigned num_edges = 0;

  for (unsigned i=0; i < n; i++)
    for (unsigned j=i+1; j < n; j++)
      if (i != j && randInt(0,3)==0) {
	G->addEdge(i, j, (1.0*rand()/rand()));
	num_edges++;
      }

  return cleanAndExit(G, G->numEdges() == num_edges);
}

bool Tester::test_10() {
  unsigned n = randInt(40,70);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  EdgeWeight w = (1.0*rand()) / rand();
  G->addEdge(V[0], V[1], w);

  list<NWPair> E1 = G->getAdj(V[0]);
  list<NWPair> E2 = G->getAdj(V[1]);

  return cleanAndExit(G, E1.size() == 1 && E2.size() == 1 &&
		      E1.begin()->first == V[1] && E1.begin()->second == w &&
		      E2.begin()->first == V[0] && E2.begin()->second == w);
}

bool Tester::test_11() {
  unsigned n = randInt(40, 70);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  for (unsigned i=1; i < n; i++)
    G->addEdge(V[0], V[i], 2.2*i);

  list<NWPair> E = G->getAdj(V[0]);
  for (unsigned i=1; i < n; i++) {
    list<NWPair>::iterator j = E.begin();
    while (j != E.end() && j->first != V[i]) 
      j++;
    if (j == E.end() || j->second != 2.2*i)
      return cleanAndExit(G, false);

    list<NWPair>E2 = G->getAdj(V[i]);
    if (E2.size() != 1 || E2.begin()->first != V[0] || E2.begin()->second != 2.2*i)
      return cleanAndExit(G, false);
  }

  return cleanAndExit(G, true);
}


bool Tester::test_12() {
  unsigned n = randInt(40, 70);
  Graph* G = createGraph(n);
  vector<NodeID> V = randNodeList(n);

  for (unsigned i=0; i < n-1; i++)
    for (unsigned j=i+1; j < n; j++) 
      if (i != j) 
	G->addEdge(V[i], V[j], ((i << 8) | j) + 1);
  
  for (unsigned i=0; i < n; i++) {
    list<NWPair> E = G->getAdj(V[i]);
    if (E.size() != n-1)
      return cleanAndExit(G, false);

    for (unsigned j=0; j < n; j++) {
      list<NWPair>::iterator k = find(E.begin(), E.end(), make_pair(V[j], (EdgeWeight)(((min(i,j) << 8) | max(i,j)) + 1)));
      if (j == i) { // j should not have been found
	if (k != E.end())
	  return cleanAndExit(G, false);
      }
      else {
	if (k == E.end() || k->second != ((min(i,j) << 8) | max(i,j)) + 1)
	  return cleanAndExit(G, false);
      }
    }
  }

  return cleanAndExit(G, true);
}  
  
bool Tester::run_test(int i) {
  switch (i) {
  case 1: return test_1();
  case 2: return test_2();
  case 3: return test_3();
  case 4: return test_4();
  case 5: return test_5();
  case 6: return test_6();
  case 7: return test_7();
  case 8: return test_8();
  case 9: return test_9();
  case 10: return test_10();
  case 11: return test_11();
  case 12: return test_12();
  default: assert(false);
  }
  return false;
}

void Tester::test_all() {
  if (matrix_graph)
    cout << "Matrix Graph:";
  else
    cout << "List Graph:";
  cout << endl;

  for (int i=1; i <= 12; i++)
    cout << "Test " << i << ": " << (run_test(i) ? "Working" : "Failed") << endl;
}
