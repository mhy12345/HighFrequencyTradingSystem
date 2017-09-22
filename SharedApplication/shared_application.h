#ifndef __SHARED_APPLICATION_H
#define __SHARED_APPLICATION_H
#include <atomic>
#include <cstdlib>
#include <sys/shm.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <new>
#define APPKEY 112341


class SharedApplication
{
	public:
		static int appId;
		static size_t defaultSize;
		static size_t currentIndex;
		static SharedApplication* self;
		static SharedApplication* instance();
		static SharedApplication* start();
		static void release_instance();
		static void set_size(size_t s);
	private:
		size_t dataSize;
		std::atomic_int timestamp;
		std::atomic_int total;
		SharedApplication() ;
		~SharedApplication();
	public:
		void* malloc(size_t s);
};
#define smalloc(t) SharedApplication::instance()->malloc(t)

#endif
