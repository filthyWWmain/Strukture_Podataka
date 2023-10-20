//2. Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

//kad dodaje element na kraj a lista je prazna 
//kad ide bristali element a taj element je prvi
//kad input u menu funkciji broj ili string umisto char puca
// za delete brise samo prvoga po ton prezimenu i ne  porvjerava ime i date_of_birth


#define Prolaz_predmeta true
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 128
#define FILE_NOT_OPENED -1
#define bool int
#define false 0
#define true 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

struct _person;
typedef struct _person* personP;
typedef struct _person {
	char firstname[MAX_LENGTH];
	char lastname[MAX_LENGTH];
	int date_of_birth;
	personP next;
}person;


char* input_firstname() {

	char firstname[MAX_LENGTH] = { 0 };
	printf("\n\tinput firstname:  ");
	scanf(" %s", firstname);

	return firstname;
}

char* input_lastname() {

	char lastname[MAX_LENGTH] = { 0 };
	printf("\n\tinput lastname:  ");
	scanf(" %s", lastname);

	return lastname;
}

int input_date_of_birth() {

	int date_of_birth = 0 ;
	printf("\n\tinput date_of_birth:  ");
	scanf(" %d", &date_of_birth);

	return date_of_birth;
}


personP create_node() {

	personP q = NULL;

	q = (personP)malloc(sizeof(person));
	if (!q) {
		perror("\tCan't allocate memory");
		return NULL;
	}
	strcpy(q->firstname, input_firstname());
	strcpy(q->lastname, input_lastname());
	q->date_of_birth = input_date_of_birth();

	q->next = NULL;
	return q;

}


personP Input_first(personP head, personP q) {
	if (head == NULL)
		return q;
	else {
		q->next = head;
		return q;
	}
}

// prints all values of elements in list
int print_all_elements(personP head) {
	printf("\n*********************************************************\n\n");
	printf("\t list :\n");

	
	while (head != NULL) {
		printf("\n\t");
		printf(" %s %s %d ", head->firstname, head->lastname, head->date_of_birth);
		head = head->next;
	}
	
	
	printf("\n\n*********************************************************\n");
	return 0;
}

//stavlja na zadnje misto novog clana
personP input_last(personP head, personP q) {
	if (head) {
		while (head->next != NULL) {
			head = head->next;
		}
		head->next = q;
	}
	else {
		return q;
	}
	return head;
}

int find_by_lastname(personP head) {

	char lastname[MAX_LENGTH] = { 0 };

	strcpy(lastname, input_lastname());

	while (strcmp(head->lastname, lastname) != 0) {
		if (head->next == NULL) {

			printf("\n\tNo person with that last name");
			return 0;
		}

		head = head->next;
	}
	printf("\n*********************************************************\n\n");
	printf(" Person found : %s \t %s \t %s", head->firstname, head->lastname, head->date_of_birth);
	printf("\n\n*********************************************************\n");
	return 0;
}

//trazi element i onda ga obrise
personP delete_person(personP head) {

	personP temp = head;
	personP prev_temp = NULL;//pokazuje na clana ispred clana temp u listi, da moremo izbrisati clan temp
	char firstname[MAX_LENGTH] = { 0 };
	char lastname[MAX_LENGTH] = { 0 };
	int date_of_birth = 0 ;
	bool is_first = true;

	strcpy(firstname, input_firstname());
	strcpy(lastname, input_lastname());
	date_of_birth = input_date_of_birth();

	while (temp && strcmp(temp->firstname, firstname) != 0 && strcmp(temp->lastname, lastname) != 0 && temp->date_of_birth == date_of_birth) {

		is_first = false;
		prev_temp = temp;
		temp = temp->next;

	}
	if (temp && strcmp(temp->firstname, firstname) == 0 && strcmp(temp->lastname, lastname) == 0 && temp->date_of_birth == date_of_birth) {
		printf("\n*********************************************************\n\n");
		printf("\n\t Deleting: %s %s %d \n", temp->firstname, temp->lastname, temp->date_of_birth);
		if (is_first == true) {
			temp = head->next;
			free(head);
			return temp;
		}
		else {
			prev_temp->next = temp->next;
			free(temp);
		}
	}
	else {
		printf("\n\tList does't have that person");
	}

	return head;
}

//dealocira cilu list
int free_the_memory(personP head) {

	personP to_delete = NULL;
	while (head) {

		to_delete = head;
		head = head->next;

		printf("\n\tDeleting : %s %s %d", to_delete->firstname, to_delete->lastname, to_delete->date_of_birth);
		free(to_delete);
	}
}

int menu(personP head) {
	char input[MAX_LENGTH] = { 0 };
	int answer = 0;
	char garbage_colection[1024] = { 0 };
	while (answer != 1) {
		printf("\n*********************************************************\n");
		printf("\n\tKill program (1) \n");
		printf("\tInput person at the start of list (2) \n");
		printf("\tPrint all (3) \n");
		printf("\tInput person at the end of list(4) \n");
		printf("\tSearch_by_lastname (5) \n");
		printf("\tDelete a person from the list (6) \n");
		printf("\n*********************************************************\n");

		printf("\n\tInput: ");
		scanf(" %[^\n]s", input);
		// provjera eli unesen broj a ne char
		if (isdigit(input[0]) == 0 || input[0] - '0' < 1 || input[0] - '0' > 6) {
			printf("\n*********************************************************\n\n");
			printf("\tInvalid Input,try again\n");

			//scanf(" %s", garbage_colection);

		}
		else {

			answer = input[0] - '0'; // pretvara char u int

			if (answer == 2) {
				head = Input_first(head, create_node());
			}
			else if (answer == 3) {
				if (!head) {
					printf("\n\tNothing to see here, listi is empty\n");
				}
				else {
					print_all_elements(head);
				}
				
			}
			else if (answer == 4) {
				head = input_last(head, create_node());
			}
			else if (answer == 5) {
				if (!head) {
					printf("\n\tNothing to search here, listi is empty\n");
				}
				else {
					find_by_lastname(head);
				}
			}
			else if (answer == 6) {
				if (!head) {
					printf("\n\tNothing to delete here, listi is empty\n");
				}
				else {
					head = delete_person(head);
				}

			}
		}

	}

	free_the_memory(head);

	printf("\n \n \n**************************************\n \n");
	printf("\tProgram killed");
	printf("\n \n \n**************************************\n \n");


	return 0;
}

int main() {
	char* name[MAX_LENGTH] = { 0 };
	personP head = NULL;

	menu(head);


	return 0;
}