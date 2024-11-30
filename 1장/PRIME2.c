#include<stdio.h>
#include<math.h>

#define TRUE 1

int is_prime1(int n){
	int i;
	for(i = 2; i<n; i++)
		if(n%i==0)
			return !TRUE;
	return TRUE;
}

int is_prime2(int n){
	int i, sqrn;
	sqrn = (int)sqrt(n);
	for(i = 2; i <= sqrn; i++)
		if(n % i == 0)
			return !TRUE;
	return TRUE;
}

void result(int i, int n, int r){
	printf("\n  Prim%d Ans : %d is%s prim number"
			, i, n, r ? "":" not");
}

void main(void)
{
	int n;
	int r;
	int i;
	
	puts("\n PRIME2  :  Prime algorithm speed test."
		"\n			Input 0 to end program,");
		
	while(TRUE){
		printf("\n\nInput number to test ->");
		scanf("%d", &n);
		if(n<0)
			continue;
		if (n == 0)
			break;
		
		r = is_prime1(n);	
		result(1, n, r);

		r = is_prime2(n);
		result(2, n, r);
	}
}
