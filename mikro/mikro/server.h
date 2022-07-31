#ifndef __server_h__
#define __server_h__

#include <Python.h>

typedef struct {
    int sockfd;
    PyObject *host;
    PyObject *port;
} ServerInfo;

void server_run(ServerInfo*);


#endif