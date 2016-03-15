#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "test_statements.h"

extern const struct CMUnitTest StatementTests[STATEMENT_TESTS_TOTAL];

int main(int argc, char** argv) {
    return cmocka_run_group_tests(StatementTests, NULL, NULL);
}
