#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v1;
	int v2;
	int cost;
}edgeinfo;

void weightedUnion(int parent[], int i, int j);
int collapsingFind(int parent[], int i);
void kruskal(int total_v, int total_e, edgeinfo *E);

int main()
{
	int total_v, total_e;
	int i;
	FILE *file;
	edgeinfo *E;
	
	file = fopen("input.txt", "r");
	fscanf(file, "%d %d \n", &total_v, &total_e);
	E = (edgeinfo*)malloc(sizeof(edgeinfo) * (total_e + 1));

	//파일입력
	for (i = 1; i < total_e + 1; i++)
		fscanf(file, "%d %d %d\n", &E[i].v1, &E[i].v2, &E[i].cost);
	
	

	kruskal(total_v, total_e, E);
	

	return 0;
}


void weightedUnion(int parent[], int i, int j)
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		parent[i] = j;
		parent[j] = temp;
	}

	else
	{
		parent[j] = i;
		parent[i] = temp;
	}
}

int collapsingFind(int parent[], int i)
{
	int r, s;

	for (r = i; parent[r] > 0; r = parent[r]);
	while (i != r)
	{
		s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}


void kruskal(int total_v, int total_e, edgeinfo *E)
{
	int i, j, index;
	int p, q;
	int *set;
	edgeinfo e;
	edgeinfo *F;
	
	set = (int *)malloc(sizeof(int) * (total_v + 1));
	F = (edgeinfo*)malloc(sizeof(edgeinfo) * total_v);
	
	
	
	//initial(n)
	for (i = 1; i <= 20; i++)
		set[i] = -1;


	i = 1; index = 0;
	while (index < total_v - 1)
	{
		e = E[i];
		p = collapsingFind(set, e.v1);
		q = collapsingFind(set, e.v2);

		if (p != q)
		{
			weightedUnion(set, p, q);
			F[index] = e;
			printf("%d %d %d\n", e.v1, e.v2, e.cost);
			index++;
		}
		i++;
	}


}