#include "test_interp.h"

void test_interpExp_numExp(void** state) {
    A_exp exp = A_NumExp(42);
    Table_ t = Table("a", 7, NULL);
    IntAndTable_ result = interpExp(exp, t);

    assert_int_equal(42, result.i);
    assert_ptr_equal(t, result.t);
}

void test_interpExp_idExp(void** state) {
    A_exp exp = A_IdExp("foo");
    Table_ t = Table("foo", 42, NULL);
    IntAndTable_ result = interpExp(exp, t);

    assert_int_equal(42, result.i);
    assert_ptr_equal(t, result.t);
}

void test_interpExp_idExp_nested(void** state) {
    A_exp exp = A_IdExp("foo");
    Table_ t = Table("a", 7, Table("foo", 19, NULL));
    IntAndTable_ result = interpExp(exp, t);

    assert_int_equal(19, result.i);
    assert_ptr_equal(t, result.t);
}

void test_interpExp_idOp(void** state) {
    A_exp exp = A_OpExp(A_NumExp(7), A_plus, A_NumExp(75));
    Table_ t = Table("a", 8, NULL);
    IntAndTable_ result = interpExp(exp, t);

    assert_int_equal(82, result.i);
    assert_ptr_equal(t, result.t);
}

void test_interpExp_idOp_nested(void** state) {
    A_exp exp = A_OpExp(
        A_NumExp(3),
        A_minus,
        A_OpExp(A_NumExp(8), A_div, A_IdExp("foo"))
    );
    Table_ t = Table("a", 14, Table("foo", 2, NULL));
    IntAndTable_ result = interpExp(exp, t);

    assert_int_equal(-1, result.i);
    assert_ptr_equal(t, result.t);
}

const struct CMUnitTest InterpTests[] = {
    cmocka_unit_test(test_interpExp_numExp),
    cmocka_unit_test(test_interpExp_idExp),
    cmocka_unit_test(test_interpExp_idExp_nested),
    cmocka_unit_test(test_interpExp_idOp),
    cmocka_unit_test(test_interpExp_idOp_nested),
};
