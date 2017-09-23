#include "spsc_queue.hpp"
#include <sys/time.h>

int main()
{
	spsc_queue<timeval,1024> q;
}
