#include <stdio.h>
#include <stdlib.h>


void Coin2(int n);

int main()
{
	//int n;
	int i;
	//scanf("%d", &n);
	
	//for (i = 1; i < 21; i++)
	//	Coin2(i);
	Coin2(20);

	return 0;
}

void Coin2(int n) {
	int *N, M;
	int *P;
	int c1, c2, c6, c8;
	int result;
	N = (int*)malloc(sizeof(int) * (n + 1));
	P = (int*)malloc(sizeof(int) * (n + 1));
	N[0] = 0; P[0] = 0;
	c1 = c2 = c6 = c8 = 0;

	result = n;
	while (result != 0)
	{
		for (int i = 1; i <= result; i++) {
			M = N[i - 1]; P[i] = 1;
			if (i >= 2 && M > N[i - 2]) { M = N[i - 2]; P[i] = 2; }
			if (i >= 6 && M > N[i - 6]) { M = N[i - 6]; P[i] = 6; }
			if (i >= 8 && M > N[i - 8]) { M = N[i - 8]; P[i] = 8; }
			N[i] = M + 1;
		}
		printf("%d ", P[result]);
		result = result - P[result];
	}
	printf("\n");
	printf("%d %d %d\n", n, N[n], P[n]);
	free(N);
	free(P);
}