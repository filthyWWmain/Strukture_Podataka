//10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država.Uz
//ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
//države.Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
//broj_stanovnika.
//a) Potrebno je formirati sortiranu vezanu listu država po nazivu.Svaki čvor vezane liste
//sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
//b) Potrebno je formirati stablo država sortirano po nazivu.Svaki čvor stabla sadrži vezanu
//listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
//Nakon formiranja podataka potrebno je ispisati države i gradove te omogućiti korisniku putem
//tastature pretragu gradova određene države koji imaju broj stanovnika veći od unosa na
//tastatur

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGHT 128
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define FIRST_IS_BIGGER 1
#define SECOND_IS_BIGGER 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _city;

typedef struct _city* cityP;

typedef struct _city {
    int population;
    char* name[MAX_LENGHT];
    cityP left;
    cityP right;
} city;

struct _country;
typedef struct _country* countryP;

typedef struct _country {
	char* name[MAX_LENGHT];
    cityP first_city;
	countryP next;
}country;

int readcountry(country*);
countryP create_country(countryP, char*);
cityP read_city(cityP, char* );
cityP create_city ( char*, int);
cityP insert_sorted_city(cityP, cityP);
int compare_city( cityP, cityP);
int insert_country(countryP, countryP);
int print_country(countryP);
cityP print_city(cityP, int);
int query(countryP);

int main() {

    country head = { .name = {0}, .next = NULL, .first_city = { .population = 0, .name = {0}, .left = NULL, .right = NULL } };
    char* country_name = { 0 };
    readcountry(&head);

    print_country(head.next);
    
    query(head.next);

    return 0;
}

int readcountry(country *head){
    FILE* fp = NULL;
    char* countryname[MAX_LENGHT] = { 0 };
    char* filename[MAX_LENGHT] = { 0 };
    
    fp = fopen("drzave.txt", "r");
    if(fp == NULL){
        return EXIT_FAILURE;
    }
    while(fscanf(fp," %s, %s", countryname, filename ) != EOF) {
        countryP new_country = create_country(head, countryname);
        new_country->first_city = read_city(new_country->first_city, filename);
        insert_country(head, new_country);

    }
    return 0;
}

countryP create_country(countryP head, char* name) {
    countryP new_country = NULL;
    new_country = (countryP)malloc(sizeof(country));
    if (new_country == NULL) {
        printf("malloc fault");
        return EXIT_FAILURE;
    }
    strcpy(new_country->name, name);
    new_country->first_city = NULL;
    new_country->next = NULL;

    return  new_country;
}

cityP read_city(cityP root, char* filename) {

    FILE fp = NULL;
    char* city_name[MAX_LENGHT] = { 0 };
    int population = 0;

    fp = fopen("filename", "r");
    if (fp == NULL) {
        printf("file not found!_city");
        return EXIT_FAILURE;
    }

    while (fscanf(fp, "%s, %d ", city_name , &population ) != EOF) {
        cityP new_city = create_city(city_name, population);
        root = insert_sorted_city(root,new_city);
    }


    return root;
}

cityP create_city(char* city_name, int population) {

    cityP new_city = NULL;

    new_city = (cityP)malloc(sizeof(city));

    strcpy(new_city->name, city_name);
    new_city->population = population;
    new_city->left = NULL;
    new_city->right = NULL;

    return new_city;
}

cityP insert_sorted_city(cityP root, cityP new_city) {
    if (root == NULL) {
        return new_city;
    }
    if (compare_city(root, new_city) == FIRST_IS_BIGGER) {
        root->left = inser_sorted_city(root->left,new_city)
    }
    else if (compare_city(root, new_city) == SECOND_IS_BIGGER) {
        root->right = insert_sorted_city(root->right,new_city);
    }
}

int compare_city( cityP first, cityP second) {
    if (first->population == second->population) {
        if (strcmp(first->name, second->name) > 0) {
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
int insert_country(countryP head, countryP new_country) {
    while (strcmp(head->name, new_country->name) > 0 && head->next != NULL) {
        head = head->next;
    }
    head->next = new_country;
    return EXIT_SUCCESS;
}

int print_country(countryP current) {
    while (current != NULL) {
        printf("\nDrzava je: %s", current->name);
        print_city(current->first_city,0);
        current = current->next;
    }
    return EXIT_SUCCESS;
}
cityP print_city(cityP root,int population_minimum) {
    if(root != NULL){
        if (root->population > population_minimum) {
            printf("Grad je : %s sa populacijom %d:", root->name, root->population);
        }
        print_city(root->left,population_minimum);
        print_city(root->right,population_minimum);
    }
}
int query(countryP current) {
    char* country_name = { 0 };
    int Required_population= 0;

    printf("\nUnesite ime drzave(Hrvatska/Italija/Engleska)");
    scanf(" %s", country_name);
    printf("\n unesitite minimalni broj ljudi koji grad mora imati: ");
    scanf("%d",&Required_population);

    while (strcmp(current->name, country_name) != 0 || current != NULL) {
        current = current->next;
    }
    if (current == NULL) {
        printf("U listi nema te drzave");
            return EXIT_SUCCESS;
    }
    else {
        print_city(current->first_city, Required_population);

        }
    }
}