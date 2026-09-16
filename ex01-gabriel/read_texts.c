#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 64

ssize_t bytes_read(int fd, void* buf, size_t count) {
    size_t bytes_read = 0;
    while (bytes_read < count) {
        ssize_t res = read(fd, (char*)buf + bytes_read, count - bytes_read);
        if (res < 0) {
            return res;  // Error
        }
        if (res == 0) {
            break;  // EOF
        }
        bytes_read += (size_t)res;
    }
    return (ssize_t)bytes_read;
}

int main(void) {
    int fd = open("texts.bin", O_RDONLY);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE + 1];
    ssize_t nbytes;

    while ((nbytes = bytes_read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[nbytes] = '\0';
        printf("%s\n", buffer);
    }

    close(fd);
    return EXIT_SUCCESS;
}