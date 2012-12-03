#include "stdafx.h"
#include "StarbucksMap.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


bool operator==(const Store& S1, const Store& S2) {
  return S1.x == S2.x && S1.y == S2.y;
}

bool operator<(const Store& S1, const Store& S2) {
  return S1.x < S2.x || (S1.x == S2.x && S1.y < S2.y);
}

double dist(const Store& S1, const Store& S2) {
  return sqrt((S1.x - S2.x)*(S1.x - S2.x) + (S1.y - S2.y)*(S1.y - S2.y));
}

StarbucksMap::StarbucksMap() {
  ifstream inFile("Starbucks.csv");
  if(!inFile){
    std::cout << "Error opening Starbucks.csv file" << endl;
    exit(0);
  }

  int n;
  inFile >> n;
  
  char buffer[256];
  for(int i=0; i<n; i++){
    Store S;
    inFile.getline(buffer, 256, ',');//Getline reads up until the first occurence of ',', and consumes the ',' for me
    S.city = buffer;
    inFile.getline(buffer,256,',');
    S.address = buffer;
    inFile >> S.x;
    char c;
    inFile.get(c); //consume the comma, because >> does not do so
    inFile >> S.y; //Don't need to worry about consuming the \n, because getline handles this
    StoreList.push_back(S);
  }

  sort(StoreList.begin(), StoreList.end());
  StoreList.resize(unique(StoreList.begin(), StoreList.end()) - StoreList.begin());
}


vector<Store> StarbucksMap::randomSet(int n) {
  vector<Store> finalList;
  for (int i=0; i < n; i++) {
    int k = rand() % (size()-i);
    finalList.push_back(StoreList[k]);
    if ((unsigned)k != size()-i-1)
      swap(StoreList[k], StoreList[size()-i-1]);
  }

  return finalList;
}

