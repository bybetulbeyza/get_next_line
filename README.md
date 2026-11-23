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
- Uses a configurable `BUFFER_SIZE` to determine how many bytes are read at a time. Every call to `read()` uses exactly `BUFFER_SIZE` as its size argument.

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

The project contains no `main` function. To build an executable, add your own test file (for example `main.c`) to the compilation command.

### Mandatory Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

To use the default buffer size:

```bash
cc -Wall -Wextra -Werror \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Bonus Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
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

1. **Validate:** The function returns `NULL` immediately if `fd` is negative or `BUFFER_SIZE` is not greater than zero. No extra `read()` call is made for validation, so `read()` is only ever called with `BUFFER_SIZE` as its size. Read errors are detected from the return value of the real `read()` call.
2. **Read:** The `read_file()` function reads data from the file descriptor in chunks of `BUFFER_SIZE` bytes.
3. **Store:** The newly read data is appended to the existing stash using `ft_strjoin_and_free()`.
4. **Detect:** Reading continues until a newline character is found or the end of the file is reached.
5. **Extract:** The `ft_extract_line()` function allocates and returns a new string containing the first line, including `\n` when present.
6. **Update:** The `ft_next()` function creates a new stash containing only the remaining characters after the extracted line.
7. **Return:** The extracted line is returned to the caller.

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

**Limits:** The bonus function returns `NULL` if `fd` is negative or if `fd >= MAX_FILES`, because such a value would fall outside the array. The array is still a single static variable, as required by the subject.

### 3. Justification of the Algorithm

**Why a static stash?**
A call to `read()` returns `BUFFER_SIZE` bytes, which almost never ends exactly at a newline. The bytes read after the newline belong to the next line, and they cannot be pushed back into the file descriptor (and `lseek()` is forbidden). A static variable keeps its value between calls, so it is the natural place to keep these leftover bytes without using a global variable.

**Why read in chunks and stop at the first newline?**
The subject asks to read as little as possible and not to read the whole file before processing it. The loop therefore stops as soon as the stash contains a `\n`. This keeps memory usage proportional to the current line (plus at most one extra buffer), and it also works with standard input, pipes, and other file descriptors that are not regular files, where the total size is unknown and the data may arrive progressively.

**Why does it work for any `BUFFER_SIZE`?**

- With `BUFFER_SIZE = 1`, every call reads one byte at a time. The loop simply runs more times, and the stash grows until a newline appears. The result is correct but slower because of more system calls.
- With a very large `BUFFER_SIZE` (for example 9999 or 10000000), one `read()` may return many lines at once. The first line is extracted and the rest stays in the stash, ready for the next calls. The temporary buffer is allocated on the heap (not on the stack), so a large value does not cause a stack overflow.
- The buffer is allocated with `BUFFER_SIZE + 1` bytes so a terminating `'\0'` can be written after the bytes returned by `read()`.

**Why separate `ft_extract_line()` and `ft_next()`?**
Each function has a single responsibility (read, extract the line, keep the remainder), which keeps the code readable and small enough to respect the Norm.

**Trade-off:**
`ft_strjoin()` allocates a new string and copies the stash on every `read()` call. For very long lines with a very small `BUFFER_SIZE`, this means repeated copying. This was accepted in favor of simplicity and clarity.

### 4. Utility Functions

Both implementations use custom utility functions instead of the `libft` library.

| Function | Purpose |
|---|---|
| `ft_strlen()` | Calculates the length of a string |
| `ft_strchr()` | Searches for a character in a string |
| `ft_strjoin()` | Concatenates two strings |
| `ft_calloc()` | Allocates and initializes memory to zero |
| `ft_free()` | Frees allocated memory and returns `NULL` |

### 5. Memory Management and Error Handling

Dynamic memory allocation is essential to this project because the size of a line is not known in advance.

The implementation uses `malloc()` and custom allocation utilities to manage:

- The temporary read buffer.
- The stash containing unread data.
- The extracted line returned to the caller.
- Temporary strings created during concatenation and stash updates.

Allocated memory is released when it is no longer needed. The caller is responsible for freeing each returned line.

Failures are handled so that no memory is leaked and no crash occurs:

- If `read()` returns `-1`, the buffer and the stash are freed and `NULL` is returned.
- If any `malloc()` fails (buffer, stash, joined string, extracted line, or new stash), the memory already owned by the function is freed and `NULL` is returned.
- If joining the stash with the new data fails, the stash becomes `NULL`, and the reading loop checks for this before using it.
- When the end of the file is reached and nothing remains in the stash, the stash is freed and set to `NULL`.

## Resources

- **42 Get Next Line Subject:** Official project requirements and evaluation guidelines.
- **Oceano – Get Next Line Explained:** [YouTube Tutorial](https://www.youtube.com/watch?v=8E9siq7apUU). A tutorial covering file descriptors, the `read()` system call, static variables, and the implementation logic.
- **Linux Manual – read():** [man7.org](https://man7.org/linux/man-pages/man2/read.2.html). Documentation about the `read()` system call.
- **C Library – malloc():** [cppreference](https://en.cppreference.com/w/c/memory/malloc). Reference for dynamic memory allocation.

### AI Usage Declaration

Artificial Intelligence was used as a learning aid throughout the project. It helped clarify concepts such as file descriptors, static variables, buffer management, dynamic memory allocation, and the behavior of the `read()` system call.

Artificial Intelligence was also used to help write and structure this `README.md` file (its sections, wording, and formatting), ensuring the requirements of the subject were covered.

The implementation, testing, and understanding of the algorithms remain part of the learning process.
