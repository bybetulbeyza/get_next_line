#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDWR , 0644);
	if (fd == -1)
		return (1);
	//int i = 0;
	//while (i < 1111)
	//{
	//	write(fd, "a",1);
	//	i++;
	//}
	////write (fd, "\n",1);
	//i = 0;
	//while (i < 1111)
	//{
	//	write(fd, "b",1);
	//	i++;
	//}
	//lseek(fd, 0,SEEK_SET);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (0);
}