#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <map>
#include "Graph.h"

class MatrixGraph : public Graph{	
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size) : Graph(type, size) {
		m_Mat = new int*[size];
		for (int i = 0; i < size; i++) {
			m_Mat[i] = new int[size];
			memset(m_Mat[i], 0, sizeof(int)*size);
		}
		//Creates a two-dimensional array of size n * n and set all values in the array to 0.
	}
	~MatrixGraph() {
		for (int i = 0; i < getSize(); i++) 
			delete[] m_Mat[i];
		delete[] m_Mat;
		//Free the graph matrix.
	}		
	void getAdjacentEdges(const int vertex, map<int, int>* m);
	//Find and save the edge heading to the entered vertex from matrix graph.
	void getAdjacentEdgesDirect(const int vertex, map<int, int>* m);
	//Find and save the edge starting from the entered vertex.
	void insertEdge(const int from, const int to, const int weight);
	//Insert edge information into the graph with delivered values.
	bool printGraph();
	//Print graph inormation.
	vector<int>* getSegmentTree(const int vertex) {return nullptr;}
	//Get segment tree.
	//In the matrix graph, the "KWANGWOON" algorithm cannot use so return the nullptr.
};

#endif