#include "str.h"
#include "unistd.h"

void	ft_strccat(char *dest, const char *src, char c, bool include_char)
{
	while (*dest)
		dest++;
	while (*src && *src != c)
		*dest++ = *src++;
	if (include_char == true && *src == c)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strcdup(const char *str, char c, bool include_char)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = str_clen(str, c, include_char);
	copy = (char *) malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strcjoinfree(char *str1, char *str2, char c)
{
	char	*output;

	output = malloc((str_clen(str1, c, 1) + str_clen(str2, c, 1) + 1));
	ft_strcpy(output, str1);
	ft_strccat(output, str2, c, true);
	free(str1);
	return (output);
}

char	*get_next_line(int fd)
{
	static char	buffer[GNL_BUFFER_SIZE + 1] = {0};
	char		*line;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 1024 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strcdup(buffer, '\n', true);
	while (str_chr(buffer, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, GNL_BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && line[0] == '\0'))
			return (free(line), buffer[0] = '\0', NULL);
		buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		line = ft_strcjoinfree(line, buffer, '\n');
	}
	ft_strcpy(buffer, buffer + str_clen(buffer, '\n', true));
	return (line);
}
