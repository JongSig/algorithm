#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BASE(i) ((char*)base + (i)*width)
typedef int (*FCMP) (const void*, const void*);

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++;	// 순차 검색 
	return (i<*num ? i : -1);	// 키를 찾았으면 i를, 아니면 -1을 리턴 
}

int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	memcpy(BASE((*num)++), key, width);	// 추가하고 num증가 
	return *num - 1;	// 추가된 위치를 리턴 
}

int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int p;
	int i;
	if(*num > 0)	// 자료가 하나라도 있을 때만 삭제할 수 있다. 
	{
		if ((p = lv_search(key, base, num, width, fcmp)) < 0) return -1;	// 검색 
		for (i = p+1; i<*num; i++) memcpy(BASE(i-1), BASE(i), width);	// 당김 
		(*num)--;	// 자료수 감소 
		return p;	// 찾았던 위치 리던 
	}
	return -1;
}

int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0, j;
	void *v;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++; // 순차 검색 
	if(i >= *num) return -1;
	v = malloc(width);
	memcpy(v, BASE(i), width);
	for(j = i-1; j >= 0; j--) 
		memcpy(BASE(j+1), BASE(j), width);
	memcpy(base, v, width);	// 선두에 키
	return 0;	// 키값의 위치를 리턴 
}
