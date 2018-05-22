#include<stdio.h>
#include<stdlib.h>


int *player,*tree;

void init_tree(int n, int bin_size)  //init_tree(leaf_size,bin_size);
{
	int k,p;

	for (k=1; k<=n; k = k+2) 
	{  
		p = (k + n - 1 )/2;
		tree[p] = k;
	}

	for (k = (n-1)/2; k > 0; k--) 
		tree[k] = tree[k * 2];

	for(k=1;k<=n;k++)
		player[k] = bin_size;
}

void winner(int in,int n)
{
	int root,idx,big,parent;

	idx = 1;

	//insert
	while( (idx*2) < n) //leaf�� parent�� ã�ư���. ���� ���°��� ��ģ�ٸ� brother�ΰ�
	{
		if(player[ tree[idx] ] >= in)
			idx *= 2;
		else
			idx = (idx/2)*2 + 1;  //���� ����ġ�� ���� over�ϸ� brother�� ã�ư���. #39�� input 6�λ�Ȳ
	}

	
	//���� leaf	= tree[idx]
	if(player[ tree[idx] ] < in) //���� ���� ���� ���� ��ģ�ٸ�   #p36��Ȳ
	{
		if(idx % 2 == 0)
			idx++; //tree�� brother�� ����.
		else
			idx--;  //tree�� brother�� ����. �ٵ� �� ���� ����. ¦���� ���»�Ȳ���� �̹� ���ʺκ��� �ȵȴٰ� Ȯ����.
	}
	
	if( tree[idx] % 2 == 1 ) //leaf�� Ȧ�� == �����̴�.
		player[ tree[idx] ] -= in;
	else
	{
		if( player[ tree[idx]-1 ] >= in) //leaf�� �����ʲ��϶��� ���ʲ��� �����ִ��� ����
			player[ tree[idx]-1 ] -= in;
		else
			player[ tree[idx] ] -= in;
	}


	//update
	if( (tree[idx] % 2) == 1) //Ȧ��
	{
		if( player[tree[idx]] < player[tree[idx]+1] ) //left < right
		{
			big = tree[idx]+1; //brother �� �� ū�� ����..�������� ���ʼ���
		}
		else
			big = tree[idx];
	}
	else
	{
		if( player[tree[idx]-1] < player[tree[idx]] ) //left < right
		{
			big = tree[idx]; //brother �� �� ū�� ����..�������� ���ʼ���
		}
		else
			big = tree[idx]-1;
	}

	parent = (tree[idx] + n - 1)/2; //�츮�� ���°��� parent�� ����
	tree[parent] = big; 

	while(parent != 1)
	{
		if(parent % 2 == 0) //���纸�� parent�� ����
		{
			if(player[ tree[parent] ] < player[ tree[parent+1] ]) //left < right
				tree[parent/2] = tree[parent+1];
			else
				tree[parent/2] = tree[parent];
		}
		else
		{
			if(player[ tree[parent-1] ] < player[ tree[parent] ]) //left < right
				tree[parent/2] = tree[parent];
			else
				tree[parent/2] = tree[parent-1];
		}
		parent /= 2; 
	}
}

void print_tree(int n)
{
	int i;
	for(i=1;i<n;i++)
		printf("%d ",tree[i]);
	printf("\nplayer\n");

	for(i=1;i<=n;i++)
		printf("%d ",player[i]);
	printf("\n\n");
}

int main()
{
	FILE* f;
	char input[50];
	int bin_size,item_size,leaf_size,in;
	printf("input : ");
	scanf("%s",input);
	f=fopen(input,"r");
	
	fscanf(f,"%d %d %d",&bin_size,&item_size,&leaf_size); //����ũ��, �����ۼ�, leaf����

	player = (int*)malloc(sizeof(int)*(leaf_size+1)); //1~n
	tree = (int*)malloc(sizeof(int)*(leaf_size)); //1~n-1

	init_tree(leaf_size,bin_size);

	while(!feof(f))
	{
		fscanf(f,"%d",&in);
		winner(in,leaf_size);

		print_tree(leaf_size);
	}

	//system("pause");
}