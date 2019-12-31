#pragma once

#include <c++\foudationlib\datastructlib\pointerlist.h>
#include "threadbase.h"

using namespace std;

class CThreadList : public CPointerList<CThreadBase *>
{
public:
	CThreadList(void);
	~CThreadList(void);

	void startAll();
	void stopAll();
	void removeAll();
	int getAliveCount();  // 创建、运行、暂停和预暂停
	int getStartedCount();  // 运行、暂停、预暂停
	void dontStopThread();

private:
	BOOL m_toStopThread;
};
