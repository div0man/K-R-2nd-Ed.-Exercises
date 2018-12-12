/* Exercise 1-19. Write a function `reverse(s)` that reverses the character
 * string `s`. Use it to write a program that reverses its input a line at a
 * time.
 */

#include <stdio.h>
#define BUFSIZE 10 /* line buffer size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);
int reverseinput(char lastchar[]);

main()
{
	char lastchar[1];

	while (reverseinput(lastchar) != 0)
		if (lastchar[0] == '\n')
			putchar('\n');
	return 0;
}

/* reverseinput: read from input until end of line is reached and then
 * print the line in reverse */
int reverseinput(char lastchar[])
{
	int len;
	char line[BUFSIZE];
	int retval;
	
	if ((len = getline(line, BUFSIZE)) > 0) {
		if ((lastchar[0] = line[len-1]) == '\n') {
			line[len-1] = '\0';
			retval = 1;
		}
		else
			retval = reverseinput(lastchar);
		reverse(line);
		printf("%s", line);
	}
	else
		retval = 0;
	return retval;
}

/* getline: read a line into s, return length */
int getline(char s[],int lim)
{
	int c, i;

	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

/* reverse: reverse a '\0' terminated string */
void reverse(char s[])
{
	int tail;
	int head;
	char c;

	/* find the last character index */
	tail = 0;
	while (s[tail] != '\0')
		++tail;
	if (tail > 0)
		--tail;
	/* reverse the string by swapping first and last elements */
	for (head = 0; head < tail; ++head && --tail) {
		c = s[head];
		s[head] = s[tail];
		s[tail] = c;
	}
}

