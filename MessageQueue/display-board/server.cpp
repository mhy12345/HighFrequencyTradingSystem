#include "shared_application.hpp"
#include <iostream>
#include <cstdio>
#include <random>
#include <sys/signal.h>
#include <ctime>
#include <vector>
#include "setting.h"
using namespace std;

#ifdef BOOST_IMP
#include <boost/lockfree/spsc_queue.hpp>  
using namespace boost::lockfree;
typedef spsc_queue<timespec,capacity<BUFFER_SIZE> > queue_t;
#else
#include "broadcaster.hpp"
typedef broadcaster<timespec,BUFFER_SIZE> queue_t;
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


vector<pair<long,long> > rec;
int main()
{
	signal(SIGINT,signalDealer);
	sApp.setSize(sizeof(queue_t));
	sApp.start();
	//queue_t *sq = (queue_t*) sApp.malloc(sizeof(queue_t));
	queue_t *sq = (queue_t*)new(sApp.malloc(sizeof(queue_t))) queue_t();
	timespec tv;
	int total = 0;
	bool flag;
	while (keepRunning)
	{
		clock_gettime(CLOCK_REALTIME, &tv);
		total += flag = sq->push(tv);
		rec.push_back(make_pair(tv.tv_sec,tv.tv_nsec));
#ifdef DEBUG
		if (total%1==0)
			printf("%d:Write %lds %ldus\n",total,tv.tv_sec,tv.tv_nsec);
		usleep(random()%200000);
#else
		if (total%500==0)
			printf("%d:Write %lds %ldus\n",total,tv.tv_sec,tv.tv_nsec);
		usleep(random()%20);
#endif
	}
	FILE *fout = fopen("server-data.txt","w");
	for (auto w : rec)
		fprintf(fout,"%ld %ld\n",w.first,w.second);
	fclose(fout);
}

