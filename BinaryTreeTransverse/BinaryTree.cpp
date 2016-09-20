// BinaryTree.cpp: �������ľ���ʵ��
#include "stdafx.h"
#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

void BinaryTree::createFromFile(const std::string& filename)
{
	ifstream fin(filename);
	list<Node*> leafs;  // ���浱ǰ����Ҷ�ڵ㣨���Բ����ӽڵ㣩

	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		auto tokens = split(line, ',');
		if (!root)
		{
			root = new Node{ tokens[0], nullptr, nullptr };
			root->lchild = new Node{ tokens[1], nullptr, nullptr };
			root->rchild = new Node{ tokens[2], nullptr, nullptr };
			leafs.emplace_back(root->lchild);
			leafs.emplace_back(root->rchild);
		}
		else
		{	// �ҵ�����ڵ�
			list<Node*>::iterator iter = find_if(leafs.begin(), leafs.end(),
				[&](const Node* pNode) { return pNode->data == tokens[0]; });
			// ������������������
			(*iter)->lchild = new Node{ tokens[1], nullptr, nullptr };
			(*iter)->rchild = new Node{ tokens[2], nullptr, nullptr };
			leafs.emplace_back((*iter)->lchild);
			leafs.emplace_back((*iter)->rchild);
			leafs.erase(iter);
		}
	}

	fin.close();
}