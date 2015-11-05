#pragma once
typedef void* PVOID;
#include<vector>

typedef class Linker {
//ID=0
public:
	Linker();
	Linker(int);
	PVOID Port1;
	size_t Id1;
	PVOID Port2;
	size_t Id2;
	int Weight;
	PVOID GetThat(PVOID);
}*pLinker;

typedef class Node2x {
//ID=1
public:
	Node2x();
	int IntData;
	pLinker LastL;
	pLinker NextL;
protected:
	PVOID DataArea;
}*pNode2x;

typedef class NodeNx {
//ID=5
public:
	NodeNx();
	int IntData;
	std::vector<pLinker> LinkerList;
	int current;
	PVOID DataArea;
}*pNode10x;