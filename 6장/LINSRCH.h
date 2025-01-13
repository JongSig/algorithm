#ifndef _LINSRCH_H
#define _LINSRCH_H

#include <stddef.h>

typedef int (*FCMP) (const void*, const void*);

/*
	���� �˻��� �����Ͽ� key�� ��ġ�ϴ� �������� �ε����� ��ȯ�մϴ�.
	@param key		�˻��� Ű ��
	@param base		������ �迭�� ���� �ּ�
	@param num		�迭�� ��� ��(������)
	@param width	�� ����� ũ��
	@param fcmp		�� �Լ�
	@return			key�� ���ؽ� �Ǵ� -1 (���� ���) 
	*/
int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	�����͸� �����մϴ�. 
	@param key		�˻��� Ű ��
	@param base		������ �迭�� ���� �ּ�
	@param num		�迭�� ��� ��(������)
	@param width	�� ����� ũ��
	@param fcmp		�� �Լ�
	@return			���Ե� ��ġ�� �ε��� 
	*/
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	�����͸� �����մϴ�. 
	@param key		�˻��� Ű ��
	@param base		������ �迭�� ���� �ּ�
	@param num		�迭�� ��� ��(������)
	@param width	�� ����� ũ��
	@param fcmp		�� �Լ�
	@return			������ �������� �ε��� �Ǵ� -1 (���� ���) 
	*/			 
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
/*
	�˻��� �����͸� �迭�� ���η� �̵��մϴ�. 
	@param key		�˻��� Ű ��
	@param base		������ �迭�� ���� �ּ�
	@param num		�迭�� ��� ��(������)
	@param width	�� ����� ũ��
	@param fcmp		�� �Լ�
	@return			0 ����, -1 ���� 
	*/	
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);

#endif
