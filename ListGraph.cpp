#include "ListGraph.h"
#include <iostream>
#include <utility>

void ListGraph::getAdjacentEdges(const int vertex, map<int, int>* m) {
	for (int i = 0; i < m_Size; i++) {
		auto it = m_List[i].find(vertex);
		if (it != m_List[i].end())
			m->insert({i+1, it->second});
		
	}
	return;
}
void ListGraph::getAdjacentEdgesDirect(const int vertex, map<int, int>* m) {
	//Add edges that connected with input vertex which is start.
	for (auto it = m_List[vertex-1].begin(); it != m_List[vertex-1].end(); it++)
		m->insert({it->first, it->second});
	
	return;
}

void ListGraph::insertEdge(const int from, const int to, const int weight) {
	//Insert edge.
	m_List[from-1].insert({to, weight});
	kw_graph[from-1].push_back(to);
	kw_graph[to-1].push_back(from);
	return;
}

bool ListGraph::printGraph() {
	if (m_List == nullptr)
		return false;
	if (m_List->size() == 0)
		return false;
	//Print graph.
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << "======== PRINT ========" << endl;
	for(int i=0; i<m_Size; i++) {
		flog << "[" << i+1 << "]";
		for(auto it = m_List[i].begin(); it !=m_List[i].end() && flog << " -> "; it ++) 
			flog << "(" << it ->first << "," << it -> second << ")";
		flog << endl;
	}
	flog << "======================" << endl << endl;
	flog.close();
	return true;
}