#include "tools/path.h"

bool	path_check(char *path, t_path_check check)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	if (check == E_PATH_EXIST)
		return (true);
	if (check == E_PATH_IS_FILE && S_ISREG(path_stat.st_mode))
		return (true);
	if (check == E_PATH_IS_DIRECTORY && S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}
