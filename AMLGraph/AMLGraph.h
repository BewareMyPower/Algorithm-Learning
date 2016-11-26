#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>

struct Edge;
// ������������ָ����ΪĬ�ϱ�ָ�����ͣ���Ϊ�ڶ��ر������ѭ������
typedef std::shared_ptr<Edge> EdgePtr;
struct Vertex
{	// ������
	std::string name;   // ������
	EdgePtr firstedge;  // �������ӵĵ�һ����

	Vertex(const std::string& _name) : name(_name) { }
};

struct Edge
{	// ������
	typedef std::string string;
	int length;   // ���γ���
	std::array<Vertex, 2> vex;  // ��������

	Edge(const string& vi, const string& vj, int len = 1)
		: vex{ vi, vj }, length(len) { }
	// ȡ�ö���vex_name��Ӧ������ţ����������򷵻�-1
	int GetPos(const string& vex_name) const
	{
		if (vex_name == vex[0].name)
			return 0;
		if (vex_name == vex[1].name)
			return 1;
		return -1;
	}
	// ȡ�ö���vex_name�ĵ���һ���ߣ����������򷵻�nullptr
	EdgePtr next(const string& vex_name) const
	{
		if (vex_name == vex[0].name)
			return vex[0].firstedge;
		if (vex_name == vex[1].name)
			return vex[1].firstedge;
		return nullptr;
	}

	~Edge() { std::cout << "����: " << vex[0].name << " " << vex[1].name << std::endl; }
};

class AMLGraph
{	// ����ͼ���ڽӶ��ر�
public:
	typedef std::string string;
	typedef std::vector<Vertex> Container;
	AMLGraph(std::initializer_list<string> il);

	size_t vex_size() const { return data.size(); }  // ����
	size_t edge_size() const { return edgenum; }   // ����

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
	// ȡ�õ�vex_name���ڽӶ��ر�
	EdgePtr getAdjMList(const string& vex_name) const
	{	// ͨ��������ȡ��Ӧ�ڽӶ��ر�
		return this->find(vex_name)->firstedge;
	}
	// �ֱ�ͨ������vi,vj�͵��i,jȡ�ñ߳����������ڸñ��򷵻�-1
	int getLength(const string& vi, const string& vj) const;
	int operator()(size_t i, size_t j) const
	{
		return getLength(data[i].name, data[j].name);
	}

private:
	size_t edgenum = 0;
	Container data;   // �ڽӶ��ر����Ϣ
	std::unordered_map<std::string, size_t> vexStrIdx;  // ����->��ŵ�ӳ��
};
