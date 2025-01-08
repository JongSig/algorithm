#include<stdio.h>
#include<stdlib.h> 

typedef struct _node
{
	int key;
	struct _node *left;
	struct _node *right;
} node;

node *head, *tail;

#define MAX 100

node *stack[MAX];
int top;

void init_stack(void)
{
	top = -1;
}

node *push(node *t)
{
	if(top >= MAX-1)
	{
		printf("\n	Stack overflow");
		return NULL;
	}
	stack[++top] = t;
	return t;
}

node *pop(void)
{
	if(top<0)
	{
		printf("\n	Stack overflow");
		return NULL;
	}
	return stack[top--];
}

int is_stack_empty(void)
{
	return (top == 1);
}

node *queue[MAX];
int front, rear;

void init_queue(void)
{
	front = rear = 0;
}

node *put(node *k)
{
	if((rear + 1) % MAX == front) // 큐가 꽉참
	{
		printf("\n	Queue overflow.");
		return NULL; 
	}
	queue[rear] = k;
	rear = ++rear % MAX;
	return k; 
}

node *get(void)
{
	node *i;
	if(front == rear)
	{
		printf("\n	Queue underflow");
		return NULL;
	}
	i = queue[front];
	front = ++front % MAX;
	return i;
}

int is_queue_empty(void)
{
	return (front == rear);
}

void init_tree(void)
{
	head = (node*)malloc(sizeof(node));
	tail = (node*)malloc(sizeof(node));
	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}

int is_operator(int k)
{
	return (k=='+' || k=='-' || k=='*' || k=='/');
}

 void visit(node *t)
 {
 	printf("%c ", t->key);
 }

void preorder_traverse(node *t)
{
	if(t != tail)
	{
		visit(t);	// 뿌리 방문 
		preorder_traverse(t->left); // 왼쪽 작은 나무를 방문 
		preorder_traverse(t->right);	// 오른쪽 작은 나무 방문 
	}
}

void inorder_traverse(node *t)
{
	if(t != tail)
	{
		inorder_traverse(t->left);	// 왼쪽 
		visit(t);	// 뿌리 
		inorder_traverse(t->right); // 오른쪽 
	}
}

void postorder_traverse(node *t)
{
	if(t != tail)
	{
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}

void levelorder_traverse(node *t)
{
	put(t);
	while(!is_queue_empty())
	{
		t = get();
		visit(t);
		if(t->left != tail)
			put(t->left);
		if(t->right != tail)
			put(t->right);
	}
}

node *make_parse_tree(char *p)
{		// 후위표기법 수식 p를 읽어 수식 나무를 구성 
	node *t;
	while(*p)
	{
		while(*p == ' ')	// 공백 문자는 제거 
			p++;
		t = (node*)malloc(sizeof(node));
		t->key = *p;
		t->left = tail;
		t->right = tail;
		if(is_operator(*p))	// 연산자이면 팝을 하여 자식 노드로 삼음 
		{
			t->right = pop();
			t->left = pop();
		}
		push(t);
		p++;
	}
	return pop();
}

int is_legal(char *s)
{
	int f = 0;
	while (*s)
	{
		while (*s == ' ')	// 공백제거 
			s++;
		if (is_operator(*s))
			f--;		// 연산자이면 감소 
		else
			f++;		// 피연산자이면 증가 
		if (f < 1) break;	// f가 1보다 작아지면 언더플로 
		s++;
	}
	return (f == 1);	// 피연산자수 - 연산자수 = 1이 되어여함 
 }
 
 void main(void)
 {
 	char post[256];
 	init_stack();
 	init_queue();
 	init_tree();
 	while(1)
 	{
 		printf("\n\nInput Postfix expression -> ");
 		gets(post);
 		if (*post == NULL)
 		{
 			printf("\n	Program ends... ");
 			exit(0);
		}
		if (!is_legal(post))
		{
			printf("\nExpression is not legal.");
			continue;
		}
		
		head->right = make_parse_tree(post);
		
		printf("\nPreorder   treaverse -> ");
		preorder_traverse(head->right);
		
		printf("\nInorder    traverse -> ");
		inorder_traverse(head->right);
		
		printf("\nPostorder  traverse -> ");
		postorder_traverse(head->right);
		
		printf("\nLevelorder traverse ->");
		levelorder_traverse(head->right);
	 }
 }
