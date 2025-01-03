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

line *head, *tail;	// 머리와 꼬리 노드 
int total, now;		// 파일의 총 라인 수와 현재의 라인 번호 
char filename[13];	// 파일의 이름을 저장 

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
	char buf[256];		// fgets()를 위해서 여유를 많이 둔다. 
	line *t;
	if((fp = fopen(filename, "rt")) == NULL)	// 파일 이름이 틀리면 
	{
		printf("\n Error : Can't read that file.");
		exit(1); 
	}
	total = 0;
	printf("\n File loading...");
	while (!feof(fp))	// 파일 이름이 틀리면 
	{
		fgets(buf, 255, fp);	// 파일에서 한 문장 읽음 
		if(strlen(buf) > 80)	// 한 라인을 80자로 자름 
			buf[80] = 0;
		if((t = (line*)malloc(sizeof(line))) == NULL) // 노드 생성
		{
			printf("\n Error : Out of Memory");
			exit(1);
		}
		if((t->buf = (char*)malloc(strlen(buf))) == NULL)
		{	// 문자열을 저장할 공간 확보 
			printf("\n Error : Out of Memory");
			exit(1); 
		}
		strcpy(t->buf, buf);	// 입력된 문자열을 복사 
		// 생성된 노드를 제일 뒤에 삽입
		t->prev = tail->prev;	// t의 앞은 꼬리의 앞 노드 
		t->next = tail;			// t의 다음은 꼬리 노드 
		tail->prev->next = t;	// 꼬리 앞 노드의 다음은 t 노드 
		tail->prev = t;			// t의 앞노드는 t노드 
		total++;				// 전체 라인 수 증가 
	}
	fclose(fp);	// 파일 닫음 
}

void show_header(void)
{
	textattr((LIGHTGRAY<<4) | BLACK);	// 반전 
	gotoxy(1, 1);		// 커서를 화면 좌측 상단으로 
	cprintf(" TVIEW : %-12s		Loc : %6d of %6d	By Lee jaekyu	",
			filename, now, total);
	textattr((BLACK<<4) | LIGHTGRAY);	// 보통으로
}

void show_page(line *t)
{
	int i=0;
	clrscr();	// 화면을 지운다. 
	show_header();	// 상태 라인을 출력 
	gotoxy(1, 2);	// 상태 라인 바로 아래에 커서를 옮김 
	while(i++ < 23 && t != tail)
	{	// 23라인을 다 출력하거나 마지막 라인을 넘어서면 중지 
		cprintf("%-80s\r", t->buf);
		t = t->next;	// t는 다음 노드로 이동 
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
	int key;		// 키 입력을 받을 변수 
	now = 1;		// 현재의 라인은 1 
	t = head->next;	// t는 제일 처음 노드 
	show_page(t);	// 화면을 출력, 제일 첫 페이지 
	while ((key = bioskey(0)) != ESC)	//ESC이면 끝 
	{
		switch (key)
		{
			case PGUP : move_line(-23, &t); //23라인 앞으로 이동 
				show_page(t);
				break;
			case PGDN : move_line(+23, &t);	//23라인 뒤로 이동 
				show_page(t);
				break;
		}
	}
	clrscr(); // 화면 지우기 
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
