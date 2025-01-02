#include<stdio.h>
#include<stdlib.h>
//#include<alloc.h>

 typedef struct _dnode
{
     int key;                 // ���� ����
     struct _dnode *prev;     // �ٷ� ���� ��带 ����Ű�� ��ũ
     struct _dnode *next;     // �ٷ� ���� ��带 ����Ű�� ��ũ
} dnode;

dnode *head, *tail;

void init_dlist(void)
{
     head = (dnode*)malloc(sizeof(dnode));
     tail = (dnode*)malloc(sizeof(dnode));
     head->next = tail;     // �Ӹ��� ������ ����
     head->prev = head;   // �Ӹ��� ���� �Ӹ�
     tail->next = tail;       // ������ ������ ����
     tail->prev = head;     // ������ ���� �Ӹ�
}

dnode *find_dnode(int k)
{
     dnode *s;
     s = head->next;
     while(s->key != k && s != tail) // ã�ų� �����̸� ��
          s = s->next;
     return s;
}

int delete_dnode(int k)
{
     dnode *s;
     s = find_dnode(k);     // k�� ���� ���� ��带 ã�´�.
     if (s != tail)            // s�� tail�� �ƴϸ� ã�� ���̴�.
     {
          s->prev->next = s->next; // s �� ����� ������ s�� ���� ����̴�.
          s->next->prev = s->prev; // s ���� ����� ���� s �� ����̴�.
          free(s);
          return 1;
     }
     return 0;
}

dnode *insert_dnode(int k, int t)  // t �տ� k�� ����
{
     dnode *s;
     dnode *i = NULL;
     s = find_dnode(t);     // t���� ��带 ã�´�.
     if(s != tail)            // ���� ã������
     {
          i = (dnode*)malloc(sizeof(dnode));
          i->key = k;
          s->prev->next = i;   // s �� ����� ������ i����̴�.
          i->prev = s->prev;   // i�� ���� s �� ����̴�.
          s->prev = i;    // s�� ���� I ����̴�.
          i->next = s;    // i�� ������ s ����̴�.
     }
     return i;   // �� ã������ null�� �����Ѵ�.
}

dnode *ordered_insert(int k)
{
     dnode *s;
     dnode *i;
     s = head->next;
     while(s->key <= k && s != tail)
          s = s->next;
     i = (dnode*)malloc(sizeof(dnode));
     i->key = k;
     s->prev->next = i;
     i->prev = s->prev;
     s->prev = i;
     i->next = s;
     return i;
}

dnode *insert_dnode_ptr(int k, dnode * t) // t�տ� k�� ����
{
     dnode *i;            // i�� ���Ե� ���
     if(t == head)         // �Ӹ� �տ��� �ƹ��͵� ������ �� ����.
          return NULL;
     i = (dnode*)malloc(sizeof(dnode));
     i->key = k;
     t->prev->next = i;    // t �� ����� ������ I ����̴�.
     i->prev = t->prev;    // I�� ���� t�� �� ����̴�.
     t->prev = i;          // t�� ���� I ����̴�.
     i->next = t;          // i�� ������ t ����̴�.
     return;
}

int delete_dnode_ptr(dnode *p)
{
     if(p == head || p == tail)     // �Ӹ��� ������ ���� ���� ����.
          return 0;
     p->prev->next = p->next;    // p �� ����� ������ p ���� ����̴�.
     p->next->prev = p->prev;    // p ���� ����� ���� p �� ����̴�.
     free(p);                      // p�� �޸𸮿��� ����
     return 1;
}

void print_dlist(dnode *p)
{
	printf("\n");
	while(p != tail)
	{
		printf("%-8d", p->key);
		p = p->next;
	}
}

void delete_all(void)
{
	dnode *p;
	dnode *s;
	p = head->next;
	while(p != tail)
	{
		s = p;
		p = p->next;
		free(s);
	}
	head->next = tail;
	tail->prev = head;
}

void main(void)
{
	dnode *t;
	init_dlist();
	
	ordered_insert(10);
	ordered_insert(5);
	ordered_insert(8);
	ordered_insert(3);
	ordered_insert(1);
	ordered_insert(7);
	ordered_insert(8);
	
	printf("\nInitial Linked list is ");
	print_dlist(head->next);
	
	printf("\nFinding 4 is %ssuccessful", find_dnode(4) == tail ? "un" : "");
	
	t = find_dnode(5);
	printf("\nFinding 5 is %ssuccessful", t == tail ? "un" : "");
	
	printf("\nInserting 7 before 5");
	insert_dnode_ptr(7, t);
	print_dlist(head->next);
	
	t = find_dnode(3);
	printf("\nDeleting 3 ");
	delete_dnode_ptr(t);
	print_dlist(head->next);
	
	printf("\nInserting node 2 before 10");
	insert_dnode(2, 10);
	print_dlist(head->next);
	
	printf("\nDeleting node 2");
	if(!delete_dnode(2))
		printf("\n  deleting 2 is unsuccessful");
	print_dlist(head->next);
	
	printf("\nDeleting node 1");
	insert_dnode_ptr(15, head->next);
	print_dlist(head->next);
	
	printf("\nDeleting all node");
	delete_all();
	print_dlist(head->next);
}
