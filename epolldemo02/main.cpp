#include "epoll_server.h"

int
main(int argc, char* argv[])
{
    int port;
    epoll_server my_epoll_server;

    if (argc == 2) {
        port = atoi(argv[1]);
        my_epoll_server.init(port);
    } else
        my_epoll_server.init();

    my_epoll_server.run(5000);

    return 0;
}
