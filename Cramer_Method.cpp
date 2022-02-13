#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

// Получение дополнительного минора матрицы без i-й строки и j-го столбца
void Minor(float** array, float** temparr, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < (m - 1); ki++) { // проверка индекса строки
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < (m - 1); kj++) { // проверка индекса столбца
			if (kj == j) dj = 1;
			temparr[ki][kj] = array[ki + di][kj + dj];
		}
	}
}

// Рекурсивное вычисление определителя
float Determ(float** bmass, int m, float* b) {
	float** temparr = (float**)malloc(m * m * sizeof(float*));
	for (int i = 0; i < m; i++)
		temparr[i] = (float*)malloc(m * sizeof(float));

	int j = 0; 
	float det = 0; //определитель
	int k = 1; //(-1) в степени i
	int m1 = m - 1;

	if (m < 1)
		printf("Определитель найти невозможно!");

	if (m == 1) {
		det = bmass[0][0];
		return(det);
	}
	if (m == 2) {
		det = bmass[0][0] * bmass[1][1] - (bmass[1][0] * bmass[0][1]);
		return(det);
	}
	if (m > 2) {
		for (int i = 0; i < m; i++) {
			Minor(bmass, temparr, i, 0, m);
			det +=  k * bmass[i][0] * Determ(temparr, m1, b);
			k = -k;
		}
	}
	return(det);

	for (int i = 0; i < m; i++)
		free(temparr[i]);
	free(temparr);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	// Основная матрица
	int m;
	printf("Введите размер матрицы: ");
	scanf_s("%d", &m);

	printf("Введите коэффициенты уравнений системы:\n");
	float** array = (float**)malloc(m * sizeof(float*)); // выделение памяти под исходный массив коэффициентов
	// Ввод элементов массива
	for (int i = 0; i < m; i++) {
		array[i] = (float*)malloc(m * sizeof(float));
		for (int j = 0; j < m; j++) { 
			printf("array[%d][%d] = ", i, j);
			scanf_s("%f", &array[i][j]);
		}
	}
	float* b = (float*)calloc(m, sizeof(float)); // выделение памяти под вектор правых частей
	float* det = (float*)calloc(m, sizeof(float)); // память под определители
	//Ввод вектора правых частей
	printf("Введите вектор правых частей:\n");
	for (int i = 0; i < m; i++) { 
		printf("answer[%d] = ", i);
		scanf_s("%f", &b[i]);
	}
	printf("\n");
	//Вывод исходной матрицы
	printf("Исходная матрица коэффициентов:\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%2.2f ", array[i][j]);
		}
		printf("\n");
	}

	float** bmass = (float**)malloc(m * sizeof(float*)); // массив, в который будем подставлять вектор правых частей
	for (int i = 0; i < m; i++)
		bmass[i] = (float*)malloc(m * sizeof(float));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			bmass[i][j] = array[i][j];
	}
	//Определитель из начальных коэффициентов
	det[0] = Determ(bmass, m, b);
	if (det[0] == 0){
		printf("Определитель det = %.2f \n", det[0]);
		printf("Особенная матрица! \n");
		for (int i = 0; i < m; i++) {
			free(array[i]);
			free(bmass[i]);
		}
		free(array);
		free(bmass);
		free(b);
		free(det);
		return 0;
	}
	printf("Определитель det = %.2f \n", det[0]);
	printf("\n");
	printf("Далее произведется последовательная замена столбцов исходной матрицы на вектор правых частей.\n");
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < m; i++)
			bmass[i][j] = b[i];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				printf("%2.2f ", bmass[i][j]);
			}
			printf("\n");
		}
		det[j + 1] = Determ(bmass, m, b);
		printf("Определитель det(%d) = %.2f \n", j+1, det[j + 1]);
		printf("\n");
		for (int i = 0; i < m; i++)
			bmass[i][j] = array[i][j];
	}
	printf("Ответ: \n");
	for (int i = 1; i < m + 1; i++) {
		printf("X(%d) = %.2f \n", i, det[i] / det[0]);
	}
	for (int i = 0; i < m; i++) {
		free(array[i]);
		free(bmass[i]);
	}
	free(array);
	free(bmass);
	free(b);
	free(det);
	return 0;
}
