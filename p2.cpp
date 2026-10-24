#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include <map>
#include <sstream>
#include <set>

using namespace std;

class Graph
{
private:
	map<string, vector<string>> adjlist;

public:
	void VGraph(const string& filepath);
	bool isonegraph();
	bool isgspr();

};

//fileG plik grafu


void Graph::VGraph(const string& filepath)
{
	ifstream fileG(filepath);

	if (!fileG.is_open())
	{
		cerr << "file error";
		
		return;

	}

	string gline;
	
	while (getline(fileG, gline))
		{
			stringstream ss(gline);

			string sym;
			string vert;
			bool firstsym = true;

			while (ss >> sym)
			{
				if (firstsym)
				{
					vert = sym;
					firstsym = false;

					if (!vert.empty() && vert.back() == ':')
					{
						vert.pop_back();
						adjlist[vert];
					}

					adjlist[vert];
				}
				else
				{
					if (sym == "->")
					{
						continue;
					}

					adjlist[vert].push_back(sym);
					adjlist[sym];
				}
			}
						
		}


	//check
	for (auto& p : adjlist)
	{
		cout << p.first << " -> ";

		for (auto& s : p.second)
		{
			cout << s << " ";
		}

		cout << endl;
	}
	fileG.close();
}

bool Graph::isonegraph() 
{
	for (auto& p : adjlist)
	{
			for (size_t i = 0; i < p.second.size(); i++)
			{
				for (size_t j = i + 1; j <  p.second.size(); j++)
				{
					if (p.second[i] == p.second[j])
					{
						return false;
					}
				}
			}
	}
	return true;
}


bool Graph::isgspr()
{
	if(!isonegraph())
	{
		return false;
	}

	for (auto x = adjlist.begin(); x != adjlist.end(); ++x)
	{
		auto y = x;
		y++;

		for (; y != adjlist.end(); ++y)
		{
			bool wspolne = false;
			
			for (const auto& nx : x->second)
			{
				for (const auto& ny : y->second)
				{
					if (nx == ny)
					{
						wspolne = true;
						break;
					}
				}
			}

			if (wspolne)
			{
				set<string> nsx(x->second.begin(), x->second.end());
				set<string> nsy(y->second.begin(), y->second.end());

				if (nsx != nsy)
				{
					return false;
				}
			}
		}
		
	}




	return true;
}


int main()
{

	Graph vg;
	vg.VGraph("graph.txt");


	if (vg.isgspr() == 1)
	{
		cout << "Graf jest  sprzezonym";
	}
	else
	{
		cout << "graf nie jest sprzezony";
	}

	return 0;
}