#ifndef INTERP_H
#define INTERP_H

#include <string.h>

#include "utils.h"
#include "statements.h"

typedef struct table* Table_;
typedef struct IntAndTable IntAndTable_;

struct table { string id; int value; Table_ tail; };
struct IntAndTable { int i; Table_ t; };

Table_ Table(string, int, Table_);
Table_ interpStm(A_stm, Table_);
IntAndTable_ interpExp(A_exp, Table_);

#endif
