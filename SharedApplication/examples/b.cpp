#include "shared_application.hpp"
#include <iostream>
using namespace std;

extern SharedApplication sApp;
extern volatile int keepRunning;

void haha(int *data)
{
	cout<<"Enter haha()"<<endl;
	for (int i=0;i<1024;i++) 
		printf("%d ",data[i]);printf("\n");
	for (int i=0;i<1024;i++)
		data[i] = i;
	while(keepRunning)
	{
		sleep(1);
	}
}
