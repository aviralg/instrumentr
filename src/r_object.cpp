#include "Object.hpp"
#include "r_object.h"

using instrumentr::Object;
using instrumentr::ObjectSPtr;

ObjectSPtr Object::from_sexp(SEXP r_object) {
    void* object = R_ExternalPtrAddr(r_object);
    if (object == NULL) {
        Rf_errorcall(R_NilValue, "Object::from_sexp: object is null");
    } else {
        return *static_cast<ObjectSPtr*>(object);
    }
}

SEXP r_object_get_id(SEXP r_object) {
    ObjectSPtr object = Object::from_sexp(r_object);
    return ScalarInteger(object->get_id());
}

SEXP r_object_set_data(SEXP r_object, SEXP r_data) {
    ObjectSPtr object = Object::from_sexp(r_object);
    object->set_data(r_data);
    return R_NilValue;
}

SEXP r_object_get_data(SEXP r_object) {
    ObjectSPtr object = Object::from_sexp(r_object);
    SEXP r_data = object->get_data();
    return r_data;
}

SEXP r_object_remove_data(SEXP r_object) {
    ObjectSPtr object = Object::from_sexp(r_object);
    object->remove_data();
    return R_NilValue;
}

SEXP r_object_has_data(SEXP r_object) {
    ObjectSPtr object = Object::from_sexp(r_object);
    return ScalarLogical(object->has_data());
}
