#include<stdio.h>
 
#define MAX 10

int queue[MAX];
int front, rear;

void init_queue(void)
{
	front = rear = 0;
}

void clear_queue(void)
{
	front = rear;
}

int put(int k)
{
	if((rear + 1) % MAX == front)	// 큐가 꽉 찼는지 확인 
	{
		printf("\n	Queue overflow");
		return -1;
	}
	queue[rear] = k;	// rear는 빈 공간을 가리키므로 바로 k를 저장한다. 
	rear = ++rear % MAX;	// rear를 다음으로 
	return k;
}

int get(void)
{
	int i;
	if(front == rear)	// 큐가 비어있는가? 
	{
		printf("\n	Queue underflow");
		return -1;
	}
	i = queue[front];	// front의 값을 취득 
	front = ++front % MAX;	// front를 다음 요소로 
	return i;
}

void print_queue(void)
{
	int i;
	printf("\n	Queue contents : Front ----> Rear\n");
	for (i = front; i != rear; i = ++i % MAX)	// 주위 
		printf("%-6d", queue[i]);
}

void main(void)
{
	int i;
	init_queue();
	
	printf("\nPut 5, 4, 7, 8, 2, 1");
	put(5);
	put(4);
	put(7);
	put(8);
	put(2);
	put(1);
	print_queue();
	
	printf("\nGet");
	i = get();
	print_queue();
	printf("\n	getting value is %d", i);
	
	printf("\nPut 3, 2, 5, 7");
	put(3);
	put(2);
	put(5);
	put(7);
	print_queue();
	
	printf("\nNow queue is full, put 3");
	put(3);
	print_queue();
	
	printf("\nInitialize queue");
	clear_queue();
	print_queue();
	
	printf("\nNow queue is empty, get");
	i = get();
	print_queue();
	printf("\n	getting value is %d", i);
 } 
