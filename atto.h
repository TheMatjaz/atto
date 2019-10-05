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
#include <math.h>   /* For fabs(), fabsf() */
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
 * value.
 *
 * If the difference between the two float values is bigger than this
 * tolerance, the assertion fails.
 */
#define ATTO_FLOAT_EQ_ABSTOL (1e-5f)

/**
 * Absolute tolerance when comparing two double-precision floating point
 * value.
 *
 * If the difference between the two double values is bigger than this
 * tolerance, the assertion fails.
 */
#define ATTO_DOUBLE_EQ_ABSTOL (1e-8)

/**
 * Verifies if the given boolean expression is true.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * The `do-while(0)` construct allows to write multi-line macros.
 *
 * Example:
 * ```
 * atto_assert(1);      // Passes
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

#define atto_false(x) atto_assert(!(x))
#define atto_eq(a, b) atto_assert((a) == (b))
#define atto_neq(a, b) atto_assert((a) != (b))
#define atto_gt(a, b) atto_assert((a) > (b))
#define atto_ge(a, b) atto_assert((a) >= (b))
#define atto_lt(a, b) atto_assert((a) < (b))
#define atto_le(a, b) atto_assert((a) <= (b))

/**
 * Verifies if two single-precision floating point values are closer than
 * the float absolute tolerance #ATTO_FLOAT_EQ_ABSTOL.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_assert(1.0f == 1.00000001f);  // Fails
 * atto_fapprox(1.0f, 1.00000001f);   // Passes
 * atto_fapprox(1.0f, 2.0f);          // Fails
 * ```
 */
#define atto_fapprox(a, b) atto_assert(fabsf((a)-(b)) <= ATTO_FLOAT_EQ_ABSTOL)
#define atto_fdelta(a, b, delta) atto_assert(fabsf((a) - (b)) <= fabsf(delta))

/**
 * Verifies if two double-precision floating point values are closer than
 * the double absolute tolerance #ATTO_DOUBLE_EQ_ABSTOL.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_assert(1.0 == 1.00000001);  // Fails
 * atto_dapprox(1.0, 1.00000001);   // Passes
 * atto_dapprox(1.0, 2.0);          // Fails
 * ```
 */
#define atto_dapprox(a, b) atto_assert(fabs((a)-(b)) <= ATTO_DOUBLE_EQ_ABSTOL)
#define atto_ddelta(a, b, delta) atto_assert(fabs((a) - (b)) <= fabs(delta))

/**
 * Verifies if the bits of the value specified as a bit mask is set to 1.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_flag(7, 0x04);  // Passes
 * atto_flag(7, 0x06);  // Passes
 * atto_flag(7, 0xF0);  // Fails
 * ```
 */
#define atto_flag(value, mask) atto_assert(((value) & (mask)))

/**
 * Verifies if the bits of the value specified as a bit mask is set to 0.
 *
 * Otherwise stops the test case and reports on standard output.
 *
 * Example:
 * ```
 * atto_flag(7, 0x04);  // Fails
 * atto_flag(7, 0xF8);  // Passes
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
 * atto_streq("abcd", "abcd", 100);  // Passes
 * atto_streq("abcd", "ABCD", 4);    // Fails
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
