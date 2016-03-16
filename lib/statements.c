#include "statements.h"
#include <stdio.h>

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

int maxargs(A_stm stm) {
    int max = 0;
    int _max = 0;
    int seqMax = 0;
    A_expList expList = NULL;

    if (stm->kind == A_printStm) {
        expList = stm->u.print.exps;
        while (TRUE) {
            max++;
            if (expList->kind == A_lastExpList) {
                if (expList->u.last->kind == A_eseqExp) {
                    seqMax = maxargs(expList->u.last->u.eseq.stm);
                    _max = _max > seqMax ? _max : seqMax;
                }
                break;
            }
            expList = expList->u.pair.tail;
        }
        max = max > _max ? max : _max;
        return max;
    }
    else if (stm->kind == A_compoundStm) {
        if ((_max = maxargs(stm->u.compound.stm1)) > max)
            max = _max;
        if ((_max = maxargs(stm->u.compound.stm2)) > max)
            max = _max;
    }
    else if (stm->kind == A_assignStm) {
        if (stm->u.assign.exp->kind == A_eseqExp)
            return maxargs(stm->u.assign.exp->u.eseq.stm);
    }

    return max;
}
