/* Exercise 1-13. Write a program to print a histogram of the lengths of words in
 * its input. It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 */

/* Solution 1: Horizontal Bars
 */

#include <stdio.h>

#define	MAXLEN	10	/* Any word longer than this will get counted in the >MAXLEN histogram.
					 * For output formatting, the program assumes this won't be greater than 999.
					 * */
#define	IN		1	/* inside a word */
#define	OUT		0	/* outside a word */

int main()
{
	int c, state;
	int i, j;
	int histo[MAXLEN+1];
	int counter;

	for (i = 0; i < MAXLEN+1; ++i)
		histo[i] = 0;

	/* Perform the counting */
	state = OUT;
	counter = 0;
	while ((c = getchar()) != EOF)
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN && counter > 0) {
				if (counter-1 < MAXLEN)
					++histo[counter-1];
				else
					++histo[MAXLEN];
			}
			state = OUT;
			counter = 0;
		}
		else {
			++counter;
			if (state == OUT)
				state = IN;
		}

	/* Print horizontal histogram. I'd use a function for formatting
	 * with regards to max. number of digits, but functions haven't
	 * been introduced yet.
	 * */
	for (i = 0; i < MAXLEN; ++i) {
		if (MAXLEN < 10)
			printf(" %1d | ", i+1);
		else if (MAXLEN < 100)
			printf(" %2d |", i+1);
		else
			printf(" %3d |", i+1);
		for (j = 0; j < histo[i]; ++j)
			putchar('*');
		putchar('\n');
	}
	if (MAXLEN < 10)
		printf(">%1d |", i);
	else if (MAXLEN < 100)
		printf(">%2d |", i);
	else
		printf(">%3d |", i);
	for (j = 0; j < histo[i]; ++j)
		putchar('*');
	putchar('\n');
}
