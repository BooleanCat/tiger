#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "utils.h"

typedef struct A_stm_     *A_stm;
typedef struct A_exp_     *A_exp;
typedef struct A_expList_ *A_expList;

typedef enum { A_plus, A_minus, A_times, A_div } A_binop;

struct A_stm_ {
    enum { A_compoundStm, A_assignStm, A_printStm } kind;
    union {
        struct { A_stm stm1, stm2; } compound;
        struct { string id; A_exp exp; } assign;
        struct { A_expList exps; } print;
    } u;
};

A_stm A_CompoundStm(A_stm, A_stm);
A_stm A_AssignStm(string, A_exp);
A_stm A_PrintStm(A_expList);

struct A_exp_ {
    enum { A_idExp, A_numExp, A_opExp, A_eseqExp } kind;
    union {
        string id;
        int num;
        struct { A_exp left; A_binop oper; A_exp right; } op;
        struct { A_stm stm; A_exp exp; } eseq;
    } u;
};

A_exp A_IdExp(string);
A_exp A_NumExp(int);
A_exp A_OpExp(A_exp, A_binop, A_exp);
A_exp A_EseqExp(A_stm, A_exp);

struct A_expList_ {
    enum { A_pairExpList, A_lastExpList } kind;
    union {
        struct { A_exp head; A_expList tail; } pair;
        A_exp last;
    } u;
};

A_expList A_PairExpList(A_exp, A_expList);
A_expList A_LastExpList(A_exp);

#define NewA(a) checked_malloc(sizeof(*a))
#define MAX(a, b) a > b ? a : b

int maxargs(A_stm);

#endif
