//////////////////////////////////////////////////////////////////////////
// Author:	XYZ
// Date:	2016-09-19
// BinaryTree.h: 二叉树的实现
// 包含了读取特定格式的文档来建立二叉树
// 格式为每一行3个字符串被","分开，依次代表根、左子、右子节点
// 以及实现了先序、中序、后序遍历
// 通过中序遍历实现树节点的释放
// 结点类型为字符串（从文档中读取）
// 树的数据结构为BinaryTree
// 测试函数为void use_binary_tree();
// 数据文档为data.txt
//////////////////////////////////////////////////////////////////////////
#ifndef _BINARY_TREE
#define _BINARY_TREE
#include "SimpleSplit.h"
#include <iostream>
#include <vector>
#include <string>

// 数结点，元素类型为字符串
struct TreeNode
{
	TreeNode(const std::string& _data, TreeNode* _left, TreeNode* _right)
		: data(_data), lchild(_left), rchild(_right) { }
	std::string data;
	TreeNode* lchild;
	TreeNode* rchild;
	~TreeNode() { std::cout << "析构" << data << std::endl; }
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

	// 读取指定格式文件，并建立相应的二叉树
	void createFromFile(const std::string& filename);

	// 先序遍历，根->左子->右子
	template <typename Pred>
	void PreOrderTraverse(Pred _Pr)
	{
		__PreOrderTraverse(root, _Pr);
	}

	// 中序遍历，左子->根->右子
	template <typename Pred>
	void InOrderTraverse(Pred _Pr)
	{
		__InOrderTraverse(root, _Pr);
	}

	// 后序遍历，左子->右子->根
	template <typename Pred>
	void PostOrderTraverse(Pred _Pr)
	{
		__PostOrderTraverse(root, _Pr);
	}

private:
	NodePtr root = nullptr;  // 根节点	
};

// 测试用例
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
{	// 先序遍历的具体实现
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
{	// 中序遍历的具体实现
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
{	// 后序遍历的具体实现
	if (curr)
	{
		TreeNode* lchild = curr->lchild;
		TreeNode* rchild = curr->rchild;		__PostOrderTraverse(lchild, _Pr);		__PostOrderTraverse(rchild, _Pr);
		_Pr(curr);
	}
}

#endif