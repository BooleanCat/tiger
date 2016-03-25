#include "statements.h"

A_stm A_CompoundStm(A_stm stm1, A_stm stm2) {
    A_stm s = NewA(s);
    s->kind = A_compoundStm;
    s->u.compound.stm1 = stm1;
    s->u.compound.stm2 = stm2;

    return s;
}

A_stm A_AssignStm(string id, A_exp exp) {
    A_stm s = NewA(s);
    s->kind = A_assignStm;
    s->u.assign.id = id;
    s->u.assign.exp = exp;

    return s;
}

A_stm A_PrintStm(A_expList exps) {
    A_stm s = NewA(s);
    s->kind = A_printStm;
    s->u.print.exps = exps;

    return s;
}

A_exp A_IdExp(string id) {
    A_exp e = NewA(e);
    e->kind = A_idExp;
    e->u.id = id;

    return e;
}

A_exp A_NumExp(int num) {
    A_exp e = NewA(e);
    e->kind = A_numExp;
    e->u.num = num;

    return e;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right) {
    A_exp e = NewA(e);
    e->kind = A_opExp;
    e->u.op.left = left;
    e->u.op.oper = oper;
    e->u.op.right = right;

    return e;
}

A_exp A_EseqExp(A_stm stm, A_exp exp) {
    A_exp e = NewA(e);
    e->kind = A_eseqExp;
    e->u.eseq.stm = stm;
    e->u.eseq.exp = exp;

    return e;
}

A_expList A_PairExpList(A_exp head, A_expList tail) {
    A_expList e = NewA(e);
    e->kind = A_pairExpList;
    e->u.pair.head = head;
    e->u.pair.tail = tail;

    return e;
}

A_expList A_LastExpList(A_exp last) {
    A_expList e = NewA(e);
    e->kind = A_lastExpList;
    e->u.last = last;

    return e;
}

static int maxargs_compound(A_stm stm) {
    int max1 = maxargs(stm->u.compound.stm1);
    int max2 = maxargs(stm->u.compound.stm2);

    return MAX(max1, max2);
}

static int maxargs_assign(A_stm stm) {
    if (stm->u.assign.exp->kind == A_eseqExp)
        return maxargs(stm->u.assign.exp->u.eseq.stm);
    return 0;
}

static int maxargs_exp(A_exp);

static int maxargs_exp_eseq(A_exp exp) {
    int expMax = maxargs_exp(exp->u.eseq.exp);
    int stmMax = maxargs(exp->u.eseq.stm);

    return MAX(expMax, stmMax);
}

static int maxargs_exp_op(A_exp exp) {
    int left = maxargs_exp(exp->u.op.left);
    int right = maxargs_exp(exp->u.op.right);

    return MAX(left, right);
}

static int maxargs_exp(A_exp exp) {
    switch(exp->kind) {
        case A_eseqExp: return maxargs_exp_eseq(exp);
        case A_opExp:   return maxargs_exp_op(exp);
        default:        return 0;
    }
}

static int maxargs_print(A_stm stm) {
    int max = 0;
    int _max = 0;
    int expMax;
    A_expList expList = stm->u.print.exps;

    while (TRUE) {
        max++;
        if (expList->kind == A_lastExpList) {
            expMax = maxargs_exp(expList->u.last);
            _max = MAX(_max, expMax);
            break;
        } else {
            expMax = maxargs_exp(expList->u.pair.head);
            _max = MAX(_max, expMax);
        }

        expList = expList->u.pair.tail;
    }
    return MAX(max, _max);
}

int maxargs(A_stm stm) {
    switch (stm->kind) {
        case A_printStm:    return maxargs_print(stm);
        case A_compoundStm: return maxargs_compound(stm);
        case A_assignStm:   return maxargs_assign(stm);
    }
}
