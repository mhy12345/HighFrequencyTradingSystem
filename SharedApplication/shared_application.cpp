#include "shared_application.h"

int SharedApplication::appId = 10;
size_t SharedApplication::defaultSize = 1024;
size_t SharedApplication::currentIndex = 0;
SharedApplication *SharedApplication::self = NULL;
SharedApplication::SharedApplication():total(0)
{
	dataSize = defaultSize;
}

void SharedApplication::set_size(size_t s)
{
	defaultSize = s;
}
SharedApplication* SharedApplication::instance()
{
	return self;
}

SharedApplication* SharedApplication::start()
{
	if (self)
		return self;
	bool newApp = false;
	if ((appId = shmget(APPKEY,sizeof(SharedApplication),0666)) == -1)
	{
		if ((appId = shmget(APPKEY,sizeof(SharedApplication)+defaultSize,0666 | IPC_CREAT)) == -1)
		{
			fprintf(stderr,"CANNOT CREATE SHM!\n");
			return NULL;
		}
		printf("Shared Memory Segment not exist, creat one.\n");
		newApp = true;
	}
	printf("Create header block<%d>\n",appId);
	void *shmAddr = shmat(appId,NULL,0);
	if (shmAddr == (void*)-1)
	{
		fprintf(stderr,"Cannot alloc shm\n");
		return NULL;
	}
	if (newApp)
		self = new(shmAddr) SharedApplication();
	else
		self = (SharedApplication*)shmAddr;
	self->total+= 1;
	atexit(SharedApplication::release_instance);
	return self;
}

void SharedApplication::release_instance()
{
	printf("Release instance...\n");
	self->total -= 1;
	if (self->total.load() == 0)
	{
		shmdt(self);
		shmctl(appId,IPC_RMID,NULL);
		printf("Delete header block<%d>\n",appId);
	}else
	{
		shmdt(self);
		printf("Detach header block<%d>\n",appId);
	}
}

void* SharedApplication::malloc(size_t s)
{
	if (currentIndex + s > dataSize) {
		fprintf(stderr,"Data Buffer is full!\n");
	}
	void* ret = (char*)(self+1) + currentIndex;
	currentIndex += s;
	return ret;
}
