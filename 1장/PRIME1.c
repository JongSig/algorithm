#include<stdio.h>

#define TRUE 1

int is_prime(int n){
	int i;
	for(i=2; i<n; i++) /* i를 2부터 n+1까지 증가*/ 
		if(n%i==0)	/* n이 i로 나누어 떨어지는가?*/
			return !TRUE;
	return TRUE; /* 여기까지 오면 소수 */ 
}

void main(void){
	int n;
	
	puts("\n PRIME1  :  The that input number is prime or not."
	"\n				Input 0 to end program.");
	
	while(TRUE){
		puts("\nInput number to test ->");
		scanf("%d", &n);
		if(n<0)
			continue;
		if(n == 0)
			break;
		printf("\n Ans : %d is%s prime number"
				,n , is_prime(n) ? "" : " not");
	}
}
