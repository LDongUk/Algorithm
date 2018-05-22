#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef struct node *nodePointer;

struct node {
	int vertex;
	int capacity;
	int flow;
	nodePointer link;

};

int *visit, *p;

void init_visit_parent(int total_vertex);
void BFS(nodePointer *adj, int total_vertex);
void Set_max_flow(nodePointer *adj, int total_vertex);


int main()
{
	FILE *f, *e, *out;
	int total_vertex, total_edge;
	int i, j;
	int vert1, vert2, cap;
	int max_flow;
	int isPath = 0;
	nodePointer *adj;
	nodePointer x, y;

	int n;
	int *verties;
	int node;
	int current_node, under_node;
	int edge_count = 0;
	int input_count = 0;

	e = fopen("escape_input6.txt", "r");
	fscanf(e, "%d\n", &n);
	verties = (int *)malloc(sizeof(int) * n);

	out = fopen("escape.txt", "w+");
	

	for (i = 1; i < n + 1; i++) {
		for (j = 1; j < n + 1; j++) {
			fscanf(e, "%1d", &node);
			current_node = 2 * (n * (i - 1) + j) - 1;
			if (node == 1) {
				fprintf(out, "0 %d 1\n", current_node);
				input_count++;
				edge_count++;
			}
		}
	}

	for (i = 1; i < n + 1; i++) {
		for (j = 1; j < n + 1; j++) {
			current_node = 2 * (n * (i - 1) + j) - 1;
			fprintf(out, "%d %d 1\n", current_node, current_node + 1);
			edge_count++;
			if (j != n) {
				fprintf(out, "%d %d 1\n", current_node + 1, current_node + 2);
				fprintf(out, "%d %d 1\n", current_node + 3, current_node);
				edge_count += 2;
			}
			under_node = current_node + (2 * n);

			if (under_node < 2 *  n * n)
			{
				fprintf(out, "%d %d 1\n", current_node + 1, under_node);
				fprintf(out, "%d %d 1\n", under_node + 1, current_node);
				edge_count += 2;
			}
			if (i == 1 || i == n || j == 1 || j == n)
			{
				fprintf(out, "%d %d 1\n", current_node + 1, 2 * n * n + 1);
				edge_count++;
			}
		}
	}
	



	fclose(out);




	f = fopen("escape.txt", "r");

	//fscanf(f, "%d %d\n", &total_vertex, &total_edge);
	total_vertex = 2 * n * n;
	total_edge = edge_count;
	total_vertex += 2;

	//인접행렬 생성 및 초기화
	adj = (nodePointer*)malloc(sizeof(nodePointer) * total_vertex );
	for (i = 0; i < total_vertex + 1; i++)
	{
		adj[i] = (struct node*)malloc(sizeof(struct node));
		adj[i] = NULL;
	}

	//visit, parent초기화
	visit = (int*)malloc(sizeof(int) * total_vertex );
	p = (int*)malloc(sizeof(int) * total_vertex );


	//insert
	for (i = 0; i < total_edge; i++) {
		x = (struct node*)malloc(sizeof(struct node));
		fscanf(f, "%d %d %d\n", &vert1, &vert2, &cap);
		vert1; vert2;

		x->vertex = vert2;
		x->flow = 0;
		x->capacity = cap;
		x->link = NULL;

		if (adj[vert1] == NULL)
			adj[vert1] = x;

		else {
			for (y = adj[vert1]; y->link != NULL; y = y->link);
			y->link = x;

		}


	}


	while (1)
	{
		BFS(adj, total_vertex - 1);

		if (p[total_vertex - 1] == -1)
			break;

		Set_max_flow(adj, total_vertex - 1);

	}


	max_flow = 0;
	for (y = adj[0]; y != NULL; y = y->link)
		max_flow += y->flow;
	printf("Start flow is %d\n", input_count);
	printf("max_flow is %d\n", max_flow);

	return 0;
}

















void init_visit_parent(int total_vertex) {
	int i;

	for (i = 0; i < total_vertex + 1; i++)
	{
		visit[i] = 0;
		p[i] = -1;
	}
}




void BFS(nodePointer *adj, int total_vertex) {

	nodePointer u, v;
	nodePointer x, rearQ, frontQ;
	nodePointer temp;
	int pre;

	frontQ = (struct node*) malloc(sizeof(struct node));

	init_visit_parent(total_vertex);

	//시작점 0
	frontQ = (struct node*) malloc(sizeof(struct node));
	frontQ->vertex = 0;
	frontQ->link = NULL;

	pre = frontQ->vertex;

	rearQ = frontQ;

	u = adj[frontQ->vertex];
	while (frontQ != NULL)
	{

		for (v = u; v != NULL; v = v->link) {
			if (visit[v->vertex] == 0 && v->flow < v->capacity) {
				visit[v->vertex] = 1;
				p[v->vertex] = pre;

				x = (struct node*) malloc(sizeof(struct node));
				x->vertex = v->vertex;
				x->link = NULL;


				rearQ->link = x;
				rearQ = rearQ->link;


			}

		}



		temp = frontQ;
		frontQ = frontQ->link;
		free(temp);
		visit[pre] = 1;

		if (frontQ != NULL)
		{
			if (adj[frontQ->vertex] == NULL) continue;
			u = adj[frontQ->vertex];

			pre = frontQ->vertex;
			if (visit[u->vertex] == 0)
				p[u->vertex] = pre;
		}

	}


}

void Set_max_flow(nodePointer *adj, int total_vertex) {
	int min_flow;
	int find_path;
	int pre_vertex;
	int cap;
	nodePointer y, pre_node;

	min_flow = 9999;
	for (find_path = total_vertex; find_path != -1; find_path = p[find_path]) {
		pre_vertex = p[find_path];

		if (pre_vertex == -1) {
			break;
		}



		for (y = adj[pre_vertex]; y != NULL; y = y->link) {

			if (y->vertex == find_path) {

				for (pre_node = adj[find_path]; pre_node != NULL; pre_node = pre_node->link) {

					if (pre_node->vertex == pre_vertex) {
						break;
					}
				}

				if (pre_node != NULL)
					cap = (y->capacity - y->flow) + pre_node->flow;
				else {
					cap = (y->capacity - y->flow);
				}

				if (min_flow >= cap)
					min_flow = cap;
			}
		}

	}

	for (find_path = total_vertex; find_path != -1; find_path = p[find_path]) {
		pre_vertex = p[find_path];

		if (pre_vertex == -1) {
			break;
		}

		for (y = adj[pre_vertex]; y != NULL; y = y->link) {

			if (y->vertex == find_path) {

				for (pre_node = adj[find_path]; pre_node != NULL; pre_node = pre_node->link) {

					if (pre_node->vertex == pre_vertex) {
						break;
					}
				}

				if (pre_node != NULL) {
					if (min_flow > pre_node->flow) {
						y->flow += min_flow - pre_node->flow;
						pre_node->flow = 0;
					}

					else {
						pre_node -= min_flow;
					}

				}

				else
					y->flow += min_flow;
			}
		}

	}

}

