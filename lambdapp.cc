#include "lambdapp.h"
//#include <iostream>

using namespace std;

namespace lambdapp {

string tailvar(const expr_t & x) {
    switch (type(x)) {
        case IDENTIFIER:
            return name(x);
        case ABSTRACTION: {
            string a = var(x);
            string b = tailvar(term(x));
            return a > b ? a : b;
        }
        case APPLICATION: {
            string a = tailvar(func(x));
            string b = tailvar(arg(x));
            return a > b ? a : b;
        }
    }
}

expr_t replace(const expr_t & x, const string & from, const string & to) {
    switch (type(x)) {
        case IDENTIFIER:
            return name(x) == from ? id(to) : copy(x);
        case ABSTRACTION:
            return var(x) == from ? copy(x) : abs(var(x), replace(term(x), from, to));
        case APPLICATION:
            return app(replace(func(x), from, to), replace(arg(x), from, to));
    }
}

expr_t substitute(const expr_t & x, const string & from, const expr_t & to) {
    switch (type(x)) {
        case IDENTIFIER:
            return name(x) == from ? copy(to) : copy(x);
        case ABSTRACTION: {
            if (var(x) == from) return copy(x);
            string a = tailvar(x);
            string b = tailvar(to);
            string v = (a > b ? a : b) + "0";
            expr_t t = replace(term(x), var(x), v);
            return abs(v, substitute(t, from, to));
        }
        case APPLICATION:
            return app(substitute(func(x), from, to), substitute(arg(x), from, to));
    }
}

expr_t reduce(const expr_t & f, const expr_t & x) {
    if (type(f) != ABSTRACTION) {
        throw runtime_error("lambdapp::reduce(): 'f' must be an absion object");
    }
    return substitute(term(f), var(f), x);
}

expr_t leftmost(const expr_t & x) {
    switch (type(x)) {
        case IDENTIFIER:
            return copy(x);
        case ABSTRACTION:
            return abs(var(x), leftmost(term(x)));
        case APPLICATION: {
            expr_t f = leftmost(func(x));
            const expr_t & a = arg(x);
            return type(f) == ABSTRACTION ? leftmost(reduce(f, a)) : app(f, a);
        }
    }
}

}

