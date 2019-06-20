// 
// 
// 

#include "BaseNode.h"


bool BaseNodeClass::allowInner()
{
	return true;
}

bool BaseNodeClass::allowOwner()
{
	return true;
}

bool BaseNodeClass::allowNext()
{
	return true;
}
bool BaseNodeClass::allowPrev()
{
	return true;
}

BaseNodeClass * BaseNodeClass::getPrev()
{
	return _Prev;
}

BaseNodeClass * BaseNodeClass::getNext()
{
	return _Next;
}

BaseNodeClass * BaseNodeClass::getOwner()
{
	return _Owner;
}

BaseNodeClass * BaseNodeClass::getInner()
{
	return _Inner;
}

void BaseNodeClass::setPrev(BaseNodeClass * node)
{
	_Prev = node;
}

void BaseNodeClass::setNext(BaseNodeClass * node)
{
	_Next = node;
}

void BaseNodeClass::setOwner(BaseNodeClass * node)
{
	_Owner = node;
}


void BaseNodeClass::setInner(BaseNodeClass * node)
{
	_Inner = node;
}




