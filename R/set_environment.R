
set_environment <- function(context, environment, ...) {
    UseMethod("set_environment")
}

set_environment.instrumentr_context <- function(context, environment, ...) { # nolint
    stopifnot(is_environment(environment))

    .Call(C_context_set_environment, context, environment)

    invisible(NULL)
}
