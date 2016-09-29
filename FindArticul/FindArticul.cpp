// FindArticul.cpp: 寻找图的割点，并且输出所有强连通分支
#include <string>
#include <map>
#include <list>
#include <stack>
#include <algorithm>
#include <cstdio>

typedef std::string Vertex;  // 用点名的字符串代表节点
typedef std::map<Vertex, std::list<Vertex>> AdjList;  // 邻接表为每个点到邻接点链表的映射
typedef AdjList Graph;  // 使用邻接表为图的表示方法
typedef std::map<Vertex, int> VexIntMap;  // 由节点到int的映射
typedef std::stack<std::pair<Vertex, Vertex>> LineStack;  // 存放边的栈

// 使用全局变量来记录信息（避免被递归所重置）
Graph graph;      // 用来处理的邻接表
VexIntMap DFN;    // 深索数，即进行DFS时访问每个点的次序
VexIntMap DFNL;   // 该点或其子孙节点通过余边能到达的最低深索数
int n0 = 1;       // 访问顺序，初始为0
LineStack lines;  // 记录访问过的边

void initAdjList()
{
	graph = Graph
	{
		{ "A", { "B", "F" } },
		{ "B", { "A", "C" } },
		{ "C", { "B", "D", "E", "F" } },
		{ "D", { "C" } },
		{ "E", { "C" } },
		{ "F", { "A", "C", "G", "I", "J" } },
		{ "G", { "F", "H", "I" } },
		{ "H", { "G" } },
		{ "I", { "F", "G", "J" } },
		{ "J", { "F", "G", "I" } }
	};
}

// v0为当前访问点, prev为访问v0之前访问的节点
void DFSArticul(const Graph& g, const Vertex& v0, const Vertex& prev)
{
	DFN[v0] = DFNL[v0] = n0++;
	for (const Vertex& vadj : g.at(v0))
	{	// 访问v0的每个邻接点vadj
		if (vadj != prev)
		{	// 若vadj未访问则添加新边(v0,vadj)
			if (DFN.count(vadj) == 0)
				lines.emplace(v0, vadj);
			// 若vadj先于v0被访问则添加回边(v0,vadj)
			else if (DFN[vadj] < DFN[v0])
				lines.emplace(v0, vadj);
		}
		if (DFN.count(vadj) == 0)
		{
			DFSArticul(g, vadj, v0);
			// 上式递归完成后已经求得了DFNL[vadj]
			if (DFNL[vadj] >= DFN[v0])
			{
				printf("新的2-连通分量\n");
				while (true)
				{
					auto line = lines.top();
					lines.pop();
					printf("(%s, %s)\n", line.first.c_str(), line.second.c_str());
					if (line.first == v0 && line.second == vadj)
						break;
					if (line.first == vadj && line.second == v0)
						break;
				}
			}
			DFNL[v0] = std::min(DFNL[v0], DFNL[vadj]);
		}
		else
		{	// vadj已访问意味着vadj先于v0被访问
			// 即DFN[vadj]<DFN[v0],(v0, vadj)属于回边
			if (vadj != prev)
				DFNL[v0] = std::min(DFNL[v0], DFN[vadj]);
		}
	}
}

int main()
{
	initAdjList();
	DFSArticul(graph, "A", "");

	return 0;
}