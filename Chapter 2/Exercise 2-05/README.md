## Notes

In function `any`, to support the biggest possible string we'd need to use
`size_t`. However, in that case we can't use signed type as a return value
because it could overflow. If we use unsigned type as return value, we could
instead return either the index of the character found or index of '\0'
character. Then, the user could test `s[retval] == '\0'` to find that no
character had been found.

With pointers, it's simpler because we'd either return the pointer to the
character or return the `NULL` pointer.
