/*****
 * Author   : karroje
 * Date     : 2011-04-10
 * Sources  : All code is original
 * Purpose  : This class is used for reading in and managing the Starbucks data for purpose of testing the
 *            graph code.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#pragma once

/* 
 * A helper class to hold information on a specific store.
 */
class Store {
 public:
  std::string city;
  std::string address;
  double x;
  double y;
};

/*
 * Various operators to allow the for the application of certaint stl algorithms
 * to the store class and to make life easier
 */
bool operator==(const Store& S1, const Store& S2);
bool operator<(const Store& S1, const Store& S2);
double dist(const Store& S1, const Store& S2);

template<class ostream>
ostream& operator<<(ostream& out, const Store& S) {
  out << S.city << "\n" << S.address << "\n" << "(" << S.x << ", " << S.y << ")\n";
  return out;
}



/*
 * A class containing all StartbucksMap information.
 */
class StarbucksMap {
 public:
  StarbucksMap();
  
  std::vector<Store> randomSet(int n);
  unsigned size() {return StoreList.size();}

 private:
  std::vector<Store> StoreList;
};
