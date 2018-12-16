/* **Exercise 2-10.** Rewrite the function `lower`, which converts upper case
 * letters to lower case, with a conditional expression instead of `if-else`.
 */

#include <stdio.h>

/* lower:  convert c to lower case; ASCII only */
int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(void)
{
	char str[] = "----0000aaaAAAAbbbBBBFFzzzZZZxXXXX44[[[";
	for (size_t i = 0; str[i] != '\0'; ++i)
		str[i] = (char)lower(str[i]);
	printf("%s\n", str);
}
