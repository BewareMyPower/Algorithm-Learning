#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>

struct Edge;
// 将共享型智能指针作为默认边指针类型，因为在多重表不会出现循环引用
typedef std::shared_ptr<Edge> EdgePtr;
struct Vertex
{	// 顶点类
	std::string name;   // 弧段名
	EdgePtr firstedge;  // 弧段连接的第一条边

	Vertex(const std::string& _name) : name(_name) { }
};

struct Edge
{	// 弧段类
	typedef std::string string;
	int length;   // 弧段长度
	std::array<Vertex, 2> vex;  // 两个顶点

	Edge(const string& vi, const string& vj, int len = 1)
		: vex{ vi, vj }, length(len) { }
	// 取得顶点vex_name对应数组序号，若不存在则返回-1
	int GetPos(const string& vex_name) const
	{
		if (vex_name == vex[0].name)
			return 0;
		if (vex_name == vex[1].name)
			return 1;
		return -1;
	}
	// 取得顶点vex_name的的下一条边，若不存在则返回nullptr
	EdgePtr next(const string& vex_name) const
	{
		if (vex_name == vex[0].name)
			return vex[0].firstedge;
		if (vex_name == vex[1].name)
			return vex[1].firstedge;
		return nullptr;
	}

	~Edge() { std::cout << "析构: " << vex[0].name << " " << vex[1].name << std::endl; }
};

class AMLGraph
{	// 无向图的邻接多重表
public:
	typedef std::string string;
	typedef std::vector<Vertex> Container;
	AMLGraph(std::initializer_list<string> il);

	size_t vex_size() const { return data.size(); }  // 点数
	size_t edge_size() const { return edgenum; }   // 边数

	Container::iterator find(const string& vex_name)
	{
		auto it = vexStrIdx.find(vex_name);
		if (it != vexStrIdx.end())
			return data.begin() + it->second;
		return data.end();
	}
	Container::const_iterator find(const string& vex_name) const
	{
		auto it = vexStrIdx.find(vex_name);
		if (it != vexStrIdx.end())
			return data.begin() + it->second;
		return data.end();
	}
	Container::reference operator[](size_t i)
	{
		return data[i];
	}
	Container::const_reference operator[](size_t i) const
	{
		return data[i];
	}

	void addVertex(const string& vex_name);
	void addEdge(const string& vi, const string& vj, int len = 1);
	// 取得点vex_name的邻接多重表
	EdgePtr getAdjMList(const string& vex_name) const
	{	// 通过点名获取相应邻接多重表
		return this->find(vex_name)->firstedge;
	}
	// 分别通过点名vi,vj和点号i,j取得边长，若不存在该边则返回-1
	int getLength(const string& vi, const string& vj) const;
	int operator()(size_t i, size_t j) const
	{
		return getLength(data[i].name, data[j].name);
	}

private:
	size_t edgenum = 0;
	Container data;   // 邻接多重表的信息
	std::unordered_map<std::string, size_t> vexStrIdx;  // 点名->点号的映射
};
