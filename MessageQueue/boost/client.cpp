#include <boost/lockfree/spsc_queue.hpp>  
#include "shared_application.hpp"
#include "data.h"
//#include "cqueue.hpp"
#include <iostream>
#include <cstdio>
#include <sys/signal.h>
#include <cmath>
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
	queue_t *sq = (queue_t*) sApp.malloc(sizeof(queue_t));
	timespec tv1,tv2;
	long long a,b;
	a = b = 0;
	int total = 0;
	while (keepRunning)
	{
		if (!sq->pop(tv1))continue;
		total ++;
		clock_gettime(CLOCK_REALTIME,&tv2);
		long tp = -((tv1.tv_sec - tv2.tv_sec)*1000000000 + (tv1.tv_nsec - tv2.tv_nsec));
		if (total%1000==0)
			printf("%d:GET %lds %ldns %ld\n",total,tv1.tv_sec,tv1.tv_nsec,tp);
		if (abs(tp) < 3000)
		{
			a += tp;
			b ++;
			if (b%1000==0)
				printf("Timeval = %dns, average = %lldns\n",tp,a/b);
		}
	}
}
