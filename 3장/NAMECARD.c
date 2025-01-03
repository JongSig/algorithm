#include<stdio.h>
#include<stdlib.h> 

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE  16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

typedef struct _card
{
	char name[NAME_SIZE];    // 이름 저장 
	char corp[CORP_SIZE];    // 화사 저장 
	char tel[TEL_SIZE];      // 전화번호 저장 
	struct _card *next;      // 다음 노드로의 링크 
} card;

card *head, *tail;           // 머리와 꼬리 

void init_card(void)
{
	head = (card*)malloc(sizeof(card));
	tail = (card*)malloc(sizeof(card));
	head->next = tail;       // 머리 다음의 꼬리 노드 
	tail->next = tail;        // 꼬리 노드 다음은 꼬리 노드 
	return; 
}

void input_card(void)
{
	card *t;
	t = (card*)malloc(sizeof(card));
	
	printf("\nInput namecard menu : ");
		printf("\n   Input name -> ");				// 이름을 입력받음 
			gets(t->name);
		printf("\n   Input corporation -> ");		// 회사를 입력바음 
			gets(t->corp);
		printf("\n   Input telephone number -> ");	// 전화번호 입력 
			gets(t->tel);
	
	t->next = head->next;		// 연결리스트의 최선두에 놓음 
	head->next = t;	
}

void print_card(card *t, FILE *f)
{
	fprintf(f, "\n%-20s   %-30s   %-15s", t->name, t->corp, t->tel);
}

void print_header(FILE *f)
{
	fprintf(f,	"\nName				"
				"Corporation			"
				"Telephone number");
	fprintf(f,	"\n--------------------"
				"------------------------------"
				"----------------");
}

int delete_card(char *s)
{
	card *t;
	card *p;
	p = head;
	t = p->next;
	while (strcmp(s, t->name) != 0 && t != tail)	// 이름을 찾음 
	{
		p = p->next;
		t = p->next;
	}
	if(t == tail)	// 이름을 찾지 못했다. 
		return 0;
	p->next = t->next; // 이름을 찾은 경우 삭제, p의 다음은 t의 다음 노드 
	free(t);
	return 1;
}

card *search_card(char *s)
{
	card *t;
	t = head->next;
	while (strcmp(s, t->name) != 0 && t != tail)
		t = t->next;
	if (t == tail)
		return NULL;	// 찾지 못했음 
	else
		return t;
}

void save_cards(char *s)
{
	FILE *fp;
	card *t;
	if((fp = fopen(s, "wb")) == NULL)
	{			// 파일 쓰기 에러, 대부분 디스크가 꽉 찼을 경우이다. 
		printf("\n   Error : Disk write failure.");
		return;
	}
	t = head->next;		// t는 제일 처음 노드 
	while(t != tail)
	{
		fwrite(t, REC_SIZE, 1, fp);
		t = t->next;	// 다음 노드로 이동 
	}
	fclose(fp);
}

void load_cards(char *s)
{
	FILE *fp;
	card *t;
	card *u;
	if ((fp = fopen(s, "rb")) == NULL)
	{
		printf("\n Error : %s is not exist.", s);
		return;
	}
	t = head->next; // 디스크에서 읽기 전에 모든 노드를 다 지운다. 
	while(t != tail)
	{
		u = t;
		t = t->next;
		free(u);
	}
	head->next = tail;
	while (1)
	{
		t = (card*)malloc(sizeof(card));
		if (!fread(t, REC_SIZE, 1, fp))  // 파일의 끝이면 
		{
			free(t);
			break;
		}
		t->next = head->next;
		head->next = t;
	}
	fclose(fp);
}

int select_menu(void)
{
	int i;
	char s[10];
	printf("\n\nNAMECARD Manger");
	printf("\n--------------------------");
	printf("\n1. Input	Namecard");
	printf("\n2. Delete Namecard");
	printf("\n3. Search	NameCard");
	printf("\n4. Load	NameCard");
	printf("\n5. Save	NameCard");
	printf("\n6. List	NameCard");
	printf("\n7. Print	NameCard");
	printf("\n8. End	NameCard");
	do
	{
		printf("\n\n   : select operation -> ");
		i = atoi(gets(s));
		// 숫자를 입력하더라도 이것은 어디까지나 문자열이다.
		// 문자열을 숫자로 바꾸기 위해 atoi()함수를 이용한다. 
	}while (i<0 || i>8);
	return i;
}

void main(void)
{
	char *fname = "NAMECARD.DAT";
	char name[NAME_SIZE];
	int i;
	card *t;
	init_card();
	while((i=select_menu()) != 8)
	{
		switch(i)
		{
			case 1 : 
				input_card();
				break;
			case 2 : 
				printf("\n   Input name to delet -> ");
				gets(name);
				if(!delete_card(name))
					printf("\n   Input name to search -> ");
				break;
			case 3 : 
				printf("\n   Input name t0 search -> ");
				gets(name);
				t = search_card(name);
				if (t==NULL)
				{
					printf("\n   Can't find that name.");
					break;
				}
				print_header(stdout);
				print_card(t, stdout);
				break;
			case 4 : 
				load_cards(fname);
				break;
			case 5 : 
				save_cards(fname);
				break;
			case 6 : 
				t = head->next;
				print_header(stdout);
				while(t != tail)
				{
					print_card(t, stdout);
					t = t->next;
				}
				break;
			//case 7 : t = head->next;
			//	print_header(stdprn);
			//	while (t != tail)
			//	{
			//		print_card(t, stdprn);
			//		t = t->next;
			//	}
			//	break;
		}
	}
	printf("\n\nProgram ends...");
}
