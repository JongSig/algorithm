#include<stdio.h>

int sigma(int n){
	int r;
	for(r = 0; n>0; n--)
		r+=n;
	return r;
}

void main(void){
	int a;
	printf("\nInput number -> ");
	scanf("%d", &a);
	printf("\nSigma 1 to %d id %d.", a, sigma(a));
}
