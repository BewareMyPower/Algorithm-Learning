#include "AMLGraph.h"
using namespace std;

int main()
{
	AMLGraph g = { "A", "B", "C", "D" };
	g.addEdge("A", "B", 30);
	g.addEdge("A", "C", 6);
	g.addEdge("A", "D", 5);
	g.addEdge("B", "C", 4);
	g.addEdge("B", "D", 10);
	g.addEdge("C", "D", 20);
	size_t vnum = g.vex_size();  // 点数
	cout << "点名 点号" << endl;
	for (size_t i = 0; i < vnum; ++i)
	{
		printf("%-6s%-4d\n", g[i].name.c_str(), i);
	}
	cout << "对应邻接矩阵" << endl;
	for (size_t i = 0; i < vnum; ++i)
	{
		for (size_t j = 0; j < vnum; ++j)
			printf("%-4d", g(i, j));
		printf("\n");
	}

	return 0;
}

AMLGraph::AMLGraph(std::initializer_list<string> il)
{
	data.assign(il.begin(), il.end());
	for (size_t i = 0; i < data.size(); ++i)
		vexStrIdx.emplace(data[i].name, i);
}

void AMLGraph::addVertex(const string& vex_name)
{
	if (this->find(vex_name) == data.end())
		data.emplace_back(vex_name);
}

void AMLGraph::addEdge(const string& vi, const string& vj, int len)
{
	EdgePtr edgeptr = std::make_shared<Edge>(vi, vj, len);
	// 寻找两个顶点的邻接表末端
	auto vex_i = this->find(vi);
	if (vex_i != data.end())
	{
		if (vex_i->firstedge == nullptr)
			vex_i->firstedge = edgeptr;
		else
		{
			auto it = vex_i->firstedge;
			while (it->next(vi) != nullptr)
				it = it->next(vi);
			int npos = it->GetPos(vi);
			if (npos != -1)
				it->vex[npos].firstedge = edgeptr;
		}
		++edgenum;
	}

	auto vex_j = this->find(vj);
	if (vex_j != data.end())
	{
		if (vex_j->firstedge == nullptr)
			vex_j->firstedge = edgeptr;
		else
		{
			auto it = vex_j->firstedge;
			while (it->next(vj) != nullptr)
				it = it->next(vj);
			int npos = it->GetPos(vj);
			if (npos != -1)
				it->vex[npos].firstedge = edgeptr;
		}
		++edgenum;
	}
}

int AMLGraph::getLength(const string& v1, const string& v2) const
{
	if (v1 == v2)
		return 0;
	EdgePtr v1_adj = getAdjMList(v1);
	while (v1_adj != nullptr)
	{
		if (v1_adj->GetPos(v2) != -1)
		{
			return v1_adj->length;
		}
		v1_adj = v1_adj->next(v1);
	}
	return -1;
}