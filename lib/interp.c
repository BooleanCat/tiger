#include "interp.h"

Table_ Table(string id, int value, struct table* tail) {
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;

    return tail;
}

Table_ interpStm(A_stm stm, Table_ t) {
    return Table("Foo", 7, t);
}

IntAndTable_ interpExp(A_exp exp, Table_ t) {
    IntAndTable_ r;
    r.i = 0;
    r.t = Table("Foo", 7, t);

    return r;
}
