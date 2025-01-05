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
	init_stack();		// 스택을 초기화 
	while (*src)		// 중위표기법의 수식이 남아있는 동안 
	{
		if(*src == ')')		// ')'를 만나면 푸시되어 있던 연산자를 팝하여 
		{					// dst의 현 위치에 저장한다. 
			*dst++ = pop();
			*dst++ = ' ';	// 문자의 구분을 위해 공백을 출력 
			src++;
		}
		else if (*src == '+' || *src == '-' || *src == '*' || *src == '/')
		{			// 연산자이면 연산자를 스택에 푸시한다. 
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9')
		{		// 숫자는 피 연산자이다. 숫자의 연속을 읽어들여 dst에
			do	// 그대로 복사 
			{
				*dst++ = *src++; 
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' '; 
		}
		else	// 이것도 저것도 아니면 무시하고 src를 하나 증가 
			src++;
	}
	*dst = 0; 	// 후기표기법의 문자열의 뒤에 NULL 문자를 붙여준다. 
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
{	// 후위표기법 수식이 적법한가 체크 
	int f = 0;
	while (*s)
	{
		while(*s == ' ')	// remove space 
			s++;
		if (is_operator(*s))
			f--;		// 연산자이면 감수 
		else
		{
			f++;		// 피 연산자이면 증가 
			while (*s != ' ')
				s++;
		}
		if (f < 1) break;	// f가 1보다 적으면 언더플로 
		s++;
	}
	return (f == 1);	// 피연산자의 수 - 연산자의 수 = 1 
}

void postfix(char *dst, char *src)
{
	char c;
	init_stack();	// 스택의 초기화 
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
			{	// 우선순위가 높은 연산자들을 모두 팝
				*dst++ = pop();
				*dst++ = ' ';
			}
			push(*src);	// 그리고 나서 푸시 
			src++;
		}
		else if(*src >= '0' && *src <= '9')
		{	// 피연산자는 그냥 출력 
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
	{	// 모두 끝났으면 스택에 있는 모든 내용을 팝 
		*dst++ = pop();
		*dst++ = ' '; 
	}
	dst--;
	*dst = 0;
}

int calc(char *p)
{
	int i;
	init_stack();	// 스택을 초기화 
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
			push(i);	// 피연산자는 스택에 푸시 
		}
		else if(*p == '+')
		{		// 연산자를 만나면 스택에서 팝하여 연산하고 푸시 
			push(pop() + pop());
			p++;
		}
		else if(*p == '*')
		{
			push(pop() * pop());
			p++;
		}
		else if(*p == '-')
		{		// 교환법칙이 성립하지 않는 연산자들 
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
	postfix(exp, argv[1]);	// 후위표기법으로 바꿈 
	printf("\nPostfix : %s", exp);
	if(!is_legal(exp))	// 수식이 적법한가 점검 
	{
		printf("\n Expression is not legal!");
		exit(1); 
	}
	r = calc(exp);	// 연산 
	printf("\nAnswer : %d", r);
} 
