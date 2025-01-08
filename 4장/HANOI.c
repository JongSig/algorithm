#include<stdio.h>

void move(int from, int to)
{
	printf("\nMove from %d to %d", from, to);
}

void hanoi(int n, int from, int by, int to)
{
	if(n == 1)	// 1개의 원반을 움직이는 문제로 줄어들었다. 
		move(from, to); // from->to;
	else
	{
		hanoi(n-1, from, to, by);	// 알고리즘의 1번
		move(from, to);				// 알고리즘의 2번 
		hanoi(n-1, by, from, to); 	// 알고리즘의 3번 
	}
}

void main(void)
{
	int i = 0;
	printf("\nIf you want to quit, enter minus integer");
	while(1)
	{
		printf("\nEnter height of HANOT tower -> ");
		scanf("%d", &i);
		if (i <= 0) break;
		hanoi (i, 1, 2, 3);
	}
}
