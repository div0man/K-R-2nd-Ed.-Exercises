/* Exercise 2-2. Write a loop equivalent to the `for` loop above without using
 * `&&` or `||`.
 */

#include <stdio.h>

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* getline_nobool:  read a line into s, return length; version without boolean
 * operators */
int getline_nobool(char s[], int lim)
{
	int c, i, exit;

	for (i=0, exit=0; !exit; ) {
		if (i<lim-1) {
			if ((c=getchar()) != '\n') {
				if (c != EOF) {
					s[i] = c;
					++i;
				}
				else {
					exit = 1;
				}
			}
			else {
				exit = 1;
			}
		}
		else {
			exit = 1;
		}
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int main(void)
{
	char line[100];
	int len;
	while((len = getline_nobool(line, 100)) > 0)
		printf("%s", line);
	return 0;
}
