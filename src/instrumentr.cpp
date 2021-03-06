#include "instrumentr.hpp"
#include "Context.hpp"
#include "Application.hpp"
#include "Package.hpp"
#include "Function.hpp"
#include "Call.hpp"
#include "Parameter.hpp"
#include "Argument.hpp"
#include "utilities.h"
#include <vector>

namespace instrumentr {

std::vector<bool> tracing_status_stack;
std::vector<ExecutionContext> execution_context_stack;

SEXP UndefinedObject = NULL;

bool is_tracing_enabled() {
    return !tracing_status_stack.empty() && tracing_status_stack.back();
}

void set_tracing_status(bool tracing_status) {
    tracing_status_stack.push_back(tracing_status);
}

void enable_tracing() {
    tracing_status_stack.push_back(true);
}

void disable_tracing() {
    tracing_status_stack.push_back(false);
}

void reinstate_tracing() {
    if (!tracing_status_stack.empty()) {
        tracing_status_stack.pop_back();
    }
}

void clear_tracing() {
    tracing_status_stack.clear();
}

ExecutionContext peek_execution_context() {
    return execution_context_stack.back();
}

void push_execution_context(ExecutionContext execution_context) {
    execution_context_stack.push_back(execution_context);
}

ExecutionContext pop_execution_context() {
    ExecutionContext execution_context = execution_context_stack.back();
    execution_context_stack.pop_back();
    return execution_context;
}

void clear_execution_context() {
    execution_context_stack.clear();
}

SEXP get_undefined_object() {
    return UndefinedObject;
}

bool is_undefined_object(SEXP object) {
    return object == UndefinedObject;
}

bool is_defined_object(SEXP value) {
    return !(is_undefined_object(value));
}

void initialize_instrumentr(SEXP r_package_environment,
                            SEXP r_state_environment,
                            SEXP r_undefined_object) {
    if (UndefinedObject == NULL) {
        initialize_utilities(r_package_environment, r_state_environment);
        UndefinedObject = r_undefined_object;
        Context::initialize();
        Application::initialize();
        CallStack::initialize();
        Package::initialize();
        Function::initialize();
        Call::initialize();
        Parameter::initialize();
        Argument::initialize();
    }
}

void finalize_instrumentr() {
    if (UndefinedObject != NULL) {
        finalize_utilities();
        UndefinedObject = NULL;
        Context::finalize();
        Application::finalize();
        CallStack::finalize();
        Package::finalize();
        Function::finalize();
        Call::initialize();
        Parameter::initialize();
        Argument::initialize();
    }
}

} // namespace instrumentr
