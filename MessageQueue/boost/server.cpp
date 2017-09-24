#include <boost/lockfree/spsc_queue.hpp>  
#include "shared_application.hpp"
//#include "cqueue.hpp"
#include <iostream>
#include <cstdio>
#include <random>
#include <sys/signal.h>
#include <ctime>
using namespace std;
using namespace boost::lockfree;
SharedApplication sApp;

volatile int keepRunning = 1;
void signalDealer(int id)
{
	if (id == SIGINT || id == SIGSEGV)
	{
		keepRunning = 0;
	}
}

//typedef spsc_queue<timespec,1024> queue_t;
typedef spsc_queue<timespec,capacity<1024> > queue_t;

int main()
{
	signal(SIGINT,signalDealer);
	sApp.setSize(sizeof(queue_t));//set the default size to fit the queue
	sApp.start();
	queue_t *sq = new(sApp.malloc(sizeof(queue_t))) queue_t;
	timespec tv;
	int total = 0;
	while (keepRunning)
	{
		clock_gettime(CLOCK_REALTIME, &tv);
		total += sq->push(tv);
		if (total%1000==0)
			printf("%d:Write %lds%ldus\n",total,tv.tv_sec,tv.tv_nsec);
		usleep(random()%20);
	}
}

