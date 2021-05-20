/**
 * @file
 * Example usage of Atto and also the test for Atto itself.
 *
 * @copyright Copyright © 2019-2021, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "atto.h"
#include <stdint.h>

static size_t expected_failures_counter = 0;

#define SHOULD_FAIL(failing) \
    printf("Expected failure: "); \
    expected_failures_counter++; \
    failing

static void test_initially_no_test_have_failed(void)
{
    atto_eq(atto_at_least_one_fail, 0);
}

static void test_assert(void)
{
    atto_assert(1);
    SHOULD_FAIL(atto_assert(0));
}

static void test_true(void)
{
    atto_true(1);
    SHOULD_FAIL(atto_true(0));
}

static void test_false(void)
{
    atto_false(3000 < 0);
    atto_false(0);
    SHOULD_FAIL(atto_false(1));
}

static void test_eq(void)
{
    atto_eq(12, 12);
    atto_eq(12.0f, 12U);
    SHOULD_FAIL(atto_eq(100, 1));
}

static void test_neq(void)
{
    atto_neq(100, 1);
    SHOULD_FAIL(atto_neq(12, 12));
}

static void test_neq_casting(void)
{
    SHOULD_FAIL(atto_neq(12.0f, 12U));
}

static void test_gt(void)
{
    atto_gt(100, 1);
    SHOULD_FAIL(atto_gt(1, 100));
}

static void test_gt_equality(void)
{
    SHOULD_FAIL(atto_gt(100, 100));
}

static void test_ge(void)
{
    atto_ge(100, 1);
    SHOULD_FAIL(atto_ge(1, 100));
}

static void test_ge_equality(void)
{
    atto_ge(100, 100);
}

static void test_lt(void)
{
    atto_lt(1, 100);
    SHOULD_FAIL(atto_lt(100, 1));
}

static void test_lt_equality(void)
{
    SHOULD_FAIL(atto_lt(100, 100));
}

static void test_le(void)
{
    atto_le(1, 100);
    SHOULD_FAIL(atto_le(100, 1));
}

static void test_le_equality(void)
{
    atto_le(100, 100);
}

static void test_fapprox(void)
{
    atto_fapprox(1.0f, 1.0f);
    atto_fapprox(1.0f, 1U);
    atto_fapprox(1.0f, 1.000001f);
    SHOULD_FAIL(atto_fapprox(1.0f, 1.1f));
}

static void test_fdelta(void)
{
    atto_fdelta(1.0f, 1.0f, 0.01f);
    atto_fdelta(1.0f, 1.1f, 0.15f);
    atto_fdelta(1.0f, 1.000001f, 0.01f);
    atto_fdelta(1.0f, 1.00000001f, 0.1f);
    SHOULD_FAIL(atto_fdelta(1.0f, 1.1f, 0.01f));
}

static void test_fdelta_negatives(void)
{
    atto_fdelta(-1.0f, -1.0f, 0.01f);
    atto_fdelta(-1.0f, -1.0f, -0.01f);
    atto_fdelta(-1.0f, -1.000001f, 0.01f);
    atto_fdelta(-1.0f, -1.000001f, -0.01f);
    atto_fdelta(-1.0000001f, -1.0f, 0.01f);
    atto_fdelta(-1.0000001f, -1.0f, -0.01f);
    SHOULD_FAIL(atto_fdelta(-1.0f, -1.1f, 0.01f));
}

static void test_dapprox(void)
{
    atto_dapprox(1.0, 1.0);
    atto_dapprox(1.0, 1U);
    atto_dapprox(1.0, 1.00000001);
    SHOULD_FAIL(atto_dapprox(1.0, 1.1));
}

static void test_ddelta(void)
{
    atto_ddelta(1.0, 1.1, 0.15);
    atto_ddelta(1.0, 1.0, 0.01);
    atto_ddelta(1.0, 1.000001, 0.01);
    SHOULD_FAIL(atto_ddelta(1.0, 1.1, 0.01));
}

static void test_ddelta_negatives(void)
{
    atto_ddelta(-1.0, -1.0, 0.01);
    atto_ddelta(-1.0, -1.0, -0.01);
    atto_ddelta(-1.0, -1.000001, 0.01);
    atto_ddelta(-1.0, -1.000001, -0.01);
    atto_ddelta(-1.0000001, -1.0, 0.01);
    atto_ddelta(-1.0000001, -1.0, -0.01);
    SHOULD_FAIL(atto_ddelta(-1.0, -1.1, 0.01));
}

static void test_nan(void)
{
    atto_nan(NAN);
    atto_nan(nan(""));
    atto_nan(nanf(""));
}

static void test_nan_finite_float(void)
{
    SHOULD_FAIL(atto_nan(1.0f));
}

static void test_nan_finite_double(void)
{
    SHOULD_FAIL(atto_nan(1.0));
}

static void test_nan_infinity(void)
{
    SHOULD_FAIL(atto_nan(INFINITY));
}

static void test_inf(void)
{
    atto_inf(INFINITY);
    atto_inf(+INFINITY);
    atto_inf(-INFINITY);
}

static void test_inf_finite_float(void)
{
    SHOULD_FAIL(atto_inf(1.0f));
}

static void test_inf_finite_double(void)
{
    SHOULD_FAIL(atto_inf(1.0));
}

static void test_inf_nan(void)
{
    SHOULD_FAIL(atto_inf(NAN));
}

static void test_plusinf(void)
{
    atto_plusinf(INFINITY);
    atto_plusinf(+INFINITY);
    SHOULD_FAIL(atto_plusinf(-INFINITY));
}

static void test_plusinf_finite_float(void)
{
    SHOULD_FAIL(atto_plusinf(1.0f));
}

static void test_plusinf_finite_double(void)
{
    SHOULD_FAIL(atto_plusinf(1.0));
}

static void test_plusinf_nan(void)
{
    SHOULD_FAIL(atto_plusinf(NAN));
}

static void test_minusinf(void)
{
    atto_minusinf(-INFINITY);
    SHOULD_FAIL(atto_minusinf(INFINITY));
}

static void test_minusinf_finite_float(void)
{
    SHOULD_FAIL(atto_minusinf(1.0f));
}

static void test_minusinf_finite_double(void)
{
    SHOULD_FAIL(atto_minusinf(1.0));
}

static void test_minusinf_nan(void)
{
    SHOULD_FAIL(atto_minusinf(NAN));
}

static void test_notfinite(void)
{
    atto_notfinite(INFINITY);
    atto_notfinite(+INFINITY);
    atto_notfinite(-INFINITY);
    atto_notfinite(NAN);
    atto_notfinite(nanf(""));
    atto_notfinite(nan(""));
}

static void test_notfinite_finite_float(void)
{
    SHOULD_FAIL(atto_notfinite(1.0f));
}

static void test_notfinite_finite_double(void)
{
    SHOULD_FAIL(atto_notfinite(1.0));
}

static void test_finite(void)
{
    atto_finite(0.0f);
    atto_finite(-0.0f);
    atto_finite(0.0);
    atto_finite(-0.0);
    atto_finite(1.0f);
    atto_finite(1.0);
    atto_finite(-1.0f);
    atto_finite(-1.0);
}

static void test_finite_plusinf(void)
{
    SHOULD_FAIL(atto_finite(INFINITY));
}

static void test_finite_minusinf(void)
{
    SHOULD_FAIL(atto_finite(-INFINITY));
}

static void test_finite_nan_macro(void)
{
    SHOULD_FAIL(atto_finite(NAN));
}

static void test_finite_nan_call(void)
{
    SHOULD_FAIL(atto_finite(nan("")));
}

static void test_finite_nanf_call(void)
{
    SHOULD_FAIL(atto_finite(nanf("")));
}

static void test_flag(void)
{
    atto_flag(1, 1);
    atto_flag(0xFF, 1);
    atto_flag(0xFF, 2);
    atto_flag(0xFF, 3);
    atto_flag(0xFF, 0x0F);
    atto_flag(0xFF, 0xFF);
    atto_flag(0x18, 0x08);
    atto_flag(0x18, 0x10);
    atto_flag(0x07, 1 << 1);
    atto_flag(0x07, 0x04);
    atto_flag(0x07, 0x06);
    SHOULD_FAIL(atto_flag(0x07, 0xF0));
}

static void test_flag_when_none(void)
{
    /* atto_flag() checks for flag presence. To check for their absence,
     * atto_noflag() should be used instead; or even atto_eq(flags, 0). */
    SHOULD_FAIL(atto_flag(0, 0));
}

static void test_noflag(void)
{
    atto_noflag(0, 1);
    atto_noflag(2, 1);
    atto_noflag(3, 8);
    atto_noflag(0x0F, 0xF0);
    atto_noflag(0xFF, 0);
    atto_noflag(0, 0);
    atto_noflag(0x07, 1U << 5U);
    atto_noflag(0x07, 0xF8);
    SHOULD_FAIL(atto_noflag(0x07, 0x04));
}

static void test_streq(void)
{
    const char a[] = "hello";
    const char b[] = "hello";
    const char c[] = "HELLO";

    atto_streq(a, b, 0);
    atto_streq(a, b, 1);
    atto_streq(a, b, 2);
    atto_streq(a, b, 3);
    atto_streq(a, b, 4);
    atto_streq(a, b, 5);
    atto_eq(a[5], b[5]);
    atto_streq(a, b, 6); // Null terminator
    atto_streq("", "", 0);
    SHOULD_FAIL(atto_streq(a, c, 5));
}

static void test_memeq(void)
{
    const uint8_t a[] = {255, 255, 255, 255, 255};
    const uint8_t b[] = {255, 255, 255, 255, 255};
    const uint8_t c[] = {255, 255, 255, 255, 55};

    atto_memeq(a, b, 0);
    atto_memeq(a, b, 1);
    atto_memeq(a, b, 2);
    atto_memeq(a, b, 3);
    atto_memeq(a, b, 4);
    atto_memeq(a, b, 5);
    atto_memeq("", "", 0);
    atto_memeq("abcd", "abcd", 2);
    atto_memeq("abcd", "abcd", 4);
    SHOULD_FAIL(atto_memeq(c, a, 5));
}

static void test_memneq(void)
{
    const uint8_t a[] = {255, 255, 255, 255, 255};
    const uint8_t b[] = {255, 255, 255, 255, 255};
    const uint8_t c[] = {11, 22, 33, 44, 55};

    atto_memneq(a, c, 1);
    atto_memneq(a, c, 2);
    atto_memneq(a, c, 3);
    atto_memneq(a, c, 4);
    atto_memneq(a, c, 5);
    atto_memneq("abcd", "ABcd", 2);
    atto_memneq("abcd", "ABcd", 4);
    atto_memneq("abcd", "abcD", 4);
    SHOULD_FAIL(atto_memneq(a, b, 5));
}

static void test_zeros(void)
{
    const uint8_t a[] = {0, 0, 0, 0, 0};
    const uint8_t b[] = {0, 0, 255, 255, 255};
    const uint8_t c[] = {11, 22, 33, 0, 0};
    const uint32_t d[] = {0, 0, 0};

    atto_zeros(a, 0U);
    atto_zeros(a, 1U);
    atto_zeros(a, 2U);
    atto_zeros(a, 3U);
    atto_zeros(a, 4U);
    atto_zeros(a, 5U);
    atto_zeros(b, 2U);
    atto_zeros(d, 3U * sizeof(uint32_t));
    atto_zeros("\0\0\0", 3U);
    SHOULD_FAIL(atto_zeros(b, 5U));
}

static void test_nzeros(void)
{
    const uint8_t a[] = {0, 0, 0, 0, 0};
    const uint8_t b[] = {0, 0, 255, 255, 255};
    const uint8_t c[] = {11, 22, 33, 0, 0};

    atto_nzeros(b, 3U);
    atto_nzeros(c, 3U);
    atto_nzeros(c, 4U);
    atto_nzeros(c, 5U);
    atto_nzeros(&c[2], 1U);
    atto_nzeros(&c[2], 2U);
    atto_nzeros(&c[2], 3U);
    atto_nzeros("\0\0c\0", 4U);
    atto_nzeros("a\0c\0", 4U);
    atto_report();  // Dummy report somewhere to check it's working properly
    SHOULD_FAIL(atto_nzeros(a, 5U));
}

static void test_fail(void)
{
    SHOULD_FAIL(atto_fail());
}

static void test_at_the_end_some_tests_have_failed(void)
{
    atto_eq(atto_at_least_one_fail, 1);
}

int main(void)
{
    test_initially_no_test_have_failed();
    test_assert();
    test_true();
    test_false();
    test_eq();
    test_neq();
    test_neq_casting();
    test_gt();
    test_gt_equality();
    test_ge();
    test_ge_equality();
    test_lt();
    test_lt_equality();
    test_le();
    test_le_equality();
    test_fapprox();
    test_fdelta();
    test_fdelta_negatives();
    test_dapprox();
    test_ddelta();
    test_ddelta_negatives();
    test_nan();
    test_nan_finite_float();
    test_nan_finite_double();
    test_nan_infinity();
    test_inf();
    test_inf_finite_float();
    test_inf_finite_double();
    test_inf_nan();
    test_plusinf();
    test_plusinf_finite_float();
    test_plusinf_finite_double();
    test_plusinf_nan();
    test_minusinf();
    test_minusinf_finite_float();
    test_minusinf_finite_double();
    test_minusinf_nan();
    test_notfinite();
    test_notfinite_finite_float();
    test_notfinite_finite_double();
    test_finite();
    test_finite_plusinf();
    test_finite_minusinf();
    test_finite_nan_macro();
    test_finite_nanf_call();
    test_finite_nan_call();
    test_flag();
    test_flag_when_none();
    test_noflag();
    test_streq();
    test_memeq();
    test_memneq();
    test_zeros();
    test_nzeros();
    test_fail();
    test_at_the_end_some_tests_have_failed();
    atto_report();

    // This self-test should generate a very precise amount of expected
    // failures. If this is not the case, then something went wrong with the
    // self-test and a non-zero exit-code should be provided when this
    // executable ends.
    return expected_failures_counter != atto_counter_assert_failures;
}
