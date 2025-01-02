#include<stdio.h>
#include<stdlib.h>
//#include<alloc.h>

 typedef struct _dnode
{
     int key;                 // 정보 전달
     struct _dnode *prev;     // 바로 전의 노드를 가리키는 링크
     struct _dnode *next;     // 바로 뒤의 노드를 가리키는 링크
} dnode;

dnode *head, *tail;

void init_dlist(void)
{
     head = (dnode*)malloc(sizeof(dnode));
     tail = (dnode*)malloc(sizeof(dnode));
     head->next = tail;     // 머리의 다음은 꼬리
     head->prev = head;   // 머리의 앞은 머리
     tail->next = tail;       // 꼬리의 다음은 꼬리
     tail->prev = head;     // 꼬리의 앞은 머리
}

dnode *find_dnode(int k)
{
     dnode *s;
     s = head->next;
     while(s->key != k && s != tail) // 찾거나 꼬리이면 끝
          s = s->next;
     return s;
}

int delete_dnode(int k)
{
     dnode *s;
     s = find_dnode(k);     // k의 값을 갖는 노드를 찾는다.
     if (s != tail)            // s가 tail이 아니면 찾은 것이다.
     {
          s->prev->next = s->next; // s 앞 노드의 다음은 s의 다음 노드이다.
          s->next->prev = s->prev; // s 다음 노드의 앞은 s 앞 노드이다.
          free(s);
          return 1;
     }
     return 0;
}

dnode *insert_dnode(int k, int t)  // t 앞에 k를 삽입
{
     dnode *s;
     dnode *i = NULL;
     s = find_dnode(t);     // t값의 노드를 찾는다.
     if(s != tail)            // 만약 찾았으면
     {
          i = (dnode*)malloc(sizeof(dnode));
          i->key = k;
          s->prev->next = i;   // s 앞 노드의 다음은 i노드이다.
          i->prev = s->prev;   // i의 앞은 s 앞 노드이다.
          s->prev = i;    // s의 앞은 I 노드이다.
          i->next = s;    // i의 다음은 s 노드이다.
     }
     return i;   // 못 찾았으면 null을 리턴한다.
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

dnode *insert_dnode_ptr(int k, dnode * t) // t앞에 k를 삽입
{
     dnode *i;            // i는 삽입될 노드
     if(t == head)         // 머리 앞에는 아무것도 삽입할 수 없다.
          return NULL;
     i = (dnode*)malloc(sizeof(dnode));
     i->key = k;
     t->prev->next = i;    // t 앞 노드의 다음은 I 노드이다.
     i->prev = t->prev;    // I의 앞은 t의 앞 노드이다.
     t->prev = i;          // t의 앞은 I 노드이다.
     i->next = t;          // i의 다음은 t 노드이다.
     return;
}

int delete_dnode_ptr(dnode *p)
{
     if(p == head || p == tail)     // 머리나 꼬리를 없앨 수는 없다.
          return 0;
     p->prev->next = p->next;    // p 앞 노드의 다음은 p 다음 노드이다.
     p->next->prev = p->prev;    // p 다음 노드의 앞은 p 앞 노드이다.
     free(p);                      // p를 메모리에서 해제
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
