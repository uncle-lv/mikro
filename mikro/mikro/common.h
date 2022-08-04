#ifndef __common_h__
#define __common_h__

#include <Python.h>
#include "log.h"

#ifdef DEBUG
#define DBG(...)                                                               \
    do {                                                                       \
        log_debug(__VA_ARGS__);                                                   \
    } while (0)
#else
#define DBG(...)                                                               \
    do {                                                                       \
    } while (0)
#endif

#define _FromLong(n) PyLong_FromLong(n)
#define _PEP3333_Bytes_AS_DATA(bytes) PyBytes_AS_STRING(bytes)
#define _PEP3333_Bytes_FromString(bytes) PyBytes_FromString(bytes)
#define _PEP3333_Bytes_FromStringAndSize(data, len) PyBytes_FromStringAndSize(data, len)
#define _PEP3333_Bytes_GET_SIZE(bytes) PyBytes_GET_SIZE(bytes)
#define _PEP3333_Bytes_Check(bytes) PyBytes_Check(bytes)
#define _PEP3333_Bytes_Resize(bytes, len) _PyBytes_Resize(bytes, len)
#define _PEP3333_BytesLatin1_FromUnicode(u) PyUnicode_AsLatin1String(u)
#define _PEP3333_String_FromUTF8String(data) PyUnicode_FromString(data)
#define _PEP3333_String_FromLatin1StringAndSize(data, len) PyUnicode_DecodeLatin1(data, len, "replace")
#define _PEP3333_String_Empty() PyUnicode_FromString("")
#define _PEP3333_String_FromFormat(...) PyUnicode_FromFormat(__VA_ARGS__)
#define _PEP3333_String_GET_SIZE(u) PyUnicode_GET_LENGTH(u)
#define _PEP3333_String_Concat(u1, u2) PyUnicode_Concat(u1, u2)
#define _PEP3333_String_CompareWithASCIIString(o, c_str) PyUnicode_CompareWithASCIIString(o, c_str)

PyObject *_REMOTE_ADDR, *_PATH_INFO, *_QUERY_STRING, *_REQUEST_METHOD, *_GET,
         *_HTTP_CONTENT_LENGTH, *_CONTENT_LENGTH, *_HTTP_CONTENT_TYPE,
         *_CONTENT_TYPE, *_SERVER_PROTOCOL, *_SERVER_NAME, *_SERVER_PORT,
         *_http, *_HTTP_, *_HTTP_1_1, *_HTTP_1_0, *_wsgi_input, *_close,
         *_empty_string, *_empty_bytes, *_BytesIO, *_write, *_read, *_seek;

long PyObj_ToLong(PyObject *);
const char *PyObj_ToStr(PyObject *);

#endif
