#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

char *PATH = "c:/Users/Radsim/Desktop/Test/111_LIST.CSV";

void *thread_read(void) {
    FILE *fp;
    char buf[10];
    memset(buf, 0x00, sizeof(buf));
    fp = fopen(PATH, "r");
    if (fp != NULL) {
        printf("打开文件成功\n");
    }
    int64_t a;
    fscanf(fp, "%lld\n", &a);
    printf("%lld\n", a);
}



int main(void) {
    pthread_t pid_read;
    if (pthread_create(&pid_read, NULL, thread_read, NULL) != 0)
    {
        printf("g_monitor 线程启动失败\n");
    }
    printf("线程启动成功\n");
    pthread_join(pid_read, NULL);
    return 0;
}
