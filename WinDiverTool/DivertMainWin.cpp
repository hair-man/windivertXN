#include <QMessageBox>
#include <qstring.h>
#include <qboxlayout.h>
#include <QGroupBox>
#include <windivert.h>
#include <stdint.h>

#include "ToolCommon.h"
#include "DivertMainWin.h"

QVBoxLayout* DivertMainWin::CreateNTLVBox()
{
	QVBoxLayout* NTLVBox = new QVBoxLayout();
	mNTLSize.setText(QStringLiteral("流量："));
	QHBoxLayout* NTLSizeLayout = new QHBoxLayout();
	NTLSizeLayout->addWidget(&mNTLSize);
	NTLSizeLayout->addWidget(&mNetToLocalSize);
	NTLVBox->addLayout(NTLSizeLayout);

	mNTLPkts.setText(QStringLiteral("包数："));
	QHBoxLayout* NTLPktsLayout = new QHBoxLayout();
	NTLPktsLayout->addWidget(&mNTLPkts);
	NTLPktsLayout->addWidget(&mNetToLocalPkts);
	NTLVBox->addLayout(NTLPktsLayout);

	mNTLBPS.setText(QStringLiteral("BPS："));
	QHBoxLayout* NTLBPSLayout = new QHBoxLayout();
	NTLBPSLayout->addWidget(&mNTLBPS);
	NTLBPSLayout->addWidget(&mNetToLocalBPS);
	NTLVBox->addLayout(NTLBPSLayout);

	mNTLPPS.setText(QStringLiteral("PPS："));
	QHBoxLayout* NTLPPSLayout = new QHBoxLayout();
	NTLPPSLayout->addWidget(&mNTLPPS);
	NTLPPSLayout->addWidget(&mNetToLocalPPS);
	NTLVBox->addLayout(NTLPPSLayout);

	INFGet.setText(QStringLiteral("FqGet:"));
	QHBoxLayout* INFGetLayout = new QHBoxLayout();
	INFGetLayout->addWidget(&INFGet);
	INFGetLayout->addWidget(&INFreeQueueGet);
	NTLVBox->addLayout(INFGetLayout);

	INFPut.setText(QStringLiteral("FqPut:"));
	QHBoxLayout* INFPutLayout = new QHBoxLayout();
	INFPutLayout->addWidget(&INFPut);
	INFPutLayout->addWidget(&INFreeQueuePut);
	NTLVBox->addLayout(INFPutLayout);

	INBGet.setText(QStringLiteral("BqGet:"));
	QHBoxLayout* INBGetLayout = new QHBoxLayout();
	INBGetLayout->addWidget(&INBGet);
	INBGetLayout->addWidget(&INBusyQueueGet);
	NTLVBox->addLayout(INBGetLayout);

	INBPut.setText(QStringLiteral("BqPut:"));
	QHBoxLayout* INBPutLayout = new QHBoxLayout();
	INBPutLayout->addWidget(&INBPut);
	INBPutLayout->addWidget(&INBusyQueuePut);
	NTLVBox->addLayout(INBPutLayout);

	INCurrent.setText(QStringLiteral("INCurrent:"));
	QHBoxLayout* INCurrentLayout = new QHBoxLayout();
	INCurrentLayout->addWidget(&INCurrent);
	INCurrentLayout->addWidget(&INCurrentQueue);
	NTLVBox->addLayout(INCurrentLayout);

	return NTLVBox;
}

QVBoxLayout* DivertMainWin::CreateLTNVBox()
{
	QVBoxLayout* LTNVBox = new QVBoxLayout();

	mLTNSize.setText(QStringLiteral("流量："));

	QHBoxLayout* LTNSizeLayout = new QHBoxLayout();
	LTNSizeLayout->addWidget(&mLTNSize);
	LTNSizeLayout->addWidget(&mLocalToNetSize);
	LTNVBox->addLayout(LTNSizeLayout);

	mLTNPkts.setText(QStringLiteral("包数："));

	QHBoxLayout* LTNPktsLayout = new QHBoxLayout();
	LTNPktsLayout->addWidget(&mLTNPkts);
	LTNPktsLayout->addWidget(&mLocalToNetPkts);
	LTNVBox->addLayout(LTNPktsLayout);

	mLTNBPS.setText(QStringLiteral("BPS："));

	QHBoxLayout* LTNBPSLayout = new QHBoxLayout();
	LTNBPSLayout->addWidget(&mLTNBPS);
	LTNBPSLayout->addWidget(&mLocalToNetBPS);
	LTNVBox->addLayout(LTNBPSLayout);

	mLTNPPS.setText(QStringLiteral("PPS："));

	QHBoxLayout* LTNPPSLayout = new QHBoxLayout();
	LTNPPSLayout->addWidget(&mLTNPPS);
	LTNPPSLayout->addWidget(&mLocalToNetPPS);
	LTNVBox->addLayout(LTNPPSLayout);

	OUTFGet.setText(QStringLiteral("FqGet:"));
	QHBoxLayout* OUTFGetLayout = new QHBoxLayout();
	OUTFGetLayout->addWidget(&OUTFGet);
	OUTFGetLayout->addWidget(&OUTFreeQueueGet);
	LTNVBox->addLayout(OUTFGetLayout);

	OUTFPut.setText(QStringLiteral("FqPut:"));
	QHBoxLayout* OUTFPutLayout = new QHBoxLayout();
	OUTFPutLayout->addWidget(&OUTFPut);
	OUTFPutLayout->addWidget(&OUTFreeQueuePut);
	LTNVBox->addLayout(OUTFPutLayout);

	OUTBGet.setText(QStringLiteral("BqGet:"));
	QHBoxLayout* OUTBGetLayout = new QHBoxLayout();
	OUTBGetLayout->addWidget(&OUTBGet);
	OUTBGetLayout->addWidget(&OUTBusyQueueGet);
	LTNVBox->addLayout(OUTBGetLayout);

	OUTBPut.setText(QStringLiteral("BqPut:"));
	QHBoxLayout* OUTBPutLayout = new QHBoxLayout();
	OUTBPutLayout->addWidget(&OUTBPut);
	OUTBPutLayout->addWidget(&OUTBusyQueuePut);
	LTNVBox->addLayout(OUTBPutLayout);

	OUTCurrent.setText(QStringLiteral("OUTCurrent:"));
	QHBoxLayout* OUTCurrentLayout = new QHBoxLayout();
	OUTCurrentLayout->addWidget(&OUTCurrent);
	OUTCurrentLayout->addWidget(&OUTCurrentQueue);
	LTNVBox->addLayout(OUTCurrentLayout);

	return LTNVBox;
}

void DivertMainWin::CreateDivertMainWin()
{
	if (objectName().isEmpty())
	{
		setObjectName(QStringLiteral("DivertMainWin"));
		setWindowTitle(QStringLiteral("WinDivertTool"));
		mCenterWin.setFixedSize(800, 300);
	}

	mTitle.setText(QStringLiteral("WinDivert测试工具"));
	QHBoxLayout* TitleLayout = new QHBoxLayout();
	TitleLayout->addStretch(1);
	TitleLayout->addWidget(&mTitle);
	TitleLayout->addStretch(1);

	mStopTool.setText(QStringLiteral("停止"));
	mStartTool.setText(QStringLiteral("开始"));
	QHBoxLayout* ButtonLayout = new QHBoxLayout();
	ButtonLayout->addStretch(1);
	ButtonLayout->addWidget(&mStartTool);
	ButtonLayout->addSpacing(2);
	ButtonLayout->addWidget(&mStopTool);


	mLTNGBox = new QGroupBox(QStringLiteral("本地->互联网"));
	mLTNGBox->setCheckable(true);
	mLTNGBox->setChecked(false);

	mNTLGBox = new QGroupBox(QStringLiteral("互联网->本地"));
	mNTLGBox->setCheckable(true);
	mNTLGBox->setChecked(false);

	mLTNGBox->setLayout(CreateLTNVBox());
	mNTLGBox->setLayout(CreateNTLVBox());

	QHBoxLayout* CenterHbox = new QHBoxLayout();
	CenterHbox->addWidget(mLTNGBox);
	CenterHbox->addWidget(mNTLGBox);

	QVBoxLayout* MasterVbox = new QVBoxLayout();
	MasterVbox->addLayout(TitleLayout);
	MasterVbox->addStretch(1);
	MasterVbox->addLayout(CenterHbox);
	MasterVbox->addStretch(8);
	MasterVbox->addLayout(ButtonLayout);

	mStartTool.setDisabled(false);
	mStopTool.setDisabled(true);

	mCenterWin.setLayout(MasterVbox);
	setCentralWidget(&mCenterWin);
}

void DivertMainWin::ClickedStart()
{
	pFlushDataTimer->start(1000);

	if (mINRecvThread.isRunning() || mINSendThread.isRunning() || mOUTRecvThread.isRunning() || mOUTSendThread.isRunning())
	{
		QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("Error Msg:[Test already Running!]\n测试已经启动"));
		return;
	}

	if (!mLTNGBox->isChecked() && !mNTLGBox->isChecked())
	{
		QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("Error Msg:[No One Checked!]\n选择一个方向进行测试验证"));
		return;
	}

	if (mLTNGBox->isChecked())
	{
		memcpy(mInitOUTDivertThread.mFilter, "outbound", strlen("outbound"));
		mInitOUTDivertThread.mFilter[strlen("outbound")] = '\0';
		mInitOUTDivertThread.start();
	
		fprintf(stderr, "OUT --- mLTNGBox ckeced!\n");
	}
	
	if (mNTLGBox->isChecked())
	{
		memcpy(mInitINDivertThread.mFilter, "inbound", strlen("inbound"));
		mInitINDivertThread.mFilter[strlen("inbound")] = '\0';
		mInitINDivertThread.start();

		fprintf(stderr, "IN ---- mNTLGBox ckeced!\n");
	}
}

void DivertMainWin::ClickedStop()
{
	pFlushDataTimer->stop();

	INRecvPktsOld = 0;
	INRecvSizeOld = 0;
	INSendPktsOld = 0;
	INSendSizeOld = 0;
	OUTRecvPktsOld = 0;
	OUTRecvSizeOld = 0;
	OUTSendPktsOld = 0;
	OUTSendSizeOld = 0;

	//先停止接收
	mINRecvThread.stop();
	mOUTRecvThread.stop();
}

void DivertMainWin::InitWinINDivertSuccessed()
{

	mINSendThread.start();
	mINRecvThread.start();

	mStartTool.setDisabled(true);
	mStopTool.setDisabled(false);
}

void DivertMainWin::InitWinINDivertFailed()
{
	QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("Error Msg:[WinDivert Init fail!]\nWinDivert初始化失败，程序启动失败"));
}


void DivertMainWin::WinDivertINRecvThreadStopSuccessed()
{
	//再停止发送
	mINSendThread.stop();
}

void DivertMainWin::WinDivertINSendThreadStopSuccessed()
{
	mStartTool.setDisabled(false);
	mStopTool.setDisabled(true);

	QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("停止<b>[互联网->本地]</b>成功"));
}

void DivertMainWin::InitWinOUTDivertSuccessed()
{

	mOUTSendThread.start();
	mOUTRecvThread.start();

	mStartTool.setDisabled(true);
	mStopTool.setDisabled(false);
}

void DivertMainWin::InitWinOUTDivertFailed()
{
	QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("Error Msg:[WinDivert Init fail!]\nWinDivert初始化失败，程序启动失败"));
}


void DivertMainWin::WinDivertOUTRecvThreadStopSuccessed()
{
	//再停止发送
	mOUTSendThread.stop();
}

void DivertMainWin::WinDivertOUTSendThreadStopSuccessed()
{
	mStartTool.setDisabled(false);
	mStopTool.setDisabled(true);

	QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("停止<b>[本地->互联网]</b>成功"));
}

void DivertMainWin::WinDivertConnectSlots()
{
	disconnect(&mInitINDivertThread, SIGNAL(InitWinDivertSuccess()), this, SLOT(InitWinINDivertSuccessed()));
	connect(&mInitINDivertThread, SIGNAL(InitWinDivertSuccess()), this, SLOT(InitWinINDivertSuccessed()));
	
	disconnect(&mInitINDivertThread, SIGNAL(InitWinDivertFail()), this, SLOT(InitWinINDivertFailed()));
	connect(&mInitINDivertThread, SIGNAL(InitWinDivertFail()), this, SLOT(InitWinINDivertFailed()));

	disconnect(&mINRecvThread, SIGNAL(WinDivertRecvThreadStopSuccess()), this, SLOT(WinDivertINRecvThreadStopSuccessed()));
	connect(&mINRecvThread, SIGNAL(WinDivertRecvThreadStopSuccess()), this, SLOT(WinDivertINRecvThreadStopSuccessed()));
	
	disconnect(&mINSendThread, SIGNAL(WinDivertSendThreadStopSuccess()), this, SLOT(WinDivertINSendThreadStopSuccessed()));
	connect(&mINSendThread, SIGNAL(WinDivertSendThreadStopSuccess()), this, SLOT(WinDivertINSendThreadStopSuccessed()));
	

	disconnect(&mInitOUTDivertThread, SIGNAL(InitWinDivertSuccess()), this, SLOT(InitWinOUTDivertSuccessed()));
	connect(&mInitOUTDivertThread, SIGNAL(InitWinDivertSuccess()), this, SLOT(InitWinOUTDivertSuccessed()));

	disconnect(&mInitOUTDivertThread, SIGNAL(InitWinDivertFail()), this, SLOT(InitWinOUTDivertFailed()));
	connect(&mInitOUTDivertThread, SIGNAL(InitWinDivertFail()), this, SLOT(InitWinOUTDivertFailed()));

	disconnect(&mOUTRecvThread, SIGNAL(WinDivertRecvThreadStopSuccess()), this, SLOT(WinDivertOUTRecvThreadStopSuccessed()));
	connect(&mOUTRecvThread, SIGNAL(WinDivertRecvThreadStopSuccess()), this, SLOT(WinDivertOUTRecvThreadStopSuccessed()));

	disconnect(&mOUTSendThread, SIGNAL(WinDivertSendThreadStopSuccess()), this, SLOT(WinDivertOUTSendThreadStopSuccessed()));
	connect(&mOUTSendThread, SIGNAL(WinDivertSendThreadStopSuccess()), this, SLOT(WinDivertOUTSendThreadStopSuccessed()));


	disconnect(&mStartTool, SIGNAL(clicked()), this, SLOT(ClickedStart()));
	connect(&mStartTool, SIGNAL(clicked()), this, SLOT(ClickedStart()));
	
	disconnect(&mStopTool, SIGNAL(clicked()), this, SLOT(ClickedStop()));
	connect(&mStopTool, SIGNAL(clicked()), this, SLOT(ClickedStop()));
}

int DivertMainWin::InitRbBuffer()
{
	int i = 0;

	prb_msg_t pINRingBuff = (prb_msg_t)malloc(sizeof(rb_msg_t) * QUEUE_NUM_FOR_RB);
	if (pINRingBuff == NULL)
	{
		fprintf(stderr, "rb malloc failed!\n");
		return -1;
	}
	memset(pINRingBuff, 0, sizeof(rb_msg_t) * QUEUE_NUM_FOR_RB);

	rb_create(QUEUE_NUM_FOR_RB, sizeof(prb_msg_t), mpINBufferFreeQueue);
	rb_create(QUEUE_NUM_FOR_RB, sizeof(prb_msg_t), mpINBufferBusyQueue);

	for (i = 0; i < QUEUE_NUM_FOR_RB; i++)
	{
		while (rb_writeInValue(mpINBufferFreeQueue, prb_msg_t, &(pINRingBuff[i])) == 0)
		{
			Sleep(1);
		}
	}

	fprintf(stderr, "Init IN RbBuffer Succsess! FQueue Node:[%d]\n", QUEUE_NUM_FOR_RB);

	prb_msg_t pOUTRingBuff = (prb_msg_t)malloc(sizeof(rb_msg_t) * QUEUE_NUM_FOR_RB);
	if (pOUTRingBuff == NULL)
	{
		fprintf(stderr, "rb malloc failed!\n");
		return -1;
	}
	memset(pOUTRingBuff, 0, sizeof(rb_msg_t) * QUEUE_NUM_FOR_RB);

	rb_create(QUEUE_NUM_FOR_RB, sizeof(prb_msg_t), mpOUTBufferFreeQueue);
	rb_create(QUEUE_NUM_FOR_RB, sizeof(prb_msg_t), mpOUTBufferBusyQueue);

	for (i = 0; i < QUEUE_NUM_FOR_RB; i++)
	{
		while (rb_writeInValue(mpOUTBufferFreeQueue, prb_msg_t, &(pOUTRingBuff[i])) == 0)
		{
			Sleep(1);
		}
	}

	fprintf(stderr, "Init OUT RbBuffer Succsess! FQueue Node:[%d]\n", QUEUE_NUM_FOR_RB);

	return 0;
}

QString ByteToKMGT(uint64_t size)
{
	uint64_t k = 1024;
	uint64_t m = 1024 * 1024;
	uint64_t g = 1024 * 1024 * 1024;
	uint64_t t = g * 1024;

	double ret = 0.0;
	ret = size / k;
	if (ret > 0)
	{
		ret = size / m;
		if (ret > 0 )
		{
			ret = size / g;
			if (ret > 0)
			{
				ret = size / t;
				if (ret > 0)
				{
					QString s = QString::number(ret, 'f', 2);
					return QString("%1 T").arg(s);
				}
				else
				{
					ret = (size * 1.0) / (g * 1.0);
					QString s = QString::number(ret, 'f', 2);
					return QString("%1 G").arg(s);
				}
			}
			else
			{
				ret = (size * 1.0) / (m * 1.0);
				QString s = QString::number(ret, 'f', 2);
				return QString("%1 M").arg(s);
			}
		}
		else
		{
			ret = (size * 1.0) / (k * 1.0);
			QString s = QString::number(ret, 'f', 2);
			return QString("%1 K").arg(s);
		}
	}

	return QString("%1 B").arg(size);

}

void DivertMainWin::timeouted()
{
	mLocalToNetPkts.setText(QString("Recv:%1 Send:%2").arg(ByteToKMGT(mOUTRecvThread.mRecvPkts), -20).arg(ByteToKMGT(mOUTSendThread.mSendPkts), 20));
	mLocalToNetPPS.setText(QString("Recv:%1 Send:%2").arg(mOUTRecvThread.mRecvPkts - OUTRecvPktsOld, -20).arg(mOUTSendThread.mSendPkts - OUTSendPktsOld, 20));

	mNetToLocalPkts.setText(QString("Recv:%1 Send:%2").arg(ByteToKMGT(mINRecvThread.mRecvPkts), -20).arg(ByteToKMGT(mINSendThread.mSendPkts), 20));
	mNetToLocalPPS.setText(QString("Recv:%1 Send:%2").arg(mINRecvThread.mRecvPkts - INRecvPktsOld, -20).arg(mINSendThread.mSendPkts - INSendPktsOld, 20));

	mLocalToNetSize.setText(QString("Recv:%1 Send:%2").arg(ByteToKMGT(mOUTRecvThread.mRecvBytes), -20).arg(ByteToKMGT(mOUTSendThread.mSendBytes), 20));
	mLocalToNetBPS.setText(QString("Recv:%1 Send:%2").arg(mOUTRecvThread.mRecvBytes - OUTRecvSizeOld, -20).arg(mOUTSendThread.mSendBytes - OUTSendSizeOld, 20));

	mNetToLocalSize.setText(QString("Recv:%1 Send:%2").arg(ByteToKMGT(mINRecvThread.mRecvBytes), -20).arg(ByteToKMGT(mINSendThread.mSendBytes), 20));
	mNetToLocalBPS.setText(QString("Recv:%1 Send:%2").arg(mINRecvThread.mRecvBytes - INRecvSizeOld, -20).arg(mINSendThread.mSendBytes - INSendSizeOld, 20));


	INFreeQueueGet.setText(QString("%1").arg(mINRecvThread.mFreeQueueGet)); //Fq获取了
	INFreeQueuePut.setText(QString("%1").arg(mINSendThread.mFreeQueuePut)); //Fq归还了

	INBusyQueuePut.setText(QString("%1").arg(mINRecvThread.mBusyQueuePut));	//Bq归还了
	INBusyQueueGet.setText(QString("%1").arg(mINSendThread.mBusyQueueGet)); //Bq获取了

	INCurrentQueue.setText(QString("%1").arg(mINRecvThread.mFreeQueueGet - mINSendThread.mBusyQueueGet));


	OUTFreeQueueGet.setText(QString("%1").arg(mOUTRecvThread.mFreeQueueGet)); //Fq获取了
	OUTFreeQueuePut.setText(QString("%1").arg(mOUTSendThread.mFreeQueuePut)); //Fq归还了

	OUTBusyQueuePut.setText(QString("%1").arg(mOUTRecvThread.mBusyQueuePut));	//Bq归还了
	OUTBusyQueueGet.setText(QString("%1").arg(mOUTSendThread.mBusyQueueGet)); //Bq获取了

	OUTCurrentQueue.setText(QString("%1").arg(mOUTRecvThread.mFreeQueueGet - mOUTSendThread.mBusyQueueGet));

	INRecvPktsOld = mINRecvThread.mRecvPkts;
	INRecvSizeOld = mINRecvThread.mRecvBytes;
	INSendPktsOld = mINSendThread.mSendPkts;
	INSendSizeOld = mINSendThread.mSendBytes;
	OUTRecvPktsOld = mOUTRecvThread.mRecvPkts;
	OUTRecvSizeOld = mOUTRecvThread.mRecvBytes;
	OUTSendPktsOld = mOUTSendThread.mSendPkts;
	OUTSendSizeOld = mOUTSendThread.mSendBytes;
}

void DivertMainWin::ConnectRingBufferToThread()
{
	mINRecvThread.mFreeQueue = mpINBufferFreeQueue;
	mINRecvThread.mBusyQueue = mpINBufferBusyQueue;
	mINRecvThread.mpHandle = &wdtINHandle;

	mINSendThread.mFreeQueue = mpINBufferFreeQueue;
	mINSendThread.mBusyQueue = mpINBufferBusyQueue;
	mINSendThread.mpHandle = &wdtINHandle;

	mOUTRecvThread.mFreeQueue = mpOUTBufferFreeQueue;
	mOUTRecvThread.mBusyQueue = mpOUTBufferBusyQueue;
	mOUTRecvThread.mpHandle = &wdtOUTHandle;

	mOUTSendThread.mFreeQueue = mpOUTBufferFreeQueue;
	mOUTSendThread.mBusyQueue = mpOUTBufferBusyQueue;
	mOUTSendThread.mpHandle = &wdtOUTHandle;


	mInitINDivertThread.mpHandle = &wdtINHandle;
	mInitOUTDivertThread.mpHandle = &wdtOUTHandle;


	pFlushDataTimer = new QTimer(this);
	connect(pFlushDataTimer, SIGNAL(timeout()), this, SLOT(timeouted()));
}

DivertMainWin::DivertMainWin()
{
	INRecvPktsOld = 0;
	INRecvSizeOld = 0;
	INSendPktsOld = 0;
	INSendSizeOld = 0;
	OUTRecvPktsOld = 0;
	OUTRecvSizeOld = 0;
	OUTSendPktsOld = 0;
	OUTSendSizeOld = 0;

	//初始化rb
	if (0 != InitRbBuffer())
	{
		QMessageBox::warning(NULL, QStringLiteral("启动警告"), QStringLiteral("Error Msg:[InitRbBuffer!]\n内存不足，程序启动失败"));
	}

	ConnectRingBufferToThread();
	
	CreateDivertMainWin();
	WinDivertConnectSlots();
}

DivertMainWin::~DivertMainWin()
{
}
