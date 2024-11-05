#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;


bool BFS(Graph* graph, const char option, const int start_vertex) {
    int n = graph->getSize();
    if (n == 0) return false;
    //If the graph is not exist, return false.
    ofstream fout;
    map<int, int>m;
    map<int, int>::iterator it;
    queue<int> q;
    bool visited[n];
    //Initialize visit table.
    fill(visited, visited+n, false);
    graph->getAdjacentEdgesDirect(start_vertex, &m);
    if (option == 'N' || option == 'n') 
        graph->getAdjacentEdges(start_vertex, &m);
    if (m.size() == 0)
        return false;
    int vertex = start_vertex;
    fout.open("log.txt", ios::app);
    fout << "======== BFS ========\n";
    fout << "Start vertex : " << start_vertex << endl;
    q.push(start_vertex);
    //Push the starting vertex into the queue.
    while(!q.empty()) {
        for (it = m.begin(); it != m.end(); it++) {
            if (visited[it->first - 1] == false) 
                q.push(it->first);
        }
        //Push the vertecies that is not visited yet into the queue and set the next vertex.
        for (q; !q.empty(); q.pop()) {
            vertex = q.front();
            if (visited[vertex - 1] == false) {
                q.pop();
                visited[vertex - 1] = true;
                fout << vertex;
                vertex = q.front();
                break;
            //If the vertex that is head of queue, is not visited,
            //set the visited value at "vertex" to true and print the vertex.
            }
        }
        if (q.empty())  break;
        else fout << " -> ";
        //If the vertex is already visited, just pop the vertex from the queue.
        m.clear();
        graph->getAdjacentEdgesDirect(vertex, &m);
        if (option == 'N' || option == 'n')
            graph->getAdjacentEdges(vertex, &m);
        //Get edge information according to directionality option.
    }
    fout << "\n======================" << endl << endl;			
    fout.close();
    m.clear();
    map<int, int>().swap(m);
    return true;
}
void DFS_R(Graph* graph, const char option, bool* visit, const int vertex) {
    ofstream fout;
    map<int, int> m;
    visit[vertex - 1] = true;
    fout.open("log.txt", ios::app);
    fout << vertex;
    graph->getAdjacentEdgesDirect(vertex, &m);
    if (option == 'N' || option == 'n')
        graph->getAdjacentEdges(vertex, &m);
    return;

}
bool DFS(Graph* graph, const char option,  const int start_vertex) {   
    int n = graph->getSize();
    if (n == 0) return false;
    ofstream fout;
    map<int, int> m;
    map<int, int>::iterator it;
    bool visited[n];
    int cur_vertex = start_vertex;
    fill(visited, visited+n, false);
    graph->getAdjacentEdgesDirect(start_vertex, &m);
    if (option == 'N' || option == 'n')
        graph->getAdjacentEdges(start_vertex, &m);

    if (m.size() == 0)
        return false;
    //If there's novertex delivered, then return false and terminate the DFS algorithm.
    fout.open("log.txt", ios::app);
	fout << "======== DFS ========" << endl;
    fout << "Start vertex : " << start_vertex << endl;
    it = m.begin();
    //Traverse the graph and print vertcies that are visited.
    //When the destination is visited then, return to previous node and go to another adjacented node.
    stack<int>st;
    st.push(cur_vertex);
    while (!st.empty()) {
        if (!visited[st.top()-1]) {
            fout << st.top();
            visited[st.top()-1] = true;
            for (it; it != m.end(); it++) {
                if (!visited[it->first - 1]) {
                    cur_vertex = it->first;
                    st.push(cur_vertex);
                    break;
                }
            }
            if (!visited[st.top()-1])
                fout << " -> ";
            m.clear();
            if (option == 'N' || option == 'n')
                graph->getAdjacentEdges(cur_vertex, &m);
            graph->getAdjacentEdgesDirect(cur_vertex, &m);
            it = m.begin();
        }
        else {
            st.pop();
            m.clear();
            cur_vertex = st.top();
            if (option == 'N' || option == 'n')
                graph->getAdjacentEdges(cur_vertex, &m);
            graph->getAdjacentEdgesDirect(cur_vertex, &m);
            for (it = m.begin(); it != m.end(); it++) {
                if (!visited[it->first-1]) {
                    cur_vertex = it->first;
                    break;
                }
            }
            if (it == m.end()) {
                st.pop();
                cur_vertex = st.top();
            }
                
        }
    }
    fout << "\n======================" << endl << endl;			
    fout.close();
    m.clear();
    map<int, int>().swap(m);
    
    return true;
}

bool Kruskal(Graph* graph) {
    if (graph == nullptr) return false;
    int n = graph->getSize();
    if (n == 0) return false;
    map<int, int>edge_set[n];
    vector<tuple<int, int, int>>SPT;
    multimap<int, pair<int, int>>min_spt;
    int disjoint_set[n+1];
    fill(disjoint_set, disjoint_set + n + 1, -1);
    int count = 0, cost = 0, root1 = -1, root2 = -1, temp1 = 0, temp2 = 0;
    ofstream fout;
    //Get edges that are included in graph.
    for (int i = 1; i <= n; i++) {
        graph->getAdjacentEdgesDirect(i, &edge_set[i-1]);
        count = count + edge_set[i-1].size();
        for (auto it = edge_set[i-1].begin(); it != edge_set[i-1].end(); it++) {
            SPT.push_back(make_tuple(it->second, i, it->first));
            cost++;
        } 
    }
    QuickSort(&SPT, 0, cost - 1);
    cost = 0;
    count = 0;
    // Make minimum spanning tree(MST).
    int SPT_index = 0;
    
    while (count < n-1) {
        auto it = SPT.at(SPT_index);
        if (!checkLink(&min_spt, {get<1>(it), get<2>(it)}, n)) {
            min_spt.insert({get<1>(it), {get<2>(it), get<0>(it)}});
            min_spt.insert({get<2>(it), {get<1>(it), get<0>(it)}});
            count++;
            if (disjoint_set[get<1>(it)] == -1) {
                if (disjoint_set[get<2>(it)] == -1)
                    disjoint_set[get<2>(it)] = get<1>(it);
            }
            else 
                disjoint_set[get<1>(it)] = get<2>(it);
        }
        else {
            if (!checkCycle(&min_spt, disjoint_set, {get<1>(it), get<2>(it)})) {
                min_spt.insert({get<1>(it), {get<2>(it), get<0>(it)}});
                min_spt.insert({get<2>(it), {get<1>(it), get<0>(it)}});
                count++;
                if (temp1 >= temp2)
                    disjoint_set[get<1>(it)] = get<2>(it);
                else
                    disjoint_set[get<2>(it)] = get<1>(it);
                
            }
            root1 = -1;
            root2 = -1;
            temp1 = 0;
            temp2 = 0;
        }
        SPT_index++;
    }
    //Print result.
    fout.open("log.txt", ios::app);
	fout << "======== KRUSKAL ========";
    count = 0;
    int curr_edge = 1;
    for (auto it = min_spt.begin(); it != min_spt.end(); it++) {
        curr_edge = it->first;
        if (curr_edge != count) {
            fout << "\n[" << it->first << "] \t";
            count = it->first;
        }
        fout << it->second.first << "(" << it->second.second << ")\t";
        cost += it->second.second;
    }
    fout << "\ncost : " << cost/2 << endl;
    fout << "=========================" << endl << endl;
    fout.close();
    
    return true;
}

void QuickSort(vector<tuple<int, int, int>>* graph, const int start, const int end) {
    if (end - start + 1 < 7)
        InsertionSort(graph, start, end);
    
    else if (start < end) {
        int i = start + 1, j = end, pivot = get<0>(graph->at(start));
        do {
            while(get<0>(graph->at(i)) <= pivot) {
                i++;
            }
            while(get<0>(graph->at(j)) > pivot) {
                j--;
            }
            if (i < j)
                swap(graph->at(i), graph->at(j));
        } while (i < j);
        swap(graph->at(j), graph->at(start));
        QuickSort(graph, start, j-1);
        QuickSort(graph, j + 1, end);
    }
    return;
    
}
void InsertionSort(vector<tuple<int, int, int>>* graph, const int start, const int end) {
    if (start == end)
        return;
    int insert_index = start, ise_weight, count;
    for (insert_index; insert_index <= end; insert_index++) {
        count = insert_index - 1;
        ise_weight = get<0>(graph->at(insert_index));
        while (count >= start) {
            if (ise_weight < get<0>(graph->at(count))) {
                swap(graph->at(count), graph->at(count+1));
                count--;
            }
            else
                break;
        }
    }
    return;
}
bool checkCycle(multimap<int, pair<int, int>>* spt, int* disjoint_set, const pair <int, int> edge) {
    if (spt->size() == 0 || spt == nullptr) return false;
    int root1, root2, count = -1;

    root1 = edge.first;
    while (disjoint_set[root1] > 0)
        root1 = disjoint_set[root1];
    //get a first node's root.
    root2 = edge.second;
    while (disjoint_set[root2] > 0)
        root2 = disjoint_set[root2];
    //get a second node's root.
    if (root1 != root2)
        return false;
    //If root1 and root2 are different, there's no cycle so return false.
    else
        return true;
    //If root1 and root2 are same, there's cycle so return true.
}

bool checkLink(multimap<int, pair<int, int>>* spt, const pair<int, int>edge, const int size) {
    if (spt->size() == 0)
        return false;
    bool visited[size + 1];
    fill(visited, visited + size + 1, false);
    for (auto it = spt->begin(); it != spt->end(); it++) {
        if (visited[it->second.first] == false)
            visited[it->second.first] = true;
        if (visited[it->first] == false)
            visited[it->first] = true;
    }
    return (visited[edge.first] & visited[edge.second]);
}

bool Dijkstra(Graph* graph, const char option, const int start) {
    if (option != 'Y' && option != 'N')
        return false;
    //If wrong option is delivered, return flase and terminate the function.
    int n = graph->getSize();
    if (n == 0)
        return false;
    //If the graph does not exist, finish the algoritm.
    map<int, int>m[n];
        for (int i = 0; i < n; i++) {
            graph->getAdjacentEdgesDirect(i+1, &m[i]);
            if (option == 'N' || option == 'n')
                graph->getAdjacentEdges(i+1, &m[i]);
    }
    //Get the whole edge information in the graph corresponding to the given option.
    if (m[start-1].empty()) return false;
    //If there's no edge starts at the vertex given, terminate the function.
    int distance[n+1];
    int path[n+1];
    bool visit[n];
    int tmp_dist1, tmp_dist2, tmp_node, vertex;
    bool done = false;
    map<int, int>* unioned_vertex_edge;
    map<int, int> :: iterator it_edge;
    ofstream fout;

    fill(distance, distance+n+1, MAX);
    distance[start] = 0;
    fill(path, path + n + 1, -1);
    fill(visit, visit+n, false);
    visit[start-1] = true;
    for (it_edge = m[start-1].begin(); it_edge != m[start-1].end(); it_edge++) {
        path[it_edge->first] = start;
        distance[it_edge->first] = it_edge->second;
        if (it_edge->second < 0)
            return false;
        
        if (distance[0] > it_edge->second)
            distance[0] = it_edge->second;
            tmp_node = it_edge->first;
            path[0] = tmp_node;
    }
    while (!done) {
        visit[path[0]-1] = true;
        unioned_vertex_edge = &m[path[0]-1];
        it_edge = unioned_vertex_edge->begin();
        done = true;
        for (it_edge; it_edge != unioned_vertex_edge->end(); it_edge++) {
            if (visit[it_edge->first - 1])
                continue;
            else {
                if (it_edge->second < 0)
                    return false;
                done = false;
                tmp_dist1 = it_edge->second + distance[0];
                tmp_node = it_edge->first;
                if (tmp_dist1 < distance[tmp_node]) {
                    path[tmp_node] = path[0];
                    distance[tmp_node] = tmp_dist1;
                }
            }
            tmp_dist2 = tmp_dist1;
        }
        for (int i = 1; i <= 10; i++) {
            if (i != path[0]) {
                if (!visit[i-1] && distance[i] < tmp_dist2) {
                    tmp_node = i;
                    tmp_dist2 = distance[i];
                }
            }
        }
        path[0] = tmp_node;
        distance[0] = tmp_dist2;
    }
    //Print the result by using stack.
    stack<int> st;
    fout.open("log.txt", ios::app);
	fout << "======== DIJKSTRA ========" << endl;
    fout << "StartVertex : " << start << endl;
    for (int i = 1; i <= n; i++) {
        if (distance[i] == MAX)
            fout << "[" << i << "] " << "X" << endl;
        else if (distance[i] == 0)
            continue;
        else {
            fout << "[" << i << "] ";
            tmp_node = path[i];
            do {
                st.push(tmp_node);
                tmp_node = path[tmp_node];
            } while (tmp_node != -1);
            do {
                fout << st.top() << " -> ";
                st.pop();
            } while (!st.empty());
            fout << i << " (" << distance[i] << ")" << endl;
        }
    }
    fout << "==========================" << endl << endl;
    fout.close();
    
    return true;
}

bool Bellmanford(Graph* graph, const char option, const int s_vertex, const int e_vertex) {
    if (option != 'Y' && option != 'N')
        return false;
    int n = graph->getSize();
    if (n == 0)
        return false;
    map<int, int>edgeset[n];
    
    //If the graph does not exist, finish the algoritm.
    for (int i = 0; i < n; i++) {
        graph->getAdjacentEdgesDirect(i+1, &edgeset[i]);
        if (option == 'N' || option == 'n')
            graph->getAdjacentEdges(i+1, &edgeset[i]);
    }
    
    if (edgeset[s_vertex-1].empty())
        return false;
    //If there's no edge that connects with the given start vertex and the other one, return false.
    
    int cur_temp_dist, temp_vertex = s_vertex, temp_min;
    vector<int>sub_weights;
    int distance[n];
    int path[n];
    fill(distance, distance+n, MAX);
    fill(path, path+n, -1);
    distance[s_vertex-1] = 0;
    auto it1 = edgeset[s_vertex-1].begin();
    for (it1; it1 != edgeset[s_vertex-1].end(); it1++) {
        distance[it1->first - 1] = it1->second;
        path[it1->first - 1] = s_vertex;
        //Initialize each distance by edge weight.
    }
    for (int k = 2; k < n; k++) {
        for (int i = 0; i < n; i++) {
            it1 = edgeset[i].begin();
            if (i == s_vertex -1)
                continue;
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                it1 = edgeset[j].find(i+1);
                if (it1 != edgeset[j].end()) {
                    cur_temp_dist = distance[j] + it1->second;
                    if (distance[i] > cur_temp_dist) {
                        distance[i] = cur_temp_dist;
                        path[i] = j + 1;
                    }
                    //distance[i] = min(distance[i], distance[j] + edge[j][i])
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        it1 = edgeset[i].begin();
        if (i == s_vertex -1)
            continue;
        for (int j = 0; j < n; j++) {
            if (j == i)
                continue;
            it1 = edgeset[j].find(i+1);
            if (it1 != edgeset[j].end()) {
                cur_temp_dist = distance[j] + it1->second;

                if (distance[i] > cur_temp_dist) 
                    return false;
                //Find negative cycle and it occured, return error.
                
            }
        }
    }
    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "======== BELLMANFORD ========" << endl;
    fout << "Shortest path " << s_vertex << " to " << e_vertex << endl;
    if (distance[e_vertex-1] == MAX)
        fout << "x" << endl;
    //If graph does not reach to given end vertex when starts with given start vertex,
    //print "x" to the log file.
    else {
        stack<int> st;
        st.push(e_vertex);
        temp_vertex = st.top();
        while (path[temp_vertex - 1] != -1) {
            st.push(path[temp_vertex - 1]);
            temp_vertex = path[temp_vertex - 1];
        }
    /*  If the graph reach at end vertex, push all of route vertex into stack
    between start and end vertex by follow up the vertex with path array rrecursively.  */
        for (st; st.top() != e_vertex; st.pop()) 
            fout << st.top() << " -> ";
        fout << e_vertex << endl;
        fout << "cost : " << distance[e_vertex-1] << endl;
    }
    /*  Print the route by popping the vertices from the stack. */
    fout << "=============================" << endl << endl;
	fout.close();
    return true;
}

bool FLOYD(Graph* graph, const char option) {
    if (option != 'Y' && option != 'y' && option != 'N' && option != 'n')
        return false;
    int n = graph->getSize();
    if (n == 0)
        return false;
    map<int, int>edgeset[n];
    
    //If the graph does not exist, finish the algoritm.
    for (int i = 0; i < n; i++) {
        graph->getAdjacentEdgesDirect(i+1, &edgeset[i]);
        if (option == 'N' || option == 'n')
            graph->getAdjacentEdges(i+1, &edgeset[i]);
    }
    int prev_result;
    int result[n][n];
    auto it = edgeset[0].begin();
    for (int i = 0; i < n; i++) {
        fill(result[i], result[i] + n, MAX);
        it = edgeset[i].begin();
        result[i][i] = 0;
        for (it;it != edgeset[i].end();it++)
            result[i][it->first -1] = it->second;
    }
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                result[i][j] = min(result[i][j], result[i][k] + result[k][j]);
                //Get shortest path by floyd's algorithm.
        }
    }
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                prev_result = result[i][j];
                if (prev_result != min(prev_result, result[i][k] + result[k][j])) 
                    return false;
                //Check negative cycle. If it occured, return false.
                
            }
                
        }
    }
    ofstream fout;
    fout.open("log.txt", ios::app);
	fout << "======== FLOYD ========\n";
    fout << "\t\t";
	for(int i = 1; i <= n; i++)
		fout<<"["<< i <<"]"<< "\t\t";
	fout << endl;
	for(int i=0; i < n; i++) {
		fout << "[" << i+1 << "]";
		for(int j = 0; j < n; j++) {
			fout << "\t\t ";
            if (result[i][j] == MAX)
                fout << "x";
			else
                fout << result[i][j];
		}
		fout << endl;
	}
	fout << "======================" << endl << endl;
	fout.close();
    //Print the results.
    return true;
}