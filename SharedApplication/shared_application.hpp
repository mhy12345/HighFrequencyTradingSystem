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
#include <stdexcept>
#define APPKEY 112341

class MemoryBlock
{
	public:
		size_t dataSize;
		std::atomic_int timestamp;
		std::atomic_int total;
		MemoryBlock():total(0)
		{
		}
};

class SharedApplication
{
	private:
		size_t currentIndex;
		size_t defaultSize;
		int appId;
		MemoryBlock* info;
	public:
		SharedApplication()
		{
			defaultSize = 1024;
			info = NULL;
			currentIndex = 0;
		}
		~SharedApplication(){
			release_instance();
		}
		void* malloc(size_t s){
			if (currentIndex + s > info->dataSize) {
				printf("Data Buffer is full!\n");
				return NULL;
			}
			void* ret = (char*)(info+1) + currentIndex;
			currentIndex += s;
			return ret;
		}
		void set_size(size_t s){
			if (info)
			{
				printf("Cannot set size after started!\n");
				return ;
			}
			this->defaultSize = s;
		}
		void start()
		{
			bool newApp = false;
			if ((appId = shmget(APPKEY,sizeof(MemoryBlock) + defaultSize,0666)) == -1)
			{
				if ((appId = shmget(APPKEY,sizeof(MemoryBlock)+defaultSize,0666 | IPC_CREAT)) == -1)
				{
					printf("CANNOT CREATE SHM!\n");
					return ;
				}
				printf("Shared Memory Segment not exist, creat one.\n");
				newApp = true;
			}
			printf("Create header block<%d>\n",appId);
			info = (MemoryBlock*)shmat(appId,NULL,0);
			if (info == (void*)-1) {
				{
					printf("Cannot alloc shm\n");return;
				}
			}
			if (newApp)
			{
				info = new(info) MemoryBlock();
				info->dataSize = defaultSize;
			}
			info->total += 1;
		}
		void release_instance() {
			if (!info)
				return ;
			printf("Release instance...\n");
			info->total -= 1;
			if (info->total.load() == 0)
			{
				shmdt(info);
				shmctl(appId,IPC_RMID,NULL);
				info = NULL;
				printf("Delete header block<%d>\n",appId);
			}else
			{
				shmdt(info);
				info = NULL;
				printf("Detach header block<%d>\n",appId);
			}
		}
};

#endif
