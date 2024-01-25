//10. Napisati program koji èita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država.Uz
//ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
//države.Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
//broj_stanovnika.
//a) Potrebno je formirati sortiranu vezanu listu država po nazivu.Svaki èvor vezane liste
//sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
//b) Potrebno je formirati stablo država sortirano po nazivu.Svaki èvor stabla sadrži vezanu
//listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
//Nakon formiranja podataka potrebno je ispisati države i gradove te omoguæiti korisniku putem
//tastature pretragu gradova odreðene države koji imaju broj stanovnika veæi od unosa na
//tastatur

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGHT 128
#define FIRST_IS_BIGGER 1
#define SECOND_IS_BIGGER 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _city;

typedef struct _city* cityP;
typedef struct _city {
	char name[MAX_LENGHT];
	int population;
	cityP next;
}city;

struct _country;
typedef struct _country* countryP;
typedef struct _country {
	char name[MAX_LENGHT];
	countryP left;
	countryP right;
	cityP first_city;
}country;

countryP create_country(char*);
cityP create_city(char*, int);
int read_city_file(cityP, char*);
cityP insert_city_sorted(cityP, cityP);
int compare_city(cityP first, cityP second);
countryP insert_country(countryP, countryP);
int print_city(cityP, int);
countryP print_country(countryP);
int querry(countryP);
countryP search_country(countryP, char*);

int main() {
	countryP root = NULL;
	char countryname[MAX_LENGHT] = { 0 };
	char filename[MAX_LENGHT] = { 0 };
	countryP new_country = NULL;

	FILE* fp = NULL;
	fp = fopen("drzave.txt", "r");
	if (fp == NULL) {
		printf("can't open file");
		return EXIT_FAILURE;
	}
	while (fscanf(fp, " %s , %s", countryname, filename) != EOF) {
		new_country = create_country(countryname);
		
		read_city_file(new_country->first_city, filename);
		root = insert_country(root, new_country);
		printf("\nInsert country in main root (%s) new (%s), country city : %s", root->name, new_country->name,new_country->first_city->name);
	}

	print_country(root);

	return 0;
}

countryP insert_country(countryP root, countryP new_country) {
	
	if (root == NULL) {
	
		return new_country;
	}
	if (strcmp(new_country->name,root->name) < 0 ) {
		root->left = insert_country(root->left, new_country);
	}
	if (strcmp(new_country->name,root->name) > 0) {

		root->right = insert_country(root->right, new_country);
		
	}
	return root;
}

countryP create_country(char* country_name) {

	countryP new_country = NULL;
	new_country = (countryP)malloc(sizeof(country));
	if (new_country == NULL) {
		printf("malloc fail");
		return NULL;
	}

	strcpy(new_country->name, country_name);
	new_country->left = NULL;
	new_country->right = NULL;
	new_country->first_city = NULL;

	return new_country;
}
int read_city_file(cityP head, char* filename) {

	FILE* fp = NULL;
	int population = 0;
	char city_name[MAX_LENGHT] = { 0 };
	cityP new_city = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\ncan't read file");
		return EXIT_FAILURE;
	}
	while (fscanf(fp, " %s , %d", city_name, &population) != EOF) {
		new_city = create_city(city_name, population);
		printf("\n novi city je %s",new_city->name);
		head = insert_city_sorted(head, new_city);
		printf("\nhead je :%s", head->name);
	}
	return EXIT_SUCCESS;

}

cityP create_city(char* city_name, int population) {
	cityP new_city = NULL;

	new_city = (cityP)malloc(sizeof(city));

	if (new_city == NULL) {
		printf("Malloc fail");
		return NULL;
	}
	new_city->population = population;
	strcpy(new_city->name, city_name);
	new_city->next = NULL;

	return new_city;

}

cityP insert_city_sorted(cityP head, cityP new_city) {
	cityP current = head;
	if (head == NULL) {
		
		return new_city;
	}
	if (head->next == NULL) {
		if (compare_city(head, new_city) == SECOND_IS_BIGGER) {
			
			new_city->next = head;
			return head;
		}
	}
	while (current->next != NULL && compare_city(current->next, new_city) == FIRST_IS_BIGGER) {
		current = current->next;
	}
	if (current->next == NULL) {
		
		current->next = new_city;
	}
	else if (compare_city(current->next, new_city) == SECOND_IS_BIGGER) {
		
		new_city->next = current->next;
		current->next = new_city;
	}
	return head;
}

int compare_city(cityP first, cityP second) {
	if (first->population == second->population) {
		if (strcmp(first->name, second->name) < 0) {
			return FIRST_IS_BIGGER;
		}
		else {
			return SECOND_IS_BIGGER;
		}

	}
	else {
		if (first->population > second->population) {
			return FIRST_IS_BIGGER;
		}
		else {
			return SECOND_IS_BIGGER;
		}
	}
}

countryP print_country(countryP root) {
	if (root->left != NULL) {
		print_country(root->left);
	}
	printf("\nCountry name: %s ", root->name);
	print_city(root->first_city, 0);

	if (root->right != NULL) {
		print_country(root->right);
	}
	return root;
}
int print_city(cityP head, int population) {
	printf("\nusli");
	printf("\nhead je : %s",head->name );
	cityP current = head;
	while (current != NULL) {
		printf("\nusli2");
		if (current->population > population) {
			printf("\nCity: %s woth population %d ", current->name, current->population);
		}
	}
	return EXIT_SUCCESS;
}
int querry(countryP root) {
	int popualtion = 0;
	countryP searched_country = NULL;
	char country_name[MAX_LENGHT] = { 0 }; 

	printf("\nunesite ime drzave:");
	scanf("%s", country_name);

	searched_country = search_country(root, country_name);
	if (searched_country == NULL) {
		printf("\ncountry can't be found");
	}
	else {
		printf("\nUnesite minimalni broj stanovnika nekog grada: ");
		scanf("%d", &popualtion);

		print_city(searched_country->first_city, popualtion);
	}
	return 0;
}
countryP search_country(countryP root, char* searched_country_name) {
	if (strcmp(root->name, searched_country_name) == 0) {
		return root;
	}
	if (root->left != NULL) {
		search_country(root->left, searched_country_name);
	}
	if (root->right != NULL) {
		search_country(root->right, searched_country_name);
	}
	return NULL;
}