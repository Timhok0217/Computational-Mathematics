#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>


void Plus(float** mass, float**mass2, int n, int m, int n2, int m2) {
//�������� ���������� ������� ��� ��������
	float** massC = (float**)malloc(m * n * sizeof(float*)); 
	for (int i = 0; i < n; i++) {
		massC[i] = (float*)malloc(m * sizeof(float));
	}
	if (n == n2) {//���������
		if (m == m2) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					massC[i][j] = mass[i][j] + mass2[i][j];
				}
			}
		}
	}
	else {
		printf("������� ������ ���� ���������� ��������!");
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
	// �������� �������
	int n, m, n2, m2;
	printf("������� ���-�� ����� ������ �������: ");
	scanf_s("%d", &n);

	printf("������� ���-�� ������� ������ �������: ");
	scanf_s("%d", &m);

	printf("������� ������������ ��������� �������:\n");
	float** mass = (float**)malloc(m*n * sizeof(float*)); // ��������� ������ ��� �������� ������ �������������
	// ���� ��������� �������
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

	printf("������� ���-�� ����� ������ �������: ");
	scanf_s("%d", &n2);

	printf("������� ���-�� ������� ������ �������: ");
	scanf_s("%d", &m2);

	float** mass2 = (float**)malloc(m2 * n2 * sizeof(float*)); // ��������� ������ ��� �������� ������ �������������
	// ���� ��������� �������
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
	
	printf("����� ����� ������: \n");
	Plus(mass, mass2, n, m, n2, m2);


	return 0;
}