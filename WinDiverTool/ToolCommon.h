#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windivert.h>

#include "rb.h"
#include "rb_strcut.h"

enum ThreadStatus
{
	ThreadIdel = 0,
	ThreadRunning,
	ThreadStop,
	ThreadStoped
};

extern HANDLE wdtINHandle; 
extern HANDLE wdtOUTHandle;