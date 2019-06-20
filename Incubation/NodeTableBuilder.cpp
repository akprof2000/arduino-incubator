// 
// 
// 



#include "NodeTableBuilder.h"
#include "function.h"
#include "objects.h"
#include "RowDayCount.h"
#include "RowTHVal.h"
#include "RowRotateVent.h"
#include "RowCooling.h"

#define MENULENGTHT 5


BaseNodeClass * NodeTableBuilderClass::getInner()
{

	if (_listMenu != NULL)
		return _listMenu[0];

	_listMenu = createListMenu(MENULENGTHT);
	


	RowDayCountClass *mp = new RowDayCountClass();
	mp->type = type;
	mp->type1 = type1;

	_listMenu[0] = (mp);

	//mp->Text[0] = 18;
	//mp->Text[1] = 19;
	mp->setOwner(this);
	this->setInner(mp);

	RowTHValClass *mt = new RowTHValClass();
	mt->type = type;
	mt->type1 = type1;
	_listMenu[1] = (mt);

	mt->setOwner(this);
	mp->setNext(mt);
	mt->setPrev(mp);

	RowRotateVentClass *mr = new RowRotateVentClass();
	mr->type = type;
	mr->type1 = type1;

	_listMenu[2] = (mr);
	mr->setOwner(this);
	mt->setNext(mr);
	mr->setPrev(mt);

	RowCoolingClass *mf = new RowCoolingClass();
	mf->type = type;
	mf->type1 = type1;

	_listMenu[3] = (mf);
	mf->setOwner(this);
	mr->setNext(mf);
	mf->setPrev(mr);


	NodeClass *me = new NodeClass();
	_listMenu[4] = (me);

	me->Text[0] = 253;

	me->setOwner(this);
	me->setInner(this);
	mf->setNext(me);
	me->setNext(mp);
	me->setPrev(mf);
	mp->setPrev(me);

	return mp;
}

void NodeTableBuilderClass::show()
{

	deleteListMenu(MENULENGTHT, _listMenu);
	_listMenu = NULL;


	baseShowData(2, gettextprj(12 + type1), gettextprj(32 + type));

}
