#include"CDST.h"
#include"DSInstance.h"
#include<iostream>

int main() {
	GraphManager pool(3);
	pGraphNode n1 = pool.NewGraph(1);
	pGraphNode n2 = pool.NewGraph(2);
	pGraphNode n3 = pool.NewGraph(3);
	pGraphNode n4 = pool.NewGraph(4);
	pGraphNode n5 = pool.NewGraph(5);
	pGraphNode n6 = pool.NewGraph(5);
	pGraphNode n7 = pool.NewGraph(4);
	pool.Link(n1, n2, 1);
	pool.Link(n1, n3, 2);
	pool.Link(n2, n4, 2);
	pool.Link(n2, n6, 2);
	pool.Link(n4, n7, 2);
	pool.Link(n3, n5, 1);
	pool.Link(n3, n1, 2);
	n1->Roll();
	n2->Roll();
	DotFileGenerate(&pool);
	//system("pause");
	return 1;
}