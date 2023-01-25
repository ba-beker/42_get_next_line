#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
char *get_next_line()
{
	int fd;
	char *msg = "Hi there!";
	char buffer[80];
	fd = open("index.txt", O_RDWR);
	printf("%d",fd);
	write(fd, msg, sizeof(msg));
	read(fd, buffer, sizeof(msg));
	printf("%s", buffer);
	close(fd);

}
int main()
{
	get_next_line();
}
// 