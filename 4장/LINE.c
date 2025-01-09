#include<stdio.h>
#include<bio.h>
#include<graphics.h>

void recursive_line(int x1, int y1, int x2, int y2, int color)
{
	if(x1-x2 <= 1 && x1-x2 >= -1 && y1-y2 <= 1 && y1-y2 >= -1)
		return;	//x1과x2, y1과y2의 차이가 1보다 작아지면 끝 
	else
	{
		putpixel((x1+x2)/2, (y1+y2)/2, color);
		recursive_line(x1, y1, (x1 + x2)/2, (y1+y2)/2, color);
		recursive_line(x2, y2, (x1 + x2)/2, (y1+y2)/2, color);
	}
}

void main(void)
{
	int gd = detect, gm;
	initgragh(&gd, &gm, "c:\\tc\\bgi");
	if(graghresult() !=  grok)
	{
		printf("\nGraphic System Error!");
		exit(1);
	}
	
	recursive_line(10, 10, 600, 350, white);
	bioskey(0);
}
