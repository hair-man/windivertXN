#include <windivert.h>

#include "WinDivertThread.h"
#include "rb.h"
#include "rb_strcut.h"
#include "ToolCommon.h"

WinDivertRecvThread::WinDivertRecvThread()
{
	mStatus = ThreadIdel;
	mRecvPkts = 0;
	mRecvBytes = 0;
	mpHandle = NULL;
	mFreeQueue = NULL;
	mBusyQueue = NULL;
	mFreeQueueGet = 0;
	mBusyQueuePut = 0;
}  

WinDivertRecvThread::~WinDivertRecvThread()
{
}

void WinDivertRecvThread::stop()
{
	mStatus = ThreadStop;
}

void WinDivertRecvThread::run()
{
	unsigned char packet[65535];
	UINT packet_len;
	WINDIVERT_ADDRESS addr;

	int ret = 0;
	uint64_t* rb_add_num = NULL;

	prb_msg_t rb_curbuf = NULL;

	mStatus = ThreadRunning;
	mRecvPkts = 0;
	mRecvBytes = 0;
	mFreeQueueGet = 0;
	mBusyQueuePut = 0;

	if (mFreeQueue == NULL || mBusyQueue == NULL)
	{
		return;
	}

	while (1)
	{
		if (mpHandle == NULL || *mpHandle == NULL)
		{
			if (ThreadStop == mStatus)
			{
				emit WinDivertRecvThreadStopSuccess();
				break;
			}
			continue;
		}

		// Read a matching packet.
		if (!WinDivertRecv(*mpHandle, packet, sizeof(packet), &addr, &packet_len))
		{
			if (ThreadStop == mStatus)
			{
				emit WinDivertRecvThreadStopSuccess();
				break;
			}
			continue;
		}
		else
		{

			if (packet_len > BLOCK_SIZE_FOR_RB)
			{
				fprintf(stderr, "packet_len [%u] > [%d], pkts drop!\n", packet_len, BLOCK_SIZE_FOR_RB);
				continue;
			}

			while (rb_readOutValue(mFreeQueue, prb_msg_t, rb_curbuf) == 0)
			{
				QThread::usleep(100);
			}
			mFreeQueueGet ++;

			rb_curbuf->len = 0;

			//既不为NULL，剩余空间也足
			memcpy(&(rb_curbuf->addr), &addr, sizeof(WINDIVERT_ADDRESS));
			memcpy(rb_curbuf->buf, packet, packet_len);

			rb_curbuf->len = packet_len;

			while (rb_writeInValue(mBusyQueue, prb_msg_t, rb_curbuf) == 0)
			{
			}
			mBusyQueuePut ++;

			mRecvBytes += packet_len;
			mRecvPkts++;

			//fprintf(stderr, "Recv Pkts:[%llu] Bytes Total:[%llu] ", mRecvPkts, mRecvBytes);
		}

		if (ThreadStop == mStatus)
		{
			emit WinDivertRecvThreadStopSuccess();
			break;
		}
	}

	WinDivertClose(*mpHandle);
	*mpHandle = NULL;

	mStatus = ThreadStoped;
	mRecvPkts = 0;
	mRecvBytes = 0;
	mFreeQueueGet = 0;
	mBusyQueuePut = 0;
}



WinDivertSendThread::WinDivertSendThread()
{
	mStatus = ThreadIdel;
	mSendPkts = 0;
	mSendBytes = 0;
	mpHandle = NULL;
	mFreeQueue = NULL;
	mBusyQueue = NULL;
	mFreeQueuePut = 0;
	mBusyQueueGet = 0;
}

WinDivertSendThread::~WinDivertSendThread()
{

}  

void WinDivertSendThread::stop()
{
	mStatus = ThreadStop;
}

void WinDivertSendThread::run()
{
	prb_msg_t prb_buff = NULL;
	rb_msg_t  rb_buffer = { 0 };
	WINDIVERT_ADDRESS addr = { 0 };

	mStatus = ThreadRunning;
	mSendPkts = 0;
	mSendBytes = 0;
	mFreeQueuePut = 0;
	mBusyQueueGet = 0;

	while (1)
	{
		if (rb_readOutValue(mBusyQueue, prb_msg_t, prb_buff) != 0)
		{
			mBusyQueueGet ++;

			memcpy(&rb_buffer, prb_buff, sizeof(rb_msg_t));

			//将rb 归还
			while (rb_writeInValue(mFreeQueue, prb_msg_t, prb_buff) == 0)
			{
			}

			memcpy(&addr, &(rb_buffer.addr), sizeof(WINDIVERT_ADDRESS));

			while (*mpHandle == NULL)
			{
			}

			if (!WinDivertSend(*mpHandle, rb_buffer.buf, rb_buffer.len, &addr, NULL))
			{
				fprintf(stderr, "WinDivertSend failed!\n");
			}
			mFreeQueuePut++;

			mSendBytes += rb_buffer.len;
			mSendPkts++;

			//fprintf(stderr, "Send Pkts:[%llu] Bytes Total:[%llu]\n", mSendPkts, mSendBytes);
		}

		if (ThreadStop == mStatus)
		{
			emit WinDivertSendThreadStopSuccess();
			break;
		}
	}

	mStatus = ThreadStoped;
	mSendPkts = 0;
	mSendBytes = 0;
	mFreeQueuePut = 0;
	mBusyQueueGet = 0;
}



int WinDivertOpenThread::InitWinDivert()
{
	char* errstr = NULL;
	UINT errorPos = 0;
	uint64_t queue_len = 8 * 1024;
	uint64_t queue_time = 2000;
	uint64_t queue_size = 8 * 1024 * 1024;

	*mpHandle = WinDivertOpen(mFilter, WINDIVERT_LAYER_NETWORK, 0, 0);
	if (*mpHandle == INVALID_HANDLE_VALUE)
	{
#if 0
		if (GetLastError() == ERROR_INVALID_PARAMETER && !WinDivertHelperCheckFilter("true", WINDIVERT_LAYER_NETWORK, &err_str, NULL))
		{
			fprintf(stderr, "error: invalid filter \"%s\"\n", err_str);
			exit(EXIT_FAILURE);
		}
#endif
		fprintf(stderr, "error: failed to open the WinDivert device (%d)\n", GetLastError());
		return -1;
	}
	fprintf(stderr, "Success Msg: success to open the WinDivert device. Filter:[%s]\n", mFilter);

	if (!WinDivertSetParam(*mpHandle, WINDIVERT_PARAM_QUEUE_LEN, queue_len))
	{
		fprintf(stderr, "error: failed to set packet queue length (%d)\n", GetLastError());
		return -1;
	}
	fprintf(stderr, "Success Msg: success to set queue_len [%llu]\n", queue_len);

	if (!WinDivertSetParam(*mpHandle, WINDIVERT_PARAM_QUEUE_TIME, queue_time))
	{
		fprintf(stderr, "error: failed to set packet queue time (%d)\n", GetLastError());
		return -1;
	}
	fprintf(stderr, "Success Msg: success to set queue_time [%llu]ms\n", queue_time);

	if (!WinDivertSetParam(*mpHandle, WINDIVERT_PARAM_QUEUE_SIZE, queue_size))
	{
		fprintf(stderr, "error: failed to set packet queue size (%d)\n", GetLastError());
		return -1;
	}
	fprintf(stderr, "Success Msg: success to set queue_size [%llu]\n", queue_size);

	return 0;
}

WinDivertOpenThread::WinDivertOpenThread()
{
	memset(mFilter, 0, sizeof(mFilter));
	mpHandle = NULL;
}

WinDivertOpenThread::~WinDivertOpenThread()
{
}

void WinDivertOpenThread::run()
{
	//初始化WinDivert
	if (0 != InitWinDivert())
	{
		emit InitWinDivertFail();
	}
	
	emit InitWinDivertSuccess();
}