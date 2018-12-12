/* Exercise 1-2. Experiment to find out what happens when printf's argument
 * string contains \c, where \c is some character not listed above.
 */

#include <stdio.h>

main()
{
	printf("hello, world\n");
	printf("g: \g\n");
	printf("0: \0\n");
	printf("8: \8\n");
	printf("s: \s\n");
	printf("z: \z\n");
}
