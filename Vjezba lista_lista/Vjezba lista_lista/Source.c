#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LENGHT 128
#define FIRST_IS_BIGGER 1
#define SECOND_IS_BIGGER 3
#define DATES_EQUAL 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _racun;
struct _proizvod;

typedef struct _racun* racunP;
typedef struct _proizvod* proizvodP;

typedef struct _racun {
	int year;
	int month;
	int day;
	proizvodP first_proizvod;
	racunP next;
}racun;

typedef struct _proizvod {
	char name[MAX_STRING_LENGHT];
	int price;
	int quantity;
	proizvodP next;
}proizvod;

int read_from_file_racuni(racunP);
racunP create_racun(int, int, int);
int read_from_file_proizvodi(racunP, char*);
int insert_sorted_racun(racunP, racunP);
int compare_racun(racunP, racunP);
proizvodP create_proizvod(char*, int quantity, int price);
int insert_proizvod(proizvodP, proizvodP);
racunP compare_new_to_all(racunP, racunP);
int print_racuni(racunP);
int print_proizvodi(proizvodP);
int query(racunP);
int delete_proizvod(proizvodP);
int delete_racuni(racunP);


int main() {

	racun head = { .year = 0, .month = 0, .day = 0, .first_proizvod = NULL, .next = NULL };

	read_from_file_racuni(&head);
	print_racuni(&head);
	query(&head);
	delete_racuni(&head);
	return EXIT_SUCCESS;
}

int query(racunP head) {
	racunP current = head;
	racunP new, searched = NULL;

	char date[MAX_STRING_LENGHT] = { 0 };
	char proizvod_name[MAX_STRING_LENGHT] = { 0 };
	int year, month, day = 0;
	printf("\nUnesite datum(year-month-day) od kada zelite racun: ");
	scanf(" %s", date);
	printf("\nunesite artikl koji vas zanima :");
	scanf("%s", proizvod_name);
	sscanf(date, "%d-%d-%d", &year, &month, &day);
	new = create_racun(year, month, day);

	searched = compare_new_to_all(head, new);
	if (searched == NULL) {
		printf("\nneam racuna s tim datumom");
		return EXIT_FAILURE;
	}
	else
	{
		proizvodP current_1 = searched->first_proizvod;
		while (current_1->next != NULL && strcmp(current_1->next->name, proizvod_name) != 0) {
			current_1 = current_1->next;
		}
		if (current_1->next == NULL) {
			printf("\nneam ga");
		}
		else {
			printf("\nProdano je %d %s u ukuponoj cijeni od %d", current_1->next->quantity, current_1->next->name, current_1->next->price * current_1->next->quantity);
		}
	}

	free(new);
	return EXIT_SUCCESS;
}

int read_from_file_racuni(racunP head) {
	char filename[MAX_STRING_LENGHT] = { 0 };
	FILE* fp = NULL;

	fp = fopen("racuni.txt", "r");
	if (fp == NULL) {
		printf("can't open file racuni");
		return EXIT_FAILURE;
	}
	while (fscanf(fp, " %s", filename) != EOF) {

		read_from_file_proizvodi(head, filename);

	}
	fclose(fp);

	return EXIT_SUCCESS;
}

racunP create_racun(int year, int month, int day) {
	racunP new = NULL;
	new = (racunP)malloc(sizeof(racun));
	if (new == NULL) {
		printf("memory allocation fail");
		return NULL;
	}
	new->year = year;
	new->day = day;
	new->month = month;
	new->next = NULL;
	new->first_proizvod = NULL;


	return new;
}

int read_from_file_proizvodi(racunP head, char* filename) {

	FILE* fp = NULL;
	int year, month, day, quantity, price;
	char proizvod_name[MAX_STRING_LENGHT] = { 0 };
	racunP new_racun, is_same_to = NULL;
	proizvodP new_proizvod = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("can't find file");
		return EXIT_FAILURE;
	}
	fscanf(fp, " %d-%d-%d", &year, &month, &day);
	new_racun = create_racun(year, month, day);

	new_racun->first_proizvod = create_proizvod("head", 0, 0);
	is_same_to = compare_new_to_all(head, new_racun);

	while (fscanf(fp, " %s %d %d", proizvod_name, &quantity, &price) != EOF)
	{
		new_proizvod = create_proizvod(proizvod_name, quantity, price);

		if (is_same_to != NULL) {

			insert_proizvod(is_same_to->first_proizvod, new_proizvod);

		}
		else {

			insert_proizvod(new_racun->first_proizvod, new_proizvod);

		}
	}
	if (is_same_to != NULL) {
		free(new_racun->first_proizvod);
		free(new_racun);
	}
	else {
		insert_sorted_racun(head, new_racun);
	}

	return EXIT_SUCCESS;
}

int insert_sorted_racun(racunP head, racunP new) {
	racunP current = head;
	while (current->next != NULL)
	{
		if (compare_racun(current->next, new) == FIRST_IS_BIGGER) {
			new->next = current->next;
			current->next = new;
			return EXIT_SUCCESS;
		}
		current = current->next;
	}
	current->next = new;

	return EXIT_SUCCESS;
}

int compare_racun(racunP racun1, racunP racun2) {
	if (racun1->year > racun2->year) {
		return FIRST_IS_BIGGER;
	}
	else if (racun1->year < racun2->year) {
		return SECOND_IS_BIGGER;
	}
	if (racun1->month > racun2->month) {
		return FIRST_IS_BIGGER;
	}
	else if (racun1->month < racun2->month) {
		return SECOND_IS_BIGGER;
	}
	if (racun1->day > racun2->day) {
		return FIRST_IS_BIGGER;
	}
	else if (racun1->day < racun2->day) {
		return SECOND_IS_BIGGER;
	}
	else
	{ 
		return DATES_EQUAL;
	}
}

proizvodP create_proizvod(char* name, int quantity, int price) {
	proizvodP new = NULL;
	new = (proizvodP)malloc(sizeof(proizvod));
	if (new == NULL) {
		printf("memory allocation fail");
		return NULL;
	}
	strcpy(new->name, name);
	new->price = price;
	new->quantity = quantity;
	new->next = NULL;
	return new;
}

racunP compare_new_to_all(racunP head, racunP new_racun) {
	racunP	current = head;
	while (current->next != NULL) {
		if (compare_racun(current->next, new_racun) == DATES_EQUAL) {
			return current->next;
		}
		current = current->next;
	}
	return NULL;
}

int insert_proizvod(proizvodP head, proizvodP new) {
	proizvodP current = head;

	while (current->next != NULL) {
		if (strcmp(current->next->name, new->name) == 0) {
			current->next->quantity = current->next->quantity + new->quantity;
			free(new);
			return EXIT_SUCCESS;
		}
		else if (strcmp(current->next->name, new->name) > 0) {
			new->next = current->next;
			current->next = new;
			return EXIT_SUCCESS;
		}
		current = current->next;
	}
	current->next = new;
	return EXIT_SUCCESS;
}

int print_racuni(racunP head) {
	racunP current = head;
	while (current->next != NULL) {
		printf("\nRacun %d-%d-%d", current->next->year, current->next->month, current->next->day);
		print_proizvodi(current->next->first_proizvod);
		current = current->next;
	}
	return EXIT_SUCCESS;
}
int print_proizvodi(proizvodP head) {
	proizvodP current = head;
	while (current->next != NULL) {
		printf("\nProizvod : %s kolicina : %d cijena %d", current->next->name, current->next->quantity, current->next->price);
		current = current->next;
	}
	return EXIT_SUCCESS;
}

int delete_racuni(racunP head) {
	racunP current = head->next;
	racunP temp = NULL;
	while (current != NULL) {
		temp = current;
		printf("\nbrisemo : %d-%d-%d", temp->year, temp->month, temp->day);
		delete_proizvod(current->first_proizvod);
		current = current->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}
int delete_proizvod(proizvodP head) {
	proizvodP current = head;
	proizvodP temp = NULL;
	while (current != NULL) {
		temp = current;
		current = current->next;
		printf("\nbrisemo: %s", temp->name);
		free(temp);
	}
	return EXIT_SUCCESS;
}