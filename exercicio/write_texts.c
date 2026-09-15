#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 64

int main(){

    int fd = open("texts.bin", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    char texto[SIZE];

    int bytes_read = 0;
    while((bytes_read = read(0, texto, SIZE -1)) > 0){
        texto[bytes_read] = '\0'; 
        write(fd, texto, bytes_read);
    }

    close(fd);
}