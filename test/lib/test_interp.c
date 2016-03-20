#include "test_interp.h"

void test_dummy(void** state) {}

const struct CMUnitTest InterpTests[] = {
    cmocka_unit_test(test_dummy),
};
