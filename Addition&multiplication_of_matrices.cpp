#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>


void Plus(float** mass, float**mass2, int n, int m, int n2, int m2) {
//Проверка выполнения условия для сложения
	float** massC = (float**)malloc(m * n * sizeof(float*)); 
	for (int i = 0; i < n; i++) {
		massC[i] = (float*)malloc(m * sizeof(float));
	}
	if (n == n2) {//Складывае
		if (m == m2) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					massC[i][j] = mass[i][j] + mass2[i][j];
				}
			}
		}
	}
	else {
		printf("Матрицы должны быть одинаковых размеров!");
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%.2f ", massC[i][j]);
		}
		printf("\n");
	}



}



int main()
{
	setlocale(LC_ALL, "Rus");
	// Основная матрица
	int n, m, n2, m2;
	printf("Введите кол-во строк первой матрицы: ");
	scanf_s("%d", &n);

	printf("Введите кол-во стобцов первой матрицы: ");
	scanf_s("%d", &m);

	printf("Введите коэффициенты уравнений системы:\n");
	float** mass = (float**)malloc(m*n * sizeof(float*)); // выделение памяти под исходный массив коэффициентов
	// Ввод элементов массива
	for (int i = 0; i < n; i++) {
		mass[i] = (float*)malloc(m * sizeof(float));
		for (int j = 0; j < m; j++) {
			printf("mass[%d][%d] = ", i, j);
			scanf_s("%f", &mass[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%.2f ", mass[i][j]);
		}
		printf("\n");
	}

	printf("Введите кол-во строк второй матрицы: ");
	scanf_s("%d", &n2);

	printf("Введите кол-во стобцов второй матрицы: ");
	scanf_s("%d", &m2);

	float** mass2 = (float**)malloc(m2 * n2 * sizeof(float*)); // выделение памяти под исходный массив коэффициентов
	// Ввод элементов массива
	for (int i = 0; i < n2; i++) {
		mass2[i] = (float*)malloc(n2*m2*  sizeof(float));
		for (int j = 0; j < m2; j++) {
			printf("mass2[%d][%d] = ", i, j);
			scanf_s("%f", &mass2[i][j]);
		}
	}

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < m2; j++) {
			printf("%.2f ",mass2[i][j]);
		}
		printf("\n");
	}
	
	printf("Вывод суммы матриц: \n");
	Plus(mass, mass2, n, m, n2, m2);


	return 0;
}