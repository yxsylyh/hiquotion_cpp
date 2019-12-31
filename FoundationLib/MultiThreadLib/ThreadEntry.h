#include "ithread.h"

UINT ThreadEntry(LPVOID para)
{
	IThread *thrd=(IThread *)para;
	if(!thrd)
		return 0;
	return thrd->run();
}
