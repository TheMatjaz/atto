/**
 * @file
 * @brief
 * @copyright Copyright © 2019, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#ifndef ATTO_H
#define ATTO_H

#ifdef __cplusplus
extern "C"
{
#endif

#define ATTO_VERSION "0.1.0"

#include <stdio.h>  /* For printf() */
#include <math.h>   /* For fabs(), fabsf() */
#include <string.h> /* For strncmp() */

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
