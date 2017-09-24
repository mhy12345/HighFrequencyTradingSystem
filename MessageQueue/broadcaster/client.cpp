#include "shared_application.hpp"
#include <iostream>
#include <cstdio>
#include <sys/signal.h>
#include <cmath>
#include <vector>
#include "setting.h"
using namespace std;

#ifdef BOOST_IMP
#include <boost/lockfree/spsc_queue.hpp>  
using namespace boost::lockfree;
typedef spsc_queue<timespec,capacity<BUFFER_SIZE> > queue_t;
#else
#include "broadcaster.hpp"
typedef listener<timespec,BUFFER_SIZE> queue_t;
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
	sApp.setSize(queue_t::inner_size());
	cout<<"SIZE = "<<queue_t::inner_size()<<endl;
	sApp.start();
	timespec tv1,tv2;
	queue_t *sq = new queue_t(sApp.malloc(queue_t::inner_size()));
	long long a,b;
	a = b = 0;
	int total = 0;
	while (keepRunning)
	{
		if (!sq->pop(tv1))continue;
		rec.push_back(make_pair(tv1.tv_sec,tv1.tv_nsec));
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
		//usleep(random()%30);
	}
	FILE *fout = fopen("client-data.txt","w");
	for (auto w : rec)
		fprintf(fout,"%ld %ld\n",w.first,w.second);
	fclose(fout);
}
