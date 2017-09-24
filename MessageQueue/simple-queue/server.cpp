#include "shared_application.hpp"
#include <iostream>
#include <cstdio>
#include <random>
#include <sys/signal.h>
#include <ctime>
#include "setting.h"
using namespace std;

#ifdef BOOST_IMP
#include <boost/lockfree/spsc_queue.hpp>  
using namespace boost::lockfree;
typedef spsc_queue<timespec,capacity<BUFFER_SIZE> > queue_t;
#else
#include "cqueue.hpp"
typedef spsc_queue<timespec,BUFFER_SIZE> queue_t;
#endif

SharedApplication sApp;
volatile int keepRunning = 1;
void signalDealer(int id)
{
	if (id == SIGINT || id == SIGSEGV)
	{
		keepRunning = 0;
	}
}


int main()
{
	signal(SIGINT,signalDealer);
	sApp.setSize(sizeof(queue_t));//set the default size to fit the queue
	sApp.start();
	queue_t *sq = (queue_t*) sApp.malloc(sizeof(queue_t));
	timespec tv;
	int total = 0;
	bool flag;
	while (keepRunning)
	{
		clock_gettime(CLOCK_REALTIME,&tv);
		total += flag = sq->push(tv);
#ifdef DEBUG
		if (total%1==0)
			printf("%d:Write %lds %ldus\n",total,tv.tv_sec,tv.tv_nsec);
		usleep(random()%200000);
#else
		if (total%1000==0)
			printf("%d:Write %lds %ldus\n",total,tv.tv_sec,tv.tv_nsec);
		usleep(random()%20);
#endif
	}
}

