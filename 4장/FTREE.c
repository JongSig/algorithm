#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>

void fixed_tree(int order, int length, float angle)
{
	int dx, dy;
	dx = length * sin(angle);	// length�� angle�� �̿��Ͽ� 
	dy = length * cos(angle);	// ��� ��ǥ�� ���Ѵ�. 
	linerel(-dx, -dy);			// �� ���������� ��� ��ǥ�� ���� �׸� 
	if (order > 0)		// ���� ������ �ƴϸ� 
	{
		fixed_tree(order - 1, length * 0.8, angle + 0.5);
		fixed_tree(order - 1, length * 0.8, angle - 0.5);
	}
	moverel(dx, dy);	// �������� ������� �ǵ�����. 
}

void random_tree(int n, int length, float angle)
{
	int dx, dy;
	float turn1, turn2, scale;
	dx = length * sin(angle);
	dy = length * cos(angle);
	turn1 = (float)rand() / (float)RAND_MAX;
	turn2 = (float)rand() / (float)RAND_MAX;
	scale = (float)rand() / (float)RAND_MAX / 5.0 + 0.7;
	linerel(-dx, -dy);
	if(n > 0)
	{
		random_tree(n - 1, (float)length * scale, angle + turn1);
		random_tree(n - 1, (float)length * scale, angle - turn2);
	}
	moverel(dx, dy);
}

void main(void)
{
	int order;
	int gd = DETECT, gm;
	printf("\nEnter tree order -> ");
	scanf("%d", &order);
	initgraph(&gd, &gm, "c:\\TURBOC3\\BGI");
	if(graphresult() != grOk)
	{
		printf("\nGraphic system error!");
		exit(1);
	}
	outtextxy(0, 10, "Fixed tree");
	moveto(getmaxx()/2, getmaxy());
	fixed_tree(order, 70, 0);
	bioskey(0);
	cleardevice();
	randomize();
	outtextxy(0, 10, "Random tree");
	moveto(getmaxx()/2, getmaxy());
	random_tree(order, 70, 0);
	bioskey(0);
	closegraph();
}
