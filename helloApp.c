#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "common.h"
//需要先创建设备节点 mknod /dev/xxx c 111 0

int main(int argc, char *argv[])
{
    char buf[10];
    int fd = -1;
#if 1

    /* 打开/dev/目录下的xxx设备,open的返回值是一个文件描述符 */
    fd = open("/dev/xxx", O_RDWR);
    if (fd < 0) /* 文件描述符小于0表示打开文件失败 */
    {
        perror("open /dev/xxx fail\n");
        return -1;
    }
#endif
    char cmd = argv[1][0];
    printf("%c\n", cmd);
    switch (cmd)
    {
    case '1':
        printf("全部开始\n");
        printf("%s\n", ioctl(fd, IOC_START) ? "执行报错\n" : "执行成功\n");
        break;
    case '2':
        printf("全部暂停\n");
        printf("%s\n", ioctl(fd, IOC_PAUSE) ? "执行报错\n" : "执行成功\n");
        break;
    case '3':
        printf("全部重新开始\n");
        printf("%s\n", ioctl(fd, IOC_RESTART) ? "执行报错\n" : "执行成功\n");
        break;
    case '4':
        printf("全部停止\n");
        printf("%s\n", ioctl(fd, IOC_STOP) ? "执行报错\n" : "执行成功\n");
        break;
    case '5':
        printf("1号线程暂停\n");
        printf("%s\n", ioctl(fd, IOC_PAUSE_1) ? "执行报错\n" : "执行成功\n");
        break;
    case '6':
        printf("2号线程暂停\n");
        printf("%s\n", ioctl(fd, IOC_PAUSE_2) ? "执行报错\n" : "执行成功\n");
        break;
    case '7':
        printf("1号线程开始\n");
        printf("%s\n", ioctl(fd, IOC_START_1) ? "执行报错\n" : "执行成功\n");
        break;
    case '8':
        printf("2号线程开始\n");
        printf("%s\n", ioctl(fd, IOC_START_2) ? "执行报错\n" : "执行成功\n");
        break;
    case '9':
        printf("1号线程停止\n");
        printf("%s\n", ioctl(fd, IOC_STOP_1) ? "执行报错\n" : "执行成功\n");
        break;
    case 'a':
        printf("2号线程停止\n");
        printf("%s\n", ioctl(fd, IOC_STOP_2) ? "执行报错\n" : "执行成功\n");
        break;
    case 'b':
        printf("1号线程重新开始\n");
        printf("%s\n", ioctl(fd, IOC_RESTART_1) ? "执行报错\n" : "执行成功\n");
        break;
    case 'c':
        printf("2号线程重新开始\n");
        printf("%s\n", ioctl(fd, IOC_RESTART_2) ? "执行报错\n" : "执行成功\n");
        break;
    default:
        printf("输入的命令不支持\n");
        cmd = 0;
        break;
    }
    close(fd);
    return 0;
}
