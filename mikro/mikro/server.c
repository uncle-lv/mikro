#include <arpa/inet.h>
#include <fcntl.h>
#include <ev.h>

#include "server.h"

#define READ_BUFFER_SIZE 64 * 1024
#define GIL_LOCK(n) PyGILState_STATE _gilstate_##n = PyGILState_Ensure()
#define GIL_UNLOCK(n) PyGILState_Release(_gilstate_##n)

typedef void ev_io_callback(struct ev_loop *, ev_io *, const int);

static ev_io_callback ev_io_accept;
static ev_io_callback ev_io_read;

typedef struct {
    ServerInfo *server_info;
    ev_io accept_watcher;
} ThreadInfo;


void server_run(ServerInfo *server_info) {
    struct ev_loop *mainloop = ev_loop_new(EVFLAG_AUTO);
    ThreadInfo thread_info;
    thread_info.server_info = server_info;

    ev_set_userdata(mainloop, &thread_info);
    ev_io_init(&thread_info.accept_watcher, ev_io_accept, server_info->sockfd, EV_READ);
    ev_io_start(mainloop, &thread_info.accept_watcher);

    Py_BEGIN_ALLOW_THREADS
    ev_run(mainloop, 0);
    ev_loop_destroy(mainloop);
    Py_END_ALLOW_THREADS
}

static void ev_io_accept(struct ev_loop *mainloop, ev_io *watcher, const int revents) {
    int client_fd;
    struct sockaddr_in sockaddr;
    socklen_t addrlen;

    addrlen = sizeof(struct sockaddr_in);
    client_fd = accept(watcher->fd, (struct sockaddr*)&sockaddr, &addrlen);
    if (client_fd < 0) {
        return;
    }

    int flags = fcntl(client_fd, F_GETFL, 0);
    if (fcntl(client_fd, F_SETFL, (flags < 0 ? 0 : flags) | O_NONBLOCK) == -1) {
        return;
    }

    ev_io *read_watcher = (ev_io *)malloc(sizeof(ev_io));
    ev_io_init(read_watcher, ev_io_read, client_fd, EV_READ);
    ev_io_start(mainloop, read_watcher);
}

static void ev_io_read(struct ev_loop *mainloop, ev_io *watcher, const int revents) {
    char buf[READ_BUFFER_SIZE];
    ssize_t read;

    read = recv(watcher->fd, buf, READ_BUFFER_SIZE, 0);

    if (read < 0) {
        return;
    } if (read == 0) {
        ev_io_stop(mainloop, watcher);
        close(watcher->fd);
        free(watcher);
        return;
    } else {

    }

    send(watcher->fd, buf, read, 0);
    bzero(buf, read);
}