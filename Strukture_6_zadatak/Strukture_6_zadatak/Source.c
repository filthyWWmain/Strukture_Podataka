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

int main() {
    Position root = NULL;

    while (1) {
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

