#include"DSInstance.h"
#include<iostream>

LinkListNode* LinkListNode::next()
{
	pLinker linker = this->NextL;
	if (linker == nullptr) {
		return nullptr;
	}
	else {
		if (linker->Id2 != 2) {
			return nullptr;
		}
		return (pLinkListNode)(linker->Port2);
	}
}

bool LinkListNode::next(LinkListNode * nextnode)
{
	if (this->NextL == nullptr) {
		this->NextL = new Linker;
		if (this->NextL == nullptr) {
			return false;
		}
		this->NextL->Id1 = 2;
		this->NextL->Port1 = this;
		this->NextL->Id2 = 2;
		this->NextL->Port2 = nextnode;
		nextnode->LastL = this->NextL;
	}
	return true;
}

LinkListNode * LinkListNode::last()
{
	if(this->LastL==nullptr)
		return nullptr;
	else {
		if (this->LastL->Id1 != 2) {
			return nullptr;
		}
		return (pLinkListNode)(this->LastL->Port1);
	}
}

GraphNode::GraphNode()
{
	inDegree = 0;
	outDegree = 0;
	mode = 1;
}

GraphNode::GraphNode(int mode)
{
	inDegree = 0;
	outDegree = 0;
	this->mode = mode;
}

bool GraphNode::Add(GraphNode * newGraphNode,int Weight = 0,pLinker LinkerToUse=NULL)
{
	pLinker temp;
	if (newGraphNode == nullptr) {
		return false;
	}
	if (LinkerToUse==NULL) {
		temp = new Linker(Weight);
	}
	else {
		temp = LinkerToUse;
	}
	if (temp == nullptr) {
		return false;
	}
	temp->Port1 = this;
	temp->Id1 = LinkerList.capacity();
	temp->Port2 = newGraphNode;
	temp->Id2 = newGraphNode->LinkerList.capacity();
	if (mode == 1) {
		inDegree++;
		outDegree++;
		newGraphNode->inDegree++;
		newGraphNode->outDegree++;
		temp->Id2 = newGraphNode->LinkerList.capacity();
		newGraphNode->LinkerList.push_back(temp);
		newGraphNode->current = temp->Id2;
	}
	else {
		outDegree++;
		newGraphNode->inDegree++;
		temp->Id2 = -1;
	}
	LinkerList.push_back(temp);
	current = temp->Id1;
	return false;
}

int GraphNode::getMode()
{
	return mode;
}

void GraphNode::setMode(int mode)
{
	this->mode=mode;
}

void GraphNode::Roll()
{
	int temp_current=0;
	for (; temp_current < LinkerList.capacity(); temp_current++) {
		pGraphNode temp = (pGraphNode)LinkerList.at(temp_current)->GetThat(this);
		if (temp != nullptr) {
			std::cout << temp->IntData << " Weight:" << (pGraphNode)LinkerList.at(temp_current)->Weight << std::endl;
		}
		else {
			std::cout << "Unknown" << std::endl;
		}
	}
	current = temp_current;
}

GraphManager::GraphManager()
{
	mode = 1;
	NodeCount = 0;
}

GraphManager::GraphManager(int mode)
{
	this->mode = mode;
	NodeCount = 0;
}

pGraphNode GraphManager::NewGraph(int IntData=-1, PVOID CustomData = NULL)
{
	pGraphNode tempNew = new GraphNode(mode);
	if(tempNew==nullptr)
		return nullptr;
	tempNew->IntData = IntData;
	tempNew->DataArea = CustomData;
	this->GraphNodePool.push_back(tempNew);
	NodeCount++;
	return tempNew;
}

bool GraphManager::Link(pGraphNode n1, pGraphNode n2,int Weight=0)
{
	if (!Find(n1)) {
		return false;
	}
	if (!Find(n2)) {
		return false;
	}
	pLinker linker = LinkerPool.RequestNewLinker(Weight);
	if (linker == nullptr) {
		return false;
	}
	return n1->Add(n2, 0, linker);
}

GraphNodeSet GraphManager::Find(int target)
{
	GraphNodeSet result;
	result.count = 0;
	for (int i = 0; i < GraphNodePool.capacity(); i++) {
		if (GraphNodePool.at(i)->IntData == target) {
			result.Set.push_back(GraphNodePool.at(i));
			result.count++;
		}
	}
	return result;
}

bool GraphManager::Find(pGraphNode target)
{
	for (int i = 0; i < GraphNodePool.capacity(); i++) {
		if (GraphNodePool.at(i)==target) {
			return true;
		}
	}
	return false;
}

LinkerManager::LinkerManager()
{
	Head = nullptr;
	Count = 0;
	current = nullptr;
}

pLinker LinkerManager::RequestNewLinker(int weight)
{
	pLinker temp= new Linker(weight);
	if (Count == 0) {
		temp = new Linker(weight);
		if (temp == nullptr) {
			return nullptr;
		}
		Head = new struct _LinkerManageList;
		Count++;
		Head->next = nullptr;
		Head->pL = temp;
	}
	else {
		struct _LinkerManageList* RollTmp = Head;
		for (;;) {
			if (RollTmp->pL->Weight < weight) {
				if (RollTmp->next == nullptr) {
					struct _LinkerManageList* ListNodeTmp = new struct _LinkerManageList;
					ListNodeTmp->last = RollTmp;
					RollTmp->next = ListNodeTmp;
					ListNodeTmp->next = nullptr;
					ListNodeTmp->pL = temp;
					current = ListNodeTmp;
					break;
				}
				else {
					RollTmp = RollTmp->next;
				}
			}
			else {
				if (RollTmp == Head) {
					struct _LinkerManageList* ListNodeTmp = new struct _LinkerManageList;
					if (ListNodeTmp == nullptr) {
						return nullptr;
					}
					current = ListNodeTmp;
					Head->last = ListNodeTmp;
					Head->last->next = Head;
					Head->last->last = nullptr;
					Head->last->pL = temp;
					Head = Head->last;
				}
				else {
					struct _LinkerManageList* ListNodeTmp = new struct _LinkerManageList;
					if (ListNodeTmp == nullptr) {
						return nullptr;
					}
					else {
						current = ListNodeTmp;
						ListNodeTmp->next = RollTmp;
						ListNodeTmp->last = RollTmp->last;
						RollTmp->last->next = ListNodeTmp;
						RollTmp->last = ListNodeTmp;
						ListNodeTmp->pL = temp;
					}
				}
				break;
			}
		}
	}
	return temp;
}
