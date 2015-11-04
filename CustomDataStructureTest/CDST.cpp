#include"CDST.h"

Node2x::Node2x() {
	this->IntData = -1;
	this->DataArea = NULL;
	this->LastL = NULL;
	this->NextL = NULL;
}

NodeNx::NodeNx()
{
	this->current = 0;
}

Linker::Linker()
{
	this->Port1 = nullptr;
	this->Id1 = -1;
	this->Port2 = nullptr;
	this->Id2 = -1;
	Weight = 0;
}

Linker::Linker(int w)
{
	this->Port1 = nullptr;
	this->Id1 = -1;
	this->Port2 = nullptr;
	this->Id2 = -1;
	Weight = w;
}

PVOID Linker::GetThat(PVOID pointer)
{
	if (Port1 == pointer) {
		return Port2;
	}
	else {
		return Port1;
	}
}
