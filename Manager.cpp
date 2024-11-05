#include "Manager.h"
#include "GraphMethod.h"
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager()	 {
	graph = nullptr;
	load = 0;	//Anything is not loaded
	fout.open("log.txt", ios::app);
	fout.close();
}

Manager::~Manager() {
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char *command_txt) {
	ifstream fin;
	fin.open(command_txt);
	if(!fin) { //If command File cannot be read, Print error
		fout <<"Command file open error" <<endl;
		return;	//Return
	}
	string command, whole_cmd, cmd_option;
	bool operation;
	int vertex1, vertex2, temp = 0;
	char directionality;
	while (!fin.eof()) {
		getline(fin, whole_cmd);
		//Get a command from the text file.
		temp = whole_cmd.find(" ");
		if (temp == -1) {
			if (whole_cmd.compare("PRINT") == 0) {
				operation = PRINT();
				if (!operation)
					printErrorCode(200);
				//If the operation ends unsuccessfully, write failure message to the file.
			}
			else if (whole_cmd.compare("KRUSKAL") == 0) { //Execute the KRUSKAL command.
				operation = mKRUSKAL();
				if (!operation)
					printErrorCode(500);
				//If the operation ends unsuccessfully, write failure message to the file.
			}
			else if (whole_cmd.compare("EXIT") == 0) {
				//Terminate the program if the command is "EXIT".
				printSuccessCode("EXIT");
				break;
			}
			else
				printErrorCode(1000);
		}
		else {
			command = whole_cmd.substr(0, temp);
			directionality = whole_cmd[temp+1];
			if (command.compare("LOAD") == 0) {
				cmd_option = whole_cmd.substr(command.length() + 1);
				operation = LOAD(cmd_option);
				if (operation == true) {
					printSuccessCode("LOAD");
					load = 1;
				}
				else
					printErrorCode(100);
				continue;
			}
			if (command.length() + 2 < whole_cmd.length()) {
				cmd_option = whole_cmd.substr(command.length() + 1);
				vertex1 = stoi(cmd_option.substr(cmd_option.length()-1)); //Find start vertex.
			}
			if (command.compare("BFS") == 0) {
				if ((vertex1 > graph->getSize())) {
					printErrorCode(300);
				}
				operation = mBFS(directionality, vertex1);
				if (!operation)
					printErrorCode(300);
				//If the function ends unsuccessfully, print failure message to the file.
			}
			else if (command.compare("DFS") == 0) {
				if ((vertex1 > graph->getSize())) {
					printErrorCode(400);
				}
				operation = mDFS(directionality, vertex1);
				if (!operation)
					printErrorCode(400);
				//If the function ends unsuccessfully, print failure message to the file.
			}			
			else if (command.compare("DIJKSTRA") == 0) {
				if ((vertex1 > graph->getSize())) {
					printErrorCode(600);
				}
				//Execute the DIJKSTRA command.
				operation = mDIJKSTRA(directionality, vertex1);
				if (!operation)
					printErrorCode(600);
				//If the function ends unsuccessfully, print failure message to the file.
			}
			else if (command.compare("BELLMANFORD") == 0) { //Execute the BELLMANFORD command.
				vertex1 = stoi(cmd_option.substr(2, 1));
				vertex2 = stoi(cmd_option.substr(4, cmd_option.length() -1));
				if (vertex2 > graph->getSize() || vertex1 > graph->getSize()) {
					printErrorCode(700);
				}
				operation = mBELLMANFORD(directionality, vertex1, vertex2);
				if (!operation)
					printErrorCode(700);
				//If not, print failure message and write it to the file.
			}
			else if (command.compare("FLOYD") == 0) { //Execute the FLOYD command.
				operation = mFLOYD(directionality);
				if (!operation)
					printErrorCode(800);
				//If not, print failure message and write it to the file.
			}
			else
				printErrorCode(1000);	
		}
		command.clear();
		cmd_option.clear();
	}
	fin.close();
	return;
}

bool Manager::LOAD(string filename) {
	
	ifstream graph_file;
	graph_file.open(filename);
	if (!graph_file)
		return false;
	//If the file that contains graph information does not exist, finish the load operation.
	if (graph != nullptr)
		delete graph;
	//If graph is already exist, delete previous graph.
	string str_size, str_vtx, str_weight;
	int weight = 0, size, start_vtx = 0, dest_vtx = 0, temp1, i, j;
	getline (graph_file, str_size);
	if (str_size == "M" || str_size == "m") {
		getline (graph_file, str_size);
		size = stoi(str_size);
		graph = new MatrixGraph(0, size);
		int temp2;
		for (i = 0; i < size; i++) {
			getline(graph_file, str_size);
			start_vtx = i;
			temp1 = 0;
			dest_vtx = 0;
			temp2 = str_size.find(" ");
			str_weight = str_size.substr(0, temp2);
			weight = stoi(str_weight);
			graph->insertEdge(start_vtx, dest_vtx, weight);
			dest_vtx++;
			temp1 = temp2 + 1;
			for (j = 0; j < size - 2; j++) {
				temp2 = str_size.find(" ", temp1);
				str_weight = str_size.substr(temp1, temp2 - temp1);
				weight = stoi(str_weight);
				graph->insertEdge(start_vtx, dest_vtx, weight);
				temp1 = temp2 + 1;
				dest_vtx++;
			}
			str_weight = str_size.substr(temp2);
			weight = stoi(str_weight);
			graph->insertEdge(start_vtx, dest_vtx, weight);
		}
		graph_file.close();
		return true;
	}
	else if (str_size == "L" || str_size == "l") {
		getline(graph_file, str_size);
		size = stoi(str_size);
		graph = new ListGraph(1, size);
		while (!graph_file.eof()) {
			getline (graph_file, str_vtx);
			if (str_vtx.length() >= 3) {
				temp1 = str_vtx.find(" ");
				str_weight = str_vtx.substr(temp1 + 1);
				str_vtx.erase(temp1, str_vtx.length() - 1);
				dest_vtx = stoi(str_vtx);
				weight = stoi(str_weight);
			}
			else {
				if (str_vtx[0] == '\n')
					break;
				start_vtx = stoi(str_vtx);
				weight = 0;
			}
			if (weight != 0)
				graph->insertEdge(start_vtx, dest_vtx, weight);
		}
		graph_file.close();
		return true;
	}
	else return false;
}

bool Manager::PRINT() {
	result = graph->printGraph();
	return result;
}

bool Manager::mBFS(const char option, const int vertex) {
	result = BFS(graph, option, vertex);
	return result;
}

bool Manager::mDFS(const char option, const int vertex) {
	result = DFS(graph, option, vertex);
	return result;
}
bool Manager::mDIJKSTRA(const char option, const int vertex) {
	result = Dijkstra(graph, option, vertex);
	return result;
}

bool Manager::mKRUSKAL() {
	result = Kruskal(graph);
	return result;
}

bool Manager::mBELLMANFORD(const char option, int s_vertex, int e_vertex) {
	result = Bellmanford(graph, option, s_vertex, e_vertex);
	return result;
}

bool Manager::mFLOYD(const char option) {
	result = FLOYD(graph, option);
	return result;
}

void Manager::printErrorCode(const int n) {
	fout.open("log.txt", ios::app);
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl << endl;
	fout.close();
	return;
}

void Manager::printSuccessCode(const string cmd) {
	fout.open("log.txt", ios::app);
	fout << "========" << cmd << "========" << endl;
	fout << "Success" << endl;
	fout << "======================" << endl << endl;
	fout.close();
	return;
}
