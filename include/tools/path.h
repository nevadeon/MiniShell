#ifndef PATH_H
# define PATH_H

# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <unistd.h>
# include "tools/list.h"
# include "tools/str.h"

typedef enum e_path_check
{
	E_PATH_OK = 0,
	E_PATH_IS_FILE = 1 << 0,
	E_PATH_EXIST = 1 << 1,
	E_PATH_IS_DIRECTORY = 1 << 2,
	E_PATH_RIGHT = 1 << 3,
	E_PATH_LAST_INDEX
}	t_path_check;

bool	path_check(char *path, t_path_check check);
t_list	*path_get_dir_content(t_alloc *alloc, char *path);
char	*path_get_path(t_alloc *alloc, char *filepath);
char	*path_get_filename(t_alloc *alloc, char *filepath);

#endif
