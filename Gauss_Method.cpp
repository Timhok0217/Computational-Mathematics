#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

void Leaderelem(int k, float** mas, int n, float* por_korney){
	int max_i = k, max_j = k;
	float temp;

	for (int i = k; i < n; i++) {
		for (int j = k; j < n; j++) {
			if (fabs(mas[max_i][max_j]) < fabs(mas[i][j])){
				max_i = i;
				max_j = j;
			}
		}	
	}
		
	for (int j = k; j < n + 1; j++)
	{
		temp = mas[k][j];
		mas[k][j] = mas[max_i][j];
		mas[max_i][j] = temp;
	}
	
	for (int i = 0; i < n; i++)
	{
		temp = mas[i][k];
		mas[i][k] = mas[i][max_j];
		mas[i][max_j] = temp;
	}

	int i = por_korney[k];
	por_korney[k] = por_korney[max_j];
	por_korney[max_j] = i;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	printf("Enter size of matrix: ");
	scanf_s("%d", &n);

	printf("Enter coeffs of equations of the system:\n");
	float** mas = (float**)malloc(n * sizeof(float*)); 

	for (int i = 0; i < n; i++) {
		mas[i] = (float*)malloc(n* sizeof(float));
		for (int j = 0; j <=n; j++) {
			if (j==n) printf("answer[%d] = ", i);
			else printf("mas[%d][%d] = ", i, j);
			scanf_s("%f", &mas[i][j]);
		}
	}
	printf("Initial coeff matrix:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n+1; j++) {
			if (j == n) printf("| ");
			printf("%.2f ", mas[i][j]);
		}
		printf("\n");
	}

	float* x = (float*)malloc(n * sizeof(float)); 
	float* por_korney = (float*)malloc(n * sizeof(float)); 
	int k;

	for (int i = 0; i < n + 1; i++)
		por_korney[i] = i;


	for (k = 0; k < n; k++){ 
		Leaderelem(k, mas, n, por_korney); 
		if (fabs(mas[k][k]) < 0.0001) 
		{
			printf("System doesn't have a unique solution!");
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


	for (int i = 0; i < n; i++)
		x[i] = mas[i][n];
	for (int i = n - 2; i >= 0; i--)
		for (int j = i + 1; j < n; j++)
			x[i] -= x[j] * mas[i][j];


	printf("Answer:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == por_korney[j]){ 
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
