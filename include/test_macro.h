#ifndef TEST_MACRO_H
# define TEST_MACRO_H

# include "forward.h"
# include <stdio.h>
# include <errno.h>
# include <dlfcn.h>
# include <stdarg.h>
# include <fcntl.h>

// #define open(pathname, flags, ...) \
// 	open_debug(pathname, flags, __FILE__, __LINE__, ##__VA_ARGS__)

// static inline int open_debug(
// 	const char *pathname, int flags, const char *file, int line, ...
// )
// {
// 	static int (*real_open)(const char *, int, ...) = NULL;
// 	mode_t mode = 0;
// 	va_list args;
// 	int fd;

// 	if (!real_open)
// 		real_open = dlsym(RTLD_NEXT, "open");
// 	if (flags & O_CREAT) {
// 		va_start(args, line);
// 		mode = va_arg(args, int);
// 		va_end(args);
// 		fd = real_open(pathname, flags, mode);
// 		io_dprintf(STDERR,	"open(%s, %d, %o)-> %d at %s:%d\n", \
// 			pathname, flags, mode, fd, file, line);
// 	} else {
// 		fd = real_open(pathname, flags);
// 		io_dprintf(STDERR, "open(%s, %d)-> %d at %s:%d\n", \
// 			pathname, flags, fd, file, line);
// 	}
// 	if (fd == -1)
// 		perror("open");
// 	return fd;
// }

// # define pipe(pipefd) \
// ({ \
// 	int ret = pipe(pipefd); \
// 	if (ret == -1) \
// 		io_dprintf(STDERR, "pipe(%p) at %s:%d failed: %s\n", \
// 		pipefd, __FILE__, __LINE__, strerror(errno)); \
// 	else \
// 		io_dprintf(STDERR, "pipe("#pipefd") = {%d,%d} at %s:%d\n", \
// 		pipefd[0], pipefd[1], __FILE__, __LINE__); \
// 	ret; \
// })

// # define close(fd) \
// do \
// { \
// 	io_dprintf(STDERR, "close(%d) at %s:%d\n", \
// 			fd, __FILE__, __LINE__); \
// 	close(fd); \
// } while (0)

// # define dup(fd) \
// ({ \
// 	int ret = dup(fd); \
// 	io_dprintf(STDERR, "dup(%d) = %d at %s:%d\n", \
// 	fd, ret, __FILE__, __LINE__); \
// 	if (ret == -1) \
// 		perror("dup"); \
// 	ret; \
// })

// # define dup2(fd1, fd2) \
// do \
// { \
// 	io_dprintf(STDERR, "dup2(%d, %d) at %s:%d\n", \
// 			fd1, fd2, __FILE__, __LINE__); \
// 	 if (dup2(fd1, fd2) == -1) \
// 	 	perror("dup2"); \
// } while (0)

// # define malloc(size) \
// ({ \
// 	void * ret = malloc(size); \
// 	if (!ret) \
// 		io_dprintf(STDERR, "malloc fail at %s:%d failed: %s\n", \
// 			__FILE__, __LINE__, strerror(errno)); \
// 	else \
// 		io_dprintf(STDERR, "malloc at(%p) at %s:%d\n", \
// 		ret, __FILE__, __LINE__); \
// 	ret; \
// })

// # define free(ptr) \
// do \
// { \
// 	io_dprintf(STDERR, "free(%p) at %s:%d\n", \
// 			ptr, __FILE__, __LINE__); \
// 	free(ptr); \
// } while (0)

#endif
