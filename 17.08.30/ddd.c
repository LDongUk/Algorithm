#include <stdio.h>
#include <string.h>

void sort(char* a, int k, int n);
void perm(char *a, int k, int n);

int main()
{
	char a[100];
	int n;

	printf("행렬 입력 : ");
	scanf("%s", a);

	n = strlen(a);
	
	printf("%s\n", a);
	perm(a, 0, n);
	//sort(a, 2, n);

	return 0;
}

// k부터 n까지 소팅
void sort(char* a, int k, int n)
{
	int i, j;
	char temp;


	for (i = k ; i < n; i++)
	{
		temp = a[i];
		j = i - 1;

		while (j > k && a[j] > temp)
		{
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = temp;
	}

}

void perm(char *a, int k, int n)
{
	int m;
	char temp;

	if (k >= n)
		return;
	sort(a, k, n);

	perm(a, k + 1, n); sort(a, k + 1, n);
	for (m = k + 1; m < n; m++)
	{
		if (a[m] > a[k])
		{
			temp = a[m];
			a[m] = a[k];
			a[k] = temp;
			printf("%s\n", a);
			perm(a, k + 1, n); sort(a, k + 1, n);
			
		}
		
	}
	

}
