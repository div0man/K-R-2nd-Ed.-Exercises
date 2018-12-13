/* **Exercise 2-4.** Write an alternate version of `squeeze(s1,s2)` that deletes
 * each character in `s1` that matches any character in the *string* `s2`.
 */

#include <stdbool.h>
#include <stdio.h>

/* haschar: returns true if string `s` contains at least one occurence of `c` */
bool haschar(char c, const char *s)
{
	for (size_t i = 0; s[i] != '\0'; ++i) {
		if (s[i] == c)
			return true;
	}
	return false;
}

/* squeeze: delete each character in `s1` that matches any character in `s2` */
void squeeze(char *s1, const char *s2)
{
	size_t i, j;
	for (i = j = 0; s1[i] != '\0'; ++i) {
		if (!haschar(s1[i], s2))
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}

int main(void)
{
	char s1[] = "abcdefghijklmnopqrstuvzxyabcdefghijklmnopqrstuvzxy";
	char s2[] = "qxy";

	squeeze(s1, s2);

	printf("%s\n", s1);
}
