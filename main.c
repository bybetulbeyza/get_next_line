#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd1 = open("tst1.txt", O_RDONLY);
    int fd2 = open("tst2.txt", O_RDONLY);
    char *l1= get_next_line(fd1);
    char *l2= get_next_line(fd2);
    while(l1 || l2)
    {
        if(l1)
        {
            printf("%s",l1);
            free(l1);
            l1 = get_next_line(fd1);
        }
        if(l2)
        {
            printf("%s",l2);
            free(l2);
            l2 = get_next_line(fd2);
        }
    }
    close(fd1);
    close(fd2);
    return (0);
}
