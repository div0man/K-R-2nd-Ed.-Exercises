# Exercise 2-9

## Task

In a two's complement number system, `x &= (x-1)` deletes the
rightmost 1-bit in `x`. Explain why. Use this observation to write a faster
version of `bitcount`.

## Answer

In a two's complement number system, subtracting 1 from any non-zero `x` will
erase the rightmost 1-bit, and flip all bits left of it to 1. This makes the
bits right of and including the rightmost 1-bit in `x` become an inverse of
themselves in `(x-1)`. Performing `&` with the inverse results in all 0s. Since
all the bits right of the rightmost 1-bit will be 0 to begin with, the only
change is that the rightmost 1-bit gets set to 0. All the bits left of the
rightmost bit will be the same in both `x` and `(x-1)` so they will remain
unchanged with the `&` operation.

Subtracting 1 from 0 works the same if we imagine an extra 1-bit on the right.
It sets all the bits to 1 but performing `&=` with 0 always results in 0 and so
at the end nothing is done and the result will be 0.

The above is illustrated in the table below.

      x      0     1     2     3     4     5     6     7
    ---   ----  ----  ----  ----  ----  ----  ----  ----
      x   0000  0001  0010  0011  0100  0101  0110  0111
    x-1   1111  0000  0001  0010  0011  0100  0101  0110
    ---   ----  ----  ----  ----  ----  ----  ----  ----
      &   0000  0000  0000  0010  0000  0100  0100  0110
    
      x     -1    -2    -3    -4    -5    -6    -7    -8
    ---   ----  ----  ----  ----  ----  ----  ----  ----
      x   1111  1110  1101  1100  1011  1010  1001  1000
    x-1   1110  1101  1100  1011  1010  1001  1000  0111
    ---   ----  ----  ----  ----  ----  ----  ----  ----
      &   1110  1100  1100  1000  1010  1000  1000  0000

This can help us optimize `bitcount` because it will let us skip over whatever
0-bits we have. We simply perform `x &= (x-1)` while `x > 0`, and count how many
times we had to do it.
