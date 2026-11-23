#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int     fd[3];
    int     i;
    int     active;
    char    *line;

    if (argc != 4)
        return (1);

    i = 0;
    while (i < 3)
    {
        fd[i] = open(argv[i + 1], O_RDONLY);
        if (fd[i] == -1)
        {
            while (--i >= 0)
                close(fd[i]);
            return (1);
        }
        i++;
    }

    active = 3;
    while (active > 0)
    {
        i = 0;
        while (i < 3)
        {
            if (fd[i] != -1)
            {
                line = get_next_line_bonus(fd[i]);
                if (line == NULL)
                {
                    close(fd[i]);
                    fd[i] = -1;
                    active--;
                }
                else
                {
                    printf("[FD %d] %s", fd[i], line);
                    if (line[strlen(line) - 1] != '\n')
                        printf("\n");
                    free(line);
                }
            }
            i++;
        }
    }
    return (0);
}
