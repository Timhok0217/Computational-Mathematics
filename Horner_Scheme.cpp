#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

int main()
{
	setlocale(LC_ALL, "Rus");

	printf("Enter max step of polynom: ");
	int n;
	scanf_s("%d", &n);
	float* a = (float*) calloc(n + 1, sizeof(float));  
	printf("Enter coeff of polynom: ");
	for (int i = 0; i < (n + 1); i++) {
		scanf_s("%f", &a[i]);
	}
	printf("Enter free coeff binomial: ");
	float ksi;
	scanf_s("%f", &ksi);
	float* b = (float*) calloc(n, sizeof(float));  
	b[0] = a[0];
	printf("Result of dividing polynomial by binomial: ");
	printf("%.2fx^%d + ", b[0], n-1);
	for (int i = 1; i < n; i++) {
		b[i] = a[i] + b[i-1] * ksi;
		printf("%.2fx^%d", b[i], n-i-1);
		if (i < n)
			printf(" + ");
	}
	if (int i = n) b[n] = a[n] + b[n - 1] * ksi; 
	printf("%.2f; \n", b[n]);
	printf("Last: %.2f \n", b[n]);
	printf("Examing ");
	float* proof = (float*)calloc(n, sizeof(float));  
	proof[n-1] = b[n-1];
	for (int i = n - 2; i > 0; i--) {
		proof[i] =  b[i]-b[i-1]*ksi;
		if (proof[i] != a[i]) {
			printf("failed");
			free(a);
			free(b);
			free(proof);
			return 0;
		}
	}
	printf("passed");
	free(a);
	free(b);
	free(proof);
	return 0;
}