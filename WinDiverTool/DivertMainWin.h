#pragma once

#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <QGroupBox>
#include <stdint.h>
#include <QTimer>

#include "WinDivertThread.h"


class DivertMainWin : public QMainWindow
{
	Q_OBJECT

public:

	QWidget		mCenterWin;

	QLabel		mTitle;
	QPushButton mStartTool;
	QPushButton mStopTool;

	//提示Label
	QLabel	mLTNPPS;
	QLabel	mNTLPPS;
	QLabel	mLTNPkts;
	QLabel	mNTLPkts;

	//显示数值
	QLabel	mLocalToNetPPS;
	QLabel	mNetToLocalPPS;
	QLabel	mLocalToNetPkts;
	QLabel	mNetToLocalPkts;

	//提示Label
	QLabel	mLTNBPS;
	QLabel	mNTLBPS;
	QLabel  mLTNSize;
	QLabel	mNTLSize;

	//显示数值
	QLabel	mLocalToNetBPS;
	QLabel	mNetToLocalBPS;
	QLabel  mLocalToNetSize;
	QLabel	mNetToLocalSize;

	//提示
	QLabel	INFGet; //Fq获取了
	QLabel	INFPut; //Fq归还了
	QLabel	INBGet; //Bq获取了
	QLabel	INBPut;	//Bq归还了
	QLabel	INCurrent;

	QLabel	OUTFGet;
	QLabel	OUTFPut;
	QLabel	OUTBGet;
	QLabel	OUTBPut;
	QLabel	OUTCurrent;

	//显示数值
	QLabel	INFreeQueueGet; //Fq获取了
	QLabel	INFreeQueuePut; //Fq归还了
	QLabel	INBusyQueueGet; //Bq获取了
	QLabel	INBusyQueuePut;	//Bq归还了
	QLabel	INCurrentQueue;

	QLabel	OUTFreeQueueGet;
	QLabel	OUTFreeQueuePut;
	QLabel	OUTBusyQueueGet;
	QLabel	OUTBusyQueuePut;
	QLabel	OUTCurrentQueue;

	uint64_t INRecvPktsOld;
	uint64_t INRecvSizeOld;
	uint64_t INSendPktsOld;
	uint64_t INSendSizeOld;
	uint64_t OUTRecvPktsOld;
	uint64_t OUTRecvSizeOld;
	uint64_t OUTSendPktsOld;
	uint64_t OUTSendSizeOld;

	//check
	QGroupBox *mLTNGBox;
	QGroupBox *mNTLGBox;

	void* mpINBufferFreeQueue;
	void* mpINBufferBusyQueue;
	WinDivertOpenThread mInitINDivertThread;
	WinDivertRecvThread mINRecvThread;
	WinDivertSendThread mINSendThread;

	void* mpOUTBufferFreeQueue;
	void* mpOUTBufferBusyQueue;
	WinDivertOpenThread mInitOUTDivertThread;
	WinDivertRecvThread mOUTRecvThread;
	WinDivertSendThread mOUTSendThread;

	QTimer* pFlushDataTimer;
	

	DivertMainWin();
	~DivertMainWin();

	int InitRbBuffer();

	void CreateDivertMainWin();
	QVBoxLayout* CreateNTLVBox();
	QVBoxLayout* CreateLTNVBox();

	void WinDivertConnectSlots();
	void ConnectRingBufferToThread();

public slots:
	void ClickedStart();
	void ClickedStop();

	void InitWinINDivertSuccessed();
	void InitWinINDivertFailed();

	void WinDivertINRecvThreadStopSuccessed();
	void WinDivertINSendThreadStopSuccessed();

	void InitWinOUTDivertSuccessed();
	void InitWinOUTDivertFailed();

	void WinDivertOUTRecvThreadStopSuccessed();
	void WinDivertOUTSendThreadStopSuccessed();

	void timeouted();
};
