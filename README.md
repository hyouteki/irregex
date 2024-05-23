# IRREGular EXpression
Regex expression matcher in c for the subset of conventional regex.

## Syntax
| Expression | Match clause |
| :-: | :- |
| c | matches any literal character `c` |
| . | matches any single character |
| ^ | matches the beginning of the input string |
| $ | matches the end of the input string |
| c* | matches zero or more occurrences of the character `c` |
| .*c | matches zero or more of any character until `c` |
| .*\0 | matches zero or more of any character until the end of input string |
| *c | matches zero or more of any character until `c` from the start of input string |

## Quick Start
``` bash
make
make test
```

## Examples
``` console
irregex "Hello .* " "Hello nosferatu Hello ninthcircle"
> Hello nosferatu

irregex "ir*e.ex" "irrrrrregex"
> irrrrrregex
```

## References
- [A Regular Expression Matcher - Brian Kernighan](https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html)
