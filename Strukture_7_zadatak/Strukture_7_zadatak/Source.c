//9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.
//a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
//sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
//pokazivaè na korijen stabla.
//b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
//njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
//    vrijednosti u tim potomcima).Npr.stablo sa slike Slika 1 transformirat æe se u stablo na
//    slici Slika 2.
//    c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
//    funkcije rand() generira sluèajne brojeve u rasponu <10, 90>.Takoðer, potrebno je
//    upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
//    dijela zadatka

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root);
Position search(Position root, int value);
Position deleteNode(Position root, int value);
int replace(Position root);
int random();
int print_in_file(Position root, char* filename);
int inorder_file(Position root, FILE *fp);

int main() {

    Position root = NULL;

    ///*************************************** Novi dio ispod ovoga od 9.zd
    //Napomena nisan minja insert da su desno manja dica a livo veca nego san ostavia kako je bilo u proslon zadatku
    int input, i = 0;
    printf("\nNuesite 1 za replace ili 2 za random unos brojeva\n");
    scanf(" %d", &input);
    if (input == 1) {
        root = insert(root, 2);
        insert(root, 5);
        insert(root, 7);
        insert(root, 8);
        insert(root, 11);
        insert(root, 1);
        insert(root, 4);
        insert(root, 2);
        insert(root, 3);
        insert(root, 7);

        printf("\n Nakon insert funkcije: \n");
        inorder(root);
        print_in_file(root, "file.txt");
        replace(root);
        printf("\n Nakon replace funkcije: \n");

        inorder(root);
        print_in_file(root,"file2.txt");
    }
    else if (input == 2) {
        root = insert(root, random());
        while (i < 10) {
            insert(root, random());
            i++;
        }
        
    }


    ///***************************************
    /*while (1) {
        printf("\nMenu:\n");
        printf("1 - Insert node\n");
        printf("2 - Search node\n");
        printf("3 - Delete node\n");
        printf("4 - Print preorder\n");
        printf("5 - Print inorder\n");
        printf("6 - Print postorder\n");
        printf("7 - Print level order\n");
        printf("8 - exit\n");

        char choice[10] = { 0 };
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            int value = 0;
            printf("Enter value:");
            scanf("%d", &value);
            insert(root, value);
        }
        else if (strcmp(choice, "2") == 0) {
            int value = 0;
            Position result = NULL;
            printf("Enter value: ");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("Node %d is found.", value);
            else
                printf("Node %d is not found.", value);
        }
        else if (strcmp(choice, "3") == 0) {
            int value = 0;
            printf("Enter value:");
            scanf("%d", &value);
            deleteNode(root, value);
        }
        else if (strcmp(choice, "4") == 0) {
            printf("Preorder:");
            preorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "5") == 0) {
            printf("Inorder: ");
            inorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "6") == 0) {
            printf("Postorder: m");
            postorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "7") == 0) {
            printf("Level-order:");
            levelOrder(root);
            printf("\n");
        }
        else if (strcmp(choice, "8") == 0) {
            printf("Exiting the program.");
            break;
        }
        else {
            printf("Wrong input. Please try again.\n");
        }
    }
    */
    return EXIT_SUCCESS;
}


Position createNode(int value) {
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Cant allocate memory!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int levelOrder(Position root) {
    if (root == NULL)
        return;

    Position queue[100] = { 0 };
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}

Position search(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

Position deleteNode(Position root, int value) {
    if (root == NULL)
        return root;

    // prvo nalazimo node koji brisemo
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        // Ako ima samo jedno ili nema niti jedno dite
        if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }

        // Ako ima 2 onda trazimo najmanjeg u desnom
        Position temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        // kopiramo najmanjeg u trenutno
        root->value = temp->value;

        // brisemo najmanjeg
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}
int replace(Position root) {
    if (root == NULL) {
        return 0;
    }

    //Ako postoji liva ili desna grana ulazimo u njih itako sve do kraja jer moramo od dna prema gori zbrajati
    int Sum_left_children = replace(root->left);
    int Sum_right_children = replace(root->right);

    //Moramo je spremiti jer poslje na njeno misto stavljano zbroj dice pa da ne izgubimo koja je vrijednost tu -Zato mora biti ova linija prije sljedece
    int current_node_value = root->value;
    root->value = Sum_right_children + Sum_left_children;

    // Return the sum of the node's value and the sum of its children
    return current_node_value + root->value;
}

int random() {
    return (rand() % (90 - 10 + 1)) + 10;// +1 da bi ukljucili i 90
}
// PITAJ ZA FILE POINTER STO SE SALJE U DRUGU FUNKCIJU!!!
int print_in_file(Position root,char* filename) {
    FILE* fp = NULL;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    else {
        inorder_file(root, fp);
        fclose(fp);
        return EXIT_SUCCESS;
    }
}

int inorder_file(Position root, FILE *fp) {
    if (root) {
        inorder_file(root->left, fp);
        fprintf(fp, "\n%d", root->value);
        inorder_file(root->right, fp);
    }
    return EXIT_SUCCESS;
}