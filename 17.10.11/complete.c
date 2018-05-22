#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef struct node *nodePointer;

struct node {
	int vertex;
	nodePointer link;

};

int *visit, *p;
nodePointer topol;

int stack[MAX_STACK];
int top = -1;


void init_visit_parent(int total_vertex);
void DFS(nodePointer *adj, int total_vertex);
void DFS_visit(nodePointer *adj, nodePointer node, int pre);
void BFS(nodePointer *adj, int total_vertex);
int pop();
void push(int item);
void topologicaSort(nodePointer *adj, int total_vertex);

int main()
{
	FILE *f;
	int total_vertex, total_edge;
	int i;
	int vert1, vert2;
	nodePointer *adj;
	nodePointer x, y;



	f = fopen("input.txt", "r");

	fscanf(f, "%d %d\n", &total_vertex, &total_edge);


	//인접행렬 생성 및 초기화
	adj = (struct node*) malloc(sizeof(struct node) * (total_vertex + 1));
	for (i = 0; i < total_vertex + 1; i++)
	{
		adj[i] = (struct node*)malloc(sizeof(struct node));
		adj[i] = NULL;
	}
	
	//visit, parent초기화
	visit = (int*)malloc(sizeof(int) * (total_vertex + 1));
	p = (int*)malloc(sizeof(int) * (total_vertex + 1));

	
	//insert
	for (i = 0; i < total_edge; i++) {
		x = (struct node*)malloc(sizeof(struct node));
		fscanf(f, "%d %d\n", &vert1, &vert2);
		vert1; vert2;

		x->vertex = vert2;
		x->link = NULL;

		if (adj[vert1] == NULL)
			adj[vert1] = x;

		else {
			for (y = adj[vert1]; y->link != NULL; y = y->link);
			y->link = x;

		}


	}


	DFS(adj, total_vertex);

	printf("dfs p[i] : ");
	for (i = 1; i < total_vertex + 1; i++)
		printf("%3d", p[i]);
	printf("\n");

	BFS(adj, total_vertex);

	printf("bfs p[i] : ");
	for (i = 1; i < total_vertex + 1; i++)
		printf("%3d", p[i]);
	printf("\n");

	topologicaSort(adj, total_vertex);

	printf("topological sort : ");
	for (x = topol; x != NULL; x = x->link)
		printf("%3d", x->vertex);
	printf("\n");


	return 0;
}

void init_visit_parent(int total_vertex) {
	int i;

	for (i = 1; i < total_vertex + 1; i++)
	{
		visit[i] = 0;
		p[i] = -1;
	}
}



void DFS(nodePointer *adj, int total_vertex) {
	
	int i;
	
	init_visit_parent(total_vertex);
	
	for (i = 1; i < total_vertex + 1; i++)
	{
		
		if (visit[i] == 0)
			DFS_visit(adj, adj[i], i);
	}

}


void DFS_visit(nodePointer *adj, nodePointer node, int pre) {
	
	nodePointer v;

	if (node == NULL) return;

	for (v = node; v != NULL; v = v->link)
	{
		if (visit[v->vertex] == 0) {
			p[v->vertex] = pre;
			visit[v->vertex] = 1;
			DFS_visit(adj, adj[v->vertex], v->vertex);
		}
	}
}


void BFS(nodePointer *adj, int total_vertex) {

	nodePointer u, v;
	nodePointer x, r, f;
	nodePointer temp;
	int pre;

	f = (struct node*) malloc(sizeof(struct node));

	init_visit_parent(total_vertex);

	f = (struct node*) malloc(sizeof(struct node));
	f->vertex = 1;
	f->link = NULL;

	pre = f->vertex;

	r = f;

	u = adj[f->vertex];
	while (f != NULL)
	{

		for (v = u; v != NULL; v = v->link) {
			if (visit[v->vertex] == 0) {
				visit[v->vertex] = 1;
				p[v->vertex] = pre;

				x = (struct node*) malloc(sizeof(struct node));
				x->vertex = v->vertex;
				x->link = NULL;

				r->link = x;
				r = r->link;
			}

		}


		
		temp = f;
		f = f->link;
		free(temp);
		visit[pre] = 1;
		if (f != NULL)
		{
			if (adj[f->vertex] == NULL) continue;
			u = adj[f->vertex];
			
			pre = f->vertex;\
			if(visit[u->vertex] == 0)
				p[u->vertex] = pre;
		}

	}

}

int pop() {

	if (top == -1) return -1;

	return stack[top--];

}

void push(int item) {
	
	if (top == MAX_STACK) sprintf("STACK IS FULL \n", stderr);

	stack[++top] = item;
}

void topologicaSort(nodePointer *adj, int total_vertex) {
	
	int i, nodeVert, vert;
	nodePointer x, y, node;

	init_visit_parent(total_vertex);

	topol = NULL;

	for (i = 1; i < total_vertex + 1; i++) {
		
		for (x = adj[i]; x != NULL; x = x->link)
			push(x->vertex);
		
		while (top != -1) {
			nodeVert = stack[top];

			for (x = adj[nodeVert]; x != NULL; x = x->link) {
				if (visit[x->vertex] == 0) {

					for (y = x; y != NULL; y = adj[y->vertex]) {
						if (visit[y->vertex] == 0)
							push(y->vertex);
					}

				}
			}
			while(1)
			{
				vert = pop();

				if (visit[vert] == 0)
				{
					visit[vert] = 1;
					node = (struct node*)malloc(sizeof(struct node));
					node->vertex = vert;
					node->link = NULL;

					if (topol == NULL)
						topol = node;

					else {
						node->link = topol;
						topol = node;
					}
				}
				if (vert == nodeVert) break;
			}

		}

		if (visit[i] == 0)
		{
			node = (struct node*)malloc(sizeof(struct node));
			node->vertex = i;
			node->link = NULL;
			visit[i] = 1;
			if (topol == NULL)
				topol = node;

			else {
				node->link = topol;
				topol = node;
			}
		}
	}

}