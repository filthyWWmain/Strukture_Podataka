#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_LINE 1024
#define MAX_SIZE 50
#define FILE_NOT_OPEN -1
#define FAILED_MEMORY_ALLOCATION NULL
#define EMPTY_LISTS -2


#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coefficient;
	int exponent;
	Position next;
} Polinom;

int read_from_file(Position, Position, char*);
int print_all(char*, Position);
int addPoly1(Position, Position, Position);
int multiplyPoly(Position, Position, Position);
int Delete_all(Position);
int Create_list_from_buffer(Position, char*);
Position Create_node(int, int);
int insertSorted(Position, Position);
int input_in_list_after_poly(Position, Position);
int insertAfter(Position, Position);
int deleteAfter(Position);
int createAndInsertAfter(int, int, Position);



int main() {
	Polinom head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polinom head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polinom head_add = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polinom head_Multiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char* fileName = "polynomes.txt";

	if (read_from_file(&head1, &head2, fileName) == EXIT_SUCCESS) {
		print_all("First : ", head1.next);
		print_all("Second : ", head2.next);

		addPoly1(&head_add, head1.next, head2.next);
		multiplyPoly(&head_Multiply, head1.next, head2.next);

		print_all("Added polynomes: ", head_add.next);
		print_all("Multiplied polynomes: ", head_Multiply.next);

		Delete_all(&head1);
		Delete_all(&head2);
		Delete_all(&head_add);
		Delete_all(&head_Multiply);


	}

	return EXIT_SUCCESS;
}

int print_all(char * list_name, Position first) {
	Position current = first;
	printf("\nLista %s :",list_name);
	while (current != NULL) {
		printf("%dX^%d ", current->coefficient, current->exponent);
		current = current->next;
	}
	printf("\n\n");
	return EXIT_SUCCESS;
}

int read_from_file(Position head1, Position head2, char* fileName) {
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen(fileName, "r");
	if (!filePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = Create_list_from_buffer(head1, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = Create_list_from_buffer(head2, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int addPoly1(Position resultHead, Position first_in_list_1, Position first_in_list_2) {
	Position current_1 = first_in_list_1;
	Position current_2 = first_in_list_2;
	Position currentResult = resultHead;
	Position remainingPoly = NULL;


	while (current_1 != NULL && current_2 != NULL) {
		if (current_1->exponent == current_2->exponent) {
			createAndInsertAfter(current_1->coefficient + current_2->coefficient, current_1->exponent, currentResult);
			current_1 = current_1->next;
			current_2 = current_2->next;
			currentResult = currentResult->next;
		}
		else if (current_1->exponent < current_2->exponent) {
			createAndInsertAfter(current_1->coefficient, current_1->exponent, currentResult);
			current_1 = current_1->next;
			currentResult = currentResult->next;
		}
		else {
			createAndInsertAfter(current_2->coefficient, current_2->exponent, currentResult);
			current_2 = current_2->next;
			currentResult = currentResult->next;
		}

	}
	if (current_1 == NULL) {
		remainingPoly = current_2;
	}
	else {
		remainingPoly = current_1;
	}
	while (remainingPoly != NULL) {
		createAndInsertAfter(remainingPoly->coefficient, remainingPoly->exponent, currentResult);
		remainingPoly = remainingPoly->next;
		currentResult = currentResult->next;
	}

	return EXIT_SUCCESS;
}

// dvi for petle di sve svaki sa svakin mnozi dok jedna ili obe ne dodu do kraja i onda se doda na kraj multiply_liste ako je ostalo sto u listi polynoma 
int multiplyPoly(Position resultHead, Position first_in_list_1, Position first_in_list_2)
{
	if (first_in_list_1 == NULL || first_in_list_2 == NULL)
		return EMPTY_LISTS;
	for (Position current_1 = first_in_list_1; current_1 != NULL; current_1 = current_1->next) {
		for (Position current_2 = first_in_list_2; current_2 != NULL; current_2 = current_2->next) {
			Position newPolinom = Create_node(current_1->coefficient * current_2->coefficient, current_1->exponent + current_2->exponent);
			if (!newPolinom) {
				return EXIT_FAILURE;
			}

			insertSorted(resultHead, newPolinom);
		}
	}
	return EXIT_SUCCESS;

}

int Delete_all(Position head)
{
	Position current = head;

	while (current->next) {
		deleteAfter(current);
	}

	return EXIT_SUCCESS;
}

int Create_list_from_buffer(Position head, char* buffer)
{
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newPolinom = NULL;

	while (strlen(currentBuffer) > 0) {
		status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);
		if (status != 2) {
			printf("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newPolinom = Create_node(coefficient, exponent);
		if (!newPolinom) {
			return EXIT_FAILURE;
		}

		insertSorted(head, newPolinom);

		
		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}

Position Create_node(int coefficient, int exponent) {
	Position Polinom = NULL;

	Polinom = (Position)malloc(sizeof(Polinom));
	if (Polinom == NULL) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	Polinom->coefficient = coefficient;
	Polinom->exponent = exponent;
	Polinom->next = NULL;

	return Polinom;
}
//
int insertSorted(Position head, Position newPolinom) {
	Position current = head;

	while (current->next != NULL && current->next->exponent > newPolinom->exponent) {
		current = current->next;
	}

	input_in_list_after_poly(current, newPolinom);

	return EXIT_SUCCESS;
}
// prvo provjeri exponent ako su razliciti stavi novog u listu ako su isti zbroji koeficijente i provjeri da zbroj ni nula
int input_in_list_after_poly(Position current, Position newPolinom) {
	if (current->next == NULL || current->next->exponent != newPolinom->exponent) {
		insertAfter(current, newPolinom);
	}
	else {
		int resultCoefficient = current->next->coefficient + newPolinom->coefficient;
		if (resultCoefficient == 0)
		{
			deleteAfter(current);
		}
		else
		{
			current->next->coefficient = resultCoefficient;
		}
		free(newPolinom);
	}

	return EXIT_SUCCESS;
}

int insertAfter(Position current, Position newPolinom) {
	newPolinom->next = current->next;
	current->next = newPolinom;

	return EXIT_SUCCESS;
}

int deleteAfter(Position previous) {
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int createAndInsertAfter(int coefficient, int exponent, Position current) {
	Position newPolinom = Create_node(coefficient, exponent);
	if (!newPolinom) {
		return EXIT_FAILURE;
	}

	insertAfter(current, newPolinom);

	return EXIT_SUCCESS;
}