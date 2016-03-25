#include "main.h"

extern UnitTest_ UtilsTests[UTILS_TESTS_TOTAL];
extern UnitTest_ StatementTests[STATEMENT_TESTS_TOTAL];
extern UnitTest_ InterpTests[INTERP_TESTS_TOTAL];

int main(int argc, char** argv) {
    int result;
    int end_result = 0;

    result = test_group(UtilsTests);
    end_result += result;

    result = test_group(StatementTests);
    end_result += result;

    result = test_group(InterpTests);
    end_result += result;

    return end_result;
}
