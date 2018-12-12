/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion.
 */

#include <stdio.h>

/* convert Celsius to Fahrenheit */
int fahrToCelsius(int fahr);

/* print Fahrenheit-Celsius table
 * 	for fahr = 0, 20, ..., 300 */
main()
{
	int fahr;
	int lower, upper, step;
	
	lower = 0;			/* lower limit of temperature table */
	upper = 300;		/* upper limit */
	step = 20;			/* step size */
	
	fahr = lower;
	while (fahr <= upper) {
		printf("%d\t%d\n", fahr, fahrToCelsius(fahr));
		fahr = fahr + step;
	}
	return 0;
}

int fahrToCelsius(int fahr)
{
	return 5 * (fahr-32) / 9;
}
