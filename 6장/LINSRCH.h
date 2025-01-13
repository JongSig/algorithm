#ifndef _LINSRCH_H
#define _LINSRCH_H

#include <stddef.h>

typedef int (*FCMP) (const void*, const void*);

/*
	순차 검색을 수행하여 key와 일치하는 데이터의 인덱스를 반환합니다.
	@param key		검색할 키 값
	@param base		데이터 배열의 시작 주소
	@param num		배열의 요소 수(포인터)
	@param width	각 요소의 크기
	@param fcmp		비교 함수
	@return			key의 인텍스 또는 -1 (없을 경우) 
	*/
int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	데이터를 삽입합니다. 
	@param key		검색할 키 값
	@param base		데이터 배열의 시작 주소
	@param num		배열의 요소 수(포인터)
	@param width	각 요소의 크기
	@param fcmp		비교 함수
	@return			삽입된 위치의 인덱스 
	*/
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	데이터를 삭제합니다. 
	@param key		검색할 키 값
	@param base		데이터 배열의 시작 주소
	@param num		배열의 요소 수(포인터)
	@param width	각 요소의 크기
	@param fcmp		비교 함수
	@return			삭제된 데이터의 인덱스 또는 -1 (없을 경우) 
	*/			 
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	검색된 데이터를 배열의 선두로 이동합니다. 
	@param key		검색할 키 값
	@param base		데이터 배열의 시작 주소
	@param num		배열의 요소 수(포인터)
	@param width	각 요소의 크기
	@param fcmp		비교 함수
	@return			0 성공, -1 실패 
	*/	
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);

#endif
