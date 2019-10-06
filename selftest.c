/**
 * @file
 * Example usage of `atto.h` and also the test for Atto itself.
 *
 * @copyright Copyright © 2019, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "atto.h"
#include <stdint.h>

#define SHOULD_FAIL(failing) printf("Expected failure: "); failing

static void test_initially_no_test_have_failed(void)
{
    atto_eq(atto_at_least_one_fail, 0);
}

static void test_assert(void)
{
    atto_assert(1);
    SHOULD_FAIL(atto_assert(0));
}

static void test_false(void)
{
    atto_false(3000 < 0);
    atto_false(0);
    SHOULD_FAIL(atto_false(1));
}

static void test_eq(void)
{
    atto_eq(100, 100);
    SHOULD_FAIL(atto_eq(100, 1));
}

static void test_neq(void)
{
    atto_neq(1, 100);
    SHOULD_FAIL(atto_neq(100, 100));
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
    atto_fapprox(1.0f, 1.000001f);
    SHOULD_FAIL(atto_fapprox(1.0f, 1.1f));
}

static void test_fdelta(void)
{
    atto_fdelta(1.0f, 1.0f, 0.01f);
    atto_fdelta(1.0f, 1.000001f, 0.01f);
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
    atto_dapprox(1.0, 1.00000001);
    SHOULD_FAIL(atto_dapprox(1.0, 1.1));
}

static void test_ddelta(void)
{
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

static void test_flag(void)
{
    // TODO this fails. Should it? atto_flag(0, 0);
    atto_flag(1, 1);
    atto_flag(0xFF, 1);
    atto_flag(0xFF, 2);
    atto_flag(0xFF, 3);
    atto_flag(0xFF, 0x0F);
    atto_flag(0xFF, 0xFF);
    atto_flag(0x18, 0x08);
    atto_flag(0x18, 0x10);
    SHOULD_FAIL(atto_flag(0x0F, 0x30));
}

static void test_noflag(void)
{
    atto_noflag(0, 1);
    atto_noflag(2, 1);
    atto_noflag(3, 8);
    atto_noflag(0x0F, 0xF0);
    atto_noflag(0xFF, 0);
    SHOULD_FAIL(atto_noflag(0x0F, 1));
}

static void test_streq(void)
{
    const char a[] = "hello";
    const char b[] = "hello";
    const char c[] = "WORLD";

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
    const uint8_t c[] = {11, 22, 33, 44, 55};

    atto_memeq(a, b, 0);
    atto_memeq(a, b, 1);
    atto_memeq(a, b, 2);
    atto_memeq(a, b, 3);
    atto_memeq(a, b, 4);
    atto_memeq(a, b, 5);
    atto_memeq("", "", 0);
    SHOULD_FAIL(atto_memeq(c, a, 5));
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
    test_false();
    test_eq();
    test_neq();
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
    test_flag();
    test_noflag();
    test_streq();
    test_memeq();
    test_fail();
    test_at_the_end_some_tests_have_failed();

    return 0;
}
