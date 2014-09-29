#include "epoll_server.h"

/* constructor */
epoll_server::epoll_server()
{
    m_listen_sock =     0;
    m_epoll_fd =        0;
    m_max_count =       0;
    m_epoll_events =    NULL;
}

/* deconstructor */
epoll_server::~epoll_server()
{
    if (m_listen_sock > 0)
        close(m_listen_sock);   // close the listen fd socket create
    if (m_epoll_fd > 0)
        close(m_epoll_fd);      // close the epoll fd epoll create
}

/*
 *                 INIT()
 * 1. socket() to create socket and return listen fd
 * 2. bind() to bind listen fd and server address info
 * 3. listen() to listen this fd with a 5 members queue
 * 4. epoll_create() to create epoll with a max connect size and return epoll fd
 * 5. epoll_ctl() to add the listen fd to epoll events list
 */
void epoll_server::init(int port, int sock_count)
{
    m_max_count = sock_count;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family =        AF_INET;
    server_addr.sin_addr.s_addr =   htonl(INADDR_ANY);
    server_addr.sin_port =          htons(port);

    if ((m_listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cout << "create socket error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    } else {
        cout << "create listen socket...Done" << endl;
    }

    set_nonblock(m_listen_sock);


    if (bind(m_listen_sock, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1) {
        cout << "bind socket error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    } else {
        cout << "bind listen socket...Done" << endl;
    }

    if (listen(m_listen_sock, 5) == -1) {
        cout << "listen socket error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    } else {
        cout << "start listening..." << endl;
    }

    if ((m_epoll_events = new struct epoll_event[sock_count]) == NULL) {
        cout << "events create error" << endl;
        exit(1);
    }

    m_epoll_fd = epoll_create(sock_count);
    struct epoll_event ev;
    ev.data.fd = m_listen_sock;
    ev.events = EPOLLIN;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_listen_sock, &ev) == -1) {
        cout << "epoll config listen sock error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    }
}

/*
 *          EPOLL_SERVER_WAIT()
 * package the epoll_wait() to listen the change in epoll events list
 * and return the number of active socket fd
 */
int epoll_server::epoll_server_wait(int time_out)
{
    int ret = epoll_wait(m_epoll_fd, m_epoll_events, m_max_count, time_out);
    return ret;
}

/*
 *          ACCEPT()
 * accept() to accept new client sock fd when the socket listened
 * and add the client sock fd to the epoll events, then return client fd
 */
int epoll_server::accept_new_client()
{
    int new_sock, str_len, ret;
    char msg_buf[1024];
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr);
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    if ((new_sock = accept(m_listen_sock,
         (struct sockaddr *)&client_addr, &client_len)) == -1) {
        cout << "accept socket error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    }

    if (set_nonblock(new_sock) == -1) {
        close(new_sock);
    } else {
        cout << "new sock: " << new_sock
             << " accept to connect" << endl;
    }

    struct epoll_event ev;
    ev.data.fd = new_sock;
    ev.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, new_sock, &ev) == -1) {
        cout << "epoll config new sock error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        exit(1);
    }

    m_clients_list.push_back(new_sock);
    memset(msg_buf, 0, sizeof(msg_buf));
    str_len = sprintf(msg_buf, WELCOME, new_sock);
    if ((ret = send(new_sock, msg_buf, sizeof(msg_buf), 0)) == -1) {
        cout << "welcome send sock error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
    }

    return new_sock;
}

/*
 *          RECV_DATA()
 * param sock is a client sock fd which send msg to server
 * param *recv_buf is a char buf which save msg
 * recv 1024 byte in one while loop
 * finished if the recv data is less than 1024 byte
 */
int epoll_server::recv_data(int sock, char *recv_buf)
{
    char    buf[1024] = {0};
    int     len = 0;
    int     ret = 0;

    while (ret >= 0) {
        ret = recv(sock, buf, sizeof(buf), 0);
        if (ret == -1) {
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events = EPOLLERR;
            if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, sock, &ev) == -1) {
                cout << "epoll config delete recv sock error: " << strerror(errno)
                     << "(errno: " << errno << ")" << endl;
                exit(1);
            } else {
                cout << "the socket: " << sock << " is closed" << endl;
            }
            m_clients_list.remove(sock);
            cout << "recv error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
            close(sock);
            break;
        } else if (ret < 1024) {
            memcpy(recv_buf, buf, ret);
            len += ret;
            break;
        } else {
            memcpy(recv_buf, buf, sizeof(buf));
            len += ret;
        }
    }
    return ret <= 0 ? ret : len;
}

/*
 *          SEND_DATA()
 * param sock is a client sock fd which will recv msg from server
 * param *send_buf is a char buf which save msg
 * param buf_len is the total len of send_buf
 * send 1024 byte in one while loop
 * finished if the send data is less than 1024 byte
 * modify the client sock fd's config to EPOLLIN
 */
int epoll_server::send_data(int sock, char *send_buf, int buf_len)
{
    int len = 0;
    int ret = 0;

    while (len < buf_len) {
        ret = send(sock, send_buf + len, 1024, 0);
        if (ret == -1) {
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events = EPOLLERR;
            if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, sock, &ev) == -1) {
                cout << "epoll config delete send sock error: " << strerror(errno)
                     << "(errno: " << errno << ")" << endl;
                exit(1);
            }
            m_clients_list.remove(sock);
            cout << "send error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
            close(sock);
            break;
        } else if (ret < 1024)
            break;
        else
            len += ret;
    }

    if (ret > 0) {
        struct epoll_event ev;
        ev.data.fd = sock;
        ev.events = EPOLLIN | EPOLLET;
        if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, sock, &ev) == -1) {
            cout << "epoll config modify send sock error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
            exit(1);
        }
    }
    return ret <= 0 ? ret : len;
}

/*
 *              RUN()
 * run() to start the epoll_server
 * param time_out is to wait running epoll_wait once
 * determine what the m_epoll_events[i].data.fd equals
 * 1. if it equals listen sock fd, then do accept_new_client()
 * 2. if it equals client sock fd, and the property is EPOLLIN,
 *    then recv_data() from client
 * 3. if it equals client sock fd, and the property is EPOLLOUT,
 *    then send_data() to client
 */
void epoll_server::run(int time_out)
{
    while (1) {
        int ret = epoll_server_wait(time_out);

        if (ret == 0) {
            continue;
        } else if (ret == -1) {
            cout << "epoll wait error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
            continue;
        } else {
            for (int i = 0; i < ret; ++i) {
                if (m_epoll_events[i].data.fd == m_listen_sock) {
                        accept_new_client();
                } else {
                    handle_msg(m_epoll_events[i].data.fd);
                }
            }
        }
    }
}

/*
 *              SET_NONBLOCK()
 */
int epoll_server::set_nonblock(int sock)
{
    int opts;

    opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
        cout << "fcntl error: " << strerror(errno)
             << "(errno: " << errno << ")" << endl;
        return -1;
    } else {
        opts = opts | O_NONBLOCK;
        if (fcntl(sock, F_SETFL, opts) < 0) {
            cout << "fcntl error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
            return -1;
        }
    }
    return 0;
}

/*
 *              HANDLE_MSG()
 * send and recv data
 */
void epoll_server::handle_msg(int sock)
{
    int ret;
    char *recv_buf = new char[65535];
    char *send_buf = new char[65535];

    memset(recv_buf, 0, 65535);
    memset(send_buf, 0, 65535);

    recv_data(sock, recv_buf);

    if (m_clients_list.size() == 1) {
        if ((ret = send(sock, NO_CONNECTION, strlen(NO_CONNECTION), 0)) == -1) {
            cout << "send to myself error: " << strerror(errno)
                 << "(errno: " << errno << ")" << endl;
        }
    }

//    strcpy(send_buf, recv_buf);
//    memset(recv_buf, 0, 65535);
    sprintf(send_buf, CLIENT_NAME, sock);
    ret = strlen(CLIENT_NAME);
    strcpy((send_buf + (ret - 1)), recv_buf);

    list<int>::iterator it;
    for (it = m_clients_list.begin(); it != m_clients_list.end(); ++it) {
        if (*it != sock) {
            send_data(*it, send_buf, strlen(send_buf));
        }
    }

}
