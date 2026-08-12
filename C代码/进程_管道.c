#include <sys/wait.h>  // Linux
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    int fd[2];
    pid_t pid;
    char buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    // 父进程fork子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // 子进程读取管道
        close(fd[1]);  // 关闭子进程写端
        read(fd[0], buf, sizeof(buf));
        printf("子进程读取到: %s", buf);
        close(fd[0]);
        exit(0);
    }
    else {
        close(fd[0]);   // 关闭父进程读端
        write(fd[1], "hello", 5);
        close(fd[1]);
        wait(NULL);  // 等待子进程结束
        exit(0);
    }
    return 0;
}
