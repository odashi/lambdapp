#include "lambdapp.h"
#include <iostream>

using namespace std;
using namespace lambdapp;

int main() {
    expr_t x = id("x");
    expr_t y = id("y");
    expr_t z = apply(x, y);
    expr_t xx = abstract("x", z);
    expr_t yy = abstract("y", z);
    expr_t zz = apply(xx, yy);
    cout << str(zz) << endl;

    expr_t a = varsubstitute(zz, "x", "a");
    expr_t b = varsubstitute(zz, "y", "b");
    cout << str(a) << endl;
    cout << str(b) << endl;
    cout << tailvar(a) << endl;

    expr_t aa = substitute(zz, "x", abstract("a", id("a")));
    expr_t bb = substitute(zz, "z", abstract("a", id("a")));
    
    cout << str(aa) << endl;
    cout << str(bb) << endl;

    expr_t zzz = reduce(xx, yy);
    cout << str(zzz) << endl;

    // looping combinator
    expr_t w = id("w");
    w = apply(w, w);
    w = abstract("w", w);
    cout << str(w) << endl;
    w = reduce(w, w);
    cout << str(w) << endl;

    return 0;
}

