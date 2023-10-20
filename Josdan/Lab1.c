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

// stvara novi struct student te postavlja njegove vrijednosti na vrijednosti poslane u funkciju te vraca novonastali element
StudentP create_node(char* firstname, char* lastname, int points) {
	StudentP q = NULL;
	q = (StudentP)malloc(sizeof(Student));
	strcpy(q->firstname, firstname);
	strcpy(q->lastname, lastname);
	q->points = points;
	q->next = NULL;
	return q;
}
//jednadzba prima head i novi element. novi element stavljamo na misto head a stari head izad njega. Tako da je svaki novi clan head element funkcije. Fukcija vraca novi head
StudentP Input_in_list(StudentP head, StudentP q){
	if (head == NULL)
		return q;
	else{
		q->next = head;
		return q;
	}
}

StudentP read_from_file(StudentP head) {

	char* firstname[MAX_LENGTH] = { 0 };
	char* lastname[MAX_LENGTH] = { 0 };
	int points = 0;
	FILE* fp = NULL;

	fp = fopen("filename", "r");
	if (fp == NULL)
		return FILE_NOT_OPENED;

	while (!fp) {
		fscanf(fp, firstname, lastname, &points);
		head = Input_in_list(head,create_node(firstname, lastname, points));
	}
	fclose(fp);

	return head;
}
// prints all values of elements in list
int print_all_elements(studentp head){
	while (head != null) {
		printf(" %s %s %d %f \n", head->firstname, head->lastname, head->points, relativ_grade(head->points));
		head = head->next;
	}
	return 0;
}
double relativ_grade(int points) {
	double relativ = 0.0;
	relativ = points / 50.0 * 100;
	return relativ;
}


int main() {
	StudentP head = NULL;

	head = read_from_file(head);

	print_all_elements(head);

	return 0;
}