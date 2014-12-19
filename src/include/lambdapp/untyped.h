#ifndef LAMBDAPP_UNTYPED_H_
#define LAMBDAPP_UNTYPED_H_

#include <memory>
#include <stdexcept>
#include <string>

namespace lambdapp {
namespace untyped {


class Expr_;
class Id_;
class Abs_;
class App_;
typedef std::shared_ptr<Expr_> expr_t;


// term rules
enum ExprRule { IDENTIFIER, ABSTRACTION, APPLICATION };


// base class of lambda terms
class Expr_ {

    Expr_(const Expr_ &) = delete;
    Expr_ & operator=(const Expr_ &) = delete;

public:
    Expr_() {}
    virtual ~Expr_() {}

    virtual ExprRule rule() const = 0;
    virtual expr_t copy() const = 0;

    virtual const std::string & name() const = 0; // Id_entifier
    virtual const std::string & var() const = 0; // Abs_raction
    virtual const expr_t & term() const = 0; // Abs_raction
    virtual const expr_t & func() const = 0; // App_lication
    virtual const expr_t & arg() const = 0; // App_lication

    virtual std::string str() const = 0;

}; // class Term


// lambda identifier
class Id_ : public Expr_ {

    Id_() = delete;
    Id_(const Id_ &) = delete;
    Id_ & operator=(const Id_ &) = delete;

public:
    explicit Id_(const std::string & n) : n_(n) {}
    virtual ~Id_() {}

    virtual ExprRule rule() const { return IDENTIFIER; }
    virtual expr_t copy() const { return expr_t(new Id_(n_)); }

    virtual const std::string & name() const { return n_; }
    virtual const std::string & var() const { throw std::runtime_error("Id_::var(): unsupported"); }
    virtual const expr_t & term() const { throw std::runtime_error("Id_::term(): unsupported"); }
    virtual const expr_t & func() const { throw std::runtime_error("Id_::func(): unsupported"); }
    virtual const expr_t & arg() const { throw std::runtime_error("Id_::arg(): unsupported"); }

    virtual std::string str() const { return n_; }

private:
    std::string n_;

}; // class Id_


// lambda abstraction
class Abs_ : public Expr_ {

    Abs_() = delete;
    Abs_(const Abs_ &) = delete;
    Abs_ & operator=(const Abs_ &) = delete;

public:
    Abs_(const std::string & v, const expr_t & t) : v_(v), t_(t->copy()) {}
    virtual ~Abs_() {}

    virtual ExprRule rule() const { return ABSTRACTION; }
    virtual expr_t copy() const { return expr_t(new Abs_(v_, t_)); }

    virtual const std::string & name() const { throw std::runtime_error("Abs_::name(): unsupported"); }
    virtual const std::string & var() const { return v_; }
    virtual const expr_t & term() const { return t_; }
    virtual const expr_t & func() const { throw std::runtime_error("Abs_::func(): unsupported"); }
    virtual const expr_t & arg() const { throw std::runtime_error("Abs_::arg(): unsupported"); }

    virtual std::string str() const { return "(\\" + v_ + ". " + t_->str() + ")"; }

private:
    std::string v_;
    expr_t t_;

}; // class Abs_


// lambda application
class App_ : public Expr_ {

    App_() = delete;
    App_(const App_ &) = delete;
    App_ & operator=(const App_ &) = delete;

public:
    App_(const expr_t & f, const expr_t & x) : f_(f->copy()), x_(x->copy()) {}
    virtual ~App_() {}

    virtual ExprRule rule() const { return APPLICATION; }
    virtual expr_t copy() const { return expr_t(new App_(f_, x_)); }

    virtual const std::string & name() const { throw std::runtime_error("App_::name(): unsupperted"); }
    virtual const std::string & var() const { throw std::runtime_error("App_::var(): unsupperted"); }
    virtual const expr_t & term() const { throw std::runtime_error("App_::term(): unsupperted"); }
    virtual const expr_t & func() const { return f_; }
    virtual const expr_t & arg() const { return x_; }

    virtual std::string str() const { return "(" + f_->str() + " " + x_->str() + ")"; }

private:
    expr_t f_;
    expr_t x_;

}; // class App_


// utility functions

inline expr_t id(const std::string & n) { return expr_t(new Id_(n)); }
inline expr_t abs(const std::string & v, const expr_t & t) { return expr_t(new Abs_(v, t)); }
inline expr_t app(const expr_t & f, const expr_t & x) { return expr_t(new App_(f, x)); }
inline ExprRule rule(const expr_t & x) { return x->rule(); }
inline expr_t copy(const expr_t & x) { return x->copy(); }
inline const std::string & name(const expr_t & x) { return x->name(); }
inline const std::string & var(const expr_t & x) { return x->var(); }
inline const expr_t & term(const expr_t & x) { return x->term(); }
inline const expr_t & func(const expr_t & x) { return x->func(); }
inline const expr_t & arg(const expr_t & x) { return x->arg(); }
inline std::string str(const expr_t & x) { return x->str(); }

// find identifier name that is the tail in lexical order
std::string tailvar(const expr_t & x);

// x[from / to]
expr_t replace(const expr_t & x, const std::string & from, const std::string & to);

// x[from := to]
expr_t substitute(const expr_t & x, const std::string & from, const expr_t & to);

// beta reduction
expr_t reduce(const expr_t & f, const expr_t & x);

// leftmost beta reduction
expr_t leftmost(const expr_t & x);


} // namespace untyped
} // namespace lambdapp


#endif // LAMBDAPP_UNTYPED_H_

