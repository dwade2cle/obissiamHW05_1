// GraphAlgs.h
#include "Graph.h"
#include <vector>

#pragma once


/*
 * Solves the Traveling Salesperson Problem: finding the shortest cycle through a graph that 
 * vists every node exactly once (with exception of the first node, which is repeated as the 
 * last node in the cycle.)
 * 
 * Return value: Return a pair, with the first element being a vector of length n listing the 
 *  order of the nodes in the cycle (do NOT list the start node twice), and the second element
 *  being the length of that path (do NOT forget to include the edge from the last node back to
 *  the start node in the total length.
 *
 * Preconditions: 
 *     G is undirected.
 *     Every pair of nodes u,v  (u != v) has an edge connecting the of weight > 0.
 */
#include "StarbucksMap.h"
#include "stdafx.h"
#include <cmath>
#define PI 3.14159265359


std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G, std::vector<Store> R)	{

	// First, create an integer array;
	const int N = R.size();

	// Find top, bottom, left and right values
	double top, bottom, left, right; top = right = 0; left = bottom = 1;
	int leftIndex, rightIndex, topIndex, bottomIndex;
	for(int i = 0; i < N; i++)	{
		// Check x and y values and set top, bottom, left and right
		if(R[i].x < left) {left = R[i].x; leftIndex = i;}
		if(R[i].x > right) {right = R[i].x; rightIndex = i;}
		if(R[i].y > top) {top = R[i].y; topIndex = i;}
		if(R[i].y < bottom) {bottom = R[i].y; bottomIndex = i;}
	}
	std::vector<std::vector<int>> beenVisited; beenVisited.resize(2);
	beenVisited[0].resize(N); beenVisited[1].resize(N);
	for(int i = 0; i < N; i++)	{
		beenVisited[0][i] = -1;
		beenVisited[1][i] = -1;
	}
	int count = 1; int currentIndex;
	double angle;
	double angle2;
	int chosen = rightIndex; int index;
	int numVisited = 0;
	// Find outermost polygon
	// Start at the rightmost node and find smallest angle past pi/2
	numVisited++;
	bool reachedTop = false;
	while(!reachedTop)	{
		if(rightIndex == topIndex) break;
		currentIndex = chosen;
		angle = PI;
		for(int i = 0; i < N; i++)	{
			if(beenVisited[1][i] == -1 && i != rightIndex)	{
				double y2 = R[i].y; double y1 = R[currentIndex].y; 
				double x2 = R[i].x; double x1 = R[currentIndex].x; 
				if(y2 > y1)	{
					angle2 = atan((x1-x2)/(y2-y1));
					if(angle2 < angle && angle2 > 0) {angle = angle2; chosen = i;}
				}
			}
		} beenVisited[0][currentIndex] = chosen; beenVisited[1][chosen] = currentIndex;
		numVisited++;
		if(chosen == topIndex) reachedTop = true;
		else currentIndex = chosen;
	}
	// continue until we've reached top and find smallest angle past pi
	bool reachedLeft = false;
	//chosen = topIndex;
	while(!reachedLeft)	{
		if(topIndex == leftIndex) break;
		currentIndex = chosen;
		angle = PI;
		for(int i = 0; i < N; i++)	{
			if(beenVisited[1][i] == -1 && i != topIndex)	{
				double y2 = R[i].y; double y1 = R[currentIndex].y; 
				double x2 = R[i].x; double x1 = R[currentIndex].x; 
				if(x2 < x1)	{
					angle2 = atan((y1-y2)/(x1-x2));
					if(angle2 < angle && angle2 > 0) {angle = angle2; chosen = i;}
				}
			}
		} beenVisited[0][currentIndex] = chosen; beenVisited[1][chosen] = currentIndex; 
		numVisited++;
		if(chosen == leftIndex) reachedLeft = true;
		else currentIndex = chosen;
	}
	// keep going until returned to rightmost node
	bool reachedBottom = false;
	//chosen = leftIndex;
	while(!reachedBottom)	{
		if(leftIndex == bottomIndex) break;
		currentIndex = chosen;
		angle = PI; 
		for(int i = 0; i < N; i++)	{
			if(beenVisited[1][i] == -1 && i != leftIndex)	{
				double y2 = R[i].y; double y1 = R[currentIndex].y; 
				double x2 = R[i].x; double x1 = R[currentIndex].x; 
				if(y2 < y1)	{
					angle2 = atan((x2-x1)/(y1-y2));
					if(angle2 < angle && angle2 > 0) {angle = angle2; chosen = i;}
				}
			}
		} beenVisited[0][currentIndex] = chosen; beenVisited[1][chosen] = currentIndex;; 
		numVisited++;
		if(chosen == bottomIndex) reachedBottom = true;
		else currentIndex = chosen;
	}
	bool reachedRight = false;
	//chosen = bottomIndex;
	while(!reachedRight)	{
		if(bottomIndex == rightIndex) break;
		currentIndex = chosen;
		angle = PI; 
		for(int i = 0; i < N; i++)	{
			if(beenVisited[1][i] == -1 && i != bottomIndex)	{
				double y2 = R[i].y; double y1 = R[currentIndex].y; 
				double x2 = R[i].x; double x1 = R[currentIndex].x; 
				if(x2 > x1)	{
					angle2 = atan((y2-y1)/(x2-x1));
					if(angle2 < angle && angle2 > 0) {angle = angle2; chosen = i;}
				}
			}
		}
		beenVisited[0][currentIndex] = chosen; beenVisited[1][chosen] = currentIndex; 
		if(chosen == rightIndex) break; 
		numVisited++;
		currentIndex = chosen;
	}
	// Note: When we look at right value we only worry about values higher (unless right is also top)
	// When we look at top we only worry about values to the left (unless top is also left)
	// ...and so on
	

	// Once outer polygon has been found, start making new connections. For each node, find which edge and node it is closest to.
	for(int i = 0; i < (N-numVisited); i++)	{
		// First we need to find the node that is closest to either another node or one of the edges
		//if(beenVisited[1][i] == -1)		{
			double closestWeight; int indexOut, indexIn;
			closestWeight = 1;
			for(int i = 0; i < N; i++)	{
				if(beenVisited[0][i] == -1)		{
					for(int j = 0; j < N; j++)	{
						if(beenVisited[0][j] != -1)	{
							if(G->weight(i,j) < closestWeight && G->weight(i,j) > 0) {
								closestWeight = G->weight(i,j); indexOut = i; indexIn = j;
							}
						}
					}
				}
			}
			/**double y1, x1, y2, x2; double angle;
			double m1; double m2; double distToEdge; 
			double vertX, vertY;
			double closestWeight1 = 1; int indexOut1, indexIn1;
			for(int i = 0; i < N; i++)	{
				if(beenVisited[0][i] == -1)	{
					y2 = R[i].y; x2 = R[i].x; 
					for(int j = 0; j < N; j++)	{
						if(beenVisited[0][j] != -1)		{
							vertY = R[j].y; vertX = R[j].x; 
							y1 = R[beenVisited[0][j]].y; x1 = R[beenVisited[0][j]].x; 
							//y1 -= vertY; y2 -= vertY; x1 -= vertX; x2 -= vertX; vertX = 0; vertY = 0;
							m1 = (y1-vertY)/(x1-vertX); m2 = (y2-vertY)/(x2-vertX);
							distToEdge = G->weight(i,j); 
							angle = atan(m2 - m1)/(1 + m2*m1);
							//if(distToEdge*cos(angle) < G->weight(j, beenVisited[0][j]))	{
							distToEdge = distToEdge*sin(angle);
							if(distToEdge < closestWeight1 && angle > 0)	{
								closestWeight1 = distToEdge; indexOut1 = i; indexIn1 = j;
							}
							//}
						}
					} 
				} 
			}*/
			// Next we update our vector showing that this node is in between the others.
			//if(closestWeight < closestWeight1)	{
				if(G->weight(indexOut, beenVisited[0][indexIn]) < G->weight(indexOut, beenVisited[1][indexIn]))	{
					// indexIn points forward to a value, that value now points backward to the indexOut
					beenVisited[1][beenVisited[0][indexIn]] = indexOut;
					// indexOut now points backwards to indexIn
					beenVisited[1][indexOut] = indexIn; 
					// indexOut points forward to the value indexIn points to
					beenVisited[0][indexOut] = beenVisited[0][indexIn];
					// finally, indexIn points forward to indexOut;
					beenVisited[0][indexIn] = indexOut; 
				} else {
					// indexIn points backward to a value, that value now points forward to the indexOut
					beenVisited[0][beenVisited[1][indexIn]] = indexOut;
					// indexOut now points forwards to indexIn
					beenVisited[0][indexOut] = indexIn; 
					// indexOut points backward to the value indexIn points to
					beenVisited[1][indexOut] = beenVisited[0][indexIn];
					// finally, indexIn points backward to indexOut;
					beenVisited[1][indexIn] = indexOut; 
				}
			/**} else	{
				beenVisited[1][beenVisited[0][indexIn1]] = indexOut1;
				beenVisited[1][indexOut1] = indexIn1; 
				beenVisited[0][indexOut1] = beenVisited[0][indexIn1];
				beenVisited[0][indexIn1] = indexOut1; 
			}*/
		//}
	}
	std::pair<std::vector<NodeID>, EdgeWeight> outPair;
	std::vector<NodeID> outVec;
	EdgeWeight out = 0; index = 0;
	for(int i = 0; i < N; i++)	{
		out += G->weight(index, beenVisited[0][index]);
		outVec.push_back(index);
		index = beenVisited[0][index];
	}
	outPair.first = outVec; outPair.second = out;
	return outPair;
}