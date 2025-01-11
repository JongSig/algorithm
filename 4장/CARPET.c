#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
//#include<bio.h>

void box(int x, int y, int r)
{
	int i;
	setcolor(WHITE);
	for(i = y-r/3; i <= y+r/3; i++)
		line(x-r/3, i, x+r/3, i);
 } 

void carpet1(int x, int y, int r)
{
	if(r > 0)
	{
		carpet1(x - 2*r, y + 2*r, r/3);	// ���� �ϴ� 
		carpet1(x - 2*r, y		, r/3);	// ���� 
		carpet1(x - 2*r, y - 2*r, r/3);	// ���� ��� 
		carpet1(x	   , y + 2*r, r/3);	// �ϴ� 
		carpet1(x	   , y - 2*r, r/3);	// ��� 
		carpet1(x + 2*r, y + 2*r, r/3);	// ���� �ϴ� 
		carpet1(x + 2*r, y		, r/3);	// ���� 
		carpet1(x + 2*r, y - 2*r, r/3);	// ���� ���
		box(x, y, r); 	// �簢�� �׸� 
	}
}

void carpet2(int x, int y, int r)
{
	if(r > 0)
	{
		box(x, y, r); 	// �簢�� �׸�
		carpet1(x - 2*r, y + 2*r, r/2);	// ���� �ϴ� 
		carpet1(x - 2*r, y		, r/2);	// ���� 
		carpet1(x - 2*r, y - 2*r, r/2);	// ���� ��� 
		carpet1(x	   , y + 2*r, r/2);	// �ϴ� 
		carpet1(x	   , y - 2*r, r/2);	// ��� 
		carpet1(x + 2*r, y + 2*r, r/2);	// ���� �ϴ� 
		carpet1(x + 2*r, y		, r/2);	// ���� 
		carpet1(x + 2*r, y - 2*r, r/2);	// ���� ��� 
	}
}

void carpet3(int x, int y, int r)
{
	if(r > 0)
	{
		carpet1(x - r, y + r, r/2);	// ���� �ϴ� 
		carpet1(x + r, y + r, r/2);	// ���� ��� 
		carpet1(x - r, y - r, r/2);	// ���� �ϴ� 
		carpet1(x + r, y - r, r/2);	// ���� ���
		box(x, y, r);
	}
}

void main(void)
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "c:\\TURBOC3\\BGI");
	if(graphresult() !=  grOk)
	{
		printf("\nGraphic System Error!");
		exit(1);
	}
	
	carpet1(getmaxx()/2, getmaxy()/2, 60);
	bioskey(0);
	cleardevice();
	carpet2(getmaxx()/2, getmaxy()/2, 50);
	bioskey(0);
	cleardevice();
	carpet3(getmaxx()/2, getmaxy()/2, 100);
	bioskey(0);
	closegraph();
}
