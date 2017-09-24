#ifndef __CQUEUE_H
#define __CQUEUE_H
#include<atomic>
#include <cstdlib>

//#define DEBUG

template <typename T,int capacity>
class spsc_queue
{
	private:
		std::atomic<int> head;
		T queue[capacity];
		std::atomic<int> tail;
	public:
		spsc_queue()
		{
			head.store(-1,std::memory_order_relaxed);
			tail.store(-1,std::memory_order_release);
		}
		inline bool push(const T &data)
		{
			int newtail = tail.load(std::memory_order_acquire)+1;//acquire
			if (newtail == capacity)
				newtail -= capacity;
			if (newtail == head.load(std::memory_order_relaxed))
				return false;
#ifdef DEBUG
			printf(">>POP %d %d %d\n",head.load(),tail.load(),newtail);
#endif
			queue[newtail] = data;
			tail.store(newtail,std::memory_order_release);//release
			return true;
		}
		bool empty()
		{
			return head.load() == tail.load();
		}
		inline bool pop(T &data)
		{
			int newhead = head.load(std::memory_order_acquire) + 1;//acquire
			if (newhead-1 == tail.load(std::memory_order_relaxed))
				return false;
#ifdef DEBUG
			printf(">>POP0 %d %d\n",head.load(),tail.load());
			if (head.load() == tail.load())
				return false;
#endif
			if (newhead == capacity)
				newhead -= capacity;
#ifdef DEBUG
			printf(">>POP %d %d %d\n",head.load(),tail.load(),newhead);
#endif
			data = queue[newhead];
			head.store(newhead,std::memory_order_release);//release
#ifdef DEBUG
			if (newhead == 50)
				exit(1);
#endif
			return true;
		}
		void show()
		{
			printf(">>HEAD = %d  TAIL = %d\n",head.load(std::memory_order_relaxed),tail.load(std::memory_order_relaxed));
		}
};

#endif
