*This project has been created as part of the 42 curriculum by betdemir.*

# get_next_line

## Description

The goal of this project is to write a function that returns a line read from a file descriptor, one call at a time. This project serves as an introduction to file descriptors, the `read()` system call, static variables, and dynamic memory management in C.

The `get_next_line` function has the following prototype:

```
char *get_next_line(int fd);
```

Its behavior is defined as follows:

* Each call returns the next line read from the file descriptor `fd`, including the terminating `\n` character (except when the end of the file is reached and the last line does not end with a newline).

* When there is nothing else to read, or when an error occurs, the function returns `NULL`.

* It works both with regular files and with standard input.

* The size of the read buffer is defined at compile time by the `BUFFER_SIZE` macro. If it is not defined, a default value of `42` is used.

As per the project requirements, the use of `lseek()`, global variables, and the `libft` library is not allowed. All necessary helper functions (`ft_strjoin`, `ft_calloc`, `ft_strchr`, `ft_strlen`, `ft_free`) are re-implemented in `get_next_line_utils.c`.

## Instructions

### Compilation

The project consists of the following files:

* `get_next_line.c` - Contains the main `get_next_line` function and its static helper functions.

* `get_next_line_utils.c` - Contains the utility functions used by the main file.

* `get_next_line.h` - Contains the prototypes, the required includes, and the default `BUFFER_SIZE` definition.

The files must be compiled with the flags `-Wall -Wextra -Werror`. The buffer size can be set with the `-D BUFFER_SIZE=n` option:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

If the `-D BUFFER_SIZE` option is omitted, the default value defined in the header file (`42`) is used.

### Execution / Usage

Include the header file in your C code:

```
#include "get_next_line.h"
```

Open a file, then call `get_next_line` repeatedly until it returns `NULL`. Each returned line is allocated with `malloc` and must be freed by the caller:

```
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Resources

* **Video Tutorial - ["get_next_line explained : develop a function that reads a file line by line" (Oceano)](https://www.youtube.com/watch?v=8E9siq7apUU):** A YouTube video covering file descriptors, the `read` system call, the implementation of `get_next_line`, and the meaning of the `static` keyword. I watched roughly the first half of it while trying to understand the project's core concepts.

* **AI Usage Declaration:**

* AI Usage: Artificial Intelligence was used as a learning aid while trying to understand the concepts behind this project (such as file descriptors, how `read()` behaves, and how a static variable keeps its value between calls). It was also used to assist in the initial structuring and drafting of this README.md file, ensuring all mandatory guidelines from the subject were met clearly and concisely.

## Algorithm and Data Structure

### Algorithm

The core algorithm relies on reading the file in fixed-size chunks and keeping the unprocessed remainder between calls:

1. On each call, validate the arguments: `fd` must not be negative, `BUFFER_SIZE` must be greater than zero, and a test `read(fd, 0, 0)` must not fail.

2. Call `read_file`, which reads `BUFFER_SIZE` bytes at a time into a temporary buffer and appends them to the static `stash` until the stash contains a `\n` character or the end of the file is reached.

3. Call `ft_extract_line`, which copies the content of the stash up to and including the first `\n` into a newly allocated string. If the stash is empty, `NULL` is returned.

4. Call `ft_next`, which creates a new stash containing only the characters that come after the extracted line, and frees the old one. If there is nothing left after the line, the stash is freed and set to `NULL`.

5. Return the extracted line to the caller.

6. If `read()` fails at any point, all allocated memory is freed and `NULL` is returned.

### Data Structure

* **Static Variable:** A single `static char *stash` is used inside `get_next_line` to preserve the data that was read from the file descriptor but not yet returned. Since its value persists between function calls, the next call can continue exactly where the previous one stopped.

* **Dynamic Strings:** The stash, the temporary read buffer, and every returned line are heap-allocated strings. Helper functions (`ft_strjoin`, `ft_calloc`, `ft_free`) manage their creation and release to prevent memory leaks.

* **State Tracking:** The number of bytes returned by `read()` is tracked to detect the end of the file (`0`) or an error (`-1`), and the presence of a `\n` character in the stash determines when to stop reading.
