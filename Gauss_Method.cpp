#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

void Leaderelem(int k, float** mas, int n, float* por_korney){
	int max_i = k, max_j = k;
	float temp;
	//Ищем максимальный по модулю элемент во всей матрице коэффициентов
	for (int i = k; i < n; i++) {
		for (int j = k; j < n; j++) {
			if (fabs(mas[max_i][max_j]) < fabs(mas[i][j])){
				max_i = i;
				max_j = j;
			}
		}	
	}
		
	for (int j = k; j < n + 1; j++)//перенос строк
	{
		temp = mas[k][j];
		mas[k][j] = mas[max_i][j];
		mas[max_i][j] = temp;
	}
	
	for (int i = 0; i < n; i++)//перенос столбцов
	{
		temp = mas[i][k];
		mas[i][k] = mas[i][max_j];
		mas[i][max_j] = temp;
	}

	//Учитываем изменение порядка корней
	int i = por_korney[k];
	por_korney[k] = por_korney[max_j];
	por_korney[max_j] = i;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	printf("Введите размер матрицы: ");
	scanf_s("%d", &n);

	printf("Введите коэффициенты уравнений системы:\n");
	float** mas = (float**)malloc(n * sizeof(float*)); // выделение памяти под исходный массив коэффициентов
	// Ввод элементов массива
	for (int i = 0; i < n; i++) {
		mas[i] = (float*)malloc(n* sizeof(float));
		for (int j = 0; j <=n; j++) {
			if (j==n) printf("answer[%d] = ", i);
			else printf("mas[%d][%d] = ", i, j);
			scanf_s("%f", &mas[i][j]);
		}
	}
	printf("Исходная матрица коэффициентов:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n+1; j++) {
			if (j == n) printf("| ");
			printf("%.2f ", mas[i][j]);
		}
		printf("\n");
	}

	float* x = (float*)malloc(n * sizeof(float)); //Корни системы
	float* por_korney = (float*)malloc(n * sizeof(float)); //Отвечает за порядок корней
	int k;
	//Сначала все корни по порядку
	for (int i = 0; i < n + 1; i++)
		por_korney[i] = i;

	//Прямой ход метода Гаусса
	for (k = 0; k < n; k++)
	{ //На какой позиции должен стоять главный элемент
		Leaderelem(k, mas, n, por_korney); //Установка главного элемента
		if (fabs(mas[k][k]) < 0.0001) //абсолютное значение
		{
			printf("Система не имеет единственного решения");//линейная зависимость коэффициентов
			for (int i = 0; i < n; i++) {
				free(mas[i]);
			}
			free(mas);
			free(x);
			free(por_korney);
			return 0;
		}
		for (int j = n; j >= k; j--)
			mas[k][j] /= mas[k][k];
		for (int i = k + 1; i < n; i++)
			for (int j = n; j >= k; j--)
				mas[i][j] -= mas[k][j] * mas[i][k];
	}

	//Обратный ход по Гауссу
	for (int i = 0; i < n; i++)
		x[i] = mas[i][n];
	for (int i = n - 2; i >= 0; i--)
		for (int j = i + 1; j < n; j++)
			x[i] -= x[j] * mas[i][j];

	//Вывод результата
	printf("Ответ:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == por_korney[j]){ //Расставляем корни по порядку
				printf("%.2f\n", x[j]);
				break;
			}

	for (int i = 0; i < n; i++) {
		free(mas[i]);
	}
	free(mas);
	free(x);
	free(por_korney);
	return 0;
}
