#define bool prolaz_predmeta 1
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 128
#define FILE_NOT_OPENED -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char* firstname[MAX_LENGTH];
	char* lastname[MAX_LENGTH];
	int points;
	StudentP next;
}Student;

StudentP create_node(char* firstname, char* lastname, int points) {
	StudentP q = NULL;
	q = (StudentP)malloc(sizeof(Student));
	strcpy(q->firstname, firstname);
	strcpy(q->lastname, lastname);
	q->points = points;
	q->next = NULL;
	return q;

}
StudentP Input_in_list(StudentP head, StudentP q) {
	if (head == NULL)
		return q;
	else {
		q->next = head;
		return q;
	}
}
StudentP read_from_file(StudentP head) {

	char firstname[MAX_LENGTH] = { 0 };
	char lastname[MAX_LENGTH] = { 0 };
	int points, test = 0;
	FILE* fp = NULL;

	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		perror("\njebo ga file\n");
		return FILE_NOT_OPENED;
	}
	else {
		while (fscanf(fp, " %s %s %d", firstname, lastname, &points) != EOF) {

			head = Input_in_list(head, create_node(firstname, lastname, points));

		}
		fclose(fp);
	}



	return head;
}
//tebra--- :)
double relativ_grade(int points) {
	double relativ = 0.0;
	relativ = points / 50.0 * 100.0;
	return relativ;
}

// prints all values of elements in list
int print_all_elements(StudentP head) {
	while (head != NULL) {
		printf(" %s %s %d %f \n", head->firstname, head->lastname, head->points, relativ_grade(head->points));
		head = head->next;
	}
	return 0;
}

int free_the_memory(StudentP head) {
	StudentP Temp = NULL;
	while (head != NULL) {
		Temp = head;
		head = head->next;
		printf("\n brisemo : %s %s %d", Temp->firstname, Temp->lastname, Temp->points);
		free(Temp);
	}
}

int main() {

	StudentP head = NULL;

	head = read_from_file(head);
	print_all_elements(head);
	free_the_memory(head);


	return 0;
}