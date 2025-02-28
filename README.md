# get_next_line 📑

**A kind of command `cat` implementation in C**

## 📋 Overview

`get_next_line` is a C function that reads from a file descriptor and returns one line at a time. Each call to the function returns the next line from the file, making it ideal for:

- Processing text files efficiently
- Parsing large files without loading everything into memory
- Reading from various sources (files, stdin, pipes, etc.)
- Working with multiple file descriptors simultaneously (bonus version)

## ⚙️ Key Features

- 🔍 Memory Efficient: Only loads what it needs into memory
- 🔄 Multiple FD Support: Handles multiple file descriptors concurrently (bonus version)
- 📊 Flexible Buffer Size: Works with any buffer size from 1 byte to several megabytes
- 🛡️ Zero Memory Leaks: Carefully managed memory allocation and cleanup
- 🔧 Robust Error Handling: Gracefully manages edge cases

## 💻 Usage

This is the main function to test `get_next_line`. It is already set up to read from a file or standard input. Simply compile it along with `get_next_line` and use it with test files.

```c
#include "get_next_line.h"

int main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac < 2)
		fd = 0;
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening the file");
			return (0);
		}
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (fd != 0)
		close(fd);
	return (0);
}
```

## 💻  Example Usage

Compile and run with a test file:

```bash
$ ./a.out example.txt
```
This will read and display the contents of example.txt line by line.

If you run the program without arguments, it will read from standard input:
```bash
$ ./a.out
Hello, world!    <- You type this
Hello, world!    <- Program outputs this
```

## 🔧 Buffer Size Configuration
The function's buffer size can be adjusted when compiling your program:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 *.c
```

Adjusting the buffer size affects performance:

Small buffers (e.g., BUFFER_SIZE=1): More system calls, less memory usage
Large buffers (e.g., BUFFER_SIZE=10000): Fewer system calls, more memory usage

## 🧩 Implementation Details
## 📊 Memory Management Architecture
The bonus version uses a linked list to track different file descriptors and their respective buffers:

```c
typedef struct s_list {
    int             fd;      // File descriptor identifier
    char            *stash;  // Buffer storing unprocessed data
    struct s_list   *next;   // Pointer to next FD node
} t_list;
```

### ⚖️ Why Linked Lists vs Static Arrays?

| Feature | Linked List | Static Array |
|---------|-------------|--------------|
| **Memory Usage** | Dynamic allocation per active FD | Pre-allocated maximum size |
| **Scalability** | Handles unlimited FDs | Limited by array size |
| **Memory Cleanup** | Removes inactive FDs automatically | Requires manual management |

### 🔄 How It Works

1. **Read from FD**: Gets data from the file descriptor into a buffer
2. **Process Buffer**: Searches for newline character (`\n`)
3. **Extract Line**: Returns everything up to the newline
4. **Store Remainder**: Saves any extra data for the next call
5. **Repeat**: Each new call continues where the previous left off

### 📈 Performance Considerations

Real-world file descriptor limits:
* 👤 Regular users: 1024-4096 FDs
* 🖥️ Servers: 100,000+ FDs
* 🌐 Max System Limit: Millions (RAM-dependent)

The function has been tested with both extremely small (BUFFER_SIZE=1) and extremely large (BUFFER_SIZE=100000+) buffer sizes, confirming its flexibility and robustness in various usage scenarios.
