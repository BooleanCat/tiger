#include "test_statements.h"

static void test_maxargs_no_print(void** state) {
    // maxargs(stm) returns 0 when there are no print statements nested
    A_stm stm = A_AssignStm("a", A_NumExp(7));
    assert_int_equal(0, maxargs(stm));
}

static void test_maxargs_one(void** state) {
    // maxargs(stm) returns 1 when stm is an A_PrintStm with 1 member
    A_stm stm = A_PrintStm(A_LastExpList(A_NumExp(7)));
    assert_int_equal(1, maxargs(stm));
}

static void test_maxargs_two(void** state) {
    // maxargs(stm) returns 2 stm is an A_PrintStm with 2 members
    A_stm stm = A_PrintStm(
        A_PairExpList(
            A_NumExp(7),
            A_LastExpList(A_NumExp(42))
        )
    );
    assert_int_equal(2, maxargs(stm));
}

static void test_maxargs_four(void** state) {
    // maxargs(stm) returns 4 stm is an A_PrintStm with 4 members
    A_stm stm = A_PrintStm(
        A_PairExpList(
            A_NumExp(7),
            A_PairExpList(
                A_NumExp(42),
                A_PairExpList(
                    A_NumExp(-1),
                    A_LastExpList(A_NumExp(42))
                )
            )
        )
    );
    assert_int_equal(4, maxargs(stm));
}

static void test_maxargs_nested(void** state) {
    // maxargs(stm) can work with nested statements
    A_stm stm = A_CompoundStm(
        A_PrintStm(A_LastExpList(A_NumExp(7))),
        A_AssignStm("a", A_NumExp(7))
    );
    assert_int_equal(1, maxargs(stm));
}

static void test_maxargs_deep_nested(void** state) {
    // maxargs(stm) can work with deeply nested statements
    A_stm stm = A_CompoundStm(
        A_AssignStm("a", A_NumExp(0)),
        A_CompoundStm(
            A_PrintStm(A_PairExpList(
                A_NumExp(7),
                A_LastExpList(A_NumExp(42))
            )),
            A_AssignStm("a", A_NumExp(5))
        )
    );
    assert_int_equal(2, maxargs(stm));
}

static void test_maxargs_multiple(void** state) {
    // maxargs(stm) works with multiple 'A_printStm's
    A_stm stm = A_CompoundStm(
        A_PrintStm(A_PairExpList(
            A_NumExp(7),
            A_LastExpList(A_NumExp(9))
        )),
        A_PrintStm(A_LastExpList(A_NumExp(8)))
    );

    assert_int_equal(2, maxargs(stm));
}

static void test_maxargs_print_nested(void** state) {
    // maxargs(stm) works with prints within prints
    A_stm stm = A_PrintStm(A_LastExpList(
        A_EseqExp(
            A_PrintStm(
                A_PairExpList(
                    A_NumExp(7),
                    A_LastExpList(A_NumExp(8))
                )
            ),
            A_NumExp(42)
        )
    ));

    assert_int_equal(2, maxargs(stm));
}

static void test_maxargs_assign(void** state) {
    // maxargs(stm) works with prints within assignments
    A_stm stm = A_AssignStm(
        "a",
        A_EseqExp(
            A_PrintStm(A_LastExpList(A_NumExp(7))),
            A_NumExp(42)
        )
    );

    assert_int_equal(1, maxargs(stm));
}

static void test_maxargs_eseq(void** state) {
    A_stm stm = A_PrintStm(A_PairExpList(
        A_EseqExp(
            A_PrintStm(A_PairExpList(
                A_NumExp(8),
                A_PairExpList(
                    A_NumExp(9),
                    A_LastExpList(A_NumExp(10))
                )
            )),
            A_NumExp(18)
        ),
        A_LastExpList(A_NumExp(42))
    ));

    assert_int_equal(3, maxargs(stm));
}

static void test_maxargs_eseq_nested(void** state) {
    A_stm stm = A_PrintStm(A_LastExpList(
        A_EseqExp(
            A_PrintStm(A_LastExpList(A_NumExp(42))),
            A_EseqExp(
                A_PrintStm(A_PairExpList(
                    A_NumExp(8),
                    A_PairExpList(
                        A_NumExp(9),
                        A_LastExpList(A_NumExp(10))
                    )
                )),
                A_NumExp(7)
            )
        )
    ));

    assert_int_equal(3, maxargs(stm));
}

static void test_maxargs_complex(void** state) {
    // maxargs(stm) works with an arbitrary complex statement
    A_stm stm = A_CompoundStm(
        A_AssignStm(
            "a",
            A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))
        ),
        A_CompoundStm(
            A_AssignStm("b", A_EseqExp(
                A_PrintStm(A_PairExpList(
                    A_IdExp("a"),
                    A_LastExpList(
                        A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1))
                    )
                )),
                A_OpExp(A_NumExp(10), A_times, A_IdExp("a"))
            )),
            A_PrintStm(A_LastExpList(A_IdExp("b")))
        )
    );

    assert_int_equal(2, maxargs(stm));
}

void test_maxargs_exp_op(void** state) {
    A_stm stm = A_PrintStm(A_LastExpList(A_OpExp(
        A_EseqExp(
            A_PrintStm(A_PairExpList(
                A_NumExp(8),
                A_LastExpList(A_NumExp(9))
            )),
            A_NumExp(7)
        ),
        A_plus,
        A_NumExp(17)
    )));

    assert_int_equal(2, maxargs(stm));
}

void test_maxargs_exp_op_nested(void** state) {
    A_stm stm = A_PrintStm(A_LastExpList(A_OpExp(
        A_OpExp(
            A_OpExp(
                A_EseqExp(
                    A_PrintStm(A_PairExpList(
                        A_NumExp(7),
                        A_PairExpList(
                            A_NumExp(8),
                            A_LastExpList(A_NumExp(9))
                        )
                    )),
                    A_NumExp(14)
                ),
                A_plus,
                A_NumExp(5)
            ),
            A_times,
            A_NumExp(19)
        ),
        A_minus,
        A_NumExp(42)
    )));

    assert_int_equal(3, maxargs(stm));
}

const struct CMUnitTest StatementTests[] = {
    cmocka_unit_test(test_maxargs_no_print),
    cmocka_unit_test(test_maxargs_one),
    cmocka_unit_test(test_maxargs_two),
    cmocka_unit_test(test_maxargs_four),
    cmocka_unit_test(test_maxargs_nested),
    cmocka_unit_test(test_maxargs_deep_nested),
    cmocka_unit_test(test_maxargs_multiple),
    cmocka_unit_test(test_maxargs_print_nested),
    cmocka_unit_test(test_maxargs_assign),
    cmocka_unit_test(test_maxargs_eseq),
    cmocka_unit_test(test_maxargs_eseq_nested),
    cmocka_unit_test(test_maxargs_complex),
    cmocka_unit_test(test_maxargs_exp_op),
    cmocka_unit_test(test_maxargs_exp_op_nested),
};
