#include "shared_application.hpp"
#include <sys/signal.h>

SharedApplication sApp;
void haha(int*);

volatile bool keepRunning = true;
void signalDealer(int id) {
	if (id == SIGINT) {
		keepRunning = 0;
	}
}

int main()
{
	sApp.set_size(1024*sizeof(int));
	sApp.start();
	signal(SIGINT,signalDealer);
	int *data = (int*)sApp.malloc(1024*sizeof(int));
	haha(data);
}
