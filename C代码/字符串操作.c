#include <string.h>
#include <stdio.h>

// 字符串拼接
char buf[100];
char *text = "1234";
memset(buf, 0x00, sizeof(buf))
strcat(buf, text);  // 单字符串拼接

snprintf(buf, sizeof(buf), "%s/%s", text, "567")  // 多字符串拼接

// 字符串比对，包含关系，前面全部包含后面的则p=前面
char *p = strstr("123", "12")
if (p) {

}

// 字符串比对，等于0则str1=str2， 小于0则str1<str2, 大于0则str1>str2， 是按照当前字符串的ascii码排序进行比对的
int res = strcmp("123", "213")
if (res) {

}

// 字符串copy
strcpy(buf, text);  // "1234"，如果之前有数据会被覆盖

//strtok 分隔符
char a[20] = "123 - 456 - 789";
char * ton;
int a, b;
ton = strtok(a, "-");
a = atoi(ton);      // 123
b = atoi(strtok(NULL, "-"));  //456
while (ton != NULL) {
    printf("%s\n", ton);
    ton = strtok(NULL, "-");
}


//strtoul(long)  strtoull(long long)
// 分割字符串里的数字和字符串
char buf[100] = "123456111111111 hello qweqweqw";
int64_t a;
char *p;
a = strtoull(buf, &p, 10);  // 以十进制进行读取
printf("%lld\n", a);  // 123456111111111
printf("%s\n", p);    // hello qweqweqw


// sscanf  with fscanf
// sscanf 可以把空格两边的数据分离出来 例如
char buf[10] = "hh= 123";
char buf1[10];
int num;
sscanf(buf, "%s %d", buf1, &num);
printf("%s %d\n", buf1, num);  // hh= 123
// 也可以用于数据分离，比如
sscanf(buf, "hh= %d", &num);  // 123

// fscanf 是从文件读取数据\n结尾，然后可以将数据分离
FILE *fp = fopen(PATH, "r");
fscanf(fp, "hh=%d", &num);  // 123
