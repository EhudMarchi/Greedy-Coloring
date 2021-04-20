#include<stdio.h>
typedef struct interval
{
	int num,start,end,degree,color;
	int* Edges;
}Interval;

void GreedyColoring();
void addEdge(Interval, Interval);
int partition(Interval *, int, int);
void quick_sort(Interval *, int, int);
void swap(Interval*, Interval*);
void main()
{
	GreedyColoring();
}

void GreedyColoring()
{
	int i,j, amount,last=1, MaxDegree=0, MinDegree = 0,Edges=0, Chrom=1;
	printf("Please input amount:\n");
	scanf_s("%d", &amount);
	Interval* list = (Interval*)malloc(amount * sizeof(Interval));
	printf("Please enter %d intervals (start - end)\n", amount);
	for (i = 0; i < amount; i++)//Fill the list
	{
		list[i].num = i;
		scanf_s("%d", &((list + i)->start));
		scanf_s("%d", &((list + i)->end));
		list[i].degree = 0;
		list[i].Edges = (int*)calloc(amount, sizeof(int));
		list[i].color = 1;

	}
	printf("The intervals family is:\n");
	for (i = 0; i < amount; i++)//Prints the intervals family
	{
		printf("[%d , %d]", (list + i)->start, (list + i)->end);
		if (i != amount - 1)
			printf(" , ");
	}
	quick_sort(list, 0, amount-1);//Order list by start time (ascending)
	printf("\nOrdered by start list:\n");
	for (i = 0; i < amount; i++)//Prints the intervals family
	{
		printf("[%d , %d]", (list + i)->start, (list + i)->end);
		if (i != amount - 1)
			printf(" , ");
	}

	//----------------------------------------------------------
	for (i = 0; i < amount; i++)//coloring loop
	{
		last = 1;
		for (j = 0; j < i; j++)
		{
			if (((list[i].end) < (list[j].start)) || (list[j].end < list[i].start))
			{
				continue;
			}
			else
			{
				addEdge(list[i], list[j]);
				Edges++;
				list[i].degree++;
				list[j].degree++;
				last++;
				if (list[i].color == list[j].color)
					list[i].color = last;
			}
		}
	}
	for (i = 0; i < amount; i++)
	{
		if (list[i].degree <= MinDegree)
			MinDegree = list[i].degree;
		if (list[i].degree >= MaxDegree)
			MaxDegree = list[i].degree;
		if (list[i].color >= Chrom)
			Chrom = list[i].color;
	}
	//----------------------------------------------------
	printf("\nG Edges: %d\nChromatic Number Of G:%d\nMax Degree: %d\nMin Degree: %d\nG Complement Edges: %d\nMax Degree Of G Complement: %d\nMin Degree Of G Complement: %d\n", Edges,Chrom,MaxDegree,MinDegree,(amount*(amount-1)/2)-Edges,amount-1-MinDegree,amount-1-MaxDegree);
	for (i = 0; i < amount; i++)
	{
		printf("\n [%d,%d]:", list[i].start,list[i].end);
		printf(" degree :%d", list[i].degree);
		printf(" color :'%d'", list[i].color);
		printf("\n[");
		for (j = 0; j < amount; j++)
		{
			printf("%d ", list[i].Edges[j]);
		}
		printf("]\n");
		free(list[i].Edges);
	}
	printf("Optional coloring:\n");
	for (j = 1; j <= Chrom; j++)
	{
		printf("Color '%d' : ", j);
		printf("{");
		for (i = 0; i < amount; i++)
		{
			if (list[i].color == j)
				printf("[%d , %d]", (list + i)->start, (list + i)->end);
		}
		printf("}");
		printf("\n");
	}
	free(list);
}
void addEdge(Interval u, Interval v)
{
	if ((u.Edges[v.num]) == 0 && (v.Edges[u.num] == 0))
	{
		u.Edges[v.num] = 1;
		v.Edges[u.num] = 1;
	}
}
void swap(Interval* a, Interval* b)
{
	Interval temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int partition(Interval *family, int left, int right)
{
	int first = left;
	Interval pivot = family[first];
	int pos;
	while (left < right)
	{
		while (family[right].start > pivot.start) right--;
		while ((left < right) && (family[left].start <= pivot.start)) left++;
		if (left < right)
			swap(family + left, family + right);
	}
	pos = right;
	family[first] = family[pos];
	family[pos] = pivot;
	return pos;
}
void quick_sort(Interval *family, int first, int last)
{
	int pos;
	if (first < last)
	{
		pos = partition(family, first, last);
		quick_sort(family, first, pos - 1);
		quick_sort(family, pos + 1, last);
	}
}