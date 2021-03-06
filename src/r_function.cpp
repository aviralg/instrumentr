#include "Application.hpp"
#include "Package.hpp"
#include "Function.hpp"
#include "r_function.h"

using instrumentr::Function;
using instrumentr::FunctionSPtr;

SEXP r_function_create_function(SEXP r_name,
                                SEXP r_parameter_count,
                                SEXP r_definition,
                                SEXP r_public,
                                SEXP r_s3_generic,
                                SEXP r_s3_method) {
    std::string name = CHAR(asChar(r_name));
    int parameter_count = asInteger(r_parameter_count);
    bool pub = asLogical(r_public);
    bool s3_generic = asLogical(r_s3_generic);
    bool s3_method = asLogical(r_s3_method);
    FunctionSPtr function = std::make_shared<Function>(
        name, parameter_count, r_definition, pub, s3_generic, s3_method);
    return Function::to_sexp(function);
}

SEXP r_function_get_name(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    const std::string& name = function->get_name();
    return mkString(name.c_str());
}

SEXP r_function_get_parameter_count(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    int parameter_count = function->get_parameter_count();
    return ScalarInteger(parameter_count);
}

SEXP r_function_get_definition(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    SEXP r_definition = function->get_definition();
    return r_definition;
}

SEXP r_function_is_public(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    bool pub = function->is_public();
    return ScalarLogical(pub);
}

SEXP r_function_is_s3_generic(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    bool s3_generic = function->is_s3_generic();
    return ScalarLogical(s3_generic);
}

SEXP r_function_is_s3_method(SEXP r_function) {
    FunctionSPtr function = Function::from_sexp(r_function);
    bool s3_method = function->is_s3_method();
    return ScalarLogical(s3_method);
}
