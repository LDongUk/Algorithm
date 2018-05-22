#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *bin;
int *tree;


void makeTree(int num_bin);
void insertBin(int item, int num_bin);

int main() {
	FILE *f;

	int num_bin, num_input, capa;
	int index;
	int i;
	int item;

	f = fopen("input2.txt", "r");
	fscanf(f, "%d %d %d\n", &num_bin, &num_input, &capa);

	//init bins
	bin = (int*)malloc(sizeof(int) * (num_bin + 1));

	for (i = 1; i < num_bin + 1; i++)
		bin[i] = capa;

	//make tree;
	tree = (int*)malloc(sizeof(int) * num_bin);

	makeTree(num_bin);
	
	for (i = 0; i < num_input; i++) {
		fscanf(f, "%d\n", &item);
		insertBin(item, num_bin);
	}

	return 0;
}



void makeTree(int num_bin) {

	int parent;
	int left, right;
	int bin_left, bin_right;
	int i, num_level;

	//init
	for (i = 1; i < num_bin + 1; i += 2) {
		parent = (num_bin - 1 + i) / 2;

		if (bin[i] >= bin[i + 1]) {
			tree[parent] = i;
		}

		else {
			tree[parent] = i + 1;
		}

	}

	left = num_bin / 2;
	right = (num_bin / 2) + 1;
	
	num_level = num_bin;
	for (parent = left / 2; parent != 0; parent = left / 2) {
		
		bin_left = tree[left]; bin_right = tree[right];
		
		while (right < num_level)
		{
			if (bin[bin_left] >= bin[bin_right])
				tree[parent] = bin_left;

			else
				tree[parent] = bin_right;

			left += 2;
			right += 2;
			parent = left / 2;
			bin_left = tree[left]; bin_right = tree[right];
			
		}

		num_level /= 2;
		left = num_level / 2;
		right = (num_level / 2) + 1;

	}

	printf("init tree : ");
	for (i = 1; i < num_bin; i++)
		printf("%-2d", tree[i]);
	printf("\n");

}

void insertBin(int item, int num_bin) {
	
	int parent, left, right;
	int selected;
	int index;
	int i;
	int bin_left, bin_right;

	left = 2; right = 3;
	for (parent = 1; parent < num_bin; parent = selected) {
		
		index = tree[parent];
				
		if (bin[index] >= item){
			selected = left;
			left = parent * 2;
		}
		else {
			selected = right;
			left = selected * 2;
		}
		right = left + 1;

	}

	
	bin[index] -= item;
	//rebuild tree
	if (index % 2 == 1) {
		bin_left = index;
		bin_right = bin_left + 1;
	}

	else {
		bin_right = index;
		bin_left = bin_right - 1;
	}
	parent = (num_bin - 1 + index) / 2;


	if (bin[bin_left] >= bin[bin_right]) {
		tree[parent] = bin_left;
	}

	else {
		tree[parent] = bin_right;
	}

	for (parent /= 2; parent != 0; parent /= 2) {
		left = parent * 2;
		right = left + 1;
		
		bin_left = tree[left];
		bin_right = tree[right];

		if (bin[bin_left] >= bin[bin_right]) {
			tree[parent] = bin_left;
		}

		else {
			tree[parent] = bin_right;
		}
	}

	printf("\n");
	printf("insert %d\n", item);
	printf("bin : ");
	for (i = 1; i < num_bin + 1; i++)
		printf("%-3d", bin[i]);
	printf("\n");
	
	printf("tree : ");
	for (i = 1; i < num_bin; i++)
		printf("%-2d", tree[i]);
	printf("\n");


}