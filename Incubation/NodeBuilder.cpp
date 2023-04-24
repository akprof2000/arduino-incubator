// 
// 
// 

#include "NodeBuilder.h"
#include "NodeTableBuilder.h"
#include "node.h"
#include "function.h"
#include "objects.h"




const int MENULENGTHD = 5;


BaseNodeClass * NodeBuilderClass::getInner()
{
	if (_listMenu != nullptr)
		return _listMenu[0];

	_listMenu = createListMenu(MENULENGTHD);

	auto *msc1 = new NodeTableBuilderClass();
	_listMenu[0] = msc1;
	msc1->type1 = type;
	msc1->type = 0;

	msc1->setOwner(this);
	this->setInner(msc1);

	
	auto *msc2 = new NodeTableBuilderClass();
	_listMenu[1] = msc2;
	msc2->type1 = type;
	msc2->type = 1;

	msc2->setOwner(this);
	msc1->setNext(msc2);
	msc2->setPrev(msc1);



	auto *msc3 = new NodeTableBuilderClass();
	_listMenu[2] = msc3;
	msc3->type1 = type;
	msc3->type = 2;

	msc3->setOwner(this);
	msc2->setNext(msc3);
	msc3->setPrev(msc2);


	auto *msc4 = new NodeTableBuilderClass();
	_listMenu[3] = msc4;
	msc4->type1 = type;
	msc4->type = 3;

	msc4->setOwner(this);

	msc3->setNext(msc4);
	msc4->setPrev(msc3);


	auto *msce = new NodeClass();
	_listMenu[4] = msce;
	msce->Text[0] = 253;
	msce->setOwner(this);
	msce->setInner(this);

	msc4->setNext(msce);
	msce->setPrev(msc4);
	msce->setNext(msc1);
	msc1->setPrev(msce);
	
	return msc1;
}

void NodeBuilderClass::deleteMenu()
{
	deleteListMenu(MENULENGTHD, _listMenu);

	_listMenu = nullptr;
}

void NodeBuilderClass::show()
{
	baseShowData(1, gettextprj(12 + type), gettextprj(0));
	
}


