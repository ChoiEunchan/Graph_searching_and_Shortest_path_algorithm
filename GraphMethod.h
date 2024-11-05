#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, const char option, int vertex);
bool DFS(Graph* graph, const char option,  const int vertex);
void DFS_R(Graph* graph, const char option, bool* visit, const int vertex);
bool Kruskal(Graph* graph);
void QuickSort(vector<tuple<int, int, int>>* graph, const int start, const int end);
void InsertionSort(vector<tuple<int, int, int>>* graph, const int start, const int end);
bool checkCycle(multimap<int, pair<int, int>>* spt, int* disjoint_set, const pair<int, int> edge);
bool checkLink(multimap<int, pair<int, int>>* spt, const pair<int, int>edge, const int size);
bool Dijkstra(Graph* graph, const char option, const int start);    //Dijkstra
bool Bellmanford(Graph* graph, const char option, const int s_vertex, const int e_vertex); //Bellman - Ford
bool FLOYD(Graph* graph, const char option);   //FLoyd

#endif
