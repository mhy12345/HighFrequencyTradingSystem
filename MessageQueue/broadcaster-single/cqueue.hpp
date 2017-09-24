#ifndef __CQUEUE_H
#define __CQUEUE_H
#include<atomic>
#include <cstdlib>

template <typename T,int capacity>
class spsc_queue
{
	private:
		int head;
		struct node{
			T data;
			int flag;
		}queue[capacity];
		int timestamp_r;
		int timestamp_w;
		int head2;
	public:
		spsc_queue()
		{
			memset(queue,0,sizeof(queue));
			head = -1;
			timestamp_w = 0;
			timestamp_r = 0;
		}
		inline bool push(const T &data)
		{
			head++;
			if (head == capacity)
				head -= capacity;
			queue[head].data = data;
			timestamp_w++;
			queue[head].flag = timestamp_w;
			return true;
		}
		inline bool pop(T &data)
		{
			if (!queue[head2].flag)return false;
			if (queue[head2].flag == timestamp_r+1)
			{
				data = queue[head2].data;
				timestamp_r++;
				head2++;
				if (head2 == capacity)
					head2 -= capacity;
				return true;
			}else if (timestamp_r + capacity < timestamp_w)
			{
				head2 = head;
				timestamp_r = timestamp_w-1;
				printf("Jump...");
			}
			return false;
		}
		void show()
		{
			printf("TIMESTAMP_R = %d\n",timestamp_r);
		}
};

#endif
