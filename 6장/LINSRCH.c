#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BASE(i) ((char*)base + (i)*width)
typedef int (*FCMP) (const void*, const void*);

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++;	// ���� �˻� 
	return (i<*num ? i : -1);	// Ű�� ã������ i��, �ƴϸ� -1�� ���� 
}

int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	memcpy(BASE((*num)++), key, width);	// �߰��ϰ� num���� 
	return *num - 1;	// �߰��� ��ġ�� ���� 
}

int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int p;
	int i;
	if(*num > 0)	// �ڷᰡ �ϳ��� ���� ���� ������ �� �ִ�. 
	{
		if ((p = lv_search(key, base, num, width, fcmp)) < 0) return -1;	// �˻� 
		for (i = p+1; i<*num; i++) memcpy(BASE(i-1), BASE(i), width);	// ��� 
		(*num)--;	// �ڷ�� ���� 
		return p;	// ã�Ҵ� ��ġ ���� 
	}
	return -1;
}

int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0, j;
	void *v;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++; // ���� �˻� 
	if(i >= *num) return -1;
	v = malloc(width);
	memcpy(v, BASE(i), width);
	for(j = i-1; j >= 0; j--) 
		memcpy(BASE(j+1), BASE(j), width);
	memcpy(base, v, width);	// ���ο� Ű
	return 0;	// Ű���� ��ġ�� ���� 
}
