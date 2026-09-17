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
    int fd = open("values.bin", O_RDONLY);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    int val;
    char buffer[BUFFER_SIZE + 1];

    while (1) {
        ssize_t res_val = bytes_read(fd, &val, sizeof(val));
        
        if (res_val == 0) {
            break;
        }

        if (res_val < 0 || res_val != sizeof(val)) {
            perror("read error");
            close(fd);
            return EXIT_FAILURE;
        }

        ssize_t res_text = bytes_read(fd, buffer, BUFFER_SIZE);
        if (res_text != BUFFER_SIZE) {
            perror("read error");
            close(fd);
            return EXIT_FAILURE;
        }

        buffer[BUFFER_SIZE] = '\0';
        
        printf("%d | %s\n", val, buffer);
    }

    close(fd);
    return EXIT_SUCCESS;
}