## Notes

### Take 1

Initially I thought that bits are counted using left-aligned index, i.e. counted
as `01234567` where `p = 2` and `n = 3` would mean bits `234`. My first take
solves the problem with that assumption in mind.

In the process, I learned that shifting for values greater than the type width
is [undefined][1], so I'm using `~(~0u >> (p + n - 1) >> 1)` instead of
`~(~0u >> (p + n))` to get around that for the edge case where `p = 0` and
`n = 32`.

### Take 2

Later I learned that the rest of the world [seems to count bits using
right-aligned index][2], i.e. counted as `76543210` where `p = 4` and `n = 3`
would mean bits `432`.

[1]: https://stackoverflow.com/questions/53783259/right-shift-inconsistent-behavior-when-shifting-for-type-width-related-to-kr-e

[2]: https://www.reddit.com/r/C_Programming/comments/a66zeq/why_am_i_finding_only_wrong_solutions_to_kr/
