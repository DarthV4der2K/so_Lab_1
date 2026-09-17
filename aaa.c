#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define SIZE 64

int main(){
    int fd = open("texts.bin", O_RDONLY);
    if(fd == -1) return EXIT_FAILURE;

    char texto[SIZE];

    int bytes_read = 0;
    int read_done = 0;
    
    int seconds_read = 0;
    int seconds = 0;
    while(1){

        seconds_read = read(fd, &seconds, sizeof(int));
        bytes_read = read(fd, texto + read_done, SIZE - read_done);        
        
        if((bytes_read < 0) || (seconds_read < 0)) return EXIT_FAILURE;
        if(seconds_read == 0) break;
        
        int bytes_writen = 0;
        int write_done = 0;

        // if(write(1, &seconds, sizeof(int)) == -1) return EXIT_FAILURE;

        printf("\n%d\n", seconds);
        // printf("%s", texto);      
        while((bytes_writen = write(1, texto + write_done, bytes_read - read_done - bytes_writen)) > 0){
            if(bytes_writen == -1) return EXIT_FAILURE;
            write_done += bytes_writen;
        }

        read_done = (read_done + bytes_read) % SIZE;
        
    }

    if(close(fd) == -1) return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

