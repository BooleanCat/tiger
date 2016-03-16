#include "test_utils.h"

static void test_MAX(void** state) {
    // MAX(a, b) always returns the higher of a and b
    assert_int_equal(2, MAX(2, 1));
    assert_int_equal(3, MAX(1, 3));
    assert_int_equal(0, MAX(0, 0));
    assert_int_equal(-1, MAX(-1, -2));
}

const struct CMUnitTest UtilsTests[] = {
    cmocka_unit_test(test_MAX),
};
