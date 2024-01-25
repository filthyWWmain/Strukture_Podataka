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
#define HASH_TABLE_SIZE 11

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

typedef struct _hashtable {
    countryP list[HASH_TABLE_SIZE];

}hashtable;
typedef hashtable* hashtableP;



int readcountry(country*, hashtableP);
countryP create_country(char*);
cityP read_city(cityP, char*);
cityP create_city(char*, int);
cityP insert_sorted_city(cityP, cityP);
int compare_city(cityP, cityP);
int insert_country(countryP, countryP);
int print_country(countryP);
cityP print_city(cityP, int);
int query(countryP);
hashtableP create_hastable();
int calculate_hash_value(char*);
int insert_country_in_hash(hashtableP, countryP);
int search_hash_table(hashtableP);
int delete_country(countryP);
cityP delete_tree(cityP);

int main() {

    country head = { .name = {"head_name"}, .next = NULL, .first_city = NULL };
    hashtableP hash_table = NULL;
    hash_table = create_hastable();
    char* country_name = { 0 };


    readcountry(&head, hash_table);

    //print_country(head.next);

    //query(head.next);
    search_hash_table(hash_table);

    delete_country(head.next);

    return 0;
}

int search_hash_table(hashtableP hash_table) {

    char countryname[MAX_LENGHT] = { 0 };
    countryP searched_country = NULL;

    pritnf("Input country name to search in hashtable: ");
    scanf(" %s", countryname);

    searched_country = hash_table->list[calculate_hash_value(countryname)];

    while (searched_country = !NULL && strcmp(searched_country->name, countryname) != 0) {
        searched_country = searched_country->next;
    }

    if (searched_country == NULL) {
        printf("Country doesn't exist");
        return EXIT_FAILURE;
    }
    else {
        printf("country found in hash table : %s", searched_country->name);
    }
    return EXIT_SUCCESS;

}
int insert_country_in_hash(hashtableP hashtable, countryP new_country) {

    int hash_table_value = 0;

    hash_table_value = calculate_hash_value(new_country->name);

    if (hashtable->list[hash_table_value] != NULL) {
        hashtable->list[hash_table_value] = new_country;
    }
    else {
        new_country->next = hashtable->list[hash_table_value];
        hashtable->list[hash_table_value] = new_country;
    }
    return 0;
}
int calculate_hash_value(char* countr_name) {
    int hash_vaule = 0;
    int i = 0;
    while (countr_name[i] != '\0' && i < 5) {
        hash_vaule = hash_vaule + (unsigned int)countr_name[i];
        i;
    }
    return hash_vaule % HASH_TABLE_SIZE;
}



hashtableP create_hastable() {
    hashtableP hashtable = NULL;
    hashtable = (hashtableP)malloc(sizeof(hashtable));

    if (hashtable == NULL) {
        printf("memory allocation fail at_hashtable");
        return NULL;
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashtable->list[i] = NULL;
    }

    return hashtable;;
}



int readcountry(country* head, hashtableP hash_table) {
    FILE* fp = NULL;
    char* countryname[MAX_LENGHT] = { 0 };
    char* filename[MAX_LENGHT] = { 0 };

    fp = fopen("drzave.txt", "r");
    if (fp == NULL) {
        printf("\nfile_not_fonud");
        return EXIT_FAILURE;
    }
    while (fscanf(fp, "%s , %s", countryname, filename) != EOF) {

        countryP new_country = create_country(countryname);
        new_country->first_city = read_city(new_country->first_city, filename);
        insert_country(head, new_country);
        //nova drzava za hash
        countryP new_country_hash = create_country(countryname);
        new_country_hash->first_city = read_city(new_country->first_city, filename);

        insert_country_in_hash(hash_table, new_country_hash);

    }
    return 0;
}

int insert_country(countryP head, countryP new_country) {
    countryP current = head;
    if (head->next == NULL) {

        head->next = new_country;

        return EXIT_SUCCESS;
    }

    while (current->next != NULL && strcmp(current->next->name, new_country->name) > 0) {

        current = current->next;
    }
    new_country->next = current->next;
    current->next = new_country;
    return EXIT_SUCCESS;
}

countryP create_country(char* name) {
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

    FILE* fp = NULL;
    char* city_name[MAX_LENGHT] = { 0 };
    int population = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nfile not found! %s");
        return EXIT_FAILURE;
    }

    while (fscanf(fp, "%s , %d ", city_name, &population) != EOF) {
        cityP new_city = create_city(city_name, population);


        root = insert_sorted_city(root, new_city);

    }


    return root;
}

cityP create_city(char* city_name, int population) {

    cityP new_city = NULL;

    new_city = (cityP)malloc(sizeof(city));
    if (new_city == NULL) {
        printf("malloc fail_city");
        return EXIT_FAILURE;
    }
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

        root->left = insert_sorted_city(root->left, new_city);
    }
    else if (compare_city(root, new_city) == SECOND_IS_BIGGER) {

        root->right = insert_sorted_city(root->right, new_city);
    }
    return root;
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


int print_country(countryP current) {
    while (current != NULL) {
        printf("\nDrzava je: %s", current->name);
        print_city(current->first_city, 0);
        current = current->next;
    }
    return EXIT_SUCCESS;
}
cityP print_city(cityP root, int population_minimum) {
    if (root != NULL) {
        if (root->population > population_minimum) {
            printf("\nGrad je : %s sa populacijom : %d", root->name, root->population);
        }
        print_city(root->left, population_minimum);
        print_city(root->right, population_minimum);
    }
}
int query(countryP current) {
    char* country_name[MAX_LENGHT] = { 0 };
    int Required_population = 0;

    printf("\nUnesite ime drzave(Hrvatska/Italija/Engleska): ");
    scanf(" %s", country_name);
    printf("\n unesitite minimalni broj ljudi koji grad mora imati: ");
    scanf("%d", &Required_population);

    while (current == NULL || strcmp(current->name, country_name) != 0) {
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
int delete_country(countryP head) {
    countryP Temp = NULL;
    countryP current = head;
    while (current != NULL) {
        Temp = current;
        current = current->next;
        delete_tree(Temp->first_city);
        free(Temp);
    }
    return EXIT_SUCCESS;
}

cityP delete_tree(cityP root) {
    if (root->left != NULL) {
        delete_tree(root->left);
    }
    if (root->right != NULL) {
        delete_tree(root->right);
    }
    free(root);
}