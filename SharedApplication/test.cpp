#include<iostream>
#include<sys/signal.h>
#include<ctime>
#include"shared_application.hpp"
using namespace std;

volatile bool keepRunning = true;
void signalDealer(int id) {
	if (id == SIGINT) {
		keepRunning = 0;
	}
}

int main()
{
	signal(SIGINT,signalDealer);
	SharedApplication::set_size(1024*sizeof(int));
	SharedApplication::start();
	int *data = (int*)smalloc(1024*sizeof(int));
	for (int i=0;i<1024;i++) printf("%d ",data[i]);printf("\n");
	for (int i=0;i<1024;i++)
		data[i] = i;
	while(keepRunning)
	{
		sleep(1);
	}
}
