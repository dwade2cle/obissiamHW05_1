/*****
 * Author   : karroje
 * Date     : 2011-04-10
 * Sources  : All code is original
 * Purpose  : Code for testing your graph algorithm.  First tests all 
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */
#include "stdafx.h"
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "stdafx.h"
#include <MMSystem.h>

#include "StarbucksMap.h"
#include "Tester.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "GraphAlgs.h"

#pragma comment (lib, "winmm.lib")

using namespace std;


Graph* createStarbucksGraph(vector<Store> storeList, bool use_matrix) {
  Graph* G;
  if (use_matrix)
    G = new MatrixGraph(storeList.size());
  else
    G = new ListGraph(storeList.size());

  for (NodeID u=0; u < G->size()-1; u++)
    for (NodeID v = u+1; v < G->size(); v++)
      G->addEdge(u, v, dist(storeList[u], storeList[v]));

  return G;
}


void deleteStarbucksGraph(Graph* G, bool use_matrix) {
  if (use_matrix)
    delete (MatrixGraph*)G;
  else
    delete (ListGraph*)G;
}


  /********************************
   * The following section is commented out so you can test your graph code
	* before you have written your TSP code.  Once you are ready to test your
	* TSP code, remove the comments (along with the comments taking out 
	* a portion of the main function, below).
	********************************/
void testSingleTSP(StarbucksMap& SB, int size, bool use_matrix) {
  vector<Store> R = SB.randomSet(size);
  Graph* G = createStarbucksGraph(R, use_matrix);
  pair<vector<NodeID>, EdgeWeight> p = TSP(G, R);

  EdgeWeight actual = 0;
  for (int i=0; i < size-1; i++)
    actual += G->weight(p.first[i], p.first[i+1]);
  actual += G->weight(p.first[size-1], p.first[0]);

  cout << "Best cycle length: " << p.second << " ";
  if (fabs(p.second - actual) > 0.00000001)
    cout << "(ERROR -- the length returned is not equal to the actual length)";
  else
    cout << "(Path length matches)" << endl;
  cout << "\n\n";
  //for (int i=0; i < size; i++)
	//cout << R[p.first[i]] << "\n";
  deleteStarbucksGraph(G, use_matrix);
}

pair<int,int> testSpeedTSP(StarbucksMap& SB, double time_limit, bool use_matrix) {
	int n = 3;
	int totalTime = 0;
	while (true) {
		  vector<Store> R = SB.randomSet(n);
		  Graph* G = createStarbucksGraph(R, use_matrix);

		  int startTime = timeGetTime();
		  pair<vector<NodeID>, EdgeWeight> p = TSP(G, R);
		  int newTime = timeGetTime() - startTime;
		  cout << "TSP Speed: Finished " << n << " cities in " << newTime/1000.0 << " seconds." << endl;
		  if (newTime/1000.0 > time_limit)
			  break;
		  totalTime = newTime;
		  n++;
	}
	return make_pair(n,totalTime);
}


int main(int argc, char** argv) {
  int n = 5;

  srand(1);

  // Apply each of the Tester methods to your MatrixGraph class.
  Tester T1(true);
  T1.test_all();

  cout << endl;

  // Apply each of the Tester methods to your ListGraph class.
  Tester T2(false);
  T2.test_all();

  /********************************
   * The following section is commented out so you can test your graph code
	* before you have written your TSP code.  Once you are ready to test your
	* TSP code, remove the comments (along with the comments taking out 
	* testSingleTSP and testSpeedTSP, above).
	********************************/
  //// Read in Starbucks Locations, test your TSP algorithm on a random MatrixGraph 
  //// of size n, and test your TSP algorithm on a random ListGraph of size n.

  //// Uncomment the following three lines once your TSP function has been written
  StarbucksMap SB;

  testSingleTSP(SB, 100, true);
  //testSingleTSP(SB, 5, false);

  //pair<int,int> p = testSpeedTSP(SB, 30, true);

  return 0;
}
