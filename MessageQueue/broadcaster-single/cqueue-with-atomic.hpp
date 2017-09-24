#ifndef __CQUEUE_H
#define __CQUEUE_H
#include<atomic>
#include <cstdlib>

template <typename T,int capacity>
class spsc_queue_writer
{
	private:
		int head;
		struct node{
			T data;
			int flag;
		}queue[capacity];
		int timestamp_r;
		std::atomic<int> timestamp_w;
	public:
		spsc_queue_writer()
		{
			memset(queue,0,sizeof(queue));
			head = -1;
			timestamp_w.store(0,std::memory_order_release);
		}
		inline bool push(const T &data)
		{
			head++;
			if (head == capacity)
				head -= capacity;
			int newTimeStamp = timestamp_w.load(std::memory_order_acquire)+1;
			queue[head].data = data;
			timestamp_w.store(newTimeStamp,std::memory_order_release);
			//timestamp_w.store(newTimeStamp,std::memory_order_relaxed);
			//想法：是不是timstamp通过release储存后就可以保证data已经存入了内存，这样一定不会出现flag比data先改的情况，导致错误
			queue[head].flag = newTimeStamp;
			return true;
		}
};
template <typename T,int capacity>
class spsc_queue_reader
{
	private:
		int head;
		struct node{
			T data;
			int flag;
		}queue[capacity];
		int timestamp_r;
		std::atomic<int> timestamp_w;
	public:
		spsc_queue_reader()
		{
			head = 0;
			timestamp_r = 0;
		}
		inline bool pop(T &data)
		{
			if (!queue[head].flag)return false;
			if (queue[head].flag == timestamp_r+1)
			{
				data = queue[head].data;
				timestamp_r++;
				head++;
				if (head == capacity)
					head -= capacity;
				return true;
			}
			return false;
		}
		void show()
		{
			printf("TIMESTAMP_R = %d\n",timestamp_r);
		}
};

#endif
