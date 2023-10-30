#define Prolaz_predmeta true
#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED -1
#define MAX_BUFFER 1024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _polinom;
typedef struct _polinom* polinomP;
typedef struct _polinom {
	
	int exponent;
	int coefficient;
	polinomP next;
}polinom;

int read_from_file(polinomP);
polinomP insert_sorted(polinomP, polinomP);

int main() {

	polinom head = { .coefficient = 0, .exponent = 0, .next = NULL };
	return 0;
}

int read_from_file(polinomP head) {
	int coefficient = 0;
	int exponent = 0;
	char buffer[MAX_BUFFER] = {0};
	FILE* fp = NULL;
	fp = fopen("input.txt","r");
	if (fp == NULL) {
		return FILE_NOT_OPENED;
	}
	fgets(buffer, MAX_BUFFER, fp);

	
	fclose(fp);
}
polinomP create_node(int coefficient,int exponent) {

	polinomP q = NULL;

	q = (polinomP)malloc(sizeof(polinom));
	if (!q) {
		perror("\tCan't allocate memory");
		return NULL;
	}

	q->coefficient = coefficient;
	q->exponent = exponent;
	q->next = NULL;
	return q;

}

polinomP insert_sorted(polinomP head, polinomP new_node) {
	polinomP current = head;
	polinomP before_current = NULL;
	while (current && current->exponent > new_node) {
		before_current = current;
		current = current->next;
	}
	input_after()
}