#include<iostream>
#include<atomic>
using namespace std;

template<typename T,int capacity>
class spsc_queue
{
	private:
		atomic_int head;
		atomic<T> queue[capacity];
		atomic_int tail;
	public:
		spsc_queue()
		{
			head = -1;
			tail = -1;
		}
		bool empty()
		{
			return head.load(memory_order_acquire) == tail.load(memory_order_acquire);
		}
		bool push(const T& v)
		{
			int value = head.load(std::memory_order_acquire);
		}
};
