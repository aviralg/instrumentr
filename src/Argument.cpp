#include "Argument.hpp"

namespace instrumentr {

SEXP Argument::class_ = NULL;

void Argument::initialize() {
    class_ = Object::create_class("instrumentr_argument");
    R_PreserveObject(class_);
}

void Argument::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP Argument::get_class() {
    return class_;
}

ArgumentSPtr Argument::from_sexp(SEXP r_argument) {
    void* argument = R_ExternalPtrAddr(r_argument);
    if (argument == NULL) {
        Rf_errorcall(R_NilValue, "Argument::from_sexp: argument is null");
    } else {
        return *static_cast<ArgumentSPtr*>(argument);
    }
}

SEXP Argument::to_sexp(ArgumentSPtr argument) {
    SEXP r_argument = PROTECT(
        R_MakeExternalPtr(new ArgumentSPtr(argument), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_argument, Argument::destroy_sexp, TRUE);

    setAttrib(r_argument, R_ClassSymbol, Argument::get_class());

    UNPROTECT(1);

    return r_argument;
}

void Argument::destroy_sexp(SEXP r_argument) {
    delete static_cast<ArgumentSPtr*>(R_ExternalPtrAddr(r_argument));
    R_SetExternalPtrAddr(r_argument, NULL);
}

} // namespace instrumentr
