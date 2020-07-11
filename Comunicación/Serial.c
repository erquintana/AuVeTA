#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>


void usage(void);

int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);



int main() {
        int baudrate = 38400;
        int port;
        int c;

        port = serialport_init("/dev/rfcomm2", baudrate);



        while (1) {
                printf("0.Led azul:\n");
                printf("1.Led verde:\n");
                printf("2.Led rojo:\n");
                scanf("%d", &c);

                if(c==0) {
                        char a = '0';
                        const char* ptr = &a;
                        serialport_write(port, ptr);
                }
                if(c==1) {
                        char a = '1';
                        const char* ptr = &a;
                        serialport_write(port, ptr);
                }
                if(c==2) {
                        char a = '2';
                        const char* ptr = &a;
                        serialport_write(port, ptr);
                }

        }
}






int serialport_write(int fd, const char* str)

{

        int len = strlen(str);

        int n = write(fd, str, len);

        if( n!=len )

                return -1;

        return n;

}


int serialport_init(const char* serialport, int baud)

{

        int fd;
        fd = open(serialport, O_RDWR | O_NOCTTY);
        if (fd == -1)  {

                perror("init_serialport: Unable to open port ");

                return -1;

        }
        return fd;

}
