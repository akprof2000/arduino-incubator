// 
// 
// 

#include "HeatingControl.h"
#include "VentilationControl.h"
#include "consts.h"
#include "objects.h"
#include "ControlSession.h"
#include "StatusInfo.h"

HeatingControlClass HeatingControl;

void HeatingControlClass::wait()
{

	StatusInfo.AddStatus(so_cool, 0);
	StatusInfo.AddStatus(so_heet, 0);

	VentilationControl.SetSpeed(0, fu_temp);
	analogWrite(HEATCONTROL, 0);
}

void HeatingControlClass::funcontrol()
{
	double temp = currentSetTemp;
	double base = currentTemp - temp;
	if (base <= 0)
	{
		VentilationControl.SetSpeed(0, fu_temp);
		StatusInfo.AddStatus(so_cool, 0);		
		return;
	}

	if (base >= (double)alTmpMax)
	{
		StatusInfo.AddStatus(so_cool, 0xFF);
		VentilationControl.SetSpeed(0xFF, fu_temp);
		return;
	}

	if (base > alTmpDel / 10.0)
	{
		double data = 0xFF / (double)sq(alTmpMax);
		double cntrl = sq(base) * data;

		if (minheat * 2.55 > cntrl)
			cntrl = minheat * 2.55;
		StatusInfo.AddStatus(so_cool, cntrl);
		VentilationControl.SetSpeed(cntrl, fu_temp);
	}

}

void HeatingControlClass::refresh()
{
	float temp = currentSetTemp;

	float base = temp - currentTemp;
	funcontrol();

	if (base <= 0)
	{
		StatusInfo.AddStatus(so_heet, 0);
		analogWrite(HEATCONTROL, 0);
		return;
	}

	if (base >= alTmpMax)
	{
		StatusInfo.AddStatus(so_heet, 0xFF);
		analogWrite(HEATCONTROL, 0xFF);
		return;
	}

	

	if (base > alTmpDel / 10.0)
	{
		double data = 0xFF / (double)sq(alTmpMax);
		double cntrl = sq(base) * data;

		if (minheat * 2.55 > cntrl)
			cntrl = minheat * 2.55;

		analogWrite(HEATCONTROL, cntrl);
		StatusInfo.AddStatus(so_heet, cntrl);
	}
}
