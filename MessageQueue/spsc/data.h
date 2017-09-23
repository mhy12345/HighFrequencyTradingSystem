#ifndef __DATA_H
#define __DATA_H
#include <sys/time.h>
#include <atomic>

class Data
{
	public:
		std::atomic_flag flag;
		timeval tv;
};

#endif
