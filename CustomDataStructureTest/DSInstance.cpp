#include"DSInstance.h"
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

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
	if (this->LastL == nullptr)
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
	ID = (int)this;
}

GraphNode::GraphNode(int mode)
{
	inDegree = 0;
	outDegree = 0;
	this->mode = mode;
	if (mode == 3) {//binary tree mode
		LinkerList.push_back(nullptr);
		LinkerList.push_back(nullptr);
		LinkerList.push_back(nullptr);
	}
	ID = (int)this;
}

bool GraphNode::Add(GraphNode * newGraphNode, int Weight = 0, pLinker LinkerToUse = NULL)
{
	pLinker temp;
	if (newGraphNode == nullptr) {
		return false;
	}
	if (LinkerToUse == NULL) {
		temp = new Linker(Weight);
	}
	else {
		temp = LinkerToUse;
	}
	if (temp == nullptr) {
		return false;
	}
	if (mode == 3) {
		if ((newGraphNode->LinkerList[0] != nullptr) || (newGraphNode->LinkerList[1] != nullptr)) {
			return false;
		}
	}
	temp->Port1 = this;
	temp->Id1 = LinkerList.size();
	temp->Port2 = newGraphNode;
	temp->Id2 = newGraphNode->LinkerList.size();
	if (mode == 1) {
		inDegree++;
		outDegree++;
		newGraphNode->inDegree++;
		newGraphNode->outDegree++;
		//temp->Id2 = newGraphNode->LinkerList.capacity();
		newGraphNode->LinkerList.push_back(temp);
		newGraphNode->current = temp->Id2;
		LinkerList.push_back(temp);
	}
	else if (mode == 2) {
		outDegree++;
		newGraphNode->inDegree++;
		//temp->Id2 = -1;
		LinkerList.push_back(temp);
	}
	else if (mode == 3) {
		if (Weight == 0 || newGraphNode->mode != 3) {
			return false;
			//error
		}
		else if (Weight == 1) {//left
			temp->Port1 = this;
			temp->Id1 = 30;
			temp->Port2 = newGraphNode;
			temp->Id2 = 31;
			this->LinkerList[0] = temp;
			newGraphNode->LinkerList[2] = temp;
		}
		else if (Weight == 2) {//right
			temp->Port1 = this;
			temp->Id1 = 30;
			temp->Port2 = newGraphNode;
			temp->Id2 = 32;
			this->LinkerList[1] = temp;
			newGraphNode->LinkerList[2] = temp;
		}
		else {
			return false;
		}
	}
	//LinkerList.push_back(temp);
	current = temp->Id1;
	return true;
}

int GraphNode::getMode()
{
	return mode;
}

void GraphNode::setMode(int mode)
{
	this->mode = mode;
}

void GraphNode::Roll()
{
	if (mode == 3) {
		if (LinkerList.at(2) == nullptr) {
			std::cout << "I am the root with data" << IntData << std::endl;
		}
		else {
			std::cout << "My root is" << pGraphNode(LinkerList.at(2)->Port1)->IntData << std::endl;
		}
		if (LinkerList.at(0) == nullptr) {
			std::cout << "No left" << std::endl;
		}
		else {
			std::cout << "My left is" << pGraphNode(LinkerList.at(0)->Port2)->IntData << std::endl;
		}
		if (LinkerList.at(1) == nullptr) {
			std::cout << "No right" << std::endl;
		}
		else {
			std::cout << "My right is" << pGraphNode(LinkerList.at(1)->Port2)->IntData << std::endl;
		}
		return;
	}

	int temp_current = 0;
	for (; temp_current < LinkerList.size(); temp_current++) {
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

void GraphNode::RemoveLinker(pLinker target)
{
	std::vector<pLinker>::iterator Iterator;
	for (Iterator = LinkerList.begin(); Iterator != LinkerList.end(); Iterator++) {
		if (target == *Iterator) {
			if (mode == 3) {
				*Iterator = nullptr;
				break;
			}
			LinkerList.erase(Iterator);
			break;
		}
	}
}

GraphManager::GraphManager()
{
	mode = 1;
	NodeCount = 0;
	current = -1;
}

GraphManager::GraphManager(int mode)
{
	this->mode = mode;
	NodeCount = 0;
	current = -1;
}

pGraphNode GraphManager::NewGraph(int IntData = -1, PVOID CustomData)
{
	pGraphNode tempNew = new GraphNode(mode);
	if (tempNew == nullptr)
		return nullptr;
	tempNew->IntData = IntData;
	tempNew->DataArea = CustomData;
	this->GraphNodePool.push_back(tempNew);
	NodeCount++;
	current = NodeCount - 1;
	tempNew->ID = current;
	return tempNew;
}

bool GraphManager::Link(pGraphNode n1, pGraphNode n2, int Weight = 0)//in tree mode,Weight=1 for left and Weight=2 for right.0 is not allowed
{
	if (!Find(n1)) {
		return false;
	}
	if (!Find(n2)) {
		return false;
	}
	if (mode == 3) {
		if ((n2->LinkerList[0] != nullptr) || (n2->LinkerList[1] != nullptr)) {
			return false;
		}
	}
	pLinker linker = LinkerPool.RequestNewLinker(Weight);
	if (linker == nullptr) {
		return false;
	}
	return n1->Add(n2, Weight, linker);
}

GraphNodeSet GraphManager::Find(int target)
{
	GraphNodeSet result;
	result.count = 0;
	for (int i = 0; i < NodeCount; i++) {
		if (GraphNodePool.at(i)->IntData == target) {
			result.Set.push_back(GraphNodePool.at(i));
			result.count++;
		}
	}
	return result;
}

bool GraphManager::Find(pGraphNode target)
{
	for (int i = 0; i < NodeCount; i++) {
		if (GraphNodePool.at(i) == target) {
			return true;
		}
	}
	return false;
}

void GraphManager::Unlink(pGraphNode tar1, pGraphNode tar2)
{
	for (int i = 0; i < tar1->LinkerList.size(); i++) {
		if (tar1->LinkerList.at(i)->GetThat(tar1) == tar2) {
			pLinker temp = tar1->LinkerList.at(i);
			tar1->RemoveLinker(temp);
			tar2->RemoveLinker(temp);
			LinkerPool.RemoveLinker(temp);
			break;
		}
	}
}

void Unlink(pGraphNode tar1, pGraphNode tar2)
{
	for (int i = 0; i < tar1->LinkerList.size(); i++) {
		if (tar1->LinkerList.at(i)->GetThat(tar1) == tar2) {
			pLinker temp = tar1->LinkerList.at(i);
			tar1->RemoveLinker(temp);
			tar2->RemoveLinker(temp);
			delete temp;
			break;
		}
	}
}

LinkerManager::LinkerManager()
{
	Head = nullptr;
	Count = 0;
	current = nullptr;
}

void LinkerManager::RemoveLinker(pLinker Target)
{
	struct _LinkerManageList* temp = Head;
	for (;;) {
		if (temp->pL == Target) {
			if (temp->last == nullptr) {
				Head = temp->next;
				Head->last = nullptr;
				delete temp;
			}
			else if (temp->next == nullptr) {
				temp->last->next = nullptr;
				delete temp;
			}
			else {
				struct _LinkerManageList* pre = temp->last;
				pre->next = temp->next;
				temp->next->last = pre;
				delete temp;
			}
			Count++;
			break;
		}
		if (temp->next != nullptr) {
			temp = temp->next;
		}
		else {
			break;
		}
	}
}

pLinker LinkerManager::RequestNewLinker(int weight)
{
	pLinker temp = new Linker(weight);
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
					Count++;
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
					Count++;
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
						Count++;
					}
				}
				break;
			}
		}
	}
	return temp;
}

bool DotFileGenerate(GraphManager * Graph)
{
	std::ofstream targetFile;
	targetFile.open("generate2.dot");
	std::string endline = ";\n";
	std::string buffer = "";
	std::string num;
	std::string num2;
	std::stringstream IDStr;
	if (Graph->mode == 2) {
		std::string head = "digraph GenerateNo0 {\n";
		buffer += head;
		std::string edge = "->";
		int count = Graph->NodeCount;
		for (int i = 0; i < count; i++) {
			pGraphNode temp = Graph->GraphNodePool.at(i);
			num = temp->IntData + 48;
			int edgeCount = temp->LinkerList.size();
			for (int j = 0; j < edgeCount; j++) {
				pGraphNode bingo = (pGraphNode)(temp->LinkerList.at(j)->GetThat(temp));
				if (bingo != nullptr) {
					buffer += "    ";
					num2 = bingo->IntData + 48;
					std::stringstream IDStr;
					IDStr << temp->ID;
					buffer += "ID";
					buffer += IDStr.str() += "_";
					IDStr.str("");
					buffer += num;
					buffer += edge;
					IDStr << bingo->ID;
					buffer += "ID";
					buffer += IDStr.str() += "_";
					IDStr.str("");
					buffer += num2;
					buffer += endline;
				}
			}
		}
		buffer += "}\n\n";
		targetFile << buffer;
	}
	else if (Graph->mode == 1) {
		std::string buffer = "";
		buffer += "graph GenerateNo0 {\n";
		std::string edge = "--";
		struct LinkerManager::_LinkerManageList* RollTmp = Graph->LinkerPool.Head;
		if (RollTmp == nullptr) {
			targetFile << "Empty Graph";
			targetFile.close();
			return false;
		}
		while (1) {
			if (RollTmp == nullptr) {
				break;
			}
			if (RollTmp->pL == nullptr) {
				RollTmp = RollTmp->next;
				continue;
			}
			buffer += "    ";
			num = ((pGraphNode)RollTmp->pL->Port1)->IntData + 48;
			num2 = ((pGraphNode)RollTmp->pL->Port2)->IntData + 48;
			IDStr << ((pGraphNode)RollTmp->pL->Port1)->ID;
			buffer += "ID";
			buffer += IDStr.str() += "_";
			buffer += num;
			buffer += edge;
			IDStr.str("");
			IDStr << ((pGraphNode)RollTmp->pL->Port2)->ID;
			buffer += "ID";
			buffer += IDStr.str() += "_";
			IDStr.str("");
			buffer += num2;
			buffer += endline;
			RollTmp = RollTmp->next;
		}
		buffer += "}\n\n";
		targetFile << buffer;
	}
	else if (Graph->mode == 3) {
		std::string buffer = "";
		buffer += "digraph GenerateNo0 {\n";
		std::string edge = "->";
		struct LinkerManager::_LinkerManageList* RollTmp = Graph->LinkerPool.Head;
		if (RollTmp == nullptr) {
			targetFile << "Empty Graph";
			targetFile.close();
			return false;
		}
		while (1) {
			if (RollTmp == nullptr) {
				break;
			}
			if (RollTmp->pL == nullptr) {
				RollTmp = RollTmp->next;
				continue;
			}
			buffer += "    ";
			num = ((pGraphNode)RollTmp->pL->Port1)->IntData + 48;
			num2 = ((pGraphNode)RollTmp->pL->Port2)->IntData + 48;
			IDStr << ((pGraphNode)RollTmp->pL->Port1)->ID;
			buffer += "ID";
			buffer += IDStr.str() += "_";
			IDStr.str("");
			buffer += num;
			buffer += edge;
			IDStr << ((pGraphNode)RollTmp->pL->Port2)->ID;
			buffer += "ID";
			buffer += IDStr.str() += "_";
			IDStr.str("");
			buffer += num2;
			buffer += endline;
			RollTmp = RollTmp->next;
		}
		buffer += "}\n\n";
		targetFile << buffer;
	}
	else {
		buffer += "[ERROR]Mode not correct\n";
		targetFile << buffer;
		targetFile.close();
		return false;
	}
	//
	targetFile.close();
	return true;
}