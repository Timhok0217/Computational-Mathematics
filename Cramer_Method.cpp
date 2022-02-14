#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

void Minor(float** array, float** temparr, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < (m - 1); ki++) { 
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < (m - 1); kj++) { 
			if (kj == j) dj = 1;
			temparr[ki][kj] = array[ki + di][kj + dj];
		}
	}
}

float Determ(float** bmass, int m, float* b) {
	float** temparr = (float**)malloc(m * m * sizeof(float*));
	for (int i = 0; i < m; i++)
		temparr[i] = (float*)malloc(m * sizeof(float));

	int j = 0; 
	float det = 0; 
	int k = 1; 
	int m1 = m - 1;

	if (m < 1)
		printf("Determ not found!");

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
	setlocale(LC_ALL, "Russian");

	int m;
	printf("Enter size of matrix: ");
	scanf_s("%d", &m);

	printf("Enter coeffs of equations of the system:\n");
	float** array = (float**)malloc(m * sizeof(float*)); 
	for (int i = 0; i < m; i++) {
		array[i] = (float*)malloc(m * sizeof(float));
		for (int j = 0; j < m; j++) { 
			printf("array[%d][%d] = ", i, j);
			scanf_s("%f", &array[i][j]);
		}
	}
	float* b = (float*)calloc(m, sizeof(float)); 
	float* det = (float*)calloc(m, sizeof(float)); 

	printf("Enter vector right parts:\n");
	for (int i = 0; i < m; i++) { 
		printf("answer[%d] = ", i);
		scanf_s("%f", &b[i]);
	}
	printf("\n");

	printf("Initial coeff matrix:\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%2.2f ", array[i][j]);
		}
		printf("\n");
	}

	float** bmass = (float**)malloc(m * sizeof(float*)); 
	for (int i = 0; i < m; i++)
		bmass[i] = (float*)malloc(m * sizeof(float));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			bmass[i][j] = array[i][j];
	}

	det[0] = Determ(bmass, m, b);
	if (det[0] == 0){
		printf("Determ = %.2f \n", det[0]);
		printf("Special Matrix! \n");
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
	printf("Determ = %.2f \n", det[0]);
	printf("\n");
	printf("Next, the columns of the original matrix will be sequentially replaced by the vector of right parts.\n");
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
		printf("Determ(%d) = %.2f \n", j+1, det[j + 1]);
		printf("\n");
		for (int i = 0; i < m; i++)
			bmass[i][j] = array[i][j];
	}
	printf("Answer: \n");
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
