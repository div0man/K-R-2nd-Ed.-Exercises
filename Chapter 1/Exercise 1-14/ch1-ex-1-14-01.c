/* Exercise 1-14. Write a program to print a histogram of the
 * frequencies of different characters in its input.
 */

#include <stdio.h>

#define	NPRINT	94	/* Number of printable ASCII characters */
#define FPRINT	33	/* Character code of first printable ASCII
					 * character */
#define	CHWIDTH	72	/* Width for chart printout, the whole chart will be
					 * scaled to fit. */
int main()
{
	int c;
	int i, j;
	int histogram[NPRINT];
	char character[NPRINT];
	int maxCount;
	int maxCountW;
	float scale;

	for (i = 0; i < NPRINT; ++i) {
		histogram[i] = 0;
		character[i] = FPRINT + i;
	}

	/* Perform the counting */
	while ((c = getchar()) != EOF)
		if (c == character[c-FPRINT])
			++histogram[c-FPRINT];

	/* Chart Printing Section */

	/* Each histogram will look like:
	 * "C |******************** M",
	 * where C is the character, and M the histogram value */

	/* Find max. histogram value */
	maxCount = 0;
	for (i = 0; i < NPRINT; ++i) 
		if (maxCount < histogram[i])
			maxCount = histogram[i];

	/* Calculate number of digits of max. histogram value */
	maxCountW = 1;
	for (i = maxCount;  i >= 10;  i = i/10)
		++maxCountW;

	/* Calculate the scale */
	scale = 1.0*(CHWIDTH - 3 - 1 - maxCountW) / 
			maxCount;

	/* Fix a scale rounding bug */
	if (scale * maxCount < CHWIDTH - 3 - 1 - maxCountW)
		scale = scale + 0.000001;

	/* Print the chart only if CHWIDTH is sufficient to print at least
	 * the histogram values */
	if (maxCount * scale >= 0)
		/* Print horizontal histogram. */
		/* Row loop */
		for (i = 0; i < NPRINT; ++i) {
			/* Print the histogram label */
			printf("%c |", character[i]);
			/* Column loop, print the histogram */
			for (j = 1; j <= scale*histogram[i]; ++j)
				putchar('*');
			/* Print the histogram value */
			printf(" %d", histogram[i]);
			putchar('\n');
		}
	else {
		printf("Error: insufficient width specified, ");
		printf("unable to print.\n");
	}
}
