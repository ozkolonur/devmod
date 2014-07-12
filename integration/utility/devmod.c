#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>

#define DEVMOD_DEVICE "/dev/devmod"

int main(int argc, char *argv[])
{
    int result;
    int fd;
    int i;
    unsigned long x = 100;
    for(i=0;i < argc; i++)
        printf("devmod:: argv[%d] = %s\n", i, argv[i]);
    
    if ( (fd = open(DEVMOD_DEVICE, O_RDWR)) < 0 )
    {
	perror("devmod:: error opening device file\n");
	return -1;
    }
    
    printf("devmod:: argv1 %d\n", atoi(argv[1]) );

    if ( (result = ioctl(fd, atoi(argv[1]), x )) < 0 )
    {
	perror("devmod:: error opening device file\n");
	return -1;
    }

    printf("devmod:: command 1 returned %d", result);
    close(fd);
    return 0;
}
