#include "shared_application.hpp"
#include <iostream>
#include <cstdio>
#include <sys/signal.h>
#include <cmath>
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
	timespec tv1,tv2;
	queue_t *sq = new(sApp.malloc(sizeof(queue_t))) queue_t;
	long long a,b;
	a = b = 0;
	int total = 0;
	while (keepRunning)
	{
		if (!sq->pop(tv1))continue;
		total ++;
		clock_gettime(CLOCK_REALTIME,&tv2);
		long tp = -((tv1.tv_sec - tv2.tv_sec)*1000000000 + (tv1.tv_nsec - tv2.tv_nsec));
#ifdef DEBUG
		if (total%1==0)
#else
		if (total%500==0)
#endif
			printf("%d:GET %lds %ldns %ld\n",total,tv1.tv_sec,tv1.tv_nsec,tp);
		a += tp;
		b ++;
		if (b%500==0)
		{
			printf("Timeval = %dns, average = %lldns\n",tp,a/b);
			sq->show();
		}
		//usleep(random()%10);
	}
}
