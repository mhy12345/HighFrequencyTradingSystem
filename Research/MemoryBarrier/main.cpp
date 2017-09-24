#include <atomic>
using namespace std;
atomic<int> x,y;

void function_load_relaxed()
{
	x.load(memory_order_relaxed);
}

void function_load_acquire()
{
	x.load(memory_order_acquire);
}

int main()
{
	function_load_relaxed();
	function_load_acquire();
}
