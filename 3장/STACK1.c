#include <stdio.h>

#define MAX 10
int stack[MAX];    // 스택의 긴통
int top;           // 스텍의 상단

void init_stack(void)
{
	top = -1;
}

int push(int t)
{
	if(top >= MAX - 1)	// 스택이 꽉찼는가? 
	{
		printf("\n    Stack overflow.");
		return -1;	// 에러 처리 
	}
	stack[++top] = t;	// top을 증가시키고 t를 저장 
	return t;
}

int pop(void)
{
	if(top < 0)	// 스택이 텅 비었는가? 
	{
		printf("\n     Stack underflow.");
		return -1;	// 에러 표시 
	}
	return stack[top--];	// 스택 상단의 값 리턴하고 top 감소 
}

void print_stack(void)
{
	int i;
	printf("\n    Stack contents : Top -----> Bottom\n");
	for(i = top; i >= 0; i--)
		printf("%-6d", stack[i]);
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
	printf("\n popping value is %d", i);
	
	printf("\nPush 3, 2, 5, 7, 2");
	push(3);
	push(2);
	push(5);
	push(7);
	push(2);
	print_stack();
	
	printf("\nNow statck is full, push 3");
	push(3);
	print_stack();
	
	printf("\nInitialize stack");
	init_stack();
	print_stack();
	
	printf("\nNow stack is empty, pop");
	i = pop();
	print_stack();
	printf("\n    popping value is %d", i);
}
