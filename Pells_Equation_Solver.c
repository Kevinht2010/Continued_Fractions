#include "Lists_and_Trees.h"
#include "Factors.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

int Pells_Solver(int x)
{
	int d = floor(sqrt(x));
	struct list_node* A = build_node(0);
	struct list_node* B = build_node(1);
	struct list_node* C = malloc(sizeof(struct list_node));
	C = build_node(d);

	struct list_node* temp1 = build_node(0);
	struct list_node* temp2 = build_node(1);
	struct list_node* temp3 = build_node(d);

	struct list_node* p = append(build_node(0), build_node(1));
	struct list_node* q = append(build_node(1), build_node(0));

	struct list_node* newnode1 = build_node(0);
	struct list_node* newnode2 = build_node(0);
	struct list_node* step1 = p;
	struct list_node* step2 = q;

	int n = -1;
	int m = -1;

	newnode1 = build_node((step1->next->data * temp3->data) + step1->data);
	newnode2 = build_node((step2->next->data * temp3->data) + step2->data);
	append(p, newnode1);
	append(q, newnode2);

	step1 = step1->next;
	step2 = step2->next;

	while (n < 0 && m < 0)
	{
		if ((newnode1->data * newnode1->data) - x * (newnode2->data * newnode2->data) == 1 && (newnode1->data > 1 || newnode2->data > 1))
		{
			n = newnode1->data;
			m = newnode2->data;
		}
		else
		{
			temp1 = build_node((temp3->data) * (temp2->data) - (temp1->data));
			temp2 = build_node((x - ((temp1->data) * (temp1->data))) / (temp2->data));
			append(A, temp1);
			append(B, temp2);

			temp3 = build_node(floor((sqrt(x) + temp1->data) / (temp2->data)));
			append(C, temp3);

			newnode1 = build_node((step1->next->data * temp3->data) + step1->data);
			newnode2 = build_node((step2->next->data * temp3->data) + step2->data);
			append(p, newnode1);
			append(q, newnode2);

			step1 = step1->next;
			step2 = step2->next;
		}
	}

	printf("The fundamnetal solutions are x = %d and y = %d", n, m);
}

void Pells_Equation_Solver(void)
{
	int a;

	printf("Please enter the non-square prime defining your Pells Equation:");

	scanf_s("%d", &a);

	Pells_Solver(a);
}

int main(void)
{
	Pells_Equation_Solver();
}

