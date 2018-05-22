#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct node *nodePointer;

struct node {
	int vertex;
	int weight;
	nodePointer next;
};

nodePointer *adj;
int *d, *p, *t, *visit;
int top;
int stack[STACK_SIZE];


void dfs(int node);
void push(int item);
int pop();
void dag_longest(int *topo, int num_vertices);

int main() {

	FILE *f;
	int num_vertices;
	int i;
	int from, to;
	int **temp_input;
	nodePointer x, y;

	f = fopen("input.txt", "r");

	fscanf(f, "%d\n", &num_vertices);
	num_vertices += 2;


	//make arrays
	temp_input = (int**)malloc(sizeof(int*) * num_vertices);
	adj = (nodePointer*)malloc(sizeof(nodePointer) * num_vertices);
	d = (int *)malloc(sizeof(int) * num_vertices);
	p = (int *)malloc(sizeof(int) * num_vertices);
	t = (int *)malloc(sizeof(int) * num_vertices);
	visit = (int *)malloc(sizeof(int) * num_vertices);


	for (i = 0; i < num_vertices; i++)
		temp_input[i] = (int*)malloc(sizeof(int) * 3);

	//initialize d, p, visit
	for (i = 0; i < num_vertices; i++) {
		d[i] = 0;
		p[i] = -1;
		visit[i] = 0;
	}


	//input text
	temp_input[0][0] = INT_MAX;
	temp_input[0][1] = 0;
	temp_input[0][2] = INT_MAX;

	for (i = 1; i < num_vertices - 1; i++) {
		fscanf(f, "%d %d %d\n", &temp_input[i][0], &temp_input[i][1], &temp_input[i][2]);
	}

	temp_input[num_vertices - 1][0] = 0;
	temp_input[num_vertices - 1][1] = 0;
	temp_input[num_vertices - 1][2] = 0;

	for (i = 0; i < num_vertices; i++) {
		adj[i] = (struct node*)malloc(sizeof(struct node));
		adj[i] = NULL;
	}

	fclose(f);

	//make adj list
	for (from = 0; from < num_vertices; from++) {
		for (to = 0; to < num_vertices; to++) {

			if (from == to)
				continue;

			if (temp_input[from][0] > temp_input[to][0] &&
				temp_input[from][2] > temp_input[to][2]) {

				x = (struct node*) malloc(sizeof(struct node));

				x->vertex = to;
				x->weight = temp_input[from][1];
				x->next = NULL;

				if (adj[from] == NULL)
					adj[from] = x;

				else {
					for (y = adj[from]; y->next != NULL; y = y->next);
					y->next = x;
				}	
			}
		}
	}

	//delete temp_input
	for (i = 0; i < num_vertices; i++)
		free(temp_input[i]);
	free(temp_input);


	//print adj
	for (i = 0; i < num_vertices; i++) {
		printf("%d : ", i);

		for (y = adj[i]; y != NULL; y = y->next)
			printf("(%d, %d), ", y->vertex, y->weight);

		if (adj[i] == NULL)
			printf("\n");
		else
			printf("\b\b \n");
	}

	//topological sort from stack[0] to stack[6]
	for (x = adj[0]; x->next != NULL; x = x->next)
		dfs(x->vertex);

	//t : topological sort
	for (i = 0; i < num_vertices; i++)
		t[i] = pop();
	
	//print topo
	printf("topo : ");
	for (i = 0; i < num_vertices; i++)
		printf("%-2d", t[i]);
	printf("\n");


	dag_longest(t, num_vertices);

	free(d);
	free(p);
	free(t);
	free(visit);
	free(adj);

	return 0;
}


void dfs(int node) {
	nodePointer x;

	if (visit[node] == 0)
		visit[node] = 1;

	else
		return;


	for (x = adj[node]; x != NULL; x = x->next) {
		if (visit[x->vertex] == 0)
			dfs(x->vertex);
	
	}

	push(node);
}

void push(int item) {

	if(top == STACK_SIZE)
		fprintf(stderr, "STACK IS FULL\n");

	stack[top++] = item;
}

int pop() {
	if(top == -1)
		fprintf(stderr, "STACK IS EMPTY\n");

	return stack[top--];
}

void dag_longest(int *topo, int num_vertices) {
	int u;
	int i;
	nodePointer v;

	//find longest path
	for (i = 0; i < num_vertices; i++) {
		u = topo[i];

		v = adj[u];

		while (v != NULL) {

			if (d[v->vertex] < d[u] + v->weight) {
				d[v->vertex] = d[u] + v->weight;
				p[v->vertex] = u;
			}

			v = v->next;
		}

	}

	
	//print result
	printf("ANS : ");
	for (i = num_vertices - 1; p[i] != -1; i = p[i]) {
		printf("%d ", p[i]);
	}
	printf("\n");

	printf("%d\n", d[num_vertices - 1]);

}