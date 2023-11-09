#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include <queue>
#include<Windows.h>
using namespace std;

queue<int> Q;

struct spisok_soed {
	int vershina;
	struct spisok_soed* next;
};

struct struck_queu
{
	int nomber;  // �������� ����������
	struct struck_queu* next; // ������ �� ��������� ������� 
};
struct struck_queu* head_Q, * last_Q;
struct spisok_soed* creation_element(int nomber) {

	struct spisok_soed* p = NULL;

	if ((p = (spisok_soed*)malloc(sizeof(struct spisok_soed))) == NULL) // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	p->vershina = nomber;
	p->next = NULL;

	return p;


}

struct spisok_soed* spis;

void creation_spisok(int** M, int size) {
	struct spisok_soed* q, * save = NULL;
	for (int i = 0; i < size; i++) {
		spis[i].next = NULL;
		spis[i].vershina = i;
		for (int j = 0; j < size; j++) {
			if (M[i][j] == 1) {
				q = creation_element(j);

				if (spis[i].next == NULL) {
					spis[i].next = q;
					save = q;
				}
				else {
					save->next = q;
					save = q;
				}
			}
		}
	}
}

void review(int size) {
	struct spisok_soed* save;
	cout << "\n";
	for (int i = 0; i < size; i++) {
		save = spis[i].next;
		cout << "[" << spis[i].vershina << "]";
		while (save != NULL) {
			cout << " -> " << save->vershina;
			save = save->next;
		}
		cout << "\n";
	}
	cout << "\n";

}


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

void BFS(int v, bool* NUM, int size, int** G) {
	Q.push(v);
	NUM[v] = TRUE;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		cout << v << " ";
		for (int i = 1; i < size;i++) {
			if (G[v][i] == 1 && NUM[i] == FALSE) {
				Q.push(i);
				NUM[i] = TRUE;
			}
		}
	}
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

void BFS_spisok(int v, bool* NUM, struct spisok_soed* spis) {
	struct spisok_soed* save;
	Q.push(v);
	NUM[v] = TRUE;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		save = spis[v].next;
		cout << v << " ";
		while (save != NULL) {
			if (NUM[save->vershina] == FALSE) {
				Q.push(save->vershina);
				NUM[save->vershina] = TRUE;
			}
			save = save->next;
		}
	}
}


int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, size, vershina;
	bool* NUM, * NUM_svoi, * NUM_spisok;
	clock_t start, end;
	double time;
	cout << " ������� ��������� \n \n ������� ���������� ������ �����: ";
	cin >> size;

	spis = new struct spisok_soed[size];
	G = new int* [size]; // ������ ��������� ������ 
	NUM = new bool[size];
	NUM_svoi = new bool[size];
	NUM_spisok = new bool[size];
	for (int i = 0; i < size; i++) {
		G[i] = new int[size];
		NUM[i] = FALSE;
		NUM_svoi[i] = FALSE;
		NUM_spisok[i] = FALSE;

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

	creation_spisok(G, size);
	review(size);

	cout << "����� � ������ �����: \n\n ������� �� ����������: ";

	start = clock();
	BFS(0, NUM, size, G);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "\n ����� ������ - " << time << "\n\n C��� �������: ";

	start = clock();
	BFS_svoi(0, NUM_svoi, size, G);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "\n ����� ������ - " << time << "\n\n ����� � ������ ������: ";

	start = clock();
	BFS_spisok(0, NUM_spisok, spis);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n ����� ������ - " << time << "\n";


	system("pause");
	return 0;
}
