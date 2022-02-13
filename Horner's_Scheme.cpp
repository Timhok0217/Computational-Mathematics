#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");

	printf("������� ������������ ������� ����������: ");
	int n;
	scanf_s("%d", &n);
	float* a = (float*) calloc(n + 1, sizeof(float));  //��������� ������ ��� ������������ ����������
	printf("������� ������������ ����������: ");
	for (int i = 0; i < (n + 1); i++) {
		scanf_s("%f", &a[i]);
	}
	printf("������� ��������� ����������� ��������: ");
	float ksi;
	scanf_s("%f", &ksi);
	float* b = (float*) calloc(n, sizeof(float));  //��������� ������ ��� ������������ ����������-��������
	b[0] = a[0];
	printf("��������� ������� ���������� �� �������: ");
	printf("%.2fx^%d + ", b[0], n-1);
	for (int i = 1; i < n; i++) {
		b[i] = a[i] + b[i-1] * ksi;
		printf("%.2fx^%d", b[i], n-i-1);
		if (i < n)
			printf(" + ");
	}
	if (int i = n) b[n] = a[n] + b[n - 1] * ksi; //�������
	printf("%.2f; \n", b[n]);
	printf("�������: %.2f \n", b[n]);
	printf("�������� ");
	float* proof = (float*)calloc(n, sizeof(float));  //��������� ������ ��� �������� 
	proof[n-1] = b[n-1];
	for (int i = n - 2; i > 0; i--) {
		proof[i] =  b[i]-b[i-1]*ksi;
		if (proof[i] != a[i]) {
			printf("�� ��������");
			free(a);
			free(b);
			free(proof);
			return 0;
		}
	}
	printf("��������");
	free(a);
	free(b);
	free(proof);
	return 0;
}