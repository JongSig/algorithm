#include<stdio.h>
#include<stdlib.h> 

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE  16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

typedef struct _card
{
	char name[NAME_SIZE];    // �̸� ���� 
	char corp[CORP_SIZE];    // ȭ�� ���� 
	char tel[TEL_SIZE];      // ��ȭ��ȣ ���� 
	struct _card *next;      // ���� ������ ��ũ 
} card;

card *head, *tail;           // �Ӹ��� ���� 

void init_card(void)
{
	head = (card*)malloc(sizeof(card));
	tail = (card*)malloc(sizeof(card));
	head->next = tail;       // �Ӹ� ������ ���� ��� 
	tail->next = tail;        // ���� ��� ������ ���� ��� 
	return; 
}

void input_card(void)
{
	card *t;
	t = (card*)malloc(sizeof(card));
	
	printf("\nInput namecard menu : ");
		printf("\n   Input name -> ");				// �̸��� �Է¹��� 
			gets(t->name);
		printf("\n   Input corporation -> ");		// ȸ�縦 �Է¹��� 
			gets(t->corp);
		printf("\n   Input telephone number -> ");	// ��ȭ��ȣ �Է� 
			gets(t->tel);
	
	t->next = head->next;		// ���Ḯ��Ʈ�� �ּ��ο� ���� 
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
	while (strcmp(s, t->name) != 0 && t != tail)	// �̸��� ã�� 
	{
		p = p->next;
		t = p->next;
	}
	if(t == tail)	// �̸��� ã�� ���ߴ�. 
		return 0;
	p->next = t->next; // �̸��� ã�� ��� ����, p�� ������ t�� ���� ��� 
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
		return NULL;	// ã�� ������ 
	else
		return t;
}

void save_cards(char *s)
{
	FILE *fp;
	card *t;
	if((fp = fopen(s, "wb")) == NULL)
	{			// ���� ���� ����, ��κ� ��ũ�� �� á�� ����̴�. 
		printf("\n   Error : Disk write failure.");
		return;
	}
	t = head->next;		// t�� ���� ó�� ��� 
	while(t != tail)
	{
		fwrite(t, REC_SIZE, 1, fp);
		t = t->next;	// ���� ���� �̵� 
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
	t = head->next; // ��ũ���� �б� ���� ��� ��带 �� �����. 
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
		if (!fread(t, REC_SIZE, 1, fp))  // ������ ���̸� 
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
		// ���ڸ� �Է��ϴ��� �̰��� �������� ���ڿ��̴�.
		// ���ڿ��� ���ڷ� �ٲٱ� ���� atoi()�Լ��� �̿��Ѵ�. 
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
