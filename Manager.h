#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{	
private:
	Graph* graph;	
	ofstream fout;
	int load;

public:
	Manager();	
	~Manager();	
	bool result;

	void run(const char * command_txt);
	
	bool LOAD(const string filename);
	bool PRINT();	
	bool mBFS(const char option, const int start_vertex);	
	bool mDFS(const char option, const int start_vertex);	
	bool mDIJKSTRA(const char option, const int vertex);	
	bool mKRUSKAL();	
	bool mBELLMANFORD(const char option, const int s_vertex, const int e_vertex);	
	bool mFLOYD(const char option);
	void printSuccessCode(const string cmd);
	void printErrorCode(const int n); 
};

#endif