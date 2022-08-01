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

long PyObj_ToLong(PyObject *);
const char *PyObj_ToStr(PyObject *);

#endif
