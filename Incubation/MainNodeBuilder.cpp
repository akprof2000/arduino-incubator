//
//
//

#include "function.h"


#include "objects.h"
#include "MainNodeBuilder.h"
#include "DeltaLineNode.h"
#include "ChangeDisplayNode.h"
#include "NodeChoseStart.h"
#include "node.h"
#include "MinActionPercent.h"
#include "DeltaEgg.h"

const int MENULENGTHM = 15;

BaseNodeClass * MainNodeBuilderClass::getInner()
{
	if (_listMenu != nullptr)
		return _listMenu[0];


	_listMenu = createListMenu(MENULENGTHM);

	auto *ml = new NodeClass();
	_listMenu[0] = (ml);
	ml->Text[0] = 5;
	ml->Text[1] = 6;
	this->setInner(ml);
	ml->setOwner(this);


	auto *mlc = new DeltaLineNodeClass();
	//NodeClass *mlc = new NodeClass();
	mlc->type = 0;
	_listMenu[1] = (mlc);

	ml->setInner(mlc);
	mlc->setOwner(ml);

	auto *mlch = new DeltaLineNodeClass();
	//NodeClass *mlch = new NodeClass();
	mlch->type = 1;
	_listMenu[10] = (mlch);

	mlc->setNext(mlch);
	mlch->setPrev(mlc);
	mlc->setOwner(ml);



	auto *mm = new NodeClass();
	_listMenu[11] = (mm);
	mm->Text[0] = 53;
	mm->Text[1] = 54;
	ml->setNext(mm);
	mm->setPrev(ml);
	mm->setOwner(this);


	auto *mmc = new MinActionPercentClass();
	_listMenu[12] = (mmc);

	mm->setInner(mmc);
	mmc->setOwner(mm);

	auto *mmc_ = new DeltaEggClass();
	_listMenu[13] = (mmc_);

	mmc->setInner(mmc_);
	mmc_->setOwner(mmc);



	auto *mmme = new NodeClass();
	_listMenu[14] = (mmme);

	mmme->Text[0] = 253;

	mmc->setNext(mmc_);
	mmc_->setNext(mmme);
	mmme->setNext(mmc);

	mmme->setPrev(mmc_);
	mmc_->setPrev(mmc);
	mmc->setPrev(mmme);

	mmme->setOwner(mm);




	mmme->setInner(mm);





	auto *mle = new NodeClass();
	_listMenu[2] = (mle);
	mle->Text[0] = 253;

	mlch->setNext(mle);
	mle->setPrev(mlch);
	mle->setOwner(ml);

	mlc->setPrev(mle);
	mle->setNext(mlc);

	mle->setInner(ml);

	auto *md = new NodeClass();
	_listMenu[3] = (md);
	md->Text[0] = 9;
	mm->setNext(md);
	md->setPrev(mm);
	md->setOwner(this);


	auto *mdc = new ChangeDisplayNodeClass();
	_listMenu[4] = (mdc);

	md->setInner(mdc);
	mdc->setOwner(md);


	auto *mde = new NodeClass();
	_listMenu[5] = (mde);

	mde->Text[0] = 253;
	mdc->setNext(mde);
	mde->setOwner(md);
	mde->setPrev(mdc);
	mdc->setPrev(mde);
	mde->setNext(mdc);
	mde->setInner(md);

	auto *mr = new NodeClass();
	_listMenu[6] = (mr);
	mr->Text[0] = 10;
	mr->Text[1] = 11;
	md->setNext(mr);
	mr->setPrev(md);
	mr->setOwner(this);

	auto *mrc = new NodeChoseStartClass();
	_listMenu[7] = (mrc);
	mr->setInner(mrc);
	mrc->setOwner(mr);


	auto *mre = new NodeClass();
	_listMenu[8] = (mre);

	mre->Text[0] = 253;
	mrc->setNext(mre);
	mre->setOwner(mr);
	mre->setPrev(mrc);
	mrc->setPrev(mre);
	mre->setNext(mrc);
	mre->setInner(mr);

	NodeClass *mme = new NodeClass();
	_listMenu[9] = (mme);

	mme->Text[0] = 253;
	mr->setNext(mme);
	mme->setPrev(mr);
	mme->setOwner(this);
	mme->setInner(this);
	mme->setNext(ml);

	ml->setPrev(mme);



	return ml;
}

void MainNodeBuilderClass::deleteMenu()
{
	deleteListMenu(MENULENGTHM, _listMenu);
	_listMenu = nullptr;
}

void MainNodeBuilderClass::show()
{
	baseShowData(2, gettextprj(1), gettextprj(2));

}
