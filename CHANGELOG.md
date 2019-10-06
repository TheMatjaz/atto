Changelog
===============================================================================

All notable changes to this project will be documented in this file.

The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).


[1.1.0] - 2019-10-06
----------------------------------------

More specialized macros for operators and floats, simpler examples, self test.


### Added

- `atto_false(x)`, the negation of `atto_assert()`, to avoid forgetting the 
  `!` when calling something like `atto_assert(!x)`
- Equality, inequality and other comparision operators, in particular to avoid
  mistyping the operator, especially the `==` into an assignment `=`
  when calling something like `atto_assert(a == b)`
  - Equality `atto_eq(a, b)`
  - Inequality `atto_neq(a, b)`
  - Less-Than `atto_lt(a, b)`
  - Less-Equal `atto_le(a, b)`
  - Greater-Than `atto_gt(a, b)`
  - Greater-Equal `atto_ge(a, b)`
- Floating point equality with a custom absolute tolerance
  - For floats `atto_fdelta(a, b, abstol)`
  - For doubles `atto_ddelta(a, b, abstol)`
- Non-finite floating point values checks
  - Value is NaN `atto_nan(x)`
  - Value is +/- Infinity `atto_inf(x)`
  - Value is +Infinity `atto_plusinf(x)`
  - Value is -Infinity `atto_minusinf(x)`
  - Value is NaN or +/- Infinity `atto_notfinite(x)`
  - Value is anything but Nan or +/- Infinity `atto_finite(x)`
- Proper self-test `selftest.c` of the whole Atto framework.
- More compiler flags to check for errors during compilation of the self-test.


### Removed

- `example.c` test file. Instead a simpler example is provided within the
  Readme.



[1.0.0] - 2019-05-08
----------------------------------------

Initial version.


### Added

- Various macros to test an assertion:
  - `atto_assert()`
  - `atto_fapprox()`
  - `atto_dapprox()`
  - `atto_flag()`
  - `atto_noflag()`
  - `atto_streq()`
  - `atto_memeq()`
  - `atto_fail()`
