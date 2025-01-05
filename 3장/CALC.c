#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int stack[MAX];
int top;

void init_stack(void)
{
	top = -1;
}

int push(int t)
{
	if(top >= MAX-1)
	{
		printf("\n	Stack overflow");
		exit(1);
	}
	stack[++top] = t;
	return t;
}

int pop(void)
{
	if(top < 0)
	{
		printf("\n	Stack underflow");
		exit(1);
	}
	return stack[top--];
}

/* void postfix1(char *dst, char *src)
{
	char c;
	init_stack();		// ������ �ʱ�ȭ 
	while (*src)		// ����ǥ����� ������ �����ִ� ���� 
	{
		if(*src == ')')		// ')'�� ������ Ǫ�õǾ� �ִ� �����ڸ� ���Ͽ� 
		{					// dst�� �� ��ġ�� �����Ѵ�. 
			*dst++ = pop();
			*dst++ = ' ';	// ������ ������ ���� ������ ��� 
			src++;
		}
		else if (*src == '+' || *src == '-' || *src == '*' || *src == '/')
		{			// �������̸� �����ڸ� ���ÿ� Ǫ���Ѵ�. 
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9')
		{		// ���ڴ� �� �������̴�. ������ ������ �о�鿩 dst��
			do	// �״�� ���� 
			{
				*dst++ = *src++; 
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' '; 
		}
		else	// �̰͵� ���͵� �ƴϸ� �����ϰ� src�� �ϳ� ���� 
			src++;
	}
	*dst = 0; 	// �ı�ǥ����� ���ڿ��� �ڿ� NULL ���ڸ� �ٿ��ش�. 
} */

int get_stack_top(void)
{
	return (top < 0) ? -1 : stack[top];
}

int is_stack_empty(void)
{
	return (top < 0);
}

int is_operator(int k)
{
	return (k == '+' || k == '-' || k == '*' || k == '/');
}

int precedence(int op)
{
	if(op == '(') return 0;
	if(op == '+' || op == '-') return 1;
	if(op == '*' || op == '/') return 2;
	else return 3;
}

int is_legal(char *s)
{	// ����ǥ��� ������ �����Ѱ� üũ 
	int f = 0;
	while (*s)
	{
		while(*s == ' ')	// remove space 
			s++;
		if (is_operator(*s))
			f--;		// �������̸� ���� 
		else
		{
			f++;		// �� �������̸� ���� 
			while (*s != ' ')
				s++;
		}
		if (f < 1) break;	// f�� 1���� ������ ����÷� 
		s++;
	}
	return (f == 1);	// �ǿ������� �� - �������� �� = 1 
}

void postfix(char *dst, char *src)
{
	char c;
	init_stack();	// ������ �ʱ�ȭ 
	while(*src)
	{
		if(*src == '(')
		{
			push(*src);
			src++;
		}
		else if(*src == ')')
		{
			while(get_stack_top() != '(')
			{
				*dst++ = pop();
				*dst++ = ' ';
			}
			pop();
			src++;
		}
		else if(is_operator(*src))
		{
			while (!is_stack_empty() &&
				precedence(get_stack_top()) >= precedence(*src))
			{	// �켱������ ���� �����ڵ��� ��� ��
				*dst++ = pop();
				*dst++ = ' ';
			}
			push(*src);	// �׸��� ���� Ǫ�� 
			src++;
		}
		else if(*src >= '0' && *src <= '9')
		{	// �ǿ����ڴ� �׳� ��� 
			do
			{
				*dst++ = *src++;
			} while(*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else
			src++;
	}
	while (!is_stack_empty())
	{	// ��� �������� ���ÿ� �ִ� ��� ������ �� 
		*dst++ = pop();
		*dst++ = ' '; 
	}
	dst--;
	*dst = 0;
}

int calc(char *p)
{
	int i;
	init_stack();	// ������ �ʱ�ȭ 
	while(*p)
	{
		if (*p >= '0' && *p <= '9')
		{
			i = 0;
			do
			{
				i = i * 10 + *p - '0';
				p++;
			} while (*p >= '0' && *p <= '9');
			push(i);	// �ǿ����ڴ� ���ÿ� Ǫ�� 
		}
		else if(*p == '+')
		{		// �����ڸ� ������ ���ÿ��� ���Ͽ� �����ϰ� Ǫ�� 
			push(pop() + pop());
			p++;
		}
		else if(*p == '*')
		{
			push(pop() * pop());
			p++;
		}
		else if(*p == '-')
		{		// ��ȯ��Ģ�� �������� �ʴ� �����ڵ� 
			i = pop();
			push(pop() - i);
			p++;
		}
		else if(*p == '/')
		{
			i = pop();
			push(pop()/i);
			p++;
		}
		else
			p++;
	}
	return pop();
}

void main(int argc, char *argv[])
{
	int r;
	char exp[256];
	if(argc < 2)
	{
		printf("\n	Usage : CALC < expression > ");
		printf("\n			* Expression Must not contain blank!");
		exit(0);
	}
	postfix(exp, argv[1]);	// ����ǥ������� �ٲ� 
	printf("\nPostfix : %s", exp);
	if(!is_legal(exp))	// ������ �����Ѱ� ���� 
	{
		printf("\n Expression is not legal!");
		exit(1); 
	}
	r = calc(exp);	// ���� 
	printf("\nAnswer : %d", r);
} 
