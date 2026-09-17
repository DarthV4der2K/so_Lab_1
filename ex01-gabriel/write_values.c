#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 64

ssize_t bytes_written(int fd, const void* buf, size_t count) {
    size_t written = 0;
    while (written < count) {
        ssize_t res = write(fd, (const char*)buf + written, count - written);
        if (res <= 0) {
            return res;
        }
        written += (size_t)res;
    }
    return (ssize_t)written;
}

int main(void) {
    int fd = open("values.bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    const char* text[] = {
        "sensor movimento operacional",
        "treino iniciado",
        "treino terminado"};

    int timestamps[] = {0, 15, 3600};

    int text_count = sizeof(text) / sizeof(text[0]);

    for (int i = 0; i < text_count; i++) {
        char buffer[BUFFER_SIZE] = {0};

        strncpy(buffer, text[i], BUFFER_SIZE - 1);

        if (bytes_written(fd, &timestamps[i], sizeof(timestamps[i])) < 0) {
            perror("write error");
            return EXIT_FAILURE;
        }

        if (bytes_written(fd, buffer, BUFFER_SIZE) < 0) {
            perror("write error");
            return EXIT_FAILURE;
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}