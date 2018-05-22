#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodepointer;

struct node{
	int next_vert;
	int capacity;
	int flow;
	nodepointer link1;
	nodepointer link2;
};

void print(nodepointer *adj, int total_vert);

int main()
{
	nodepointer *adj;
	nodepointer x, z, y;
	int total_vert, total_flow;
	int i, v1, v2, cap;
	FILE *f;

	
	f = fopen("Maxflow_input2.txt", "r");
	//f = fopen("Maxflow_input1", "r");

	fscanf(f, "%d %d\n", &total_vert, &total_flow);
	adj = (struct node*)malloc(sizeof(struct node) * (total_vert + 2));
	


	for (i = 0; i < total_vert + 2; i++)
	{
		adj[i] = (struct node*)malloc(sizeof(struct node));
		adj[i]->link1 = NULL;
		adj[i]->link2 = NULL;
	}

	for (i = 0; i < total_flow; i++)
	{
		x = (struct node*)malloc(sizeof(struct node));
		fscanf(f, "%d %d %d\n", &v1, &v2, &cap);

		x->link1 = NULL; x->link2 = NULL;
		x->next_vert = v2;
		x->capacity = cap;
		x->flow = 0;

		if (adj[v1]->link1 == NULL)
		{
			adj[v1]->link1 = x;
			adj[v1]->link2 = x;
		}
		else
		{
			for (y = adj[v1]->link1; y != NULL; y = y->link1)
			{
				if (y->next_vert == v2)
				{
					y->capacity = cap;
					break;
				}
			}

			if (y == NULL)
			{
				adj[v1]->link2->link1 = x;
				adj[v1]->link2 = x;
			
			}
		}
		z = (struct node*)malloc(sizeof(struct node));
		z->link1 = NULL; z->link2 = NULL;
		z->next_vert = v1;
		z->capacity = 0;
		z->flow = 0;

		if (adj[v2]->link1 == NULL)
		{
			adj[v2]->link1 = z;
			adj[v2]->link2 = z;
		}
		else
		{
			for (y = adj[v2]->link1; y != NULL; y = y->link1)
			{
				if (y->next_vert == v1)
				{
					break;
				}
			}

			if (y == NULL)
			{
				adj[v2]->link2->link1 = z;
				adj[v2]->link2 = z;
			}
		}
		x->link2 = z;
		z->link2 = x;
		
	}
	
	print(adj, total_vert);
	fclose(f);
	return 0;
}

void print(nodepointer *adj, int total_vert)
{
	int i;
	nodepointer x;

	for (i = 0; i < total_vert + 2; i++)
	{
		printf("%d | -> ", i);
		for(x = adj[i]->link1; x != NULL; x = x->link1)
			printf("%3d %3d %3d (%p) -> ", x->next_vert, x->capacity, x->flow, x->link2);
		
		printf("\b\b\b\b    ");
		printf("\n");
		

	}

}
