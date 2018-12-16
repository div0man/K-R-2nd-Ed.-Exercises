/* **Exercise 3-01.** Our binary search makes two tests inside the loop, when
 * one would suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TESTSIZE (1024*1024)
#define NRUNS 100

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
	mid = (low+high) / 2;
	while (low <= high && x != v[mid]) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (x == v[mid])
		return mid;
	return -1;  /* no match */
}

int main(void)
{
	srand((unsigned int)time(NULL));

	/* populate test array */
	int test[TESTSIZE];
	for (int i = 0; i < TESTSIZE; ++i)
		test[i] = i;

	/* benchmark */
	double avg_diff = 0;
	printf("       x\tclocks_old\tclocks_new\n");
	printf("------------------------------------------\n");
	for (int i = 0; i < NRUNS; ++i) {
		/* random search value */
		int x = rand();
		x = (int)(x * ((double)TESTSIZE / RAND_MAX));

		/* measure number of clocks for each function */
		clock_t start, end;
		clock_t clocks_old, clocks_new;
		/* old */
		start = clock();
		binsearch_old(x, test, TESTSIZE);
		end = clock();
		clocks_old = (end - start);
		/* new */
		start = clock();
		binsearch_new(x, test, TESTSIZE);
		end = clock();
		clocks_new = (end - start);
		/* update the average time difference */
		avg_diff = (avg_diff * i + ((double)clocks_new -
				(double)clocks_old)) / (i + 1);

		printf("%8d\t%10ld\t%10ld\n", x, clocks_old, clocks_new);
	}
	printf("------------------------------------------\n");
	printf("Average difference, clocks: %f\n", avg_diff);

	return 0;
}
