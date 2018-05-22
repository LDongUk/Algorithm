#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int job;
	int dead;
	int benefit;
}info;


int collapsingFind(int parent[], int i);
void scheduling(info sche_info[], int n);
void scheduling2(info sche_info[], int n);
void simpleUnion(int parent[], int i, int j);
void weightedUnion(int parent[], int empty[], int root1, int root2);

int main()
{
	int n;
	int i;
	info *sche_info;
	FILE *file;

		
	file = fopen("input.txt", "r");
	fscanf(file, "%d \n", &n);
	
	sche_info = (info *)malloc(sizeof(info) * n);

	for (i = 0; i < n; i++)
		fscanf(file, "%d %d %d\n", &sche_info[i].job, &sche_info[i].dead, &sche_info[i].benefit);
	
	scheduling2(sche_info, n);

	free(sche_info);
	fclose(file);

	return 0;
}


void scheduling(info sche_info[], int n)
{
	int root1, root2, empty_slot;
	int *parent, *schedule, *empty;
	int i, temp;
	

	parent = (int*)malloc(sizeof(int) * (n + 1));
	schedule = (int*)malloc(sizeof(int) * (n + 1));
	empty = (int*)malloc(sizeof(int) * (n + 1));
	
	for (i = 1; i < n + 1; i++)
	{
		parent[i] = -1;
		empty[i] = i;
	}

	for (i = 0; i < n; i++)
	{
		root1 = collapsingFind(parent, sche_info[i].dead);
		
		schedule[root1] = sche_info[i].job;
		

		if (root1 == 1)
			root2 = n;
		else
			root2 = root1 - 1;
		
		simpleUnion(parent, root1, root2);


	}

	for (i = 1; i < n + 1; i++)
		printf("%d ", schedule[i]);
	printf("\n");

	free(parent);
	free(schedule);
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

void simpleUnion(int parent[], int i, int j)
{
	parent[i] = j;
}


void weightedUnion(int parent[], int empty[], int root1, int root2)
{
	if (parent[root1] < parent[root2])
	{
		parent[root1] = parent[root1] + parent[root2];
		parent[root2] = root1;
		empty[root1] = empty[root2];
	}
	else {
		parent[root2] = parent[root1] + parent[root2];
		parent[root1] = root2;
	}
}


void scheduling2(info sche_info[], int n)
{
	int root1, root2, empty_slot;
	int *parent, *schedule, *empty;
	int i, temp;


	parent = (int*)malloc(sizeof(int) * (n + 1));
	schedule = (int*)malloc(sizeof(int) * (n + 1));
	empty = (int*)malloc(sizeof(int) * (n + 1));

	parent[0] = n;
	for (i = 1; i < n + 1; i++)
	{
		parent[i] = -1;
		empty[i] = i;
	}

	for (i = 0; i < n; i++)
	{
		root1 = collapsingFind(parent, sche_info[i].dead);

		empty_slot = empty[root1];
		schedule[empty_slot] = sche_info[i].job;
		

		/*if (empty_slot == 1)
			temp = n;
		else
			temp = empty_slot - 1;*/

		root2 = collapsingFind(parent, empty_slot -1);


		weightedUnion(parent, empty, root1, root2);
	}

	for (i = 1; i < n + 1; i++)
		printf("%d ", schedule[i]);
	printf("\n");

	free(parent);
	free(schedule);
	free(empty);
}