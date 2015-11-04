#include"CDST.h"
#include"DSInstance.h"
#include<iostream>

int main() {
	GraphManager pool(2);
	pGraphNode n1 = pool.NewGraph(1, NULL);
	pGraphNode n2 = pool.NewGraph(2, NULL);
	pGraphNode n3 = pool.NewGraph(3, NULL);
	pGraphNode n4 = pool.NewGraph(4, NULL);
	pGraphNode n5 = pool.NewGraph(5, NULL);
	pool.Link(n1, n2, 1);
	pool.Link(n1, n3, 8);
	pool.Link(n1, n4, 3);
	pool.Link(n3, n4, 4);
	pool.Link(n5, n3, 2);
	pool.Link(n5, n1, 6);
	n5->Roll();
	//system("pause");
	return 1;
}