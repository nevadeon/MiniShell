#include "tools/str.h"
#include "unistd.h"

static void	_strccat(char *dest, const char *src, char c, bool include_char)
{
	while (*dest)
		dest++;
	while (*src && *src != c)
		*dest++ = *src++;
	if (include_char == true && *src == c)
		*dest++ = *src++;
	*dest = '\0';
}

static char	*_strcdup(t_alloc *a, const char *str, char c, bool include_char)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = str_clen(str, c, include_char);
	copy = (char *) mem_alloc(a, (len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

static void	_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

static char	*_strcjoin(t_alloc *a, char *str1, char *str2, char c)
{
	char	*output;

	output = mem_alloc(a, (str_clen(str1, c, 1) + str_clen(str2, c, 1) + 1));
	_strcpy(output, str1);
	_strccat(output, str2, c, true);
	return (output);
}

char	*str_gnl(t_alloc *alloc, int fd)
{
	static char	buffer[GNL_BUFFER_SIZE + 1] = {0};
	char		*line;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 1024 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	line = _strcdup(alloc, buffer, '\n', true);
	while (str_chr(buffer, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, GNL_BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && line[0] == '\0'))
			return (buffer[0] = '\0', NULL);
		buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		line = _strcjoin(alloc, line, buffer, '\n');
	}
	_strcpy(buffer, buffer + str_clen(buffer, '\n', true));
	return (line);
}
