#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;

struct node {
	int vertex;
	nodePointer link;

};

int *visit, *p;

void init_visit_parent(int total_vertex);
void DFS(nodePointer *adj, int total_vertex);
void DFS_visit(nodePointer *adj, nodePointer node, int pre);
void BFS(nodePointer *adj, int total_vertex);


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

		//x = (struct node*)malloc(sizeof(struct node));
		//x->vertex = vert1;
		//x->link = NULL;

		//if (adj[vert2] == NULL)
		//	adj[vert2] = x;

		//else {
		//	for (y = adj[vert2]; y->link != NULL; y = y->link);
		//	y->link = x;

		//}
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
			//visit[v->vertex] = 1;
			p[v->vertex] = pre;
			visit[v->vertex] = 1;
			DFS_visit(adj, adj[v->vertex], v->vertex);
		}

	}
}


void BFS(nodePointer *adj, int total_vertex) {

	nodePointer u, v;
	nodePointer x, r, Q;
	nodePointer temp;
	int pre;

	Q = (struct node*) malloc(sizeof(struct node));

	init_visit_parent(total_vertex);
	r = (struct node*) malloc(sizeof(struct node));
	r = adj[1];
	Q = r;
	
	pre = 1;
	while (Q != NULL)
	{
		u = Q;

		
		for (v = u; v != NULL; v = v->link) {
			if (visit[v->vertex] == 0) {
				visit[v->vertex] = 1;
				p[v->vertex] = pre;

				x = (struct node*) malloc(sizeof(struct node));
				x->vertex = v->vertex;
				x->link = NULL;
				r->link = x;
				r = r->link;

				pre = v->vertex;
			}

		}

		temp = Q;
		Q = Q->link;
		free(temp);
		visit[u->vertex] = 1;
	}

}
