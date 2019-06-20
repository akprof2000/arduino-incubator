// 
// 
// 

#define MENULENGTH 10

#include "menuconfig.h"
#include "NodeManager.h"
#include "ChangeDisplayNode.h"
#include "DeltaLineNode.h"
#include "NodeBuilder.h"
#include "MainNodeBuilder.h"
#include "function.h"
#include "StatusMainInfo.h"
#include "TemperatureStatusInfo.h"
#include "TaskStatusInfo.h"
#include "CurrentOperation.h"
#include "objects.h"
#include "ControlSession.h"
#include "AlertInfoNode.h"

MenuconfigClass Menuconfig;

void MenuconfigClass::clearmenu()
{
	deleteListMenu(MENULENGTH, _listMenu);
	_listMenu = NULL;

}
void MenuconfigClass::clearstatus()
{
	deleteListMenu(5, _listStatus);
	_listStatus = NULL;

}
BaseNodeClass *MenuconfigClass::initstatus()
{
	currentRow.init(currentPeriod, currentTable);
	ControlSession.init();

	_listStatus = createListMenu(5);


	StatusMainInfoClass  *sn = new StatusMainInfoClass();
	_listStatus[0] = sn;
	sn->autoinner = true;

	TemperatureStatusInfoClass *sn1 = new TemperatureStatusInfoClass();
	sn1->autoinner = true;
	sn->setInner(sn1);
	_listStatus[1] = sn1;

	TaskStatusInfoClass *sn2 = new TaskStatusInfoClass();
	sn2->autoinner = true;
	sn1->setInner(sn2);
	_listStatus[2] = sn2;

	CurrentOperationClass *sn3 = new CurrentOperationClass();
	sn3->autoinner = true;
	_listStatus[3] = sn3;
	sn2->setInner(sn3);

	AlertInfoNodeClass *sn4 = new AlertInfoNodeClass();
	sn4->autoinner = true;
	_listStatus[4] = sn4;
	sn3->setInner(sn4);

	sn4->setInner(sn);

	return sn;
}

BaseNodeClass *MenuconfigClass::initmenu()
{
	
	_listMenu = createListMenu(MENULENGTH);

	MainNodeBuilderClass *mm = new MainNodeBuilderClass();
	_listMenu[0] = mm;


	NodeClass *ms = new NodeClass();
	ms->Text[0] = 3;
	ms->Text[1] = 4;
	_listMenu[1] = (ms);


	mm->setNext(ms);
	ms->setPrev(mm);
	shememenu(ms);



	NodeClass *me = new NodeClass();
	me->Text[0] = 253;

	_listMenu[2] = (me);
	me->exit = true;

	ms->setNext(me);
	me->setPrev(ms);
	me->setNext(mm);
	mm->setPrev(me);
	

	return mm;
}



void  MenuconfigClass::shememenu(BaseNodeClass *node)
{
	
	NodeBuilderClass *msc = new NodeBuilderClass();
	msc->type = 0;
	_listMenu[3] = (msc);
	msc->setOwner(node);
	node->setInner(msc);


	NodeBuilderClass *msi = new NodeBuilderClass();	
	_listMenu[4] = (msi);
	msi->type = 1;
	msi->setOwner(node);
	msi->setPrev(msc);
	msc->setNext(msi);

	NodeBuilderClass *msu = new NodeBuilderClass();
	_listMenu[5] = (msu);
	msu->type = 2;
	msu->setOwner(node);
	msu->setPrev(msi);
	msi->setNext(msu);

	NodeBuilderClass *msiu = new NodeBuilderClass();	
	_listMenu[6] = (msiu);
	msiu->type = 3;
	msiu->setOwner(node);
	msiu->setPrev(msu);
	msu->setNext(msiu);


	NodeBuilderClass *msg = new NodeBuilderClass();
	_listMenu[7] = (msg);
	msg->type = 4;
	msg->setOwner(node);
	msg->setPrev(msiu);
	msiu->setNext(msg);


	NodeBuilderClass *msp = new NodeBuilderClass();
	_listMenu[8] = (msp);
	msp->type = 5;
	msp->setOwner(node);
	msp->setPrev(msg);
	msg->setNext(msp);


	NodeClass *mse = new NodeClass();
	_listMenu[9] = (mse);

	mse->Text[0] = 253;
	mse->setOwner(node);
	mse->setInner(node);
	mse->setPrev(msp);
	msc->setPrev(mse);
	mse->setNext(msc);
	msp->setNext(mse);
	
}


