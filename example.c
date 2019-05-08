/**
 * @file
 * @brief
 * @copyright Copyright © 2019, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "atto.h"
#include <stdint.h>

static void test_case_ints(void)
{
    const int a = 1;
    const int b = 2;

    atto_assert(a < b);
    atto_assert(a == b);  /* This will fail and stop the test case. */
    atto_assert(40 < 2);  /* This will NOT be executed. */
}

static void test_case_flags(void)
{
    const uint_fast8_t flags = 0x83;

    atto_assert(flags);
    atto_flag(flags, 0x01U);
    atto_flag(flags, 0x81U);
    atto_noflag(flags, 0x04U);
    atto_noflag(flags, 0x02U);  /* This will fail. */
}

static void test_case_floats_and_doubles(void)
{
    const float radius = 0.4f;
    const float pi = 3.14159f;
    const float circle_area = pi * radius * radius;
    atto_assert(circle_area == 0.502654433f);  /* Exact value */
    atto_fapprox(circle_area, 0.5026544f);     /* Approximate value */

    const double d_radius = 0.4;
    const double d_pi = 3.141592653589793;
    const double d_circle_area = d_pi * d_radius * d_radius;
    atto_assert(d_circle_area == 0.5026548245743669); /* Exact value */
    atto_dapprox(d_circle_area, 0.50265482457);       /* Approximate value */

    atto_fapprox(1.000001f, 1.0f);
    atto_fapprox(1.0001f, 1.0f); /* This will fail. */
}

static void test_case_strings(void)
{
    char result[11] = {0};
    strcat(result, "hello");
    strcat(result, "world");
    atto_streq("helloworld", result, 11);
    atto_streq("helloworld", result, 20);
    atto_streq("helloworld", result, 6);
    atto_streq("HELLOworld", result, 11); /* This will fail. */
}

static void test_case_arrays(void)
{
    const char a1[4] = {1, 2, 3, 4};
    const char a2[4] = {1, 2, 3, 4};
    const char a3[4] = {1, 2, 120, 120};

    atto_memeq(a1, a2, 2);
    atto_memeq(a1, a2, 4);
    atto_memeq(a1, a3, 2);
    atto_memeq(a1, a3, 4);  /* This will fail. */
}

static void test_case_forced_fail(void)
{
    const uint_fast8_t data[5] = {0, 0, 0, 42, 0};
    uint_fast8_t i;
    for (i = 0; i < 5; i++)
    {
        if (data[i] != 0)
        {
            atto_fail();
        }
    }
}

int main(void)
{
    printf("Failures should appear on lines: %d, %d, %d, %d, %d, %d\n",
           18, 30, 48, 59, 71, 82);
    test_case_ints();
    test_case_flags();
    test_case_floats_and_doubles();
    test_case_strings();
    test_case_arrays();
    test_case_forced_fail();
    printf("The exit code of the program should be 1");
    return atto_at_least_one_fail;  /* Returns 1 as some tests failed. */
}
