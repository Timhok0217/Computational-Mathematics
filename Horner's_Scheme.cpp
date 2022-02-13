#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");

	printf("Введите максимальную степень многочлена: ");
	int n;
	scanf_s("%d", &n);
	float* a = (float*) calloc(n + 1, sizeof(float));  //выделение памяти под коэффициенты многочлена
	printf("Введите коэффициенты многочлена: ");
	for (int i = 0; i < (n + 1); i++) {
		scanf_s("%f", &a[i]);
	}
	printf("Введите свободный коэффициент двучлена: ");
	float ksi;
	scanf_s("%f", &ksi);
	float* b = (float*) calloc(n, sizeof(float));  //выделение памяти под коэффициенты многочлена-частного
	b[0] = a[0];
	printf("Результат деления многочлена на двучлен: ");
	printf("%.2fx^%d + ", b[0], n-1);
	for (int i = 1; i < n; i++) {
		b[i] = a[i] + b[i-1] * ksi;
		printf("%.2fx^%d", b[i], n-i-1);
		if (i < n)
			printf(" + ");
	}
	if (int i = n) b[n] = a[n] + b[n - 1] * ksi; //остаток
	printf("%.2f; \n", b[n]);
	printf("Остаток: %.2f \n", b[n]);
	printf("Проверка ");
	float* proof = (float*)calloc(n, sizeof(float));  //выделение памяти для проверки 
	proof[n-1] = b[n-1];
	for (int i = n - 2; i > 0; i--) {
		proof[i] =  b[i]-b[i-1]*ksi;
		if (proof[i] != a[i]) {
			printf("не пройдена");
			free(a);
			free(b);
			free(proof);
			return 0;
		}
	}
	printf("пройдена");
	free(a);
	free(b);
	free(proof);
	return 0;
}