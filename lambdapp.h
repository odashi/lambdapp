#ifndef LAMBDAPP_H_
#define LAMBDAPP_H_

#include <memory>
#include <stdexcept>
#include <string>

namespace lambdapp {


class Expr_;
class Id_;
class Abst_;
class Apply_;
typedef std::shared_ptr<Expr_> expr_t;


// term types
enum ExprType { IDENTIFIER, ABSTRACTION, APPLICATION };


// base class of lambda terms
class Expr_ {

    Expr_(const Expr_ &) = delete;
    Expr_ & operator=(const Expr_ &) = delete;

public:
    Expr_() {}
    virtual ~Expr_() {}

    virtual ExprType type() const = 0;
    virtual expr_t copy() const = 0;

    virtual const std::string & name() const = 0; // Id_entifier
    virtual const std::string & var() const = 0; // Abst_raction
    virtual const expr_t & term() const = 0; // Abst_raction
    virtual const expr_t & func() const = 0; // Apply_lication
    virtual const expr_t & arg() const = 0; // Apply_lication

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

    virtual ExprType type() const { return IDENTIFIER; }
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
class Abst_ : public Expr_ {

    Abst_() = delete;
    Abst_(const Abst_ &) = delete;
    Abst_ & operator=(const Abst_ &) = delete;

public:
    Abst_(const std::string & v, const expr_t & t) : v_(v), t_(t->copy()) {}
    virtual ~Abst_() {}

    virtual ExprType type() const { return ABSTRACTION; }
    virtual expr_t copy() const { return expr_t(new Abst_(v_, t_)); }

    virtual const std::string & name() const { throw std::runtime_error("Abst_::name(): unsupported"); }
    virtual const std::string & var() const { return v_; }
    virtual const expr_t & term() const { return t_; }
    virtual const expr_t & func() const { throw std::runtime_error("Abst_::func(): unsupported"); }
    virtual const expr_t & arg() const { throw std::runtime_error("Abst_::arg(): unsupported"); }

    virtual std::string str() const { return "(\\" + v_ + ". " + t_->str() + ")"; }

private:
    std::string v_;
    expr_t t_;

}; // class Abst_


// lambda application
class Apply_ : public Expr_ {

    Apply_() = delete;
    Apply_(const Apply_ &) = delete;
    Apply_ & operator=(const Apply_ &) = delete;

public:
    Apply_(const expr_t & f, const expr_t & x) : f_(f->copy()), x_(x->copy()) {}
    virtual ~Apply_() {}

    virtual ExprType type() const { return APPLICATION; }
    virtual expr_t copy() const { return expr_t(new Apply_(f_, x_)); }

    virtual const std::string & name() const { throw std::runtime_error("Apply_::name(): unsupperted"); }
    virtual const std::string & var() const { throw std::runtime_error("Apply_::var(): unsupperted"); }
    virtual const expr_t & term() const { throw std::runtime_error("Apply_::term(): unsupperted"); }
    virtual const expr_t & func() const { return f_; }
    virtual const expr_t & arg() const { return x_; }

    virtual std::string str() const { return "(" + f_->str() + " " + x_->str() + ")"; }

private:
    expr_t f_;
    expr_t x_;

}; // class Apply_


// utility functions

inline expr_t id(const std::string & n) { return expr_t(new Id_(n)); }
inline expr_t abstract(const std::string & v, const expr_t & t) { return expr_t(new Abst_(v, t)); }
inline expr_t apply(const expr_t & f, const expr_t & x) { return expr_t(new Apply_(f, x)); }
inline ExprType type(const expr_t & x) { return x->type(); }
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
expr_t varsubstitute(const expr_t & x, const std::string & from, const std::string & to);

// x[from := to]
expr_t substitute(const expr_t & x, const std::string & from, const expr_t & to);

// beta reduction
expr_t reduce(const expr_t & f, const expr_t & x);

} // namespace lambdapp

#endif // LAMBDAPP_H_

