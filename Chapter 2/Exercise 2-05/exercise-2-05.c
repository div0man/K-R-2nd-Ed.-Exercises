/* **Exercise 2-5.** Write the function `any(s1,s2)`, which returns the first
 * location in the string `s1` where any character from the string `s2` occurs,
 * or `-1` if `s1` contains no characters from `s2`. (The standard library
 * `strpbrk` does the same job but returns a pointer to the location.)
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

/* any: return index of first character in `s1` that matches any character in
 * `s2`. Returns `-1` if no match found. */
int any(const char *s1, const char *s2)
{
	for (int i = 0; s1[i] != '\0'; ++i) {
		if (haschar(s1[i], s2))
			return i;
	}
	return -1;
}

int main(void)
{
	char s1[] = "abcdefghijklmnopqrstuvzxyabcdefghijklmnopqrstuvzxy";
	char s2[] = "qxy";

	printf("%d\n", any(s1, s2));
}
