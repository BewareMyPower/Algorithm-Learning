//////////////////////////////////////////////////////////////////////////
// Author:	XYZ
// Date:	2016-09-19
// BinaryTree.h: ��������ʵ��
// �����˶�ȡ�ض���ʽ���ĵ�������������
// ��ʽΪÿһ��3���ַ�����","�ֿ������δ���������ӡ����ӽڵ�
// �Լ�ʵ�����������򡢺������
// ͨ���������ʵ�����ڵ���ͷ�
// �������Ϊ�ַ��������ĵ��ж�ȡ��
// �������ݽṹΪBinaryTree
// ���Ժ���Ϊvoid use_binary_tree();
// �����ĵ�Ϊdata.txt
//////////////////////////////////////////////////////////////////////////
#ifndef _BINARY_TREE
#define _BINARY_TREE
#include "SimpleSplit.h"
#include <iostream>
#include <vector>
#include <string>

// ����㣬Ԫ������Ϊ�ַ���
struct TreeNode
{
	TreeNode(const std::string& _data, TreeNode* _left, TreeNode* _right)
		: data(_data), lchild(_left), rchild(_right) { }
	std::string data;
	TreeNode* lchild;
	TreeNode* rchild;
	~TreeNode() { std::cout << "����" << data << std::endl; }
};

struct TreeNodePrinter
{
	TreeNodePrinter(std::ostream& os)
		: _os(os) { }
	void operator()(TreeNode* p)
	{
		if (!p->data.empty())
			_os << p->data << " ";
	}
	std::ostream& _os;
};

struct BinaryTree
{
public:
	typedef TreeNode Node;
	typedef Node* NodePtr;

	BinaryTree() = default;
	BinaryTree(const std::string& filename) { createFromFile(filename); }
	~BinaryTree() { PreOrderTraverse([](NodePtr p) { if (p) delete p; }); }

	// ��ȡָ����ʽ�ļ�����������Ӧ�Ķ�����
	void createFromFile(const std::string& filename);

	// �����������->����->����
	template <typename Pred>
	void PreOrderTraverse(Pred _Pr)
	{
		__PreOrderTraverse(root, _Pr);
	}

	// �������������->��->����
	template <typename Pred>
	void InOrderTraverse(Pred _Pr)
	{
		__InOrderTraverse(root, _Pr);
	}

	// �������������->����->��
	template <typename Pred>
	void PostOrderTraverse(Pred _Pr)
	{
		__PostOrderTraverse(root, _Pr);
	}

private:
	NodePtr root = nullptr;  // ���ڵ�	
};

// ��������
inline void use_binary_tree()
{
	BinaryTree tree;
	tree.createFromFile("data.txt");
	tree.PreOrderTraverse(TreeNodePrinter(std::cout));
	printf("\n");
	tree.InOrderTraverse(TreeNodePrinter(std::cout));
	printf("\n");
	tree.PostOrderTraverse(TreeNodePrinter(std::cout));
	printf("\n");
}

template <typename Pred>
void __PreOrderTraverse(TreeNode* curr, Pred _Pr)
{	// ��������ľ���ʵ��
	if (curr)
	{
		TreeNode* lchild = curr->lchild;
		TreeNode* rchild = curr->rchild;
		_Pr(curr);
		__PreOrderTraverse(lchild, _Pr);
		__PreOrderTraverse(rchild, _Pr);
	}
}

template <typename Pred>
void __InOrderTraverse(TreeNode* curr, Pred _Pr)
{	// ��������ľ���ʵ��
	if (curr)
	{
		TreeNode* lchild = curr->lchild;
		TreeNode* rchild = curr->rchild;
		__InOrderTraverse(lchild, _Pr);
		_Pr(curr);		__InOrderTraverse(rchild, _Pr);
	}
}

template <typename Pred>
void __PostOrderTraverse(TreeNode* curr, Pred _Pr)
{	// ��������ľ���ʵ��
	if (curr)
	{
		TreeNode* lchild = curr->lchild;
		TreeNode* rchild = curr->rchild;		__PostOrderTraverse(lchild, _Pr);		__PostOrderTraverse(rchild, _Pr);
		_Pr(curr);
	}
}

#endif