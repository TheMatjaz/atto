Atto - the microscopic C unit test framework
===============================================================================

[![Build Status Master](https://github.com/TheMatjaz/atto/actions/workflows/build_master.yml/badge.svg)](https://github.com/TheMatjaz/atto/actions/workflows/build_master.yml)
[![Build Status Develop](https://github.com/TheMatjaz/atto/actions/workflows/build_develop.yml/badge.svg)](https://github.com/TheMatjaz/atto/actions/workflows/build_develop.yml)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/TheMatjaz/atto)](https://github.com/TheMatjaz/atto/releases/latest)
[![GitHub](https://img.shields.io/github/license/TheMatjaz/atto)](https://github.com/TheMatjaz/atto/blob/master/LICENSE.md)

Atto is the simplest-to-use C unit test framework, in just one header file,
without `malloc()`, without `fork()`, without dependencies, ready for
embedded systems that can at least call `printf()`. And even those who cannot,
can easily adapt it!

Most probably you will understand most about Atto if you just read its
header: [`atto.h`](src/atto.h). I mean, **it's just 30 macros**.



Why should I use Atto instead of another framework?
-------------------------------------------------------

The goal of a unit test is generally very simple: verify that the obtained
value equals to the expected one. More generally if a boolean expression is
true (e.g. a value is in the allowed range).

There are so many complex unit test frameworks to do this in C and C++
which just increases complexity of the whole project. Suppose you are just
writing a simple program and want to test it. Oh boy! Start managing the
dependencies for the framework, check if you can install it, maybe you need
Docker etc. Some frameworks even require `fork()` - how could that work on
an embedded system?

Atto is born to remove all of that complexity. Heavily inspired by
[MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html), which has **just 3
lines of code**, Atto is just a header file you can include statically
(copy-paste) in your project and start writing your tests. Atto is so tiny that
even [its name means "tiny"](https://en.wikipedia.org/wiki/Atto-) ;)

The output is basic, but enough: indicates just where the test case failed, by
filename and line number. Open that file, go to that line. There is the error.
Start using the debugger around that point.

Passing tests are not printed, to avoid cluttering the output.



Dependencies
----------------------------------------

Only the C standard library!

- `stdio.h`, for `printf()` - if your system does not have it, replace the
  **one** call of `printf()` in `atto.h` with something else!
- `math.h`, for `fabs()`, `fabsf()`, `isnan()`, `isinf()`, `isfinite()`
- `string.h`, for `strncmp()`, `memcmp()`
- `stddef.h` for `size_t`

**No `malloc()` or `fork()` required**



How to use
----------------------------------------

### Basic idea and example

Use the `atto_*` macros in your test cases.

Here is an example where we test the `sqrt()` function from `math.h`:

```c
#include <math.h>
#include "atto.h"

void test_sqrt_valid_values(void)
{
    atto_eq(0.0, sqrt(0.0));
    atto_eq(1.0, sqrt(1.0));
    atto_eq(2.0, sqrt(4.0));
    atto_ddelta(1.4142, sqrt(2.0), 0.001);
    atto_ddelta(1.7321, sqrt(3.0), 1e-8); // This fails!
                                          // 1.7321 is not accurate enough
                                          // The test case stops here.
    atto_ddelta(2.2361, sqrt(5.0), 1e-8); // This is NOT executed!
}

void test_sqrt_negative_values(void)
{
    atto_nan(sqrt(-1.0));
}

int main(void)
{
    test_sqrt_valid_values();
    test_sqrt_negative_values();
    return atto_at_least_one_fail;
}
```


### Complete recipe

1. Add the files `atto.h`, `atto.c` to your project:
   - you can either copy the whole `src` folder into your project
   - or use `git subtree` to include this repo into your own
2. Create a file with your tests, say `test.c`.
3. Add test case functions returning `void` to `test.c`, as the two
  `test_sqrt_*` functions in the example above.
4. In each test case call `atto_assert()`, `atto_eq()`, `atto_flag()` etc.
   to verify the values you are testing. On a fail, the test case is terminated
   early and the following code is not executed.
5. Add a `main()` function to `test.c` which returns `atto_at_least_one_fail`.
   By doing so, the exit code of the test executable will be `1` in case at 
   least one test failed. Particularly useful when running the test executables
   in a pipeline that should stop when something is broken. Of course on 
   embedded systems one can use `atto_at_least_one_fail` in different ways, as
   there is no returning from `main`; for example by transmitting it via UART.
6. Call the test case functions from the `main()`.
7. Compile `test.c` into an executable and run it.
8. Check its standard output and the process exit code for failed tests.


### A test case is failing. Now what?

The output will contain one or more lines like:

```
FAIL | File: /path/to/some_project/test.c:182 | Test case: test_valid_input_length
```

1. Open the file `/path/to/some_project/test.c`
2. Go to line 182 (use some keyboard shortcut), which is in the function
   `test_valid_input_length()`
3. The assertion on that specific line failed. Now up to you to debug why.
   The easiest way is to place a debugger breakpoint earlier in the test case.
   
Once the standard output does not contains any `FAIL` lines and the exit code
of the process is `0`, you are good to go!


### This framework does not fit my needs!

It may not be the best solution for your scenario - it was born for my
personal projects and I needed something simple. You are more than welcome
to customize it to your needs within your project or simply
to use other frameworks.
