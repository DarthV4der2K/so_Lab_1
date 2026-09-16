#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 64

int main(){

    int fd = open("texts.bin", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if(fd == -1) return EXIT_FAILURE;
    
    char texto[SIZE];

    int read_done = 0;
    int bytes_read = 0;
    
    int register_id = 1; 
    
    while(1){

        bytes_read = read(0, texto + read_done, SIZE - read_done);

        if(bytes_read == -1) return EXIT_FAILURE;
        
        if(bytes_read == 0) break;
        
        int write_done = 0;
        int bytes_writen = 0;

        if(write(fd, &register_id, sizeof(int)) == -1) return EXIT_FAILURE;
        register_id += 1;

        while( (bytes_writen = write(fd, texto + write_done, bytes_read - bytes_writen - read_done)) > 0 ){
            if(bytes_writen == -1) return EXIT_FAILURE;
            write_done += bytes_writen;
        }

        read_done = (read_done + bytes_read) % SIZE;
    }
            
    if(close(fd) == -1) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
