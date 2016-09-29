// FindArticul.cpp: Ѱ��ͼ�ĸ�㣬�����������ǿ��ͨ��֧
#include <string>
#include <map>
#include <list>
#include <stack>
#include <algorithm>
#include <cstdio>

typedef std::string Vertex;  // �õ������ַ�������ڵ�
typedef std::map<Vertex, std::list<Vertex>> AdjList;  // �ڽӱ�Ϊÿ���㵽�ڽӵ������ӳ��
typedef AdjList Graph;  // ʹ���ڽӱ�Ϊͼ�ı�ʾ����
typedef std::map<Vertex, int> VexIntMap;  // �ɽڵ㵽int��ӳ��
typedef std::stack<std::pair<Vertex, Vertex>> LineStack;  // ��űߵ�ջ

// ʹ��ȫ�ֱ�������¼��Ϣ�����ⱻ�ݹ������ã�
Graph graph;      // ����������ڽӱ�
VexIntMap DFN;    // ��������������DFSʱ����ÿ����Ĵ���
VexIntMap DFNL;   // �õ��������ڵ�ͨ������ܵ�������������
int n0 = 1;       // ����˳�򣬳�ʼΪ0
LineStack lines;  // ��¼���ʹ��ı�

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

// v0Ϊ��ǰ���ʵ�, prevΪ����v0֮ǰ���ʵĽڵ�
void DFSArticul(const Graph& g, const Vertex& v0, const Vertex& prev)
{
	DFN[v0] = DFNL[v0] = n0++;
	for (const Vertex& vadj : g.at(v0))
	{	// ����v0��ÿ���ڽӵ�vadj
		if (vadj != prev)
		{	// ��vadjδ����������±�(v0,vadj)
			if (DFN.count(vadj) == 0)
				lines.emplace(v0, vadj);
			// ��vadj����v0����������ӻر�(v0,vadj)
			else if (DFN[vadj] < DFN[v0])
				lines.emplace(v0, vadj);
		}
		if (DFN.count(vadj) == 0)
		{
			DFSArticul(g, vadj, v0);
			// ��ʽ�ݹ���ɺ��Ѿ������DFNL[vadj]
			if (DFNL[vadj] >= DFN[v0])
			{
				printf("�µ�2-��ͨ����\n");
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
		{	// vadj�ѷ�����ζ��vadj����v0������
			// ��DFN[vadj]<DFN[v0],(v0, vadj)���ڻر�
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