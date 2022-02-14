#include <stdio.h>
#include <cmath>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");

	const int len_count = 6;
	const int wid_count = 6;

	
	float len[len_count] = { 20.23, 19.72, 20.15, 20.3, 19.7, 19.84 };
	float wid[wid_count] = { 30.4, 29.73, 30.2, 29.89, 30.14, 29.8 };


	float abs_delta_len = 0.1;
	float abs_delta_wid = 0.1;
	float aver_len = 0.0;
	float aver_wid = 0.0;
	float relat_delta_len, relat_delta_wid;


	for (int i = 0; i < len_count; i++) {
		aver_len += len[i];
	}
	aver_len /= len_count;

	for (int i = 0; i < wid_count; i++) {
		aver_wid += wid[i];
	}
	aver_wid /= wid_count;


	relat_delta_len = abs_delta_len / aver_len;
	relat_delta_wid = abs_delta_wid / aver_wid;

	printf("len = %.1f ˜ %.1f\n", aver_len, abs_delta_len);
	printf("wid = %.1f ˜ %.1f\n", aver_wid, abs_delta_wid);

	printf("relative error len = %.6f \n", relat_delta_len);
	printf("relative error wid = %.6f \n", relat_delta_wid);

	printf("Sum = %.1f +- %.1f\n", aver_len + aver_wid, relat_delta_len + relat_delta_wid);
	printf("Minus = %.1f +- %.1f\n", aver_wid - aver_len, relat_delta_len + relat_delta_wid);
	printf("Multiplication = %.1f +- %.1f \n", aver_len * aver_wid, (relat_delta_len + relat_delta_wid) * aver_len * aver_wid);

	printf("Div = %.1f +- %.2f \n", aver_wid / aver_len, (relat_delta_len + relat_delta_wid) * aver_wid / aver_len);

	return 0;
}