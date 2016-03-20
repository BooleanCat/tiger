#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test_statements.h"
#include "test_utils.h"
#include "test_interp.h"

extern const struct CMUnitTest UtilsTests[UTILS_TESTS_TOTAL];
extern const struct CMUnitTest StatementTests[STATEMENT_TESTS_TOTAL];
extern const struct CMUnitTest InterpTests[INTERP_TESTS_TOTAL];

int main(int argc, char** argv) {
    int result;
    int end_result = 0;

    result = cmocka_run_group_tests(UtilsTests, NULL, NULL);
    end_result = result == 0 ? end_result : end_result + result;

    result = cmocka_run_group_tests(StatementTests, NULL, NULL);
    end_result = result == 0 ? end_result : end_result + result;

    result = cmocka_run_group_tests(InterpTests, NULL, NULL);
    end_result = result == 0 ? end_result : end_result + result;

    return end_result;
}
