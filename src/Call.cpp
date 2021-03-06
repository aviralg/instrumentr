#include "Call.hpp"

namespace instrumentr {

SEXP Call::class_ = NULL;

void Call::initialize() {
    class_ = Object::create_class("instrumentr_call");
    R_PreserveObject(class_);
}

void Call::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP Call::get_class() {
    return class_;
}

CallSPtr Call::from_sexp(SEXP r_call) {
    void* call = R_ExternalPtrAddr(r_call);
    if (call == NULL) {
        Rf_errorcall(R_NilValue, "Call::from_sexp: object is null");
    } else {
        return *static_cast<CallSPtr*>(call);
    }
}

SEXP Call::to_sexp(CallSPtr call) {
    SEXP r_call =
        PROTECT(R_MakeExternalPtr(new CallSPtr(call), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_call, Call::destroy_sexp, TRUE);

    setAttrib(r_call, R_ClassSymbol, Call::get_class());

    UNPROTECT(1);

    return r_call;
}

void Call::destroy_sexp(SEXP r_call) {
    delete static_cast<CallSPtr*>(R_ExternalPtrAddr(r_call));
    R_SetExternalPtrAddr(r_call, NULL);
}

} // namespace instrumentr
