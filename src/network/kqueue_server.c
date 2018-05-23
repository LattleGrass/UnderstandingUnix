/*
 * =====================================================================================
 *
 *       Filename:  kqueue_server.c
 *
 *    Description:  kqueue异步server
 *
 *        Version:  1.0
 *        Created:  2018-05-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 1024
#define on_error(...)                                                          \
        {                                                                      \
                fprintf(stderr, __VA_ARGS__);                                  \
                fflush(stderr);                                                \
                exit(1);                                                       \
        }

static struct kevent *events;
static int events_used = 0;
static int events_alloc = 0;

static struct sockaddr_in server;
static int server_fd, queue;

/* struct kevent {  */
/*      uintptr_t ident;       /\* 事件 ID *\/  */
/*      short     filter;       /\* 事件过滤器 *\/  */
/*      u_short   flags;        /\* 行为标识 *\/  */
/*      u_int     fflags;       /\* 过滤器标识值 *\/  */
/*      intptr_t  data;         /\* 过滤器数据 *\/  */
/*      void      *udata;       /\* 应用透传数据 *\/  */
/*  };  */
struct event_data {
        char buffer[BUFFER_SIZE];
        int buffer_read;
        int buffer_write;

        int (*on_read)(struct event_data *self, struct kevent *event);
        int (*on_write)(struct event_data *self, struct kevent *event);
};

static void event_server_listen(int port) {
        int err, flags;

        // create queue
        if ((queue = kqueue()) < 0)
                on_error("could not create kqueue: %s\n", strerror(errno));

        // create socket
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                on_error("could not create server socket: %s\n",
                         strerror(errno));

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        int opt_val = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val,
                     sizeof(opt_val));

        // bind socket
        if ((err = bind(server_fd, (struct sockaddr *)&server,
                        sizeof(server))) < 0)
                on_error("could not bind server socket: %s\n", strerror(errno));

        //  set none blck
        if ((flags = fcntl(server_fd, F_GETFL, 0)) < 0)
                on_error("could not get server socket flags: %s\n",
                         strerror(errno));

        if ((err = fcntl(server_fd, F_SETFL, flags | O_NONBLOCK)) < 0)
                on_error(
                    "could not set server socket flags to none block: %s\n",
                    strerror(errno));

        // listen
        listen(server_fd, SOMAXCONN);
}

// 设置事件
static void event_change(int ident, int filter, int flags, void *udata) {
        struct kevent *e;

        // 申请event
        if (events_alloc == 0) {
                events_alloc = 64;
                events = malloc(events_alloc * sizeof(struct kevent));
        }

        if (events_alloc <= events_used) {
                events_alloc *= 2;
                events = realloc(events, events_alloc * sizeof(struct kevent));
        }

        int index = events_used++;
        e = &events[index];

        e->ident = ident;
        e->filter = filter;
        e->flags = flags;
        e->fflags = 0;
        e->data = 0;
        e->udata = udata;
}

static void event_loop() {
        int new_events;

        while (1) {
                /* int kevent(int kq, const struct kevent *changelist, int
                 * nchanges, struct kevent *eventlist, int nevents, const struct
                 * timespec *timeout); */

                /* kevent 提供向内核注册 / 反注册事件和返回就绪事件或错误事件：
                 * kq: kqueue 的文件描述符。 changelist: 要注册 /
                 * 反注册的事件数组； nchanges: changelist 的元素个数。
                 * eventlist: 满足条件的通知事件数组； nevents: eventlist
                 * 的元素个数。 timeout:
                 * 等待事件到来时的超时时间，0，立刻返回；NULL，一直等待；有一个具体值，等待
                 * timespec 时间值。 返回值：可用事件的个数 */
                new_events = kevent(queue, events, events_used, events,
                                    events_alloc, NULL);
                for (int i = 0; i < new_events; i++) {
                        struct kevent *e = &events[i];
                        struct event_data *udata =
                            (struct event_data *)e->udata;
                        if (udata == NULL)
                                continue;
                        if (udata->on_write != NULL &&
                            e->filter == EVFILT_WRITE)
                                while (udata->on_write(udata, e))
                                        ;
                        if (udata->on_read != NULL && e->filter == EVFILT_READ)
                                while (udata->on_read(udata, e))
                                        ;
                }
        }
}

static int event_flush_write(struct event_data *self, struct kevent *event) {
        int n = write(event->ident, self->buffer + self->buffer_write,
                      self->buffer_read - self->buffer_write);

        if (n < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                        return 0;
                on_error("write failed: %s\n", strerror(errno));
        }
        if (n == 0) {
                free(self);
                close(event->ident);
                return 0;
        }

        self->buffer_write += n;
        if (self->buffer_write == self->buffer_read) {
                self->buffer_read = 0;
                self->buffer_write = 0;
        }

        return 0;
}

static int event_on_read(struct event_data *self, struct kevent *event) {
        if (self->buffer_read == BUFFER_SIZE) {
                // 读失效
                event_change(event->ident, EVFILT_READ, EV_DISABLE, self);
                return 0;
        }

        int n;
        if ((n = read(event->ident, self->buffer + self->buffer_read,
                      BUFFER_SIZE - self->buffer_read)) < 0) {
                on_error("Read failed: %s\n", strerror(errno));
        }

        if (n == 0) {
                free(self);
                close(event->ident);
                return 0;
        }

        if (self->buffer_read == 0)
                // 可写
                event_change(event->ident, EVFILT_WRITE, EV_ENABLE, self);

        self->buffer_read += n;
        return event_flush_write(self, event);
}

static int event_on_write(struct event_data *self, struct kevent *event) {
        if (self->buffer_read == self->buffer_write) {
                // 写失效
                event_change(event->ident, EVFILT_WRITE, EV_DISABLE, self);
                return 0;
        }
        return event_flush_write(self, event);
}

static int event_on_accept(struct event_data *self, struct kevent *event) {
        struct sockaddr client;
        socklen_t client_len = sizeof(client);

        int client_fd = accept(server_fd, &client, &client_len);
        int flags;
        int err;

        if (client_fd < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                        return 0;
                on_error("accept failed: %s\n", strerror(errno));
        }
        flags = fcntl(client_fd, F_GETFL, 0);
        if (flags < 0)
                on_error("Count not get client socket flags:%s\n",
                         strerror(errno));
        err = fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
        if (err < 0) {
                on_error("Count not set client socket to be non blocking :%s\n",
                         strerror(errno));
        }

        struct event_data *client_data =
            (struct event_data *)malloc(sizeof(struct event_data));
        client_data->on_read = event_on_read;
        client_data->on_write = event_on_write;

        event_change(client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, client_data);
        event_change(client_fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, client_data);

        return 1;
}

int main(int argc, char **argv) {
        if (argc < 2) {
                printf("Usage: %s [port]\n", argv[0]);
                exit(1);
        }

        int port = atoi(argv[1]);

        struct event_data server = {.on_read = event_on_accept,
                                    .on_write = NULL};

        event_server_listen(port);
        event_change(server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, &server);
        event_loop();

        return 0;
}
