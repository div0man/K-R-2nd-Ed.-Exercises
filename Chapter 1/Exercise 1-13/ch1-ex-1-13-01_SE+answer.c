/* Exercise 1-13. Write a program to print a histogram of the lengths of
   words in its input. It is easy to draw the histogram with the bars
   horizontal; a vertical orientation is more challenging. */

/* Solution 1: Horizontal Bars
 * */
#include <ctype.h>
#include <stdio.h>

#define MAXLEN  10  /* Any word longer than this will get counted in the
                       >MAXLEN histogram. */

#define MAXWIDTH 72             /* screen width available for bars */

int main()
{
    int histo[MAXLEN+1] = { 0 }; /* element 0 counts over-length words */

    /* Perform the counting */
    int counter = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (isalnum(c)) {
            ++counter;
        } else {
            if (counter > 0) {
                ++histo[counter <= MAXLEN ? counter : 0];
                counter = 0;
            }
        }
    }

    if (counter > 0) {
        ++histo[counter <= MAXLEN ? counter : 0];
    }

    /* Calculate sensible scale */
    double scale = 1.0;
    for (int i = 0;  i <= MAXLEN;  ++i) {
        if (histo[i] * scale > MAXWIDTH) {
            scale = 1.0 * MAXWIDTH / histo[i];
        }
    }

    /* how wide are the labels? */
    int width = 1;
    for (int i = MAXLEN;  i >= 10;  i /= 10) {
        ++width;
    }

    /* Write the output */
    for (int i = 1;  i <= MAXLEN;  ++i) {
        printf(" %*d | ", width, i);
        for (int j = 0;  j < histo[i] * scale;  ++j) { putchar('*'); }
        putchar('\n');
    }

    /* over-long words */
    printf(">%*d | ", width, MAXLEN);
    for (int j = 0; j < histo[0] * scale; ++j) { putchar('*'); }
    putchar('\n');
}
