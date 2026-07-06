#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <fcntl.h>

static int createServer(int port)
{
    int fd;
    int rc;
    int on = 1;
    struct sockaddr_in servaddr;

    /* Configure TCP Server */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    /* Create socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    /* Set address reuse enable */
    rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(fd);
        exit(-1);
    }

    /* Set non blocking */
    rc = ioctl(fd, FIONBIO, (char *)&on);
    if (rc < 0)
    {
        perror("ioctl() failed");
        close(fd);
        exit(-1);
    }

    /* Bind to socket */
    rc = bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(fd);
        exit(-1);
    }

    /* Listen on socket */
    listen(fd, 1);
    if (rc < 0)
    {
        perror("listen() failed");
        close(fd);
        exit(-1);
    }
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    return fd;
}

static int waitServer(int fd)
{
    fd_set fds;
    struct timeval timeout;
    int rc;
    int max_fd;

    FD_ZERO(&fds);
    max_fd = fd;
    FD_SET(fd, &fds);

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;

    rc = select(max_fd + 1, &fds, NULL, NULL, &timeout);

    return rc;
}

void set_client_keepalive(int client_id)
{
    int keepalive = 1; // 开启keepalive属性
    setsockopt(client_id, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive, sizeof(keepalive));

    int keepidle = 10; // 如该连接在10秒内没有任何数据往来,则进行探测
    setsockopt(client_id, SOL_TCP, TCP_KEEPIDLE, (void *)&keepidle, sizeof(keepidle));

    int keepinterval = 2; // 探测时发包的时间间隔为2 秒
    setsockopt(client_id, SOL_TCP, TCP_KEEPINTVL, (void *)&keepinterval, sizeof(keepinterval));

    int keepcount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
    setsockopt(client_id, SOL_TCP, TCP_KEEPCNT, (void *)&keepcount, sizeof(keepcount));

    int flag = 1;
    setsockopt(client_id, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
}

void tcp_start(void) {
    int rc;
    int listenfd;
    char smbuffer[100];
    listenfd = createServer(TCP_PORT);
    while (1)
    {
        int clifd;
        struct sockaddr_in cliaddr;
        socklen_t clilen;

        clilen = sizeof(cliaddr);
        clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        if (clifd < 0)
            continue;
        set_client_keepalive(clifd);
        printf("Connection established %s\r\n", inet_ntoa(cliaddr.sin_addr));
    }
        while (1)
        {
            rc = waitServer(clifd);
            memset(smbuffer, 0x0, sizeof(smbuffer));
            if (rc < 0)
            { /* failed */
                perror("  recv() failed");
                break;
            }
            if (rc == 0)
            { /* timeout */

            }
            if (rc > 0)
            { /* something to read */
                rc = recv(clifd, smbuffer, sizeof(smbuffer), 0);
                if (rc < 0)
                {
                    if (errno != EWOULDBLOCK)
                    {
                        perror("  recv() failed");
                        break;
                    }
                }
                else if (rc == 0)
                {
                    printf("Connection closed\r\n");
                    break;
                }
                else  // > 0 数据正常
                {
                    printf("input is %s\n", smbuffer);
                }
            }
        }
        close(clifd);
    }
    return (EXIT_SUCCESS);
}