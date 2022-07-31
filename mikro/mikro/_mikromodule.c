#include <Python.h>

#include "server.h"

static PyObject *run(PyObject *self, PyObject *args) {
    ServerInfo info;
    PyObject *socket;

    if (!PyArg_ParseTuple(args, "O:server_run", &socket)) {
        return NULL;
    }

    info.sockfd = PyObject_AsFileDescriptor(socket);
    if (info.sockfd < 0) {
        return NULL;
    }

    info.host = NULL;
    if (PyObject_HasAttrString(socket, "getsockname")) {
        PyObject *sockname = PyObject_CallMethod(socket, "getsockname", NULL);
        if (sockname == NULL) {
            return NULL;
        }

        if (PyTuple_CheckExact(sockname) && PyTuple_GET_SIZE(sockname) == 2) {
            info.host = PyTuple_GET_ITEM(sockname, 0);
            info.port = PyTuple_GET_ITEM(sockname, 1);
        }
    }

    server_run(&info);

    Py_RETURN_NONE;
}

static PyMethodDef Mikro_FunctoinTable[] = {
    {"run", (PyCFunction)run, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "mikro",
    NULL,
    -1,
    Mikro_FunctoinTable,
    NULL,
    NULL,
    NULL,
    NULL,
};

#define INIT_MIKRO PyInit__mikro

PyMODINIT_FUNC INIT_MIKRO(void) {
    PyObject *mikro_module = PyModule_Create(&module);
    if (mikro_module == NULL) {
        return NULL;
    }

    PyModule_AddObject(mikro_module, "version",
                       Py_BuildValue("(iii)", 0, 0, 1));
    return mikro_module;
}
