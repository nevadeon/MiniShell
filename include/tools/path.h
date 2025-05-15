#ifndef PATH_H
# define PATH_H

# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include "mem.h"
# include "list.h"
# include "str.h"

t_list	*path_get_dir_content(char *path);
char	*path_get_path(char *filepath);
char	*path_get_filename(char *word);

#endif