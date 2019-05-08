/**
 * @file
 * @brief Atto - the microscopic C unit test framework
 * @copyright Copyright © 2019, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license Copyright © 2019, Matjaž Guštin <dev@matjaz.it> <https://matjaz.it>
 * All rights reserved.
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
 *
 */
static char atto_at_least_one_fail = 0U;

#define ATTO_FLOAT_EQ_ABSTOL 1e-5f
#define ATTO_DOUBLE_EQ_ABSTOL 1e-8

#define atto_assert(expression) do { \
    if (!(expression)) { \
        printf("FAIL | File: %s | Line: %4d | Test case: %s\n", \
               __FILE__, __LINE__, __func__); \
        atto_at_least_one_fail = 1U; \
        return; \
    } \
} while (0)

#define atto_fapprox(a, b) atto_assert(fabsf((a)-(b)) <= ATTO_FLOAT_EQ_ABSTOL)
#define atto_dapprox(a, b) atto_assert(fabs((a)-(b)) <= ATTO_DOUBLE_EQ_ABSTOL)
#define atto_flag(value, mask) atto_assert(((value) & (mask)) == 1)
#define atto_noflag(value, mask) atto_assert(((value) & (mask)) == 0)
#define atto_streq(a, b, maxlen) atto_assert(strncmp((a), (b), (maxlen)) == 0)
#define atto_fail() atto_assert(0)

#ifdef __cplusplus
}
#endif

#endif  /* ATTO_H */
