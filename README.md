Atto - the microscopic C unit test framework
===============================================================================

Atto is the simplest-to-use C unit test framework, in just one header file,
without `malloc()`, without `fork()`, without dependencies, ready for
embedded systems that can at least call `printf()`. And even those who cannot,
can easily adapt it!

Most probably you will understand most about Atto if you just read its
file: [`atto.h`](atto.h). I mean, **it's just 34 lines of code**, documentation
excluded.



Why should I use Atto instead of _\<other framework\>_?
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
even [its name means "tiny"](https://en.wikipedia.org/wiki/Atto-).

The output is basic, but enough: indicates just where the test case failed, by
filename and line number. Open that file, go to that line. There is the error.
Done. Passing tests are not printed, to avoid cluttering the output.



Dependencies
----------------------------------------

Only the C standard library!

- `stdio.h`, for `printf()` - if your system does not have it, replace the
  **one** call of `printf()` with something else!
- `math.h`, for `fabs()`, `fabsf()`, `isnan()`, `isinf()`, `isfinite()`
- `string.h`, for `strncmp()`

**No `malloc()` or `fork()` required**


How to use
----------------------------------------

Use it in your test cases like in this example file where we test the `sqrt()`
function from `math.h`:

```c
#include <math.h>
#include "atto.h"

void test_sqrt_valid_values(void)
{
    atto_eq(1.0, sqrt(1.0));
    atto_eq(2.0, sqrt(4.0));
    atto_ddelta(1.4142, sqrt(2.0), 0.001);
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

An **example usage** is available in the [`example.c`](example.c) file!

1. Add `atto.h` to your project.
2. Create a file with your tests, say `test.c`, which will contain and run
   your tests.
3. Add a `main()` to `test.c` which returns `atto_at_least_one_fail`. By doing
   so, the return value will be 1 in case at least 1 test failed. Very useful
   when running the tests in a pipeline that should stop when something is
   broken. Of course on embedded systems one can use `atto_at_least_one_fail`
   in different ways, as there is no returning from `main`.
4. Add test case functions returning `void` to `test.c`.
5. In each test case call `atto_assert()`, `atto_fapprox()`, `atto_flag()` etc.
   to verify the values you are testing. On a fail, the test case is terminated
   (by a `return`).
6. Call the test case functions from the `main()`.
7. Compile `test.c` and run it.


### A test case is failing. Now what?

The output will contain one or more lines like:

```
FAIL | File: /my/home/folder/a_project/test.c | Line:  182 | Test case: test_valid_input_length
```

1. Open the file `/my/home/folder/a_project/test.c`
2. Go to line 182 (use some keyboard shortcut), which is in the function
   `test_valid_input_length()`
3. The assertion on that specific line failed. Now up to you to debug why.
