/* Exercise 1-13. Write a program to print a histogram of the lengths of
 * words in its input. It is easy to draw the histogram with the bars
 * horizontal; a vertical orientation is more challenging.
 */

/* Solution 2: Vertical Bars
 */

#include <stdio.h>

#define	MAXLEN		20	/* Any word longer than this will get counted in
						 * the >MAXLEN histogram. */
#define	MAXHEIGHT	20	/* Height for chart printout.
						 * The whole chart will be scaled to fit. */

int main()
{
	int c;
	int readEOF;
	int alnumCount;
	int i, j, k, n, s;
	int wordCount[MAXLEN+1];	/* Last element will count the
								 * over-length words. */
	int wordCountD[MAXLEN+1];
	int maxWordCount;
	int maxWordCountD;
	int labelD[MAXLEN+1];
	float scale;
	int npow;

	for (i = 0; i <= MAXLEN; ++i)
		wordCount[i] = 0;

	/* Perform the counting */
	alnumCount = 0;
	readEOF = 0;	/* State to avoid having to repeat code just for the
					 * last word, should it be terminated with EOF. */
	c = getchar();
	while (readEOF == 0) {
		if ((c >= '0' && c <= '9') || 
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'))
			++alnumCount;
		else {
			if (alnumCount > 0) {
				if (alnumCount <= MAXLEN)
					++wordCount[alnumCount-1];
				else
					++wordCount[MAXLEN];
				alnumCount = 0;
			}
		}
		if ((readEOF = (c == EOF)) == 0)	/* ! operator not introduced
											 * yet */
			c = getchar();
	}

	/* Chart Printing Section
	 * */
	/* The chart will look like:
	 *          N      
	 *      1 1 * 1 1  
	 *      * * * * * 0
	 *      - - - - - -
	 *      1 2 3 4 M >
	 *                M
	 * showing both the label and the histogram value, so we can display
	 * accurate information in addition to scaled graphical
	 * representation.
	 * */

	/* Calculate number of digits for each histogram count,
	 * and find the maximums for both the count & number of digits */
	maxWordCount = 0;
	maxWordCountD = 0;
	for (i = 0; i <= MAXLEN; ++i) {
		wordCountD[i] = 1;
		for (j = wordCount[i];  j >= 10;  j = j/10)
			++wordCountD[i];
		if (maxWordCount < wordCount[i])
			maxWordCount = wordCount[i];
		if (maxWordCountD < wordCountD[i])
			maxWordCountD = wordCountD[i];
	}

	/* Calculate number of digits for each label */
	for (i = 0; i < MAXLEN; ++i) {
		labelD[i] = 1;
		for (j = i + 1;  j >= 10;  j = j/10)
			++labelD[i];
	}
	labelD[MAXLEN] = labelD[MAXLEN-1];

	/* Calculate the scale factor */
	scale = 1.0*(MAXHEIGHT - maxWordCountD - 1 - 1 - labelD[MAXLEN]) / 
			maxWordCount;

	/* Fix a scale rounding bug resulting in chart being 1 line
	 * shorter for some cases */
	if (scale * maxWordCount < MAXHEIGHT - maxWordCountD - 1 - 1 - 
		labelD[MAXLEN])
		scale = scale + 0.000001;

	/* Print the chart only if MAXHEIGHT is sufficient to print at least
	 * the values */
	if (maxWordCount * scale >= 0) {
		/* Print vertical histogram. */

		/* Row loop, plot count & histograms */
		for (i = MAXHEIGHT - 1 - 1 - labelD[MAXLEN]; i > 0; --i) {
			/* Column loop */
			for (j = 0; j <= MAXLEN; ++j) {
				if (i <= wordCount[j] * scale)
					printf("* ");
				else {
					/* What digit do we have to print? */
					n = wordCountD[j] - (i - wordCount[j] * scale) + 1;
					if (n > 0) {
						n = wordCountD[j] + 1 - n;
						npow = 1;
						for (k = n; k > 1; --k)
							npow = npow * 10;
						/* Calculate & print the required digit.
						 * Note: % operator not yet introduced. */
						printf("%d ", (wordCount[j]/npow) - 
						(wordCount[j]/npow)/10*10);
					}
					else
						printf("  ");
				}
			}
		putchar('\n');
		}
		/* Column loop, plot axis */
		for (j = 0; j <= MAXLEN; ++j)
			printf("--");
		putchar('\n');
		/* Row loop, plot labels */
		for (i = 0; i <= labelD[MAXLEN]; ++i) {
			/* Column loop */
			for (j = 0; j <= MAXLEN; ++j) {
				/* Tweak for the last label, print '>' and "virtually"
				 * shift the row further on. */
				if ((s = (j == MAXLEN)) && i == 0)
					printf("> ");
				/* What digit do we have to print? */
				n = labelD[j] - (i-s);
				if (n > 0 && n <= labelD[j]) {
					npow = 1;
					for (k = n; k > 1; --k)
						npow = npow * 10;
					/* Calculate & print the required digit.
					 * Note: % operator not yet introduced. */
					printf("%d ", ((j+1-s) / npow) - 
						((j+1-s) / npow)/10*10);
				}
				else
					printf("  ");
			}
			putchar('\n');
		}
	}
	else
		printf("Error: insufficient screen width for print-out.\n");
}
