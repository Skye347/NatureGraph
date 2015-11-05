#pragma once
#include"CDST.h"
#include<vector>

class LinkListNode :public Node2x {
	//id=2
public:
	LinkListNode* next();
	bool next(LinkListNode*);
	LinkListNode* last();
protected:
private:
};

typedef LinkListNode* pLinkListNode;

class GraphNode:public NodeNx {
//id=6
public:
	GraphNode();
	GraphNode(int);
	bool Add(GraphNode*,int,pLinker);
	int getMode();
	void setMode(int);
	void Roll();
	int ID;
private:
	int inDegree;
	int outDegree;
	int mode;//1 for undirected, 2 for directed, 3 for binary tree
};

typedef GraphNode* pGraphNode;

class LinkerManager {
public:
	LinkerManager();
	pLinker RequestNewLinker(int);
	struct _LinkerManageList {
		struct _LinkerManageList* last;
		pLinker pL;
		struct _LinkerManageList* next;
	};
	struct _LinkerManageList* Head;
	int Count;
	struct _LinkerManageList* current;
};

typedef struct _GraphNodeSet
{
	std::vector<pGraphNode> Set;
	int count;
}GraphNodeSet;

class GraphManager{
public:
	//
	GraphManager();
	GraphManager(int);
	//
	pGraphNode NewGraph(int,PVOID=nullptr);
	//remove
	bool Link(pGraphNode,pGraphNode,int);
	//
	friend bool DotFileGenerate(GraphManager*);
	GraphNodeSet Find(int);
	bool Find(pGraphNode);
protected:
	size_t current;
	std::vector<pGraphNode> GraphNodePool;
	LinkerManager LinkerPool;
	int NodeCount;
	int mode;//1 for undirected, 2 for directed, 3 for binary tree
};

bool DotFileGenerate(GraphManager*);