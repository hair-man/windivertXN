#pragma once

#include <QThread>
#include <windivert.h>

class WinDivertRecvThread : public QThread
{
	Q_OBJECT

public:
	void* mFreeQueue;
	void* mBusyQueue;

	uint64_t	mFreeQueueGet;
	uint64_t    mBusyQueuePut;

	HANDLE* mpHandle;
	int mStatus;

	uint64_t mRecvPkts;
	uint64_t mRecvBytes;

	WinDivertRecvThread();
	~WinDivertRecvThread();

	void stop();
	void run();

signals:
	void WinDivertRecvThreadStopSuccess();
};


class WinDivertSendThread : public QThread
{
	Q_OBJECT

public:
	void* mFreeQueue;
	void* mBusyQueue;

	uint64_t     mFreeQueuePut;		//πÈªπ
	uint64_t     mBusyQueueGet;		//¥¶¿Ì

	HANDLE* mpHandle;
	int mStatus;

	uint64_t mSendPkts;
	uint64_t mSendBytes;

	WinDivertSendThread();
	~WinDivertSendThread();

	void stop();
	void run();

signals:
	void WinDivertSendThreadStopSuccess();
};


class WinDivertOpenThread : public QThread
{
	Q_OBJECT

public:
	HANDLE* mpHandle;
	char mFilter[1024];
	int InitWinDivert();

	WinDivertOpenThread();
	~WinDivertOpenThread();
	
	void run();

signals:
	void InitWinDivertSuccess();
	void InitWinDivertFail();
};