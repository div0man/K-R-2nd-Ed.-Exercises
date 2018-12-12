# Exercise 1-11.

How would you test the word count program? What kinds of input
are most likely to uncover bugs if there are any?

## Answer

To test, feed it various lists and compare against expected counts.

The kinds of inputs which are most likely to uncover bugs are those with edge
cases and special characters.

In our case the edge cases will have any of the
characters being used in control statements: `EOF`, `'\n'`, `' '`, `'\n'`,
`'\t'`. Also, we could test the extreme sizes of the input to see what happens
when the counters get too big.
