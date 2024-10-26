#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <tuple>

using namespace std;

#define MAX 999999

class Graph{	
protected:
	bool m_Type;
	int m_Size;

public:
	Graph(bool type, int size);
	virtual ~Graph();

	bool getType();	
	int getSize();

	virtual void getAdjacentEdges(const int vertex, map<int, int>* m) = 0;		
	virtual void getAdjacentEdgesDirect(const int vertex, map<int, int>* m) = 0;	
	virtual void insertEdge(const int from, const int to, const int weight) = 0;				
	virtual	bool printGraph() = 0;
	virtual vector<int>* getSegmentTree(const int vertex) = 0;
};

#endif
