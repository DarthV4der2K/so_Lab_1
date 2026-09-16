#include <stdlib.h>
// #include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 64

int main(){

    int fd = open("texts.bin", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    char texto[SIZE];


    int read_done = 0;
    // int bytes_read = 0;

    // while((bytes_read = read(0, texto + done, SIZE -1 - done)) > 0){
    //     texto[bytes_read] = '\0';
    //     write(fd, texto + bytes_read, bytes_read);
    // }

    int register_id = 1; 
    while(1){
        int bytes_read = 0;
        bytes_read = read(0, texto + read_done, SIZE - read_done);

        if(bytes_read < 0) return EXIT_FAILURE;
        
        if(bytes_read == 0) break;

        // printf("\nregister: %d\n", register_id);
        // printf("bytes read: %d\n", bytes_read);
        
        int write_done = 0;
        int bytes_writen = 0;

        write(fd, &register_id, sizeof(int));
        register_id += 1;

        while( (bytes_writen = write(fd, texto + write_done, bytes_read - bytes_writen - read_done)) > 0 ){
            write_done += bytes_writen;
            // printf("bytes writen: %d\n", bytes_writen);
        }


        read_done = (read_done + bytes_read) % SIZE;
        
    }
    // texto[read_done] = '\0';
    
    // printf("\n");
        
    close(fd);
}
