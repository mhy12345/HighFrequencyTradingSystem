#ifndef __CQUEUE_H
#define __CQUEUE_H
#include<atomic>
#include <cstdlib>
#include<cstdio>

template <typename T,int capacity> class listener;

template <typename T,int capacity>
class broadcaster//消息的生产者
{
	public:
		int head;
		struct node{
			T data;
			int flag;//记录时间戳的地方，时间戳严格地址
		}queue[capacity];
		int timestamp;//时间戳
                friend class listener<T, capacity>;  // Will this work?
		
	public:
		broadcaster()
		{
			memset(queue,0,sizeof(queue));
			head = -1;
			timestamp = 0;
		}
		inline bool push(const T &data)//生产者无法判断队列满
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
		static int inner_size(){//由于broadcaster是被listener包含的，所以为了申请broadcaster大小的共享内存，需要知道broadcaster的大小
			return sizeof(broadcaster<T,capacity>);
		}
		listener(void* ptr)
		{
			bc=(broadcaster<T,capacity>*)ptr;
			head = 0;
			timestamp = 0;
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
			}else if (timestamp + capacity < bc->timestamp)//如果producer太快了，已经多绕了一圈了，直接把中间的丢掉
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
