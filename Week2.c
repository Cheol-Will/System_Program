#include <stdio.h>
int sum_array(int a[], unsigned len)
{
	int i;
	int result = 0;

	for (i = 0; i <= len-1; i++)
	{
		result += a[i];
	}
	return result;
}
int main(void)
{
	short int v = -12345;
	unsigned short uv = (unsigned short)v;
	printf("v = %d, uv = %d", v, uv);

	// Ex1
	unsigned i;
	for (i = 10; i >0; i--)
	{
		printf("%u\n", i);
	}
	/*
	for (i = 10; i >= 0; i--)
	{
		printf("%u\n", i);
	}
	*/

	// Ex2
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printf("%d\n",sum_array(a, 0));

	return 0;
}

