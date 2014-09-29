#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H

#include <iostream>             // cout, endl
#include <list>                 // list
#include <string.h>             // memset, memcpy
#include <stdlib.h>             // atoi
#include <stdio.h>              // sprintf
#include <unistd.h>             // close
#include <fcntl.h>              // fcntl
#include <errno.h>              // errno
#include <sys/epoll.h>          // epoll
#include <arpa/inet.h>          // socket..., htonl, htons

#define DEFAULT_SOCK_COUNT  100 // epoll size
#define DEFAULT_PORT        9999// server port
#define DEFAULT_TIME_OUT    -1  // keep waiting

/* default strings */
#define CLIENT_NAME         "Client #%d: "
#define WELCOME             "Welcome to GroupChat! You ID is: Client #%d\n"
#define NO_CONNECTION       "No one connected to server except you!\n"

using namespace std;

class epoll_server
{
    public:
        epoll_server();
        virtual ~epoll_server();

        void    init(int port = DEFAULT_PORT, int sock_count = DEFAULT_SOCK_COUNT);
        int     epoll_server_wait(int time_out);
        int     accept_new_client();
        int     recv_data(int sock, char* recv_buf);
        int     send_data(int sock, char* send_buf, int buf_len);
        void    run(int time_out = DEFAULT_TIME_OUT);
        int    set_nonblock(int sock);
        void    handle_msg(int sock);

    private:
        int     m_listen_sock;                  // server listen sock fd
        int     m_epoll_fd;                     // epoll create return fd
        int     m_max_count;                    // equals sock_count
        list<int> m_clients_list;               // clients' fd number
        struct epoll_event *m_epoll_events;     // R-B tree root
};

#endif // EPOLL_SERVER_H
