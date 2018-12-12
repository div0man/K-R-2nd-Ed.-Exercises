/* Exercise 1-13. Write a program to print a histogram of the lengths of
 * words in its input. It is easy to draw the histogram with the bars
 * horizontal; a vertical orientation is more challenging.
 * */
/* Solution 1: Horizontal Bars
 * Take 2: Implementing some comments received from SE:
 * https://codereview.stackexchange.com/questions/205674#205680
 * but sticking to the techniques which have been introduced up to this
 * point in K&R, which means the following is NOT used:
 * 		- variable declaration where first initialized,
 * 		- assignment of char array constants,
 * 		- %*d format specifier,
 * 		- <ctype.h>.
 * Some other improvements:
 * 		- avoided repeating some code by introducing `readEOF` state,
 * 		- improved scaling,
 * 		- check whether MAXWIDTH is sufficient to print the smallest
 * 			possible chart,
 * 		- printing numerical value next to histogram,
 * 		- figured out how to print labels better, while sticking to the
 * 			techniques introduced so far,
 * 		- limited source code width to 72,
 * 		- fixed a scaling bug due to flating point precision,
 * 		- reverted to storing >MAXLEN count in the last element.
 * */
#include <stdio.h>

#define	MAXLEN		10	/* Any word longer than this will get counted in
						 * the >MAXLEN histogram. */
#define	MAXWIDTH	72	/* Max. width for chart printout, the whole
						 * chart will be scaled to fit. */

int main()
{
	int c;
	int i, j;
	int histogram[MAXLEN+1]; /* last element will count the over-length
							  * words */
	int alnumCount;
	int readEOF;
	int labelW;
	int maxLabelW;
	int maxWordCount;
	int maxWordCountW;
	float scale;

	for (i = 0; i <= MAXLEN; ++i)
		histogram[i] = 0;

	/* Perform the counting */
	alnumCount = 0;
	readEOF = 0;
	c = getchar();
	while (readEOF == 0) {
		if ((c >= '0' && c <= '9') || 
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'))
			++alnumCount;
		else {
			if (alnumCount > 0) {
				if (alnumCount <= MAXLEN)
					++histogram[alnumCount-1];
				else
					++histogram[MAXLEN];
				alnumCount = 0;
			}
		}
		if ((readEOF = (c == EOF)) == 0)
			c = getchar();
	}

	/* Chart Printing Section
	 * */
	/* Each histogram will look like:
	 * ">NNN |******************** MMM",
	 * showing both the label and the histogram value, so we can display
	 * accurate information even if the chart is scaled.
	 * To be able to plot on a fixed screen width, we must calculate the
	 * max. histogram value, the widths of NNN & MMM fields, and finally
	 * the scale.
	 * */

	/* Find max. histogram value */
	maxWordCount = 0;
	for (i = 0; i <= MAXLEN; ++i) 
		if (maxWordCount < histogram[i])
			maxWordCount = histogram[i];

	/* Calculate histogram value max. width */
	maxWordCountW = 1;
	for (i = maxWordCount;  i >= 10;  i = i/10)
		++maxWordCountW;

	/* Calculate label max. width */
	maxLabelW = 1;
	for (i = MAXLEN;  i >= 10;  i = i/10)
		++maxLabelW;

	/* Calculate the scale */
	/* Note - histogram layout: ">NNN |******************** MMM". */
	scale = 1.0*(MAXWIDTH - 1 - maxLabelW - 2 - 1 - maxWordCountW) / 
			maxWordCount;

	/* Fix a scale rounding bug */
	if (scale * maxWordCount < MAXWIDTH - 1 - maxLabelW - 2 - 1 - 
		maxWordCountW)
		scale = scale + 0.000001;

	/* Print the chart only if MAXWIDTH is sufficient to print at least
	 * the values */
	if (maxWordCount * scale >= 0)
		/* Print horizontal histogram. */
		/* Row loop */
		for (i = 0; i <= MAXLEN; ++i) {
			/* Print either the " " or ">" for the last histogram */
			if (i < MAXLEN)
				putchar(' ');
			else
				putchar('>');

			/* Calculate the label width */
			labelW = 1;
			for (j = i+1;  j >= 10;  j = j/10)
				++labelW;

			/* Print blanks as required for lavel alignment and print
			 * the label */
			for (j = maxLabelW - labelW; j > 0; --j)
				putchar(' ');
			if (i < MAXLEN)
				printf("%d |", i+1);
			else
				printf("%d |", MAXLEN);

			/* Column loop, print the histogram */
			for (j = 1; j <= scale*histogram[i]; ++j)
				putchar('*');

			/* Print the histogram value */
			printf(" %d", histogram[i]);
			putchar('\n');
		}
	else
		printf("Error: insufficient screen width for print-out.\n");
}
