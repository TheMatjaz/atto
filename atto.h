/**
 * @file
 * Atto - the microscopic C unit test framework
 *
 * @copyright Copyright © 2019, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-Clause License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS “AS IS”
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ATTO_H
#define ATTO_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Semantic version of this file and framework.
 */
#define ATTO_VERSION "1.0.0"

#include <stdio.h>  /* For printf() */
#include <math.h>   /* For fabs(), fabsf(), isnan(), isinf(), isfinite() */
#include <string.h> /* For strncmp() */

/**
 * Boolean indicating if all tests passed successfully (when 0) or not.
 *
 * Useful as a value to return from the main function of the test executable,
 * so that the test executable returns non-zero in case at least one test
 * failed.
 */
static char atto_at_least_one_fail = 0;

/**
 * Absolute tolerance when comparing two single-precision floating point
 * value for approximate-equality
 *
 * If the difference between the two float values is bigger than this
 * tolerance, the assertion fails.
 */
#define ATTO_FLOAT_EQ_ABSTOL (1e-5f)

/**
 * Absolute tolerance when comparing two double-precision floating point
 * value for approximate-equality.
 *
 * If the difference between the two double values is bigger than this
 * tolerance, the assertion fails.
 */
#define ATTO_DOUBLE_EQ_ABSTOL (1e-8)

/**
 * Verifies if the given boolean expression is true.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * It's the most generic macro offered by Atto. If you need something more
 * specific, try using the other macros instead.
 *
 * The `do-while(0)` construct allows to write multi-line macros.
 *
 * If your system does not support `printf()`, replace it with something
 * else in this file! For example a `transmit()` function to communicate
 * the result to other devices.
 *
 * Example:
 * ```
 * atto_assert(1);      // Passes
 * atto_assert(0);      // Fails
 * atto_assert(3 < 1);  // Fails
 * ```
 */
#define atto_assert(expression) do { \
    if (!(expression)) { \
        printf("FAIL | File: %s | Line: %4d | Test case: %s\n", \
               __FILE__, __LINE__, __func__); \
        atto_at_least_one_fail = 1U; \
        return; \
    } \
} while (0)

/**
 * Verifies if the given boolean expression is false.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_false(1);      // Fails
 * atto_false(0);      // Passes
 * ```
 */
#define atto_false(x) atto_assert(!(x))

/**
 * Verifies if the two arguments are exactly equal.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * It is recommended to use this macro instead of calling `atto_assert(a == b)`
 * to avoid mistyping the equality comparison operator `==` into the assignment
 * operator `=`.
 *
 * Example:
 * ```
 * atto_eq(12, 12);      // Passes
 * atto_eq(12.0f, 12U);  // Passes due to implicit conversion of 12U to 12.0f
 * atto_eq(100, 1);      // Fails
 * ```
 */
#define atto_eq(a, b) atto_assert((a) == (b))

/**
 * Verifies if the two arguments are not equal.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_neq(12, 12);      // Fails
 * atto_neq(12.0f, 12U);  // Fails
 * atto_neq(100, 1);      // Passes
 * ```
 */
#define atto_neq(a, b) atto_assert((a) != (b))

/**
 * Verifies if the first argument is strictly Greater Than the second.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_gt(1, 10);     // Fails
 * atto_gt(10, 10);    // Fails
 * atto_gt(100, 10);   // Passes
 * ```
 */
#define atto_gt(a, b) atto_assert((a) > (b))

/**
 * Verifies if the first argument is Greater or Equal to the second.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_ge(1, 10);     // Fails
 * atto_ge(10, 10);    // Passes
 * atto_ge(100, 10);   // Passes
 * ```
 */
#define atto_ge(a, b) atto_assert((a) >= (b))

/**
 * Verifies if the first argument is strictly Less Than the second.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_lt(1, 10);     // Passes
 * atto_lt(10, 10);    // Fails
 * atto_lt(100, 10);   // Fails
 * ```
 */
#define atto_lt(a, b) atto_assert((a) < (b))

/**
 * Verifies if the first argument is Less or Equal to the second.
 *
 * Otherwise stops the test case immediately and reports the failing file,
 * function and line number on standard output.
 *
 * Example:
 * ```
 * atto_le(1, 10);     // Passes
 * atto_le(10, 10);    // Fails
 * atto_le(100, 10);   // Fails
 * ```
 */
#define atto_le(a, b) atto_assert((a) <= (b))

/**
 * Verifies if two single-precision floating point values are within a given
 * absolute tolerance from each other.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_fdelta(1.0f, 1.00000001f, 0.1f);  // Passes
 * atto_fdelta(1.0f, 1.1f, 0.15f);        // Passes
 * atto_fdelta(1.0f, 2.0f, 0.1f);         // Fails
 * ```
 */
#define atto_fdelta(a, b, delta) atto_assert(fabsf((a) - (b)) <= fabsf(delta))

/**
 * Verifies if two single-precision floating point values are within a fixed
 * absolute tolerance #ATTO_FLOAT_EQ_ABSTOL from each other.
 *
 * Useful to check for almost-equality but ignoring minor rounding errors.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_fapprox(1.0f, 1.000001f);  // Passes
 * atto_fapprox(1.0f, 1.1);        // Fails
 * ```
 */
#define atto_fapprox(a, b) atto_fdelta((a), (b), ATTO_FLOAT_EQ_ABSTOL)

/**
 * Verifies if two double-precision floating point values are within a given
 * absolute tolerance from each other.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_ddelta(1.0, 1.00000001, 0.1);  // Passes
 * atto_ddelta(1.0, 1.1, 0.15);        // Passes
 * atto_ddelta(1.0, 2.0, 0.1);         // Fails
 * ```
 */
#define atto_ddelta(a, b, delta) atto_assert(fabs((a) - (b)) <= fabs(delta))

/**
 * Verifies if two double-precision floating point values are within a fixed
 * absolute tolerance #ATTO_DOUBLE_EQ_ABSTOL from each other.
 *
 * Useful to check for almost-equality but ignoring minor rounding errors.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_dapprox(1.0, 1.00000001);  // Passes
 * atto_dapprox(1.0, 1.1);         // Fails
 * ```
 */
#define atto_dapprox(a, b) atto_ddelta((a), (b), ATTO_DOUBLE_EQ_ABSTOL)

#define atto_nan(value) atto_assert(isnan(value))
#define atto_plusinf(value) atto_assert((isinf(value)) && (value > 0))
#define atto_minusinf(value) atto_assert((isinf(value)) && (value < 0))
#define atto_inf(value) atto_assert(isinf(value))
#define atto_finite(value) atto_assert(isfinite(value))
#define atto_notfinite(value) atto_assert(!isfinite(value))


/**
 * Verifies if the bits of the value specified by a bit mask are set to 1.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_flag(0x07, 1 << 1);  // Passes
 * atto_flag(0x07, 0x04);    // Passes
 * atto_flag(0x07, 0x06);    // Passes
 * atto_flag(0x07, 0xF0);    // Fails
 * ```
 */
#define atto_flag(value, mask) atto_assert(((value) & (mask)))

/**
 * Verifies if the bits of the value specified by a bit mask are set to 0.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_noflag(0x07, 1 << 5);  // Passes
 * atto_noflag(0x07, 0xF8);    // Passes
 * atto_noflag(0x07, 0x04);    // Fails
 * ```
*/
#define atto_noflag(value, mask) atto_assert(((value) & (mask)) == 0)

/**
 * Verifies if two strings are equal up to a given length or until the shortest
 * string terminates.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_streq("abcd", "abcd", 2);    // Passes
 * atto_streq("abcd", "abcd", 4);    // Passes
 * atto_streq("abcd", "abcd", 100);  // Passes, reached null terminator
 * atto_streq("abcd", "ABCD", 4);    // Fails, different casing
 * ```
 */
#define atto_streq(a, b, maxlen) atto_assert(strncmp((a), (b), (maxlen)) == 0)

/**
 * Verifies if two memory sections are equal up to a given length.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_memeq("abcd", "abcd", 2);    // Passes
 * atto_memeq("abcd", "abcd", 4);    // Passes
 * atto_memeq("abcd", "abcd", 100);  // UNDEFINED as exceeding known memory
 * atto_memeq("abcd", "ABCD", 4);    // Fails
 * ```
 */
#define atto_memeq(a, b, len) atto_assert(memcmp((a), (b), len) == 0)

/**
 * Forces a failure of the test case, stopping it and reporting on standard
 * output.
 */
#define atto_fail() atto_assert(0)

#ifdef __cplusplus
}
#endif

#endif  /* ATTO_H */
