
.onLoad <- function(libname, pkgname) { # nolint

    .Call(C_instrumentr_initialize_instrumentr, parent.env(environment()), .state_env, undefined_object)

}

.onUnload <- function(libpath) { # nolint

    .Call(C_instrumentr_finalize_instrumentr)

}

.onDetach <- function(libpath) { # nolint

    .Call(C_instrumentr_finalize_instrumentr)

}
