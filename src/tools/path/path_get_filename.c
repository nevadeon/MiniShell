#include "path.h"
#include "stdio.h"

char	*path_get_filename(t_alloc *alloc, char *filepath)
{
	char	*pattern;

	pattern = str_rchr(filepath, '/');
	if (str_equals(pattern, filepath))
		return (filepath);
	pattern = str_dup(alloc, pattern + 1);
	return (pattern);
}
