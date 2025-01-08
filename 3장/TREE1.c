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
	if((rear + 1) % MAX == front) // ť�� ����
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
		visit(t);	// �Ѹ� �湮 
		preorder_traverse(t->left); // ���� ���� ������ �湮 
		preorder_traverse(t->right);	// ������ ���� ���� �湮 
	}
}

void inorder_traverse(node *t)
{
	if(t != tail)
	{
		inorder_traverse(t->left);	// ���� 
		visit(t);	// �Ѹ� 
		inorder_traverse(t->right); // ������ 
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
{		// ����ǥ��� ���� p�� �о� ���� ������ ���� 
	node *t;
	while(*p)
	{
		while(*p == ' ')	// ���� ���ڴ� ���� 
			p++;
		t = (node*)malloc(sizeof(node));
		t->key = *p;
		t->left = tail;
		t->right = tail;
		if(is_operator(*p))	// �������̸� ���� �Ͽ� �ڽ� ���� ���� 
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
		while (*s == ' ')	// �������� 
			s++;
		if (is_operator(*s))
			f--;		// �������̸� ���� 
		else
			f++;		// �ǿ������̸� ���� 
		if (f < 1) break;	// f�� 1���� �۾����� ����÷� 
		s++;
	}
	return (f == 1);	// �ǿ����ڼ� - �����ڼ� = 1�� �Ǿ�� 
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
