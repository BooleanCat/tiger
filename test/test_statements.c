#include "test_statements.h"

static void test_maxargs_no_print(void **state) {
    // maxargs(stm) returns 0 when there are no print statements nested
    A_stm stm = A_AssignStm(
        "a",
        A_NumExp(7)
    );

    assert_int_equal(0, maxargs(stm));
}

const struct CMUnitTest StatementTests[] = {
    cmocka_unit_test(test_maxargs_no_print)
};
