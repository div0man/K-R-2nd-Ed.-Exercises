/* Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 */

#include <stdio.h>
#define MINLENGTH	50	/* min. line length for printout */
#define LINEBUF		51	/* buffer size, must be greater than MINLENGTH
						 * */

int getline(char line[], int maxline);

/* print all input lines which are longer than MINLENGTH */
main()
{
	int len;				/* length of string in the buffer */
	char line[LINEBUF];		/* line buffer */

	if (MINLENGTH < LINEBUF) {
		while ((len = getline(line, LINEBUF)) > 0) {
			if (len >= MINLENGTH) {
				printf("%s", line);
				/* If we didn't reach the endl with the first call,
				 * continue printing until the end is reached */
				if (len == LINEBUF-1 && line[LINEBUF-2] != '\n')
					while ((len = getline(line, LINEBUF)) > 0 &&
					printf("%s", line) &&
					line[len-1] != '\n')
						;
			}
		}
		return 0;
	}
	else {
		printf("Insufficient buffer specified\n");
		return -1;
	}
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
