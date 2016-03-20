#include "interp.h"

Table_ Table(string id, int value, struct table* tail) {
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;

    return t;
}

Table_ interpStm(A_stm stm, Table_ t) {
    return Table("Foo", 7, t);
}

static IntAndTable_ interpExpNum(A_exp exp, Table_ t) {
    IntAndTable_ r;
    r.i = exp->u.num;
    r.t = t;

    return r;
}

static IntAndTable_ interpExpId(A_exp exp, Table_ t) {
    IntAndTable_ r;
    Table_ _t = t;

    while (TRUE) {
        if (strcmp(_t->id, exp->u.id) == 0) {
            r.i = _t->value;
            break;
        }
        _t = _t->tail;
    }

    r.t = t;
    return r;
}

static IntAndTable_ interpExpOp(A_exp exp, Table_ t) {
    IntAndTable_ r;

    IntAndTable_ left  = interpExp(exp->u.op.left, t);
    IntAndTable_ right = interpExp(exp->u.op.right, left.t);

    switch (exp->u.op.oper) {
        case A_plus:  r.i = left.i + right.i; break;
        case A_minus: r.i = left.i - right.i; break;
        case A_times: r.i = left.i * right.i; break;
        case A_div:   r.i = left.i / right.i; break;
    }

    r.t = right.t;

    return r;
}

static IntAndTable_ interpExpEseq(A_exp exp, Table_ t) {
    IntAndTable_ r;
    r.i = 0;
    r.t = NULL;

    return r;
}

IntAndTable_ interpExp(A_exp exp, Table_ t) {
    switch(exp->kind) {
        case A_numExp:  return interpExpNum(exp, t);
        case A_idExp:   return interpExpId(exp, t);
        case A_opExp:   return interpExpOp(exp, t);
        case A_eseqExp: return interpExpEseq(exp, t);
    }
}
