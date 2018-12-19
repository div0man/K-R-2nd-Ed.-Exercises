/* **Exercise 4-1.** Write the function `strindex(s,t)` which returns the
 * position of the rightmost occurrence of `t` in `s`, or `-1` if there is none.
 */

#include <stdio.h>
#define MAXLINE 1000	/* maximum input line length */

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";	/* pattern to search for */

/* find all lines matching pattern */
int main(void)
{
	char line[MAXLINE];
	int found = 0;
	int ind;

	while (getline(line, MAXLINE) > 0)
		if ((ind = strindex(line, pattern)) >= 0) {
			printf("ind = %3d\t", ind);
			printf("%s", line);
			found++;
		}
	return found;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = (char)c;
	if (c == '\n')
		s[i++] = (char)c;
	s[i] = '\0';
	return i;
}

/* strindex: return index of rightmost `t` in `s`, `-1` if none */
int strindex(char s[], char t[])
{
	int i, j, k, ret;
	int found = 0;
	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			ret = i, found = 1;
	}
	return found ? ret : -1;
}
