#include "Lists_and_Trees.h"
#include "Factors.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

struct list_node* Continued_Fraction(int x)
{
	int d = floor(sqrt(x));
	struct list_node* A = build_node(0);
	struct list_node* B = build_node(1);
	struct list_node* C = malloc(sizeof(struct list_node)); 
	C = build_node(d);

	struct list_node* temp1 = build_node(0); 
	struct list_node* temp2 = build_node(1); 
	struct list_node* temp3 = build_node(d); 

	for (int i = 1; i <= 2; i++)
	{
		temp1 = build_node((temp3->data) * (temp2->data) - (temp1->data));
		temp2 = build_node((x - ((temp1->data) * (temp1->data))) / (temp2->data));
		append(A, temp1);
		append(B, temp2);

		temp3 = (struct list_node*)malloc(sizeof(struct list_node));
		temp3 = build_node(floor((sqrt(x) + temp1->data) / (temp2->data)));
		append(C, temp3);
	} // First two terms to start off the loop; 

	while ((temp1->data != A->next->data) || (temp2->data != B->next->data) || (temp3->data != C->next->data))
	{
		temp1 = build_node((temp3->data) * (temp2->data) - (temp1->data));
		temp2 = build_node((x - ((temp1->data) * (temp1->data))) / (temp2->data));
		append(A, temp1);
		append(B, temp2);

		temp3 = malloc(sizeof(struct list_node));
		temp3 = build_node(floor((sqrt(x) + temp1->data) / (temp2->data)));
		append(C, temp3);
	}  // Loop until a repeat is found; 

	C->prev->prev->next = C;
	C->prev = C->prev->prev; 
	freelist(A); 
	freelist(B); 
	return C; 
}

int Closed_Form(struct list_node* list1)
{
	int m = list1->prev->data; 
	int a = m - list1->data;
	int n = length(list1) - 1;
	int b = list1->data;

	struct list_node* p = append(build_node(0), build_node(1));
	struct list_node* q = append(build_node(1), build_node(0));
	struct list_node* step1 = p;
	struct list_node* step2 = q;
	list1->data = 0; 
	struct list_node* step3 = list1;

	struct list_node* newnode1;
	struct list_node* newnode2;

	for (int i = 0; i < n; i++)
	{
		newnode1 = build_node((step1->next->data * step3->data) + step1->data);
		newnode2 = build_node((step2->next->data * step3->data) + step2->data);
		append(p, newnode1);
		append(q, newnode2);

		step1 = step1->next;
		step2 = step2->next;
		step3 = step3->next;
	}

	int w = p->prev->data;
	int x = ((a*p->prev->data) + p->prev->prev->data); 

	int y = q->prev->data;
	int z = ((a*q->prev->data) + q->prev->prev->data); 

	int degree2_coefficient = y;
	int degree1_coefficient = ((-1*(b * y)) + z - w);
	int constant = (- 1 * b * z) - x; 

	return(solve(degree2_coefficient, degree1_coefficient, constant));
}


void Continued_Fractions_Calculator(void)
{
	int n; 
	printf("Enter 0 if converting from Square Root to Continued Fraction or 1 for vice versa:");
	scanf_s("%d", &n);
	if (n == 0)
	{
		printf("Please enter the integer beneath the square root: \n");
		int k;
		scanf_s("%d", &k);
		print_list(Continued_Fraction(k));
	}
	else
	{
		int l; 
		printf("Please enter the integer value (non-repeating digits) of the Continued Fraction: \n");
		scanf_s("%d", &l);;
		
		int m; 
		printf("Please enter the number of repeating digits in the Continued Fraction \n");
		scanf_s("%d", &m);
		struct list_node* acc = build_node(l); 

		for (int i = 0; i < m; i++)
		{
			int x; 
			scanf_s("%d", &x);;
			struct list_node* newnode = build_node(x);
			acc = append(acc, newnode); 
		}

		Closed_Form(acc);
	}
}

int main(void)
{
	Continued_Fractions_Calculator();
} 