#include "test_utils.h"

static void test_MAX_same(void** state) {
    // MAX(a, a) returns a
    assert_int_equal(14, MAX(14, 14));
}

static void test_MAX_left(void** state) {
    // MAX(a, b) returns a when a > b
    assert_int_equal(3, MAX(3, 2));
}

static void test_MAX_right(void** state) {
    // MAX(a, b) returns b when a < b
    assert_int_equal(-4, MAX(-19, -4));
}

const struct CMUnitTest UtilsTests[] = {
    cmocka_unit_test(test_MAX_same),
    cmocka_unit_test(test_MAX_left),
    cmocka_unit_test(test_MAX_right),
};
