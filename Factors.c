#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "Lists_and_Trees.h"

struct list_node* sub_one(struct list_node* list1)
{
    list1->data = list1->data - 1;
    return list1;
}

struct list_node* add_one(struct list_node* list1)
{
    list1->data = list1->data + 1;
    return list1;
}


struct list_node* factorsof(unsigned int n)
{
    if (n == 0)
    {
        return NULL;
    }
    else
    {
        struct list_node* newnode;
        struct list_node* accumulator = NULL;

        for (int i = 1; i <= (n / 2); i++)
        {
            if ((n % i) == 0)
            {
                newnode = (struct list_node*)malloc(sizeof(struct list_node));
                newnode->data = i;
                newnode->next = newnode;
                newnode->prev = newnode;

                accumulator = append(accumulator, newnode);
            }
            else
            {
                NULL;
            }
        }
        newnode = build_node(n);

        accumulator = append(accumulator, newnode);

        return accumulator;
    }
}

int findfirstfactor(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        int p = 0;

        for (int i = 2; i <= sqrt(n) && (p == 0); i++)
        {
            if ((n % i) == 0)
            {
                p = i;
            }
            else
            {
                NULL;
            }
        }

        if (p == 0)
        {
            return n;
        }
        else
        {
            return p;
        }
    }
}

int myPow(int x, int n)
{
    int number = 1;

    for (int i = 0; i < n; ++i)
        number *= x;

    return(number);
}

int findfirstfactorpower(int n)
{
    int p;
    int power = 0;

    p = findfirstfactor(n);

    while ((n % p) == 0)
    {
        power = power + 1;
        n = (n / p);
    }
    return myPow(p, power);
}

struct list_node* primefact(int n)
{
    if (n == 0)
    {
        return build_node(0);
    }
    else
    {

        struct list_node* accumulator = NULL;
        struct list_node* newnode;
        int p = 1;
        if (n == 1)
        {
            return build_node(1);
        }
        else
        {
            while (n != 1)
            {
                p = findfirstfactor(n);
                newnode = (struct list_node*)calloc(1, sizeof(struct list_node));
                newnode->data = p;
                newnode->next = newnode;
                newnode->prev = newnode;

                accumulator = append(accumulator, newnode);

                n = (n / p);
            }

            return accumulator;
        }
    }
}

int phi(int n)
{
    struct list_node* primefactors = remove_duplicates(primefact(n));
    int p = listproduct(primefactors);
    struct list_node* newlist = map(sub_one, primefactors);
    int m = listproduct(newlist);

    return ((n / p) * m);
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
	else if (step->data == step->next->data)
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
		else if (n != 0 && m == 0)
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
