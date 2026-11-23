*This project has been created as part of the 42 curriculum by betdemir.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a C programming project from the 42 curriculum. The goal is to develop a function that reads and returns a line from a file descriptor, one line at a time.

The project introduces fundamental C programming concepts, including file descriptors, the `read()` system call, static variables, dynamic memory allocation, and memory management.

The main function has the following prototype:

```c
char *get_next_line(int fd);
```

### Function Behavior

- Each call returns the next line from the given file descriptor.
- The returned line includes the terminating `\n` character, except when the final line does not end with a newline.
- Returns `NULL` when there is nothing left to read or when an error occurs.
- Supports reading from regular files and standard input.
- Uses a configurable `BUFFER_SIZE` to determine how many bytes are read at a time.

The project consists of two parts:

- **Mandatory:** Reads one file descriptor at a time using a single static stash variable.
- **Bonus:** Supports multiple file descriptors simultaneously while maintaining their independent reading states using a single static array.

## Instructions

### Compilation

The project must be compiled with the following flags:

```bash
-Wall -Wextra -Werror
```

The buffer size can be defined during compilation using `-D BUFFER_SIZE=n`. If no value is provided, the default value is `42`.

### Mandatory Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

To use the default buffer size:

```bash
cc -Wall -Wextra -Werror \
get_next_line.c get_next_line_utils.c
```

### Bonus Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Usage

Include the appropriate header file:

```c
#include "get_next_line.h"
```

For the bonus implementation:

```c
#include "get_next_line_bonus.h"
```

Open a file and repeatedly call `get_next_line()` until it returns `NULL`.

Each returned line is dynamically allocated and must be freed by the caller.

Example:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

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

## Project Structure

### Mandatory Files

| File | Description |
|---|---|
| `get_next_line.c` | Main function and line-reading algorithm |
| `get_next_line_utils.c` | String manipulation and memory utility functions |
| `get_next_line.h` | Function prototypes, includes, and default buffer size |

### Bonus Files

| File | Description |
|---|---|
| `get_next_line_bonus.c` | Multi-file-descriptor implementation |
| `get_next_line_utils_bonus.c` | Utility functions for the bonus implementation |
| `get_next_line_bonus.h` | Bonus prototypes and configuration macros |

## Algorithm and Data Structures

### 1. Mandatory Part

The mandatory implementation uses a single static pointer called `stash` to preserve unread data between function calls.

The algorithm consists of the following steps:

1. **Read:** The `read_file()` function reads data from the file descriptor in chunks of `BUFFER_SIZE` bytes.
2. **Store:** The newly read data is appended to the existing stash using `ft_strjoin_and_free()`.
3. **Detect:** Reading continues until a newline character is found or the end of the file is reached.
4. **Extract:** The `ft_extract_line()` function allocates and returns a new string containing the first line, including `\n` when present.
5. **Update:** The `ft_next()` function creates a new stash containing only the remaining characters after the extracted line.
6. **Return:** The extracted line is returned to the caller.

The stash preserves any previously read data that has not yet been returned. This allows subsequent calls to continue reading without losing information.

### 2. Bonus Part

The bonus implementation extends the mandatory functionality to support multiple file descriptors simultaneously.

Unlike the mandatory implementation, which uses one static pointer, the bonus implementation uses a static array of pointers:

```c
static char *temp[MAX_FILES];
```

The `MAX_FILES` macro defines the maximum number of file descriptor indices that can be managed. Its default value is `1024`.

Each array index stores the stash associated with its corresponding file descriptor.

For example:

- `temp[3]` stores the unread data for file descriptor 3.
- `temp[4]` stores the unread data for file descriptor 4.
- `temp[5]` stores the unread data for file descriptor 5.

When `get_next_line()` is called with a specific file descriptor, the corresponding stash is accessed and updated independently.

This allows the function to switch between multiple file descriptors without losing their individual reading states.

For example, calls can be made in the following order:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);
get_next_line(fd1);
get_next_line(fd2);
```

Each file descriptor continues reading from where its previous call stopped.

### 3. Utility Functions

Both implementations use custom utility functions instead of the `libft` library.

| Function | Purpose |
|---|---|
| `ft_strlen()` | Calculates the length of a string |
| `ft_strchr()` | Searches for a character in a string |
| `ft_strjoin()` | Concatenates two strings |
| `ft_calloc()` | Allocates and initializes memory to zero |
| `ft_free()` | Frees allocated memory and returns `NULL` |

### 4. Memory Management

Dynamic memory allocation is essential to this project because the size of a line is not known in advance.

The implementation uses `malloc()` and custom allocation utilities to manage:

- The temporary read buffer.
- The stash containing unread data.
- The extracted line returned to the caller.
- Temporary strings created during concatenation and stash updates.

Allocated memory is released when it is no longer needed. The caller is responsible for freeing each returned line.

## Resources

- **42 Get Next Line Subject:** Official project requirements and evaluation guidelines.
- **Oceano – Get Next Line Explained:** [YouTube Tutorial](https://www.youtube.com/watch?v=8E9siq7apUU). A tutorial covering file descriptors, the `read()` system call, static variables, and the implementation logic.
- **Linux Manual – read():** [man7.org](https://man7.org/linux/man-pages/man2/read.2.html). Documentation about the `read()` system call.
- **C Library – malloc():** [cppreference](https://en.cppreference.com/w/c/memory/malloc). Reference for dynamic memory allocation.

### AI Usage Declaration

Artificial Intelligence was used as a learning aid throughout the project. It helped clarify concepts such as file descriptors, static variables, buffer management, dynamic memory allocation, and the behavior of the `read()` system call.

The implementation, testing, and understanding of the algorithms remain part of the learning process.
