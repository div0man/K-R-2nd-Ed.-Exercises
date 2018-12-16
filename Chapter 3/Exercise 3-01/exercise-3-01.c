/* **Exercise 3-01.** Our binary search makes two tests inside the loop, when
 * one would suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TESTSIZE (1024*1024)
#define NRUNS 100000

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch_old(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else  /* found match */
			return mid;
	}
	return -1;  /* no match */
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch_new(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	return (x == v[low]) ? low : -1;
}

int main(void)
{
	srand((unsigned int)time(NULL));

	/* populate test array */
	int test[TESTSIZE];
	for (int i = 0; i < TESTSIZE; ++i)
		test[i] = i;

	/* benchmark */
	clock_t cum_diff = 0;
	printf("       x\tclocks_old\tclocks_new\n");
	printf("------------------------------------------\n");
	int i;
	for (i = 0; i < NRUNS; ++i) {
		/* random search value */
		int x = rand();
		x = (int)(x * ((double)TESTSIZE / RAND_MAX));

		/* measure number of clocks for each function */
		clock_t start, end;
		clock_t clocks_old, clocks_new;
		/* old */
		#define TEST_OLD \
		start = clock();\
		binsearch_old(x, test, TESTSIZE);\
		end = clock();\
		clocks_old = (end - start)
		/* new */
		#define TEST_NEW \
		start = clock();\
		binsearch_new(x, test, TESTSIZE);\
		end = clock();\
		clocks_new = (end - start)
		/* repeating the tests seems to remove most of the bias */
		TEST_OLD;
		TEST_NEW;
		TEST_OLD;
		TEST_NEW;
		/* update the cumulative time difference */
		cum_diff += clocks_new - clocks_old;

		printf("%8d\t%10ld\t%10ld\n", x, clocks_old, clocks_new);
	}
	printf("------------------------------------------\n");
	printf("Average difference, clocks: %f\n", (double)cum_diff / i);

	return 0;
}
