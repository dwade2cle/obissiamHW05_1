#include "stdafx.h"
#include "GraphAlgs.h"
#include <cmath>
#define PI 3.14159265359


std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G, std::vector<Store> R)	{

	// First, create an integer array;
	const int N = R.size();
	std::vector<std::vector<int>> polygonNumber;
	int numVisited;

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
	std::vector<int> beenVisited; beenVisited.resize(N);
	for(int i = 0; i < N; i++)	{
		beenVisited[i] = -1;
	}
	int count = 1; int currentIndex;
	double angle = PI;
	double angle2;
	int chosen;
	int numVisited = 0;
	while (N - numVisited > 3)		{
	// Find outermost polygon
	// Start at the rightmost node and find smallest angle past pi/2
		polygonNumber.resize(count);
		polygonNumber[count - 1].push_back(rightIndex);
		numVisited++;
		bool reachedTop = false;
		while(!reachedTop)	{
			if(rightIndex = topIndex) break;
			currentIndex = rightIndex;
			for(int i = 1; i < N; i++)	{
				int index = (rightIndex + i)%N;
				if(beenVisited[index] == -1)	{
					double y2 = R[index].y; double y1 = R[currentIndex].y; 
					double x2 = R[index].y; double x1 = R[currentIndex].y; 
					if(y2 > y1)	{
						angle2 = (atan((x1-x2)/(y2-y1)) < angle);
						if(angle2 < angle && angle2 > 0;) chosen = index;
					}
				}
			} beenVisited[chosen] = count - 1; polygonNumber[count - 1].push_back(chosen);
			numVisited++;
			if(chosen == topIndex) reachedTop = true;
			else currentIndex = chosen;
		}
		// continue until we've reached top and find smallest angle past pi
		bool reachedLeft = false;
		angle = PI;
		while(!reachedLeft)	{
			if(topIndex = leftIndex) break;
			currentIndex = topIndex;
			for(int i = 1; i < N; i++)	{
				int index = (topIndex + i)%N;
				if(beenVisited[index] == -1)	{
					double y2 = R[index].y; double y1 = R[currentIndex].y; 
					double x2 = R[index].y; double x1 = R[currentIndex].y; 
					if(x2 < x1)	{
						angle2 = (atan((y1-y2)/(x1-x2)) < angle);
						if(angle2 < angle && angle2 > 0) chosen = index;
					}
				}
			} beenVisited[chosen] = count - 1; polygonNumber[count - 1].push_back(chosen);
			numVisited++;
			if(chosen == leftIndex) reachedLeft = true;
			else currentIndex = chosen;
		}
		// keep going until returned to rightmost node
		bool reachedBottom = false;
		angle = PI;
		while(!reachedLeft)	{
			if(leftIndex = bottomIndex) break;
			currentIndex = leftIndex;
			for(int i = 1; i < N; i++)	{
				int index = (leftIndex + i)%N;
				if(beenVisited[index] == -1)	{
					double y2 = R[index].y; double y1 = R[currentIndex].y; 
					double x2 = R[index].y; double x1 = R[currentIndex].y; 
					if(y2 < y1)	{
						angle2 = (atan((x2-x1)/(y1-y2)) < angle);
						if(angle2 < angle && angle2 > 0) chosen = index;
					}
				}
			} beenVisited[chosen] = count - 1; polygonNumber[count - 1].push_back(chosen);
			numVisited++;
			if(chosen == bottomIndex) reachedBottom = true;
			else currentIndex = chosen;
		}
		bool reachedRight = false;
		angle = PI;
		while(!reachedRight)	{
			if(bottomIndex = rightIndex) break;
			currentIndex = bottomIndex;
			for(int i = 1; i < N; i++)	{
				int index = (bottomIndex + i)%N;
				if(beenVisited[index] == -1)	{
					double y2 = R[index].y; double y1 = R[currentIndex].y; 
					double x2 = R[index].y; double x1 = R[currentIndex].y; 
					if(x2 > x1)	{
						angle2 = (atan((y2-y1)/(x2-x1)) < angle);
						if(angle2 < angle && angle2 > 0) chosen = index;
					}
				}
			}	if(chosen == rightIndex) {beenVisited[rightIndex] = count - 1; break;} 
			beenVisited[chosen] = count - 1; polygonNumber[count - 1].push_back(chosen);
			numVisited++;
			currentIndex = chosen;
		}
		// Note: When we look at right value we only worry about values higher (unless right is also top)
		// When we look at top we only worry about values to the left (unless top is also left)
		// ...and so on

		// While there are more than 3 Nodes that have not been taken, continue to find inner polygons
		count++;
		if(N - numVisited > 3)	{
			top = right = 0; bottom = left = 1;
			for(int i = 0; i < N; i++)	{
				// Check x and y values and set top, bottom, left and right
				if(beenVisited[i] = -1)	{
					if(R[i].x < left) {left = R[i].x; leftIndex = i;}
					if(R[i].x > right) {right = R[i].x; rightIndex = i;}
					if(R[i].y > top) {top = R[i].y; topIndex = i;}
					if(R[i].y < bottom) {bottom = R[i].y; bottomIndex = i;}
				}
			} 
		} else	{
			polygonNumber.resize(count);
			for(int i = 0; i < N; i++)	{
				if(beenVisited[i] == -1)	{
					polygonNumber[count - 1].push_back(i);
				}
			}
		}
	}
	// Once all polygons have been found, start with first inner polygon. For each node, find which edge it is closest to.
	for(int i = 0; i < polygonNumber.size();
	// If more than one node is close to an edge, find order of which one is closest to one of the nodes.
	// Once we have established all of the edges, update the edges.
	// Move to the next polygon and do the same.
	}
}