/* Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

main()
{
	int c, blanks, tabs, newlines;

	blanks = tabs = newlines = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++blanks;
		if (c == '\t')
			++tabs;
		if (c == '\n')
			++newlines;
	}
	printf("Blanks: %d\nTabs: %d\nNewlines: %d\nTotal: %d",
			blanks, tabs, newlines, blanks + tabs + newlines);
}
