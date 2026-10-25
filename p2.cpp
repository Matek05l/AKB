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
	map<string, vector<string>> pglist;
	map<string, pair<int, int>> graphH;

public:
	void VGraph(const string& filepath);
	bool isonegraph();
	bool isgspr();
	bool isglinear();
	bool convertH();
	void saveH(const string& filepath2);

};



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


bool Graph::isglinear()
{
	if (!isgspr())
	{
		return false;
	}

	pglist.clear();

	for (const auto& p : adjlist)
	{
		pglist[p.first];
	}


	for (const auto& p : adjlist)
	{
		for (const auto& nastepnik : p.second)
		{
			pglist[nastepnik].push_back(p.first);
		}
	}

	for (auto x = adjlist.begin(); x != adjlist.end(); ++x)
	{
		auto y = x;
		++y;

		for (; y != adjlist.end(); ++y)
		{
			bool cmnv = false;

			for (const auto& nx : x->second)
			{
				for (const auto& ny : y->second)
				{
					if (nx == ny)
					{
						cmnv = true;
					}
					if (cmnv)
					{
						break;
					}
				}
			}


			if (!cmnv)
			{
				continue;
			}

			bool cmpv = false;

			for (const auto& px : pglist[x->first])
			{
				for (const auto& py : pglist[y->first])
				{
					if (px == py)
					{
						cmpv = true;
						break;
					}
				}

				if (cmpv)
				{
					break;
				}
			}
			if (cmpv)
			{
				return false;
			}
		}
	}


	return true;
}

bool Graph::convertH()
{

	graphH.clear();


	if (!isgspr())
	{
		return false;
	}

	int nrl = 1;
	for (const auto& vg : adjlist)
	{
		graphH[vg.first] = { nrl, nrl + 1 };
		nrl += 2;
	}

	for (const auto& vg : adjlist)
	{
		for (const auto& nastepnik : vg.second)
		{
			int change = graphH[vg.first].second;
			int keep = graphH[nastepnik].first;

			if (keep == change)
			{
				continue;
			}

			for (auto& luk : graphH)
			{
				if (luk.second.first == change)
				{
					luk.second.first = keep;
				}

				if (luk.second.second == change)
				{
					luk.second.second = keep;
				}
			}
		}
	}
	return true;
}

void Graph::saveH(const string& filepath)
{
	map<int, vector<int>> adjH;

	for (const auto& luk : graphH)
	{
		int pb = luk.second.first;
		int ke = luk.second.second;

		adjH[pb].push_back(ke);
		adjH[ke];
	}

	ofstream fileH(filepath);

	if (!fileH.is_open())
	{
		cerr << "Blad otwarcia pliku wyjsciowego\n";
		return;
	}
	for (const auto& vertex : adjH)
	{
		fileH << vertex.first << " -> ";

		for (int vhl : vertex.second)
		{
			fileH << vhl << " ";
		}

		fileH << "\n";
	}
	fileH.close();
}


int main()
{

	Graph vg;
	vg.VGraph("graph.txt");


	if (vg.isgspr() == 1)
	{
		cout << "Graf jest  sprzezonym";
		if (vg.convertH())
		{
			vg.saveH("graphH.txt");
		}

		if (vg.isglinear() == 1)
		{
			cout << " i liniowy";
		}
		else
		{
			cout << " i nie jest liniowy";
		}
	}
	else
	{
		cout << "graf nie jest sprzezony i liniowy";
	}

	return 0;
}