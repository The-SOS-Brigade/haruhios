#include <haruhi/math.h>
#include <haruhi/types.h>

int abs(int n)
{
	if (n < 0)
		n = -n;

	return n;
}


int pow(int base, int exp)
{
	if (!base)
		return 0;

	int result = 1;

	while (exp--) {
		result *= base;
	}

	return result;
}
