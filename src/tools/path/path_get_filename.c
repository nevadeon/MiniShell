#include "path.h"
#include "stdio.h"

char	*path_get_filename(char *filepath)
{
	char	*pattern;

	pattern = str_rchr(filepath, '/');
	if (str_equals(pattern, filepath))
		return (filepath);
	pattern = str_dup(E_LFT_TASK, pattern + 1);
	return (pattern);
}
