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
	bool * NUM_spisok;
	clock_t start, end;
	double time;
	cout << " ������� ��������� \n \n ������� ���������� ������ �����: ";
	cin >> size;

	spis = new struct spisok_soed[size];
	G = new int* [size]; // ������ ��������� ������ 
	NUM_spisok = new bool[size];
	for (int i = 0; i < size; i++) {
		G[i] = new int[size];
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


	cout << "\n ����� � ������ ������: ";

	start = clock();
	BFS_spisok(0, NUM_spisok, spis);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n ����� ������ - " << time << "\n";


	system("pause");
	return 0;
}
