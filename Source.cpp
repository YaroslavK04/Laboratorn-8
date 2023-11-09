#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include <queue>
#include<Windows.h>
using namespace std;



struct struck_queu
{
	int nomber;  // �������� ����������
	struct struck_queu* next; // ������ �� ��������� ������� 
};
struct struck_queu* head_Q, * last_Q;


struct spisok_soed* spis;



struct struck_queu* get_ochered(int g)
{
	struct struck_queu* p = NULL;
	char s[256];
	if ((p = (struck_queu*)malloc(sizeof(struct struck_queu))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	if (s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	p->nomber = g;

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

void push(int g) {
	struct struck_queu* q;
	q = get_ochered(g);
	if (head_Q == NULL) {
		head_Q = q;
		last_Q = q;
	}
	else {
		last_Q->next = q;
		last_Q = q;
	}
}

int pop(void) {
	struct struck_queu* head_struc = head_Q;
	int i;
	if (head_Q == NULL)
	{
		printf("������ ����\n");
	}

	i = head_Q->nomber;
	head_Q = head_Q->next;
	delete head_struc;
	return i;
}



void BFS_svoi(int v, bool* NUM, int size, int** G) {
	push(v);
	NUM[v] = TRUE;
	while (head_Q != NULL) {
		v = pop();
		cout << v << " ";
		for (int i = 1; i < size;i++) {
			if (G[v][i] == 1 && NUM[i] == FALSE) {
				push(i);
				NUM[i] = TRUE;
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, size, vershina;
	bool* NUM_svoi;
	clock_t start, end;
	double time;
	cout << " ������� ��������� \n \n ������� ���������� ������ �����: ";
	cin >> size;

	G = new int* [size]; // ������ ��������� ������ 
	NUM_svoi = new bool[size];
	for (int i = 0; i < size; i++) {
		G[i] = new int[size];
		NUM_svoi[i] = FALSE;
	}


	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) { G[i][j] = 0; }
			else {
				G[i][j] = rand() % 2;
				G[j][i] = G[i][j];
			}
		}

	}


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << G[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "����� � ������ �����: \n\n C��� �������: ";

	start = clock();
	BFS_svoi(0, NUM_svoi, size, G);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "\n ����� ������ - " << time << "\n";

	system("pause");
	return 0;
}
