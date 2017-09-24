#ifndef __CQUEUE_H
#define __CQUEUE_H
#include<atomic>
#include <cstdlib>
#include<cstdio>
//template <typename T,int capacity>
//class listener;

template <typename T,int capacity>
class broadcaster
{
	public:
		int head;
		struct node{
			T data;
			int flag;
		}queue[capacity];
		int timestamp;
	public:
		broadcaster()
		{
			memset(queue,0,sizeof(queue));
			head = -1;
			timestamp = 0;
		}
		inline bool push(const T &data)
		{
			head++;
			if (head == capacity)
				head -= capacity;
			queue[head].data = data;
			timestamp++;
			queue[head].flag = timestamp;
			return true;
		}
};

template <typename T,int capacity>
class listener
{
	private:
		broadcaster<T,capacity> *bc;
		int head,timestamp;
	public:
		static int inner_size(){
			return sizeof(broadcaster<T,capacity>);
		}
		listener(void* ptr)
		{
			bc=(broadcaster<T,capacity>*)ptr;
			head = 0;
			timestamp = 0;
		   	//inner_size= sizeof(broadcaster<T,capacity>);
		}
		inline bool pop(T &data)
		{
			if (!bc->queue[head].flag)return false;
			if (bc->queue[head].flag == timestamp+1)
			{
				data = bc->queue[head].data;
				timestamp++;
				head++;
				if (head == capacity)
					head -= capacity;
				return true;
			}else if (timestamp + capacity < bc->timestamp)
			{
				head = bc->head;
				timestamp = bc->timestamp-1;
				printf("Jump...");
			}
			return false;
		}
		void show()
		{
			printf("TIMESTAMP_R = %d\n",timestamp);
		}
};

#endif
