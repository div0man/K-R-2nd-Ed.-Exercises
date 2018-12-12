/* Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

typedef long long int myint;

/* find max integer */
/* relies on loop stopping due to overflow */
myint int_type_max(void)
{
	myint max = 0;
	for (myint p2 = 1, prev = 0; p2 > prev; p2 *= 2) {
		prev = p2;
		max += p2;
	}
	return max;
}

/* find min integer */
/* relies on loop stopping due to overflow */
myint int_type_min(void)
{
	myint min = 0;
	for (myint p2 = -1; p2 < min; p2 *= 2)
		min = p2;
	return min;
}

typedef long double myflt;

/* find max. float */
/* relies on loop stopping due to inf == inf */
myflt float_type_max(void)
{
	myflt max;
	myflt prev;
	myflt pprev;

	/* find max. exponent */
	for (max = 1, prev = 0; max > prev; max *=2) {
		pprev = prev;
		prev = max;
	}
	max = pprev;

	/* find max. mantissa */
	prev = 0;
	for (myflt p2 = (myflt)1.0, maxp2 = max; max > prev; max += p2 * maxp2) {
		pprev = prev;
		prev = max;
		p2 /= 2;
	}
	max = pprev;

	return max;
}

/* find min float */
/* relies on loop stopping due to inf == inf */
myflt float_type_min(void)
{
	myflt min;
	myflt prev;
	myflt pprev;

	/* find min. exponent */
	for (min = 1, prev = 0; min < prev; min /=2) {
		pprev = prev;
		prev = min;
	}
	min = pprev;

	return min;
}

int main(void)
{
	printf("SCHAR_MIN: %d\n", SCHAR_MIN);
	printf("SCHAR_MAX: %d\n", SCHAR_MAX);
	printf("CHAR_MIN: %d\n", CHAR_MIN);
	printf("CHAR_MAX: %d\n", CHAR_MAX);
	printf("UCHAR_MAX: %d\n", UCHAR_MAX);
	printf("SHRT_MIN: %d\n", SHRT_MIN);
	printf("SHRT_MAX: %d\n", SHRT_MAX);
	printf("USHRT_MAX: %d\n", USHRT_MAX);
	printf("INT_MIN: %d\n", INT_MIN);
	printf("INT_MAX: %d\n", INT_MAX);
	printf("UINT_MAX: %u\n", UINT_MAX);
	printf("LONG_MIN: %ld\n", LONG_MIN);
	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("ULONG_MAX: %lu\n", ULONG_MAX);
	printf("LLONG_MIN: %lld\n", LLONG_MIN);
	printf("LLONG_MAX: %lld\n", LLONG_MAX);
	printf("ULLONG_MAX: %llu\n", ULLONG_MAX);
	printf("FLT_MIN: %a\n", FLT_MIN);
	printf("FLT_MAX: %a\n", FLT_MAX);
	printf("DBL_MIN: %a\n", DBL_MIN);
	printf("DBL_MAX: %a\n", DBL_MAX);
	printf("LDBL_MIN: %La\n", LDBL_MIN);
	printf("LDBL_MAX: %La\n", LDBL_MAX);
	printf("itmin: %lld\n", int_type_min());
	printf("itmax: %lld\n", int_type_max());
	printf("ftmin: %La\n", float_type_min());
	printf("ftmax: %La\n", float_type_max());
	return 0;
}
