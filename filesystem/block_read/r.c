#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#define BLKSIZE 512
int main(int argc, char** argv)
{
    int fd;
    int random = 0;

    srand(time(0));

    //fd = open("/dev/sda3", O_RDONLY | O_DIRECT);
    fd = open("/dev/sda3", O_RDONLY);
    //fd = open("/home/popacai/ram2", O_RDONLY, O_DIRECT);
    //fd = open("/dev/rawctl", O_RDONLY);
    if (argc < 3)
	exit (1);

    printf("fd=%d\n",fd);
    random = 0;
    if (fd < 0)
    {
	printf("error to open\n");
    }

    unsigned char* block;
    block = memalign(BLKSIZE, BLKSIZE);

    int n;
    unsigned long long total = 0;
    unsigned long long file_size = 0;
    file_size = atoi(argv[1]);
    struct timeval t1, t2;
    unsigned long long interval = 0;
    printf("file_size=%dMB\n", file_size);
    gettimeofday(&t1);
    while (1)
    {
	n = read(fd, block, BLKSIZE);
	total += n;
	if ((total / 1024 / 1024) > file_size)
	{
	    printf("%d\n",total);
	    printf("%d\n",file_size);
	    break;
	}
	printf("%llu\r", total / 1024 / 1024);
    }
    gettimeofday(&t2);
    interval = (t2.tv_sec - t1.tv_sec) * 1000000 + 
	       (t2.tv_usec - t1.tv_usec);
    printf("\n");
    printf("latency=usec/MB,%llu\n", interval / file_size);
    printf("throughputs=KB/s,%f\n", file_size * 1024.0 / interval);

    printf("\n\nafter hot\n");


    gettimeofday(&t1);
    while (1)
    {
	n = read(fd, block, BLKSIZE);
	total += n;
	if ((total / 1024 / 1024) > file_size)
	{
	    printf("%d\n",total);
	    printf("%d\n",file_size);
	    break;
	}
	printf("%llu\r", total / 1024 / 1024);
    }
    gettimeofday(&t2);
    interval = (t2.tv_sec - t1.tv_sec) * 1000000 + 
	       (t2.tv_usec - t1.tv_usec);
    printf("\n");
    printf("latency=usec/MB,%llu\n", interval / file_size);
    printf("throughputs=KB/s,%f\n", file_size * 1024.0 / interval);


    close(fd);
    return 0;
}
