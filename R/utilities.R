is_scalar_character <- function(vector) {
    is.character(vector) && (length(vector) == 1) && (nchar(vector) != 0)
}

is_vector_character <- function(vector) {
    is.character(vector)
}

is_scalar_logical <- function(vector) {
    is.logical(vector) && (length(vector) == 1)
}

is_scalar_integer <- function(vector) {
    is.integer(vector) && (length(vector) == 1)
}

is_environment <- function(env) {
    is.environment(env)
}

is_function <- function(fun) {
    is.function(fun)
}

is_null <- function(obj) {
    is.null(obj)
}

is_closure <- function(obj) {
    typeof(obj) == "closure"
}

is_language <- function(obj) {
    is.language(obj)
}

is_instrumentr_context <- function(obj) {
    "instrumentr_context" %in% class(obj)
}

is_instrumentr_application <- function(obj) {
    "instrumentr_application" %in% class(obj)
}

is_instrumentr_package <- function(obj) {
    "instrumentr_package" %in% class(obj)
}

is_instrumentr_function <- function(obj) {
    "instrumentr_function" %in% class(obj)
}

has_parameters <- function(fun, n, include_varargs = TRUE) {
    parameters <- formals(fun)
    cond <- length(parameters) >= n
    if (!cond && include_varargs) {
        cond <- "..." %in% names(parameters)
    }
    cond
}

get_package_name <- function(fun) {
    name <- environmentName(environment(fun))
    if (name == "R_GlobalEnv") ".GlobalEnv"
    else name
}

remove_package_prefix <- function(package_names) {
    prefix <- "package:"
    ifelse(startsWith(package_names, prefix),
           substring(package_names, nchar(prefix) + 1),
           package_names)
}


add_package_prefix <- function(package_names) {
    prefix <- "package:"
    paste0(prefix, package_names)
}
