
#' @export
set_application_detach_callback <- function(context, application_detach_callback, ...) { # nolint
    UseMethod("set_application_detach_callback")
}

#' @export
set_application_detach_callback.instrumentr_context <- function(context, application_detach_callback, ...) {  # nolint

    stopifnot(is_undefined(application_detach_callback) ||
              is_closure(application_detach_callback) &&
              has_parameters(application_detach_callback, 2))

    .Call(C_context_set_application_detach_callback, context, application_detach_callback)

    invisible(NULL)
}
