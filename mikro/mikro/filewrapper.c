#include "filewrapper.h"
#include "common.h"

#define FW_self ((FileWrapper *)self)
int FileWrapper_GetFd(PyObject *self) {
    return FW_self->fd;
}

static PyObject *FileWrapper_New(PyObject *cls, PyObject *args, PyObject *kwargs) {
    PyObject *file;
    PyObject *blocksize = NULL;

    if (!PyArg_ParseTuple(args, "O|O:FileWrapper", &file, &blocksize)) {
        return NULL;
    }

    Py_INCREF(file);
    Py_XINCREF(blocksize);

    int fd = PyObject_AsFileDescriptor(file);
    if (fd == -1) {
        PyErr_Clear();
    }

    FileWrapper *wrapper = PyObject_NEW(FileWrapper, cls);
    wrapper->file = file;
    wrapper->blocksize = blocksize;
    wrapper->fd = fd;

    return (PyObject *)wrapper;
}

static PyObject *FileWrapper_Iter(PyObject *self) {
    Py_INCREF(self);
    return self;
}

static PyObject *FileWrapper_IterNext(PyObject *self) {
    PyObject *data = PyObject_CallMethodObjArgs(
        FW_self->file,
        _read,
        FW_self->blocksize,
        NULL
    );

    if (data != NULL && PyObject_IsTrue(data))
    {
        return data;
    } else {
        return NULL;
    }
}

void FileWrapper_dealloc(PyObject *self) {
    Py_DECREF(FW_self->file);
    Py_XDECREF(FW_self->blocksize);
    PyObject_FREE(self);
}

PyObject *FileWrapper_close(PyObject *self) {
    if (PyObject_HasAttr(FW_self->file, _close)) {
        return PyObject_CallMethodObjArgs(
            FW_self->file,
            _close,
            NULL
        );
    } else {
        Py_RETURN_NONE;
    }
}

static PyMethodDef FileWrapper_methods[] = {
    {
        "close",
        (PyCFunction)FileWrapper_close,
        METH_NOARGS,
        NULL
    },
    { NULL }
};

PyTypeObject FileWrapper_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "FileWrapper",
    sizeof(FileWrapper),
    0,
    (destructor)FileWrapper_dealloc,
};

void _init_filewrapper(void) {
    FileWrapper_Type.tp_new = FileWrapper_New;
    FileWrapper_Type.tp_iter = FileWrapper_Iter;
    FileWrapper_Type.tp_iternext = FileWrapper_IterNext;
    FileWrapper_Type.tp_flags |= Py_TPFLAGS_DEFAULT;
    FileWrapper_Type.tp_methods = FileWrapper_methods;
}