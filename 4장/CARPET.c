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
		carpet1(x - 2*r, y + 2*r, r/3);	// 좌측 하단 
		carpet1(x - 2*r, y		, r/3);	// 좌측 
		carpet1(x - 2*r, y - 2*r, r/3);	// 좌측 상단 
		carpet1(x	   , y + 2*r, r/3);	// 하단 
		carpet1(x	   , y - 2*r, r/3);	// 상단 
		carpet1(x + 2*r, y + 2*r, r/3);	// 우측 하단 
		carpet1(x + 2*r, y		, r/3);	// 우측 
		carpet1(x + 2*r, y - 2*r, r/3);	// 우측 상단
		box(x, y, r); 	// 사각형 그림 
	}
}

void carpet2(int x, int y, int r)
{
	if(r > 0)
	{
		box(x, y, r); 	// 사각형 그림
		carpet1(x - 2*r, y + 2*r, r/2);	// 좌측 하단 
		carpet1(x - 2*r, y		, r/2);	// 좌측 
		carpet1(x - 2*r, y - 2*r, r/2);	// 좌측 상단 
		carpet1(x	   , y + 2*r, r/2);	// 하단 
		carpet1(x	   , y - 2*r, r/2);	// 상단 
		carpet1(x + 2*r, y + 2*r, r/2);	// 우측 하단 
		carpet1(x + 2*r, y		, r/2);	// 우측 
		carpet1(x + 2*r, y - 2*r, r/2);	// 우측 상단 
	}
}

void carpet3(int x, int y, int r)
{
	if(r > 0)
	{
		carpet1(x - r, y + r, r/2);	// 좌측 하단 
		carpet1(x + r, y + r, r/2);	// 좌측 상단 
		carpet1(x - r, y - r, r/2);	// 우측 하단 
		carpet1(x + r, y - r, r/2);	// 우측 상단
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
