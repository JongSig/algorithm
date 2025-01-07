#include<stdio.h>
#include<stdlib.h>

typedef struct _dnode
{
	int key;
	struct _dnode *prev;
	struct _dnode *next;
} dnode;

dnode *head, *tail;

void init_queue(void)
{
	head = (dnode*)malloc(sizeof(dnode));
	tail = (dnode*)malloc(sizeof(dnode));
	head->prev = head;
	head->next = tail;
	tail->prev = head;
	tail->next = tail;
}

int put(int k)
{
	dnode *t;
	if((t = (dnode*)malloc(sizeof(dnode))) == NULL)
	{	// 메모리가 다 되었으면 
		printf("\n	Out of memory");
		return -1;
	}
	t->key = k;
	tail->prev->next = t;	// t를 꼬리의 앞에 삽입한다. 
	t->prev = tail->prev;
	tail->prev = t;
	t->next = tail;
	return k;
}

int get(void)
{
	dnode *t;
	int i;
	t = head->next;	// 머리의 다음 노드 
	if(t == tail)	// 큐가 비어 있으면 언더플로 
	{
		printf("\n	Queue underflow.");
		return -1;
	}
	i = t->key;		// 리턴값을 물려둠 
	head->next = t->next;	// 머리 다음 노드를 삭제 
	t->next->prev = head;
	free(t);	// 메모리에서 해제 
	return i;	// 물려둔 값을 리턴  
}

void clear_queue(void)
{
	dnode *t;
	dnode *s;
	t = head->next;
	while(t != tail)	// 꼬리가 나올 때까지 
	{
		s = t;		// 삭제를 위해서 물려둠 
		t = t->next;	// t는 다음으로 넘어감 
		free(s);	// 삭제 
	}
	head->next = tail;	// 머리와 꼬리를 서로 맞물림 
	tail->prev = head;
}

void print_queue(void)
{
	dnode *t;
	t = head->next;
	printf("\n	Queue contents : Front ----> Rear\n");
	while (t != tail)
	{
		printf("%-6d", t->key);
		t = t->next;
	}
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
	
	printf("\nPut 3");
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
