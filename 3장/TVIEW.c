#include<stdio.h>
#include<stdlib.h>
#incldue<conio.h>
#include<bios.h>

#define ESC 27
#define PGUP 0x4900
#define PGDN 0x5100

typedef struct _line
{
	char *buf;
	struct _line *prev;
	struct _line *next;
} line;

line *head, *tail;	// �Ӹ��� ���� ��� 
int total, now;		// ������ �� ���� ���� ������ ���� ��ȣ 
char filename[13];	// ������ �̸��� ���� 

void init_line(void)
{
	head = (line*)malloc(sizeof(line));
	tail = (line*)malloc(sizeof(line));
	head->next = tail;
	head->prev = head;
	tail->next = tail;
	tail->prev = head;
}

void load_file(void)
{
	FILE *fp;
	char buf[256];		// fgets()�� ���ؼ� ������ ���� �д�. 
	line *t;
	if((fp = fopen(filename, "rt")) == NULL)	// ���� �̸��� Ʋ���� 
	{
		printf("\n Error : Can't read that file.");
		exit(1); 
	}
	total = 0;
	printf("\n File loading...");
	while (!feof(fp))	// ���� �̸��� Ʋ���� 
	{
		fgets(buf, 255, fp);	// ���Ͽ��� �� ���� ���� 
		if(strlen(buf) > 80)	// �� ������ 80�ڷ� �ڸ� 
			buf[80] = 0;
		if((t = (line*)malloc(sizeof(line))) == NULL) // ��� ����
		{
			printf("\n Error : Out of Memory");
			exit(1);
		}
		if((t->buf = (char*)malloc(strlen(buf))) == NULL)
		{	// ���ڿ��� ������ ���� Ȯ�� 
			printf("\n Error : Out of Memory");
			exit(1); 
		}
		strcpy(t->buf, buf);	// �Էµ� ���ڿ��� ���� 
		// ������ ��带 ���� �ڿ� ����
		t->prev = tail->prev;	// t�� ���� ������ �� ��� 
		t->next = tail;			// t�� ������ ���� ��� 
		tail->prev->next = t;	// ���� �� ����� ������ t ��� 
		tail->prev = t;			// t�� �ճ��� t��� 
		total++;				// ��ü ���� �� ���� 
	}
	fclose(fp);	// ���� ���� 
}

void show_header(void)
{
	textattr((LIGHTGRAY<<4) | BLACK);	// ���� 
	gotoxy(1, 1);		// Ŀ���� ȭ�� ���� ������� 
	cprintf(" TVIEW : %-12s		Loc : %6d of %6d	By Lee jaekyu	",
			filename, now, total);
	textattr((BLACK<<4) | LIGHTGRAY);	// ��������
}

void show_page(line *t)
{
	int i=0;
	clrscr();	// ȭ���� �����. 
	show_header();	// ���� ������ ��� 
	gotoxy(1, 2);	// ���� ���� �ٷ� �Ʒ��� Ŀ���� �ű� 
	while(i++ < 23 && t != tail)
	{	// 23������ �� ����ϰų� ������ ������ �Ѿ�� ���� 
		cprintf("%-80s\r", t->buf);
		t = t->next;	// t�� ���� ���� �̵� 
	}
}

void move_line(int d, line **t)
{
	if(d < 0)
		while (d++ != 0 && (*t)->prev != head)
		{
			*t = (*t)->prev;
			now--;
		}
	else
		while (d-- != 0 && (*t)->next != tail)
		{
			*t = (*t)->next;
			now++;
		}
}

void key_proc(void)
{
	line *t;
	int key;		// Ű �Է��� ���� ���� 
	now = 1;		// ������ ������ 1 
	t = head->next;	// t�� ���� ó�� ��� 
	show_page(t);	// ȭ���� ���, ���� ù ������ 
	while ((key = bioskey(0)) != ESC)	//ESC�̸� �� 
	{
		switch (key)
		{
			case PGUP : move_line(-23, &t); //23���� ������ �̵� 
				show_page(t);
				break;
			case PGDN : move_line(+23, &t);	//23���� �ڷ� �̵� 
				show_page(t);
				break;
		}
	}
	clrscr(); // ȭ�� ����� 
}

void main(int argc, char *argv[])
{
	line *t;
	if (argc < 2)
	{
		printf("\nUsage : TVIEW <filename.ext>");
		exit(0);
	}
	strcpy(filename, argv[1]);
	init_line();
	load_file();
	key_proc();
	printf("\nProgram ends...");
}
