#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

void MatrixGraph::getAdjacentEdges(const int vertex, map<int, int>* m) {
	//Get Adjacent edges which are heading to the input vertex.
	for (int i = 0; i < getSize(); i++) {
		if (m_Mat[i][vertex-1] != 0) {
			m->insert({i+1, m_Mat[i][vertex-1]});
		}
	}
	return;
}
void MatrixGraph::getAdjacentEdgesDirect(const int vertex, map<int, int>* m) {
	//Get Adjacent edges which starts at the input vertex.
	for (int i = 0; i < getSize(); i++) {
		if (m_Mat[vertex-1][i] != 0) {
			m->insert({i+1, m_Mat[vertex-1][i]});
		}
	}
	return;
}
void MatrixGraph::insertEdge(const int from, const int to, const int weight) {
	//from vertex:row, to vertex: column
	m_Mat[from][to] = weight;
	return;
}

bool MatrixGraph::printGraph() {
	if( m_Size < 0 )
		return 0;
	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << "======== PRINT ========" << endl;
	fout << "\t\t";
	for(int i = 1; i <= m_Size; i++)
		fout<<"["<< i <<"]"<< "\t\t";
	fout << endl;
	for(int i=0; i < m_Size; i++) {
		fout << "[" << i+1 << "]";
		for(int j = 0; j < m_Size; j++) {
			fout << "\t ";
			if (i < 9 || j > 0)
				fout << "\t ";
			fout << m_Mat[i][j];
		}
		fout << endl;
	}
	fout << "======================" << endl << endl;
	fout.close();
	return 1;
}

