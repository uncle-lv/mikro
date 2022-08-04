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

void _init_common() {

#define _(name) _##name = _PEP3333_String_FromUTF8String(#name)

    _(REMOTE_ADDR);
    _(PATH_INFO);
    _(QUERY_STRING);
    _(close);

    _(REQUEST_METHOD);
    _(SERVER_PROTOCOL);
    _(SERVER_NAME);
    _(SERVER_PORT);
    _(GET);
    _(HTTP_CONTENT_LENGTH);
    _(CONTENT_LENGTH);
    _(HTTP_CONTENT_TYPE);
    _(CONTENT_TYPE);
    _(HTTP_);
    _(http);

    _(BytesIO);
    _(write);
    _(read);
    _(seek);
#undef _

    _HTTP_1_1 = _PEP3333_String_FromUTF8String("HTTP/1.1");
    _HTTP_1_0 = _PEP3333_String_FromUTF8String("HTTP/1.0");
    _wsgi_input = _PEP3333_String_FromUTF8String("wsgi.input");
    _empty_string = _PEP3333_String_FromUTF8String("");
    _empty_bytes = _PEP3333_Bytes_FromString("");
}
