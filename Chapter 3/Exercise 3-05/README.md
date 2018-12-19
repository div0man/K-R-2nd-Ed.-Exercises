# Exercise 3-5

Write the function `itob(n,s,b)` that converts the integer `n` into a base `b`
character representation in the string `s`. In particular, `itob(n,s,16)`
formats `s` as a hexadecimal integer in `s`.

## Notes

Since the base must be positive, at first I thought that using `unsigned int b`
makes sense here. However, this introduces a complication for negative numbers
because any negative `n` would become positive after `n /= b;`. This is because
`n` is first promoted to `unsigned` and then divided by `b` and assigned to `n`.
