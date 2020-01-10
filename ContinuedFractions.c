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

struct list_node* reduce_sqrt(int x)
{
	struct list_node* list1 = primefact(x); 
	int acc = 1;
	int acc2 = 1; 
	struct list_node* step = list1;  

	while ((step->next != list1) && (step->next->next != list1))
	{
		if (step->data == step->next->data)
		{
			acc = acc * step->data;
			step = step->next->next;
		}
		else
		{
			acc2 = acc2 * step->data;
			step = step->next;
		}
	}

	if (step->next == list1)
	{
		acc2 = acc2 * step->data; 
	}
	else if(step->data == step->next->data)
	{
		acc = acc * step->data; 
	}
	else
	{
		acc2 = acc2 * step->data * step->next->data; 
	}

	freelist(list1);
	struct list_node* a = build_node(acc); 
	struct list_node* b = build_node(acc2);
	return append(a, b);
}

struct list_node* reduce(int n, int m)
{
	if (n == 0 || m == 0)
	{
		if (n == 0 && m != 0)
		{
			return append(append(build_node(0), build_node(1)), build_node(m));
		}
		else if(n != 0 && m == 0)
		{
			return append(append(build_node(1), build_node(0)), build_node(n));
		}
		else
		{
			return append(append(build_node(n), build_node(m)), build_node(0));
		}
	}
	else
	{
		struct list_node* fact1 = primefact(n);
		struct list_node* fact2 = primefact(m);
		struct list_node* step1 = fact1;
		struct list_node* step2 = fact2;
		int x = 1;
		int y = 1;
		int z = 1;

		if (step1->data < step2->data)
		{
			x = x * step1->data;
			step1 = step1->next;
		}
		else if (step1->data > step2->data)
		{
			y = y * step2->data;
			step2 = step2->next;
		}
		else
		{
			step1 = step1->next;
			step2 = step2->next;
			z = z * step1->data;
		}

		while ((step1 != fact1) && (step2 != fact2))
		{
			if (step1->data < step2->data)
			{
				x = x * step1->data;
				step1 = step1->next;
			}
			else if (step1->data > step2->data)
			{
				y = y * step2->data;
				step2 = step2->next;
			}
			else
			{
				step1 = step1->next;
				step2 = step2->next;
				z = z * step1->data;
			}
		}

		if (step1 == fact1)
		{
			while (step2 != fact2)
			{
				y = y * step2->data;
				step2 = step2->next;
			}
		}
		else
		{
			while (step1 != fact1)
			{
				x = x * step1->data;
				step1 = step1->next;
			}
		}

		struct list_node* a = build_node(x);
		struct list_node* b = build_node(y);
		struct list_node* c = build_node(z);

		freelist(fact1);
		freelist(fact2);

		return append(append(a, b), c);
	}
}

struct list_node* solve(int a, int b, int c)
{
	int z = -b; 
	int y = (b * b) - (4 * a * c);
	int x = 2 * a;
	struct list_node* f = reduce_sqrt(y);
	struct list_node* g = reduce(f->data, z);
	struct list_node* h = reduce(g->prev->data, x); 
	int denominator = h->next->data; 
	int square_root = f->next->data;
	int sqrt_coefficient = g->data * h->data;

	int int_numerator = h->data * g->next->data; 
	struct list_node* full_sqrt = append(build_node(sqrt_coefficient), build_node(square_root)); 

	printf("(%d +/- %d(sqrt(%d))) / %d \n", int_numerator, sqrt_coefficient, square_root, denominator);

	return append(append(build_node(int_numerator), full_sqrt), build_node(denominator));
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

int main(void)
{
	Closed_Form(Continued_Fraction(29));
} 