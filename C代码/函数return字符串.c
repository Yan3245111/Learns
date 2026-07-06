// 错误演示：感觉应该这么写，实际是错的，因为是局部变量，生存周期在函数里面，执行完生命周期就没了，所以报错
char * text1(void) {
    char text[100];
    sprintf(text, "%s\n", "123");
    return text;
}

// 正确方式1：使用malloc拷贝到堆，但是需要释放内存
char * text2(void) {
    char *text;
    text = (char *)malloc(100);
    sprintf(text, "%s\n", "123");
    return text;
}

int main(void) {
    char *b = text2();
    printf("%s\n", b);
    free(b);
}

//正确方式2：使用指针传进去，然后拿到text变量。注：strcpy第一个参数只能用数组，不可用指针，因为指针指向常量区，不允许修改以及text[0] = 'a'错误写法；
void text3(char * text) {
    sprintf(text, "%s\n", "123");
//    strcpy(r, "123");
}

int main(void) {
    char text[10];
    text3(text);
    printf("%s\n", text);
}

//正确方式3：全局变量，就不写示例了
