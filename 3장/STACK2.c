#include<stdio.h>
#include<stdlib.h> 

typedef struct _node
{
	int key;
	struct _node *next;
} node;

node *head, *tail;

void init_stack(void)
{
	head = (node*)malloc(sizeof(node));
	tail = (node*)malloc(sizeof(node));
	head->next = tail;
	tail->next = tail;
}

int push(int k)
{
	node *t;
	if((t = (node*)malloc(sizeof(node))) == NULL)
	{		// 메모리가 부족할 경우 에러를 낸다. 
		printf("\n	Out of memory... ");
		return -1;
	}
	t->key = k;
	t->next = head->next;	// t를 머리의 다음에 삽입한다. 
	head->next = t;
	return k;
}

int pop(void)
{
	node *t;
	int i;
	if(head->next == tail)
	{
		printf("\n    Stack underflow.");
		return -1;
	}
	t = head->next;		// head->next 노드를 삭제하기 위해 t에 물림 
	i = t->key;
	head->next = t->next;	// head->next 노드를 연결 리스트에서 제외시킴 
	free(t);				// t를 삭재 
	return i;				// 삭제된 t의 값을 리턴 
}

void clear_stack(void)
{
	node *t, *s;
	t = head->next; 	// 첫 노드를 t에 물린다. 
	while (t != tail)	// 끝 노드까지 루프 
	{
		s = t;			// 노드를 삭제하기 위해 s에 물림 
		t = t->next;	// t는 다음 노드로 건너감 
		free(s);		// 물린 노드 해제 
	}
	head->next = tail;
}

void print_stack(void){
	node *t;
	t = head->next;
	printf("\n	Stack contents : Top -----> Bottom\n");
	while (t!=tail)
	{
		printf("%-6d", t->key);
		t = t->next;
	}
}

void main(void)
{
	int i;
	init_stack();
	
	printf("\nPush 5, 4, 7, 8, 2, 1");
	push(5);
	push(4);
	push(7);
	push(8);
	push(2);
	push(1);
	print_stack();
	
	printf("\nPop");
	i = pop();
	print_stack();
	printf("\n	poping value is %d", i);
	
	printf("\nPush 3, 2, 5, 7, 2");
	push(3);
	push(2);
	push(5);
	push(7);
	push(2);
	print_stack();
	
	printf("\nPush 3");
	push(3);
	print_stack();
	
	printf("\nInitialize stack");
	clear_stack();
	print_stack();
	
	printf("\nNow stack is empty, pop");
	i = pop();
	print_stack();
	printf("\n	popping value is %d", i);
}
