#include <boost/lockfree/spsc_queue.hpp>  
#include "shared_application.hpp"
#include "data.h"
#include <iostream>
#include <cstdio>
#include <sys/signal.h>
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

int main()
{
	signal(SIGINT,signalDealer);
	sApp.setSize(sizeof(spsc_queue<timeval,capacity<1024> >));//set the default size to fit the queue
	sApp.start();
	spsc_queue<timeval,capacity<1024> > *sq = new(sApp.malloc(sizeof(spsc_queue<timeval,capacity<1024> >))) spsc_queue<timeval,capacity<1024> >;
	timeval tv1,tv2;
	long long a,b;
	a = b = 0;
	while (keepRunning)
	{
		if (!sq->empty())
			sq->pop(tv1);
		else
			continue;
		gettimeofday(&tv2,NULL);
		int tp = -((tv1.tv_sec - tv2.tv_sec)*1000000 + (tv1.tv_usec - tv2.tv_usec));
		if (tp < 3000)
		{
			a += tp;
			b ++;
			printf("Timeval = %dus, average = %lldus\n",tp,a/b);
		}
	}
}
