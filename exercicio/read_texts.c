#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// #include <stdio.h>

#define SIZE 64

int main(){
    int fd = open("texts.bin", O_RDONLY);

    char texto[SIZE];

    int bytes_read = 0;
    int read_done = 0;
    
    int register_read = 0;
    int register_id = 0;
    while(1){
        register_read = read(fd, &register_id, sizeof(int));
        bytes_read = read(fd, texto + read_done, SIZE - read_done);

        
        if(bytes_read < 0) return EXIT_FAILURE;
        if(register_read == 0) break;
        if(bytes_read == 0) break;
        
        int bytes_writen = 0;
        int write_done = 0;

        // printf("-->%d\n", register_id);


        write(1, &register_id, sizeof(int));
        while((bytes_writen = write(1, texto + write_done, bytes_read - read_done - bytes_writen)) > 0){
            write_done += bytes_writen;
        }

        read_done = (read_done + bytes_read) % SIZE;
        
    }

    close(fd);

    return 0;
}

