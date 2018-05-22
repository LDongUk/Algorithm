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
	while( (idx*2) < n) //leaf의 parent를 찾아간다. 만약 보는곳이 넘친다면 brother로감
	{
		if(player[ tree[idx] ] >= in)
			idx *= 2;
		else
			idx = (idx/2)*2 + 1;  //만약 가르치는 값이 over하면 brother에 찾아간다. #39에 input 6인상황
	}

	
	//구한 leaf	= tree[idx]
	if(player[ tree[idx] ] < in) //내가 현재 보는 곳이 넘친다면   #p36상황
	{
		if(idx % 2 == 0)
			idx++; //tree의 brother를 본다.
		else
			idx--;  //tree의 brother를 본다. 근데 이 경우는 없다. 짝수로 들어온상황에서 이미 왼쪽부분은 안된다고 확정됨.
	}
	
	if( tree[idx] % 2 == 1 ) //leaf가 홀수 == 왼쪽이다.
		player[ tree[idx] ] -= in;
	else
	{
		if( player[ tree[idx]-1 ] >= in) //leaf가 오른쪽꺼일때는 왼쪽꺼에 들어갈수있는지 본다
			player[ tree[idx]-1 ] -= in;
		else
			player[ tree[idx] ] -= in;
	}


	//update
	if( (tree[idx] % 2) == 1) //홀수
	{
		if( player[tree[idx]] < player[tree[idx]+1] ) //left < right
		{
			big = tree[idx]+1; //brother 중 더 큰걸 선택..같을때는 왼쪽선택
		}
		else
			big = tree[idx];
	}
	else
	{
		if( player[tree[idx]-1] < player[tree[idx]] ) //left < right
		{
			big = tree[idx]; //brother 중 더 큰걸 선택..같을때는 왼쪽선택
		}
		else
			big = tree[idx]-1;
	}

	parent = (tree[idx] + n - 1)/2; //우리가 보는거의 parent를 갱신
	tree[parent] = big; 

	while(parent != 1)
	{
		if(parent % 2 == 0) //현재보는 parent는 왼쪽
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
	
	fscanf(f,"%d %d %d",&bin_size,&item_size,&leaf_size); //가방크기, 아이템수, leaf노드수

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