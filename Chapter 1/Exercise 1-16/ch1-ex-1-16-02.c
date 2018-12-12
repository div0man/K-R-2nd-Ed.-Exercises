/* Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much as
 * possible of the text.
 */

/* Some optimization after comments received:
 * https://codereview.stackexchange.com/a/205992/181968 */

#include <stdio.h>
#define MAXLINE 10			/* buffer size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line length and the line itself or the first
 * MAXLINE-1 characters if the line couldn't fit in the buffer */
main()
{
	int len;				/* current line length */
	int max;				/* maximum length seen so far */
	char line[MAXLINE];		/* current [beginning of] line */
	char longest[MAXLINE];	/* [beginning of] longest line saved here */
	int c;
	
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0) {
		/* If we didn't reach the endl, consume the input until
		 * the end is reached while keeping track of the length */
		if (len == MAXLINE-1 && line[MAXLINE-2] != '\n')
			while ((c=getchar())!=EOF && ++len && c!='\n')
				;
		if (len > max) {
				max = len;
				copy(longest, line);
		}
	}

	if (max > 0) {	/* there was a line */
		if (max > MAXLINE-1) {
			printf("Longest line length: %d, first ", max);
			printf("%d characters: \n%s\n", MAXLINE-1, longest);
		}
		else
			printf("Longest line length: %d; longest line: \n%s\n", max,
			longest);
	}
	return 0;
}

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	
	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
