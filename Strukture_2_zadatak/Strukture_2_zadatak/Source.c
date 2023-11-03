//2. Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

//zna crshati nako read from file kad idemo neku funkciju poslje

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
#include <ctype.h>
#include <math.h>

struct _person;
typedef struct _person* personP;
typedef struct _person {
	char firstname[MAX_LENGTH];
	char lastname[MAX_LENGTH];
	int date_of_birth;
	personP next;
}person;

char* input_firstname();
char* input_lastname();
int input_date_of_birth();
personP create_node();
personP Input_first(personP, personP);
int print_all_elements(personP);
personP input_last(personP, personP);
int find_by_lastname(personP);
personP delete_person(personP);
int free_the_memory(personP);
int menu(personP);
int add_after_somebody(persoP);
personP add_before_somebody(personP);
personP create_node_from_file(char*, char*, int);// isto ko create_node osim sto prima izlaze sa scanf-a
// stavlja u listu osobe koje su procitane iz datoteke
personP read_from_file(personP);
int print_in_file(personP);

int main() {
	char* name[MAX_LENGTH] = { 0 };
	personP head = NULL;

	menu(head);

	return 0;
}

char* input_firstname() {

	char firstname[MAX_LENGTH] = { 0 };
	printf("\n\tInput firstname:  ");
	scanf(" %s", firstname);

	return firstname;
}

char* input_lastname() {

	char lastname[MAX_LENGTH] = { 0 };
	printf("\n\tInput lastname:  ");
	scanf(" %s", lastname);

	return lastname;
}
// inputa se uzima kao string pa se onda provjerava eli unos dobar da program ne puca kad se krivo nesto ne unese
int input_date_of_birth() {
	char input[MAX_LENGTH] = { 0 };
	int date_of_birth = 0 ;
	bool is_input_ok = false;
	int br_pokusaja = 0;

	while (is_input_ok != true && br_pokusaja < 3) {
		printf("\n\tInput year_of_birth: ");
		scanf(" %s", input);
		br_pokusaja = br_pokusaja + 1;
		date_of_birth = 0;
		for (int i = 0; i < strlen(input); i++) {
			if (isdigit(input[i]) != 0) {
				date_of_birth = date_of_birth + pow(10, strlen(input)-1 - i) * (input[i] - '0');

				is_input_ok = true;//stavi da je true svaki put i onda ako je i nakon 4. puta true znaci da su svi uneseni znakovi brojevi
			}
			else {
				is_input_ok = false;
				printf("\n\tInput must be a number between 1900 and 2023\n");
				break;
			}
			if ((date_of_birth < 1900 || date_of_birth > 2023) && i == (strlen(input)-1)) {
				printf("\n\tInput must be a number between 1900 and 2023\n");
				is_input_ok = false;
			}
		
		}
	}
	if(br_pokusaja == 3 && is_input_ok == false){
		printf("\n\tSmotan si ko sajla. Staviti cu ti da si 2000. godiste\n");
		date_of_birth = 2000;
	}
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
	personP current = head;
	if (current) {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = q;
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
	printf(" Person found : %s \t %s \t %d", head->firstname, head->lastname, head->date_of_birth);
	printf("\n\n*********************************************************\n");
	return 0;
}

//trazi element i onda ga obrise
personP delete_person(personP head) {

	personP temp = head;
	personP prev_temp = NULL;//pokazuje na clana ispred clana temp u listi, da moremo izbrisati clan temp
	char firstname[MAX_LENGTH] = { 0 };
	char lastname[MAX_LENGTH] = { 0 };
	int date_of_birth = 0;
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
	return EXIT_SUCCESS;
}

// 3.zad - nastavak na drugi 

int add_after_somebody(personP head) {

	char to_find_lastname[MAX_LENGTH] = { 0 };
	personP temp = NULL;
	printf("\n\tInput lastname of the person you are looking for:");
	strcpy(to_find_lastname, input_lastname());

	while (strcmp(head->lastname, to_find_lastname) != 0) {
		if (head->next == NULL) {

			printf("\n\tNo person with that last name");
			return 0;
		}

		head = head->next;
	}
	temp = create_node();
	temp->next = head->next;
	head->next = temp;

	return EXIT_SUCCESS;
}
personP add_before_somebody(personP head) {
	personP before_current = NULL;
	personP current = head;
	char to_find_lastname[MAX_LENGTH] = { 0 };
	personP temp = NULL;

	printf("\n\tInput lastname of the person you are looking for:");
	strcpy(to_find_lastname, input_lastname());

	while (strcmp(current->lastname, to_find_lastname) != 0) {
		if (current->next == NULL) {

			printf("\n\tNo person with that last name");
			return 0;
		}
		before_current = current;
		current = current->next;
	}
	temp = create_node();
	temp->next = current;// stavlja da je poslje tempa current, ako nema clana isprid njega onda vracamo temp jer je to novi head
	if (before_current == NULL) {
		return temp;
	}
	//inace stavljamo da je temp nakon current_before
	else {
		before_current->next = temp;
		return head;
	}
}


personP read_from_file(personP head) {

	char firstname[MAX_LENGTH] = { 0 };
	char lastname[MAX_LENGTH] = { 0 };
	int year_of_birth = 0;
	FILE* fp = NULL;
	//int test  =0;
	fp = fopen("filename.txt", "r");
	if (fp == NULL) {
		return FILE_NOT_OPENED;
	}
	//while (test != EOF) {
	//	test = fscanf(fp, " %s %s %d", firstname, lastname, &year_of_birth);
	//	head = Input_first(head, create_node_from_file(firstname, lastname, year_of_birth));
	// more i ovako provjera EOF je int;

	while (fscanf(fp," %s %s %d", firstname, lastname, &year_of_birth) != EOF) {
		head = Input_first(head, create_node_from_file(firstname, lastname, year_of_birth));
	}
	fclose(fp);

	return head;
}

personP create_node_from_file(char* firstname, char* lastname, int date_of_birth) {
	personP q = NULL;
	q = (personP)malloc(sizeof(personP));
	if (!q) {
		perror("\tCan't allocate memory");
		return NULL;
	}
	strcpy(q->firstname, firstname);
	strcpy(q->lastname, lastname);
	q->date_of_birth = date_of_birth;
	q->next = NULL;
	return q;
}

int print_in_file(personP head) {
	
	personP current = head;
	FILE* fp = NULL;
	fp = fopen("printedlist.txt", "w");
	if (fp == NULL) {
		return FILE_NOT_OPENED;
	}
	while (current) {
		fprintf(fp," %s %s %d\n",current->firstname,current->lastname,current->date_of_birth);
		current = current->next;
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int menu(personP head) {
	char input[MAX_LENGTH] = { 0 };
	int answer = 10;
	char garbage_colection[1024] = { 0 };
	while (answer != 0) {
		printf("\n*********************************************************\n");
		printf("\n\tKill program (0) \n");
		printf("\tInput person at the start of list (1) \n");
		printf("\tPrint all (2) \n");
		printf("\tInput person at the end of list(3) \n");
		printf("\tSearch_by_lastname (4) \n");
		printf("\tDelete a person from the list (5) \n");
		printf("\tAdd new person after someone (6) \n");
		printf("\tAdd new person before someone (7) \n");
		printf("\tAdd new people from a file (8) \n");
		printf("\tPrint list in a file(9) \n");
		printf("\n*********************************************************\n");

		printf("\n\tInput: ");
		scanf(" %[^\n]s", input);
		// provjera eli unesen broj a ne char
		if (isdigit(input[0]) == 0 || input[0] - '0' < 0 || input[0] - '0' > 9) {
			printf("\n*********************************************************\n\n");
			printf("\tInvalid Input,try again\n");

		}
		else {

			answer = input[0] - '0'; // pretvara char u int

			if (answer == 1) {
				head = Input_first(head, create_node());
			}
			else if (answer == 2) {
				if (!head) {
					printf("\n\tNothing to see here, listi is empty\n");
				}
				else {
					print_all_elements(head);
				}
				
			}
			else if (answer == 3) {
				head = input_last(head, create_node());
			}
			else if (answer == 4) {
				if (!head) {
					printf("\n\tNothing to search here, listi is empty\n");
				}
				else {
					find_by_lastname(head);
				}
			}
			else if (answer == 5) {
				if (!head) {
					printf("\n\tNothing to delete here, listi is empty\n");
				}
				else {
					head = delete_person(head);
				}

			}
			else if(answer == 6) {
				if (!head) {
					printf("\n\tYou can't add after somebody if the list is empty!\n");
				}
				else {
					add_after_somebody(head);
				}
				
			}
			else if (answer == 7) {
				if (!head) {
					printf("\n\tYou can't add before somebody if the list is empty!\n");
				}
				else {
					head= add_before_somebody(head);
				}

			}
			else if (answer == 8) {
				head = read_from_file(head);
			}
			else if (answer == 9) {
				print_in_file(head);
			}

		}

	}

	//free_the_memory(head);

	printf("\n \n \n**************************************\n \n");
	printf("\tProgram killed");
	printf("\n \n \n**************************************\n \n");


	return 0;
}
