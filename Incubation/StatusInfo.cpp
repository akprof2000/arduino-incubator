// 
// 
// 

#include "StatusInfo.h"
#include "function.h"
#include "objects.h"

StatusInfoClass StatusInfo;

void StatusInfoClass::AddStatus(StatusOper status, double fill)
{
	_oper[(int)status] = round(fill * 100.0 / 255.0);
	if (_oper[so_blow] != 0 && _oper[so_cool] != 0)
	{
		_oper[so_cool] = 0;
	}
}

String StatusInfoClass::Print()
{
	byte len = 0;
	String res = "";
	for (size_t i = 0; i < STATLEN; i++)
	{
		String curr = len > 0 ? "; " : "";
		switch ((StatusOper)i)
		{
		case so_none:
		case so_heet:
		case so_cool:
		case so_wet:
		case so_dry:
			curr += gettextprj(101 + i) + String(_oper[i]) + gettextprj(240);
			break;
		case so_blow:
		case so_rot:
		case so_cent:
		case so_door:
			curr += gettextprj(101 + i);
			break;
		default:
			break;
		}

		if (_oper[i] > 0)
		{
			res += curr;
			len++;
		}
	}

	if (len == 0)
		res = gettextprj(100);

	return res;
}


