//Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
//rezultat. Stog je potrebno realizirati preko vezane liste.

#define bool prolaz_predmeta 1
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 128
#define FILE_NOT_OPENED -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EMPTY_LIST 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _NUMBER;
typedef struct _NUMBER* Position;
typedef struct _NUMBER {
	double number;
	Position next;
}number;

int create_and_push(Position, double);
int calculate_result(Position, char, double*);
int insert_first(Position, Position);
int read_from_file(Position, double*);
int stog_function(Position, double*, char*);
int Pop(Position);
int print_list(Position);
int free_the_memory(Position);

int main() {

	double result = 0.0;
	number head = { .number = 0, .next = NULL};

	read_from_file(&head, &result);

	printf("\n\n Rezultat je : %d", result);
	if (free_the_memory(head.next) == EXIT_SUCCESS) {
		printf("Memory successfully deallocated");
	}

	return 0;
}


int create_and_push(Position head, double number) {
	Position new_node = (Position)malloc(sizeof(number));
	if (new_node == NULL) {
		printf(" memory allocation fail");
		return EXIT_FAILURE;
	}
	else{
		new_node->number = number;
		new_node->next = NULL;
		if (insert_first(head, new_node) == 0) {
			return EXIT_SUCCESS;
		}
		else {
			return EXIT_FAILURE;
		}
	}


}

int insert_first(Position head, Position new_node) {
	new_node->next = head->next;
	head->next = new_node;
	return EXIT_SUCCESS;

}

int read_from_file(Position head, double* result) {

	char buffer[MAX_LENGTH] = { 0 };
	FILE fp = NULL;
	fp = fopen("filename.txt", "r");
	fgets(fp, buffer, MAX_LENGTH);

	fclose(fp);

	if (stog_function(head, &result, buffer) == EXIT_SUCCESS) {
		printf("stog_function fail");
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}
// reads the buffer and does pop push and delete 
int stog_function(Position head, double* result, char *buffer) {

	char* current_buffer = buffer;
	double input_number,result_for_new_node  = 0.0;
	char input_character = '/0';
	int size_of_memory_read = 0;


	while (strlen(current_buffer) > 0) {
		if (sscanf(current_buffer, "%ls %n", &input_number, &size_of_memory_read) == 1) {

			create_and_push(head, input_number);
		}
		else {
			sscanf(current_buffer, "%c %n", &input_character, &size_of_memory_read);
			if (calculate_result(head,&input_character,&result_for_new_node) == EXIT_SUCCESS) {
				if (Pop(head) || Pop(head) == EMPTY_LIST) {
					printf("Stack empty or has only one number");
					return EXIT_FAILURE;
				}
				else {
					create_and_push(head, result_for_new_node);
				}
			}				

		}
		current_buffer += size_of_memory_read;
		print_list(head->next);

	}


}

int calculate_result(Position head, char operation, double* result) {

	if (head->next == NULL || head->next->next == NULL) {
		printf(" pop and delet fail to many opereators not enough numbers");
		return EXIT_FAILURE;
	}

	double number_one_in_list = head->next->number;
	double number_two_in_list = head->next->next->number;

	switch (operation) {
		case'+':
			*result = number_two_in_list + number_one_in_list;
		case'-':
			*result = number_two_in_list - number_one_in_list;
		case '*':
			*result = number_two_in_list * number_one_in_list;
		case '/':
			*result = number_two_in_list / number_one_in_list;
	}
	return EXIT_SUCCESS;
}


int Pop(Position head) {
	if (head->next == NULL) {
		return EMPTY_LIST;
	}
	else {
		Position to_delet = head->next;
		head->next = to_delet->next;
		free(to_delet);
		return EXIT_SUCCESS;
	}
}

int print_list(Position first) {
	Position current = first;
	if (current == NULL) {
		printf("Empty list");
	}
	else {
		printf("\n\n Current stog:");
		while (current != NULL) {
			printf("%f", current->number);
		}
	}
	
	return EXIT_SUCCESS;
}

int free_the_memory(Position first) {
	Position Temp = NULL;
	Position current = first;
	while (current != NULL) {
		Temp = current;
		current = current->next;
		free(Temp);
	}
	return EXIT_SUCCESS;
}