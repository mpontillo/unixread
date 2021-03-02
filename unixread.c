#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    int fd = open("/proc/mdstat", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    ssize_t n = -1;
    char result[BUFFER_SIZE];
    while (n != 0) {
        n = read(fd, &result, BUFFER_SIZE);
        if (n < 0) {
            perror("read");
            close(fd);
            return 2;
        }
        int written = write(STDOUT_FILENO, &result, n);
        if (written < 0) {
            perror("write");
            close(fd);
            return 3;
       }
    }
    close(fd);
}
