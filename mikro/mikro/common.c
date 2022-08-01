#include "common.h"

long PyObj_ToLong(PyObject *obj) {
    if (PyLong_Check(obj)) {
        return PyLong_AsLong(obj);
    }

    return -1;
}

const char *PyObj_ToStr(PyObject *obj) {
    if (PyUnicode_Check(obj)) {
        return PyUnicode_AsUTF8(obj);
    }

    return NULL;
}