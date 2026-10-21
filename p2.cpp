#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;

class Graph
{
private:
	vector<vector<int>> adjlist;
	bool idc;

public:
	void VGraph(const string& filepath);

};



/*
void Graph::VGraph(const string& filepath)
{
	ifstream fileG("graph.txt");

	if (!fileG.is_open())
	{
		cerr << "file error";

	}
	else
	{
		cout << fileG.rdbuf();
	}
}
*/


int main()
{

	//Graph vg;
	//vg.VGraph("graph.txt");
	// adjacency list

	return 0;
}