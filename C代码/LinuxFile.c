#include <stdio.h>   // FILE
#include <dirent.h>  // DIE
#include <libgen.h>  // basename

// 文件读写
// fputs/fgets是读写字符串使用的，fputs写字符串的时候要以\n结尾，fgets会自动读取到
FILE *fp;
fputs(buf, sizeof(buf), fp);
fgets(buf, sizeof(buf), fp);

//fprintf/fscanf可以格式化写入和格式化读写
fprintf(fp, "%d %lld %s\n", 1, 100, "a");
fscanf(fp, "%d %lld %s\n", &no, &param, &buf);

// 创建文件夹，windows是单参数，linux是双参数
mkdir(path); //win
mkdir(path, 777); //linux

// 删除文件/文件夹
remove(path);

// 检测文件夹是否存在
uint8_t check_dir_exist(void) {
    DIR *dir;
    uint8_t res = 1;
    if ((dir = opendir(USB_PATH)) == NULL) {
        printf("U盘未插入, 请检测U盘状态");
        res = 0;
        exit(1);
    }
    closedir(dir);
    return res;
}


// 获取文件修改时间和文件大小（B）
uint64_t get_file_info(char *filepath, char *modifiy) {
    uint8_t res;
    uint64_t file_size;
    struct tm *tm_p;
    struct stat file_stat;
    res = stat(filepath, &file_stat);
    if (res == 0) {
        file_size = file_stat.st_size;  // 字节B
        tm_p = localtime(&file_stat.st_mtime);  // st_ctime 创建时间，st_mtime 修改时间，st_atime 访问时间
        strftime(modifiy, 128, "%Y-%m-%d %X", tm_p);
    }
    return file_size;
}

// flock 检测文件是否上锁
int lock_fd = open("/.lock", O_CREAT | O_RDWR, 0666);
int rc = flock(lock_fd, LOCK_EX | LOCK_NB); // flock加锁，LOCK_EX -- 排它锁；LOCK_NB -- 非阻塞模式
                                            // LOCK_EX | LOCK_NB：非阻塞监听文件是否上锁，如果已经上锁，返回-1，
                                            // 如果未上锁，则上锁且返回0。只能在linux下使用
