#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test_statements.h"
#include "test_utils.h"
#include "test_interp.h"

typedef const struct CMUnitTest UnitTest_;

#define test_group(group) cmocka_run_group_tests(group, NULL, NULL)

#endif
