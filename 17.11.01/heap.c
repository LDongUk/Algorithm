#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

void makeheap(int *H, int n);
void siftdown(int *H, int i, int size);
void heapsort(int *H, int n);
void removeKeys(int *H, int n);
int root(int *H, int heapsize);
void insert(int *H, int insert_num, int size);
void Del_min(int *H, int size);
void print(int *heap, int total_num);
int *S;

int main() {

	FILE *f;
	int i;
	int total_num;
	int *heap;
	int num;

	f = fopen("heap.txt", "r");

	fscanf(f, "%d\n", &total_num);
	total_num++;
	heap = (int *)malloc(sizeof(int) * total_num);
	S = (int *)malloc(sizeof(int) * total_num);
	for (i = 1; i < total_num; i++) {
		fscanf(f, "%d\n", &num);
		heap[i] = num;
	}
	
	fclose(f);

	print(heap, total_num);
	free(heap);

	return 0;

}

void makeheap(int *H, int n){

	int i;

	for (i = n / 2; i > 0; i--)
		siftdown(H, i, n);

}


void siftdown(int *H, int i, int size)
{
	int siftkey;
	int parent;
	int found;
	int largerchild;

	siftkey = H[i];	parent = i;	found = false;
	while((2 * parent <= size) && (!found)) {

		if((2 * parent < size) && (H[2 * parent] > H[2 * parent + 1]))
			largerchild = 2 * parent + 1;
		
		else 
			largerchild = 2 * parent;
		
		if (siftkey > H[largerchild]) {
			H[parent] = H[largerchild];
			parent = largerchild;
		}
		else found = true;
	}

	H[parent] = siftkey;
}


int root(int *H, int heapsize)
{                         
	int keyout;

	keyout = H[1];
	//H[1] = H[heapsize];
	heapsize = heapsize - 1;
	siftdown(H, 1, heapsize);
	
	return keyout;
}

void removeKeys(int *H, int n)
{
	int i;
	
	for (i = n; i > 0; i--)
		S[n - i + 1] = root(H, i);
	
	//for i = n down to 1 do
	//	S[i] = root(H);  //heapsort
}

void heapsort(int *H, int n)
{
	makeheap(H, n);
	removeKeys(H, n);
}


void insert(int *H, int insert_num, int size) {

	int shiftkey, i;
	int parent;

	realloc(H, sizeof(int) * (size + 1));

	H[size] = insert_num;
	

	for (i = size; i > 0; i = i / 2) {
		parent = i / 2;

		if (H[i] < H[parent]) {
			shiftkey = H[parent];
			H[parent] = H[i];
			H[i] = shiftkey;
		}

		else {
			break;
		}
	}

}


void Del_min(int *H, int size) {
	
	int parent;
	int left, right, choosen;
	int *s;

	s = (int *)malloc(sizeof(int) * (size));

	parent = 1;
	left = parent * 2; right = parent * 2 + 1;

	while(right < size) {
		
		if (H[left] < H[right])
			choosen = left;
		else
			choosen = right;

		H[parent] = H[choosen];
		parent = choosen;
		left = parent * 2; right = parent * 2 + 1;
	}

	H[choosen] = H[size - 1];


	realloc(H, sizeof(int) * (size - 1));
}


void print(int *heap, int total_num) {
	int i;

	makeheap(heap, total_num - 1);

	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (make heap) \n");


	heapsort(heap, total_num - 1);

	for (i = 1; i < total_num; i++)
		printf("%3d", S[i]);
	printf("  (heap sort) \n");

	insert(heap, 50, total_num++);
	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (insert 50) \n");


	Del_min(heap, total_num--);
	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (delete min) \n");

	insert(heap, 11, total_num++);
	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (insert 11) \n");


	insert(heap, 1, total_num++);
	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (insert 1) \n");

	Del_min(heap, total_num--);
	for (i = 1; i < total_num; i++)
		printf("%3d", heap[i]);
	printf("  (delete min) \n");

}
