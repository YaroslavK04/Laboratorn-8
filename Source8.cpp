#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include <queue>
#include<Windows.h>
using namespace std;

queue<int> Q;

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



int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, size, vershina;
	bool * NUM;
	clock_t start, end;
	double time;
	cout << " Матрица смежности \n \n Введите количество вершин графа: ";
	cin >> size;

	
	G = new int* [size]; // создаём двумерный массив 
	NUM = new bool[size];
	for (int i = 0; i < size; i++) {
		G[i] = new int[size];
		NUM[i] = FALSE;
		

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
	
	

	cout << "Обход в ширину через: \n\n Очередь из библиотеки: ";

	start = clock();
	BFS(0, NUM, size, G);
	end = clock();
	time = (double)(end - start)/ CLOCKS_PER_SEC;

	cout << "\n Время работы - "<< time << "\n";


	system("pause");
	return 0;
}
