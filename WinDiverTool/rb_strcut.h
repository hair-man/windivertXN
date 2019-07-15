#pragma once

#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_FOR_RB 2000
#define QUEUE_NUM_FOR_RB  10000

typedef struct _msg_t
{
	int len;
	WINDIVERT_ADDRESS addr;
	uint8_t buf[BLOCK_SIZE_FOR_RB];
}rb_msg_t,*prb_msg_t;