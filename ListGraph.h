#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{	
private:
	map <int, int>* m_List;
	vector<int>* kw_graph;
	
public:	
	ListGraph(bool type, int size) : Graph(type, size) {
		m_Type = type;
		m_List = new map<int, int>[size];
		kw_graph = new vector<int>[size];
		//Create graph implemented by linked list and
		//create kw_graph which will be used for algorithm "KWANGWOON".
	}

	~ListGraph() {
		m_List->clear();
		for (int i = 0; i < getSize(); i++) {
			m_List[i].clear();
			map<int, int>().swap(m_List[i]);
			kw_graph[i].clear();
			vector<int>().swap(kw_graph[i]);
		}
		delete[] kw_graph;
		delete[] m_List;
		//Free the graph map's and kw_graph vector's memory.
	}
		
	void getAdjacentEdges(const int vertex, map<int, int>* m);
	//Find and save the edge heading to the entered vertex from linked list graph.
	void getAdjacentEdgesDirect(const int vertex, map<int, int>* m);
	//Find and save the edge starting from the entered from linked list graph.
	void insertEdge(const int from, const int to, const int weight);
	//Insert edge information into the graph with delivered values.
	bool printGraph();
	//Print graph inormation.
	vector<int>* getSegmentTree(const int vertex) {return &kw_graph[vertex-1];}
	//Get segment tree.
};

#endif