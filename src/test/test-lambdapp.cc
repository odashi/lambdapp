#include <lambdapp/untyped.h>
#include <iostream>

using namespace std;
using namespace lambdapp::untyped;


int main() {
    expr_t x = id("x");
    expr_t y = id("y");
    expr_t z = app(x, y);
    expr_t xx = abs("x", z);
    expr_t yy = abs("y", z);
    expr_t zz = app(xx, yy);
    cout << str(zz) << endl;

    expr_t a = replace(zz, "x", "a");
    expr_t b = replace(zz, "y", "b");
    cout << str(a) << endl;
    cout << str(b) << endl;
    cout << tailvar(a) << endl;

    expr_t aa = substitute(zz, "x", abs("a", id("a")));
    expr_t bb = substitute(zz, "z", abs("a", id("a")));
    
    cout << str(aa) << endl;
    cout << str(bb) << endl;

    expr_t zzz = reduce(xx, yy);
    cout << str(zzz) << endl;

    // looping combinator
    expr_t w = id("w");
    w = app(w, w);
    w = abs("w", w);
    cout << str(w) << endl;
    w = reduce(w, w);
    cout << str(w) << endl;

    // leftmost beta reduction
    expr_t zzzz = app(xx, yy);
    cout << str(zzzz) << endl;
    zzzz = leftmost(app(xx, yy));
    cout << str(zzzz) << endl;
    //expr_t ww = leftmost(w); // DANGER: never stop! 

    return 0;
}

