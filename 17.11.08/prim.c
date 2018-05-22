#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;

struct node {
	int vertex;
	int value;
	nodePointer link;
};

int *d, *p, *f;
nodePointer *adjList;
nodePointer *H;
int size_H, current_H;


nodePointer Del_min(int size);
void insert(nodePointer insert_node, int size);
void primA(nodePointer root, int total_vertex);
void dijkA(nodePointer root, int total_vertex);

int main() {
	
	FILE *file;
	int total_vertex, total_edge;
	int vert1, vert2, cost;
	int i, total_cost;
	nodePointer x, y;

	file = fopen("prim.txt", "r");

	fscanf(file, "%d %d\n", &total_vertex, &total_edge);

	adjList = (nodePointer*)malloc(sizeof(nodePointer) * (total_vertex + 1));
	H = (nodePointer*)malloc(sizeof(nodePointer) * total_edge);
	size_H = total_edge;

	d = (int*)malloc(sizeof(int) * (total_vertex + 1));
	p = (int*)malloc(sizeof(int) * (total_vertex + 1));
	f = (int*)malloc(sizeof(int) * (total_vertex + 1));

	
	for (i = 1; i < total_vertex + 1; i++) {
		adjList[i] = NULL;
		d[i] = 9999;
		p[i] = -1;
		f[i] = 0;
	}
	
	for (i = 0; i < total_edge; i++) {
		H[i] = NULL;
	}


	// make adjacency list
	for (i = 0; i < total_edge; i++) {
		fscanf(file, "%d %d %d\n", &vert1, &vert2, &cost);

		x = (struct node*)malloc(sizeof(struct node));

		x->vertex = vert2;
		x->value = cost;
		x->link = NULL;


		if (adjList[vert1] == NULL)
			adjList[vert1] = x;

		else {
			for (y = adjList[vert1]; y->link != NULL; y = y->link);
			y->link = x;
		}
			
	}

	printf("============== ADJACENCY ===============\n");

	for (i = 1; i <= total_vertex; i++) {
		printf("%d : ", i);

		for (y = adjList[i]; y != NULL; y = y->link)
			printf("(%d, %d), ", y->vertex, y->value);
		printf("\n");
	}
	printf("\n\n");
	
	x = (struct node*)malloc(sizeof(struct node));
	x->vertex = 1;
	x->value = 0;

	printf("============== PRIM ===============\n");
	primA(x, total_vertex);

	printf("\n\n\n");
	
	total_cost = 0;
	for (i = 1; i <= total_vertex; i++)
		total_cost += d[i];
	
	printf("nearest : ");
	for (i = 2; i <= total_vertex; i++)
		printf("%-3d", p[i]);
	printf("\n");

	
	printf("weightÀÇ ÇÕ : %d\n", total_cost);


	for (i = 1; i <= total_vertex; i++)
		printf("%-3d", p[i]);
	printf("\n");



	printf("============== DIJKSTRA ===============\n");

	dijkA(x, total_vertex);

	for (i = 1; i <= total_vertex; i++)
		printf("%-3d", d[i]);
	printf("\n");

	for (i = 1; i <= total_vertex; i++)
		printf("%-3d", p[i]);
	printf("\n");

	return 0;
}


nodePointer Del_min(int size) {

	int parent, i;
	int left, right, choosen;
	nodePointer min;


	parent = 1;
	left = parent * 2; right = parent * 2 + 1;

	min = (struct node*) malloc(sizeof(struct node));

	min = H[1];

	choosen = 1;
	while (right < size) {

		if (H[left]->value < H[right]->value)
			choosen = left;
		else 
			choosen = right;

		H[parent] = H[choosen];
		parent = choosen;
		left = parent * 2; right = parent * 2 + 1;
	}

	H[choosen] = H[size - 1];

	return min;
}

void insert(nodePointer insert_node, int size) {

	nodePointer shiftkey;
	int i;
	int parent;

	H[size] = insert_node;

	if (insert_node->value < d[insert_node->vertex])
	{
		//d[insert_node->vertex] = insert_node->value;
		//p[insert_node->vertex] = current_node;
	}
	for (i = size; i > 0; i = i / 2) {
		parent = i / 2;

		if (H[parent] == NULL) 
			break;

		if (H[i]->value < H[parent]->value) {
			shiftkey = H[parent];
			H[parent] = H[i];
			H[i] = shiftkey;
		}

		else {
			break;
		}
	}

}


void primA(nodePointer root, int total_vertex) {

	int i;
	nodePointer u, v;

	current_H = 0;

	for (i = 1; i <= total_vertex; i++) {
		d[i] = 999;
		f[i] = 0;
	}
	d[root->vertex] = 0;
	p[root->vertex] = -1;

	insert(root, ++current_H);

	while (current_H >= 1) {
		
		for (i = 1; i <= current_H; i++)
			printf("%-3d", H[i]->value);
		printf("\n");
		
		u = Del_min((--current_H) + 2);

		if (f[u->vertex] == 0) {
			

			for (v = adjList[u->vertex]; v != NULL; v = v->link) {
				if (f[v->vertex] == 0 && v->value < d[v->vertex]) {
					p[v->vertex] = u->vertex;
					d[v->vertex] = v->value;
					insert(v, ++current_H);
				}
			}
		}
		f[u->vertex] = 1;
	}

}

void dijkA(nodePointer root, int total_vertex) {

	int i;
	nodePointer u, v;
	current_H = 0;


	for (i = 1; i <= total_vertex; i++) {
		d[i] = 999;
		f[i] = 0;
	}
	d[root->vertex] = 0;
	p[root->vertex] = -1;

	insert(root, ++current_H);

	while (current_H >= 1) {

		

		u = Del_min((--current_H) + 2);

		if (f[u->vertex] == 0) {

			for (v = adjList[u->vertex]; v != NULL; v = v->link) {
				if (f[v->vertex] == 0 && d[v->vertex] > d[u->vertex] + v->value) {
					p[v->vertex] = u->vertex;
					d[v->vertex] = d[u->vertex] + v->value;
					insert(v, ++current_H);

				}
			}
			for (i = 1; i <= current_H; i++)
				printf("%-3d", H[i]->value);
			printf("\n");

		}
		f[u->vertex] = 1;


	}

}