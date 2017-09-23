#include <boost/lockfree/spsc_queue.hpp>  
#include "shared_application.hpp"
#include "data.h"
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

int main()
{
	signal(SIGINT,signalDealer);
	sApp.setSize(sizeof(spsc_queue<timeval,capacity<1024> >));//set the default size to fit the queue
	sApp.start();
	spsc_queue<timeval,capacity<1024> > *sq = new(sApp.malloc(sizeof(spsc_queue<timeval,capacity<1024> >))) spsc_queue<timeval,capacity<1024> >;
	timeval tv;
	while (keepRunning)
	{
		gettimeofday(&tv,NULL);
		sq->push(tv);
		printf("Write %lds%ldus\n",tv.tv_sec,tv.tv_usec);
		usleep(random()%1000000);
	}
}

