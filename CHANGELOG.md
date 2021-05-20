Changelog
===============================================================================

All notable changes to this project will be documented in this file.

The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

*******************************************************************************

[1.4.0] - 2021-05-21
----------------------------------------

Check for non-all-zero arrays, fixes to avoid compilation warnings,
CMake improvements 

### Added

- `atto_nzeros()` which is the opposite of `atto_zeros()`, checking that
  there is at least one non-zero value in the array of bytes.
  Useful to check whether a memory location has been initialised to non-zero
  values, especially for random strings or data from an outside
  source we don't know the exact format of.
- GitHub workflow scripts to build and self-test on different operating
  systems. Fancy badges in the readme included.


### Fixed

- CMake configuration now uses a more portable set of compiler flags,
  taken from LibAscon.
- Some macro arguments did not have round brackets around them.
- Self-test changed to avoid compilation warnings due to improper use of types
  (integers for float/double functions and signed/unsigned warnings).
- Cast the length values passed to `atto_zeros()` to `size_t` to avoid
  warnings about signed/unsigned integer comparison.
- Remove `.idea` folder from Git repo from now on.
- Fixed some typos/missing words in the BSD 3-Clause license text file.
- Renamed Doxygen build target to avoid name clashes.
- Fix typo in Doxygen config, now it should properly exclude the test
  and source file.



[1.3.1] - 2020-12-27
----------------------------------------

No changes in the code, only documentation.

### Fixed

- Missing home page of the Doxygen documentation (being the content of the
  Readme)
- Missing title of the v1.3.0 release.



[1.3.0] - 2020-12-27
----------------------------------------

Clickable links to failed assertions!


### Added

- `atto_true()` which simply maps to `atto_assert()` to have an opposite of
  `atto_false()` with consistent naming.


### Changed

- The printed text in case of a failed testcase now combines the filename
  and the line together in the format like `filename.c:42` with `42` being the
  line. This allows some IDEs to recognise it as a link to a specific code line
  and make them clickable for much easier testing and debugging.


### Fixed

- `atto_zeros(x, len)` supports any kind of address as `x`, even non `uint8_t*`
  thus allowing to scan arrays of other integers or floats or strings for
  zeros without explicitly casting them. They are converted to `uint8_t*`
  internally.

- Replace Doxyfile with CMake building it instead. Add stricter options.



[1.2.0] - 2020-02-05
----------------------------------------

Two more macros, some project structure changes (new `atto.c` file, new `src/` 
folder).


### Added

- `atto_memneq(a, b, len)`, the negation of `atto_memeq()`, checks that two
  memory segments are not equal.
- `atto_zeros(x, len)` checks that a memory segment is filled with zeros.


### Fixed

- Move `atto_at_least_one_fail` variable into new separate `atto.c` file.
  Required as importing `atto.h` file in many locations leads to many _static_
  copies of the same variable to be set, which means that different files see
  a different variable.
- Move selftest into subfolder `tst/`, moved `atto.h` and `atto.c` into `src/`
  Required as when incorporating this whole project (or repo)
  into another C project, the IDE may interpret selftest.c as part
  of the main project, while it's not relevant.
  With this trick, one can set the atto/src folder as the only relevant
  one.
- Variety of minor fixes in the readme.



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
